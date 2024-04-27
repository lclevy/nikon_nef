void CLASS nikon_compressed_load_raw() // used when tag 0x103 of subifd1 == 0x8799 (34713)
{
  static const uchar nikon_tree[][32] = {
    { 0,1,5,1,1,1,1,1,1,2,0,0,0,0,0,0,	/* 12-bit lossy */
      5,4,3,6,2,7,1,0,8,9,11,10,12 },
    { 0,1,5,1,1,1,1,1,1,2,0,0,0,0,0,0,	/* 12-bit lossy after split */
      0x39,0x5a,0x38,0x27,0x16,5,4,3,2,1,0,11,12,12 },
    { 0,1,4,2,3,1,2,0,0,0,0,0,0,0,0,0,  /* 12-bit lossless */
      5,4,6,3,7,2,8,1,9,0,10,11,12 },
    { 0,1,4,3,1,1,1,1,1,2,0,0,0,0,0,0,	/* 14-bit lossy */
      5,6,4,7,8,3,9,2,1,0,10,11,12,13,14 },
    { 0,1,5,1,1,1,1,1,1,1,2,0,0,0,0,0,	/* 14-bit lossy after split */
      8,0x5c,0x4b,0x3a,0x29,7,6,5,4,3,2,1,0,13,14 },
    { 0,1,4,2,2,3,1,2,0,0,0,0,0,0,0,0,	/* 14-bit lossless */
      7,6,8,5,9,4,10,3,11,12,2,0,1,13,14 } };
  struct decode *dindex;
  ushort ver0, ver1, vpred[2][2], hpred[2], csize;
  int i, min, max, step=0, huff=0, split=0, row, col, len, shl, diff;

  fseek (ifp, meta_offset, SEEK_SET); // linearization curve (0x96)
  ver0 = fgetc(ifp);
  ver1 = fgetc(ifp);
  // ver0=0x44, ver1=0x20 for 12bits and 14bits lossy (d300)
  // 0x46, 0x30 for 12bits and 14 lossless (d300 and d700)
  printf("meta_offset=%d, tiff_bps=%d, ver0=%d, ver1=%d\n", meta_offset, tiff_bps, ver0, ver1);
  if (ver0 == 0x49 || ver1 == 0x58) // never seen. firmware update or nikon raw software?
    fseek (ifp, 2110, SEEK_CUR);
  if (ver0 == 0x46) huff = 2; // lossless (implicitly 12bits). have seen a d3x nef with ver0=0x46 and ver1=0x30 (exif 0x131="ver1.00")
  // with d300 lossless : ver0=0x46, ver1=0x30. d700/14b/lossless : ver0=0x46, ver1=0x30

  if (tiff_bps == 14) huff += 3; // 14bits lossly (if huff was ==0) or 14bits lossless if ver0==0x46
  read_shorts (vpred[0], 4); // vertical predictor values ?
  
  max = 1 << tiff_bps & 0x7fff;
  if ((csize = get2()) > 1) // curve size. 567 with D100/12bits/lossy. 32 with d3x/12bits/lossless. 
    step = max / (csize-1);
  if (ver0 == 0x44 && ver1 == 0x20 && step > 0) { // lossy (d300, d90 and d5000). 
  //tag 0x93 = 2. stored curve needs interpolation
    for (i=0; i < csize; i++) // read curve
      curve[i*step] = get2();
      // curve interpolation
    for (i=0; i < max; i++)
      curve[i] = ( curve[i-i%step]*(step-i%step) +
		   curve[i-i%step+step]*(i%step) ) / step;
		   
    fseek (ifp, meta_offset+562, SEEK_SET); // csize seems 257 for recent models (0x44/0x20) like d90 and d300
    // type 2 has the split value and uses a second huffman table
    split = get2();
  } else if (ver0 != 0x46 && csize <= 0x4001) // if not lossless. 
  // with D100/D200/D2X/D40/D80/D60 12bits/lossy : ver0==0x44 && ver1==0x10
    read_shorts (curve, max=csize);
  printf("csize=%d, step=%d, split=%d, huff=%d\n", csize, step, split, huff);

/*
0x96 (linearization table) tag format 

offset how_many   type   name
----+-----------+------+---------------------------------------------------------------------------------------------
0    1           byte   version0
1    1           byte   version1
                         ver0=0x44, ver1=0x20 for 12bits and 14bits lossy (d300)
                         0x44, 0x20 : lossy (d300, d90 and d5000)
                         0x46, 0x30 for 12bits and 14 lossless (d300 and d700)
                         0x46, 0x30 : d3x/12b/lossless
                         0x46, 0x30. with d300 lossless. and d700/14b/lossless
                         0x44, 0x10 : with D100/D200/D2X/D40/D80/D60 12bits/lossy 
                         tag 0x93 = 3 for lossless (0x46/0x30).
                         tag 0x93 = 4 for lossy type 2 (0x44/0x20) 
                         tag 0x93 = 1 for lossy type 1 (0x44/0x10)
2    4           shorts vpred[2][2] (when ver0 == 0x49 || ver1 == 0x58, fseek (ifp, 2110, SEEK_CUR) before)
0x0a 1           short  curve_size. 
                         32 with d3x/12bits/lossless, d300/12bits/lossless
                         34 with 14bits/lossless (d300 and d700)
                         257 with d300/12+14b/lossy.  
                         257 with 12b/lossy for d90
                         567 with D100/12bits/lossy. 
                         683 with 12b/lossy for d200,d2x,d40x,d40,d80,d60
0x0c curve_size  shorts curve[]
                         for lossy type 2, if curve_size == 257 (d90 and d300), end of curve table is 1+257*2 = 526
562  1           short  split_value (for 0x44/0x20 only (lossy type 2), d90 and d300) 
                         
 */

  while (curve[max-2] == curve[max-1]) max--;
  init_decoder();
  make_decoder (nikon_tree[huff], 0);
  fseek (ifp, data_offset, SEEK_SET);
  getbits(-1);
  for (min=row=0; row < height; row++) {
      if (split && row == split) {
      // for lossy type 2 (0x44/0x20)
      init_decoder();
      make_decoder (nikon_tree[huff+1], 0);
      max += (min = 16) << 1;
    }
    for (col=0; col < raw_width; col++) {
      for (dindex=first_decode; dindex->branch[0]; )
	      dindex = dindex->branch[getbits(1)]; // read 12 or 14bits value bit per bit and walking through the huffman tree to find the leaf
      len = dindex->leaf & 15; // length = 4 left most bits
      shl = dindex->leaf >> 4; // shift length? = 8 or 10bits
      diff = ((getbits(len-shl) << 1) + 1) << shl >> 1; // read diff value
      if ((diff & (1 << (len-1))) == 0) // left most bit is certainly the sign 
	      diff -= (1 << len) - !shl;
      if (col < 2) 
        hpred[col] = vpred[row & 1][col] += diff; // vpred used for columns 0 and 1
      else	   
        hpred[col & 1] += diff;
      // very close to jpeg lossless decompression (ljpeg_diff and ljpeg_row), except for the shl value...
      if ((ushort)(hpred[col & 1] + min) >= max) derror();
      if ((unsigned) (col-left_margin) < width)
	      BAYER(row,col-left_margin) = curve[LIM((short)hpred[col & 1],0,0x3fff)];
    }
  }
}
