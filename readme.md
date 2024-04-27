# Description of Nikon camera RAW formats :  NEF and NRW

Version 0.3 (28may2022)

(this is work in progress)

## Introduction

Since 1999, some Nikon cameras can create files with RAW data, the first one being D1 with 12 bits compressed NEF files. With D1X, lossy compression was added, and can be considered as "visually lossless". D70 was first non pro camera to offer NEF, but only lossy / compressed. 14 bits NEF were available in 2007 with D3 and D300.

NEF (Nikon Electronic Format) is from high end models, and NRW (Nikon RAW) for Coolpix, starting with P6000. 

NEF and NRW are TIFF based formats.



https://www.nikonimgsupport.com/eu/BV_article?articleNo=000006125&lang=en_GB

N-RAW (NEV file) 12bits video

## Support from open source projects

| model         | release date | format                                                  | dcraw / libraw support                                                                                                                       |
| ------------- | ------------ | ------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| D1            | 06/1999      | **NEF 12bits** uncompressed                             | [1.49, 4apr2002](https://github.com/ncruces/dcraw/commit/0aba10d036cb72768b85ce0da2dcfc5f77f6e183)                                           |
| D1X           | 02/2001      | 12 bits, uncompressed or lossy compression              | [1.47, 29mar2002](https://github.com/ncruces/dcraw/commit/da1b0468f63bd5cf0ed9ba4c26a8dcc6b4ab1344)                                          |
| D1H           | 02/2001      | 12 bits, uncompressed or lossy compression              | [1.57, 5may2002](https://github.com/ncruces/dcraw/commit/5b9e4a33bdcc01995e458eb32191ec73e062b5f1)                                           |
| Coolpix 5000  | 09/2001      | NEF 12 bits uncompressed                                | [1.69, 16oct2002](https://github.com/ncruces/dcraw/commit/d10e52f4e9250b54b5be593fbc4aed3e6229c004)                                          |
| D100          | 02/2002      |                                                         | [1.60, 20jun2002](https://github.com/ncruces/dcraw/commit/7df24eea89a4607f70653d968ca2aea4ed634fe4)                                          |
| Coolpix 5700  | 05/2002      | NEF 12 bits uncompressed                                | [1.64, 7aug2002](https://github.com/ncruces/dcraw/commit/d331ebb420c41b7767a0f6a59932e95dd1b1bbc9)                                           |
| D70           | 01/2004      | NEF 12 bits compression                                 | [1.167, 16feb2004](https://github.com/ncruces/dcraw/commit/4941a9c502dd6e6fcbd013142c131c71ffdc3660)                                         |
| Coolpix 8400  | 09/2004      | NEF                                                     | [1.229, 21jan2005](https://github.com/ncruces/dcraw/commit/a30759f5b462b23289cc3326a3929da664c3b50e)                                         |
| D2X           | 09/2004      | NEF 12 bits, WB decryption                              | [1.250, 18apr2005](https://github.com/ncruces/dcraw/commit/dbff3076a3ce0251ca07901ee2b1dd3f0ab063c1)                                         |
|               |              | jpeg thumbs                                             | [1.368, 25feb2007](https://github.com/ncruces/dcraw/commit/af472f8a92df48c77a58c33f5d0a6e8bd9ae6c19)                                         |
| D3/D300       | 08/2007      | NEF 12 or **14bits**, compressed or lossless compressed | **[1.393, 8.78, 30oct2007, 14bits](https://github.com/ncruces/dcraw/commit/0d7914e221897bc0674e863ad320107033a3fa3c)**                       |
|               |              | split NEF                                               | [1.409, 11dec2008](https://github.com/ncruces/dcraw/commit/b0751dc5a137fbc4b05bd0eaef1c325b97a4aba7)                                         |
| Coolpix P6000 | 08/2008      | **NRW** 12bits                                          |                                                                                                                                              |
| D4S           | 02/2014      | small RAW (yuv, NEFCompression = **8**)                 | [1.471, 23feb2015](https://github.com/ncruces/dcraw/commit/b03938a7f4da149ecd1cd169cc184edff1f10f62)                                         |
| D810          | 05/2016      | small RAW                                               |                                                                                                                                              |
| D6            | 09/2019      | lossless (NEFCompression = 3)                           | [nikon_14bit_load_raw](https://github.com/LibRaw/LibRaw/blob/2a9a4de21ea7f5d15314da8ee5f27feebf239655/src/decoders/decoders_libraw.cpp#L186) |
| Z50           | 12/2019      |                                                         |                                                                                                                                              |
| Z9            | 10/2021      | NEF TicoRAW                                             |                                                                                                                                              |

#### Z9
```
- IFD#0 (22 entries)
  
  - 0x00FE, SubfileType = 1 (Reduced-resolution image  )
  
  - ...
  
  - 0x014a, SubIFD (8 entries)
    
    - 0x00FE, SubfileType = 1 (Reduced-resolution image  )
    - 0x0103, Compression = 6
    - 0x0201, JpgFromRawStart
    - 0x0202, JpgFromRawLength
    - ...
  
  - SubIFD#1
    
    - 0x00FE, SubfileType = 0 (Full-resolution image  )
    - 0x0100, ImageWidth = 8280
    - 0x0101, ImageHeight = 5520
    - 0x0102, BitsPerSample = 14
    - 0x0103, Compression = 34713 (0x8799)
    - 0xc7d5, NEFInfo (SubDirectory)
      - MakerNote (10 Entries)
  
  - SubIFD#2 (8 entries)
    
    - 0x00FE, SubfileType = 1 (Reduced-resolution image  )
  
  - SubIFD#3 (14 entries)
    
    - 0x00FE, SubfileType = 1 (Reduced-resolution image  )
    - ImageWidth = 384
    - ImageHeight = 256
  
  - SubIFD#4 (14 entries)
    
    - 0x00FE, SubfileType = 1 (Reduced-resolution image  )
  
  - SubIFD#5 (14 entries)
    
    - 0x00FE, SubfileType = 1 (Reduced-resolution image  )
  
  - ExifIFD
    
    - MakerNote (72 entries)
      
      - PreviewIFD
        - 0x0103, Compression = 6
      - 0x0051 (24 bytes). Compression : "01010500" 00 00 **0e 00** 00 00 00 00 06 00 00 00 00 00 00 00 (https://exiftool.org/TagNames/Nikon.html#NEFCompression)
```
exiftool -a -H -u -v3 -g3 d:\raw_samples\z9\DSC_2999.NEF

https://exiftool.org/TagNames/EXIF.html

## Compression

### 2002 - D100

12 bits compressed

### 2014 - Small RAW

with D4s (2014)

- https://www.popphoto.com/news/2014/05/how-exactly-does-nikons-raw-size-s-nef-work/

- Digging into Nikon RAW Size S NEFs, May 2014, https://www.rawdigger.com/howtouse/nikon-small-raw-internals/

- RAW size 'S', DPReview, D810, may 2016, https://www.dpreview.com/reviews/nikon-d810/4

### D3
```
uncompressed

  | + [SubIFD1 directory with 17 entries]
  | | 0)  SubfileType = 0
  | |     - Tag 0x00fe (4 bytes, int32u[1]):
  | |        2be6a: 00 00 00 00                                     [....]
  | | 1)  ImageWidth = 4288
  | |     - Tag 0x0100 (4 bytes, int32u[1]):
  | |        2be76: 00 00 10 c0                                     [....]
  | | 2)  ImageHeight = 2844
  | |     - Tag 0x0101 (4 bytes, int32u[1]):
  | |        2be82: 00 00 0b 1c                                     [....]
  | | 3)  BitsPerSample = 14
  | |     - Tag 0x0102 (2 bytes, int16u[1]):
  | |        2be8e: 00 0e                                           [..]
  | | 4)  Compression = **1**
  | |     - Tag 0x0103 (2 bytes, int16u[1]):
  | |        2be9a: 00 01  
```
### D810
```
Nikon NEF Compressed

  | + [SubIFD1 directory with 17 entries]
  | | 0)  SubfileType = 0
  | |     - Tag 0x00fe (4 bytes, int32u[1])
  | | 1)  ImageWidth = 7380
  | |     - Tag 0x0100 (4 bytes, int32u[1])
  | | 2)  ImageHeight = 4928
  | |     - Tag 0x0101 (4 bytes, int32u[1])
  | | 3)  BitsPerSample = 12
  | |     - Tag 0x0102 (2 bytes, int16u[1])
  | | 4)  Compression = **34713**
  | |     - Tag 0x0103 (2 bytes, int16u[1])
```
lossy type 2
```
  | | | 43) NEFCompression = **4**
  | | |     - Tag 0x0093 (2 bytes, int16u[1])
```
lossless
```
  | | | 43) NEFCompression = **3**
  | | |     - Tag 0x0093 (2 bytes, int16u[1])
```
small
```
  | | | 43) NEFCompression = **8**
  | | |     - Tag 0x0093 (2 bytes, int16u[1])
```
uncompressed
```
  | + [SubIFD1 directory with 17 entries]
  | | 0)  SubfileType = 0
  | |     - Tag 0x00fe (4 bytes, int32u[1])
  | | 1)  ImageWidth = 7380
  | |     - Tag 0x0100 (4 bytes, int32u[1])
  | | 2)  ImageHeight = 4928
  | |     - Tag 0x0101 (4 bytes, int32u[1])
  | | 3)  BitsPerSample = 14
  | |     - Tag 0x0102 (2 bytes, int16u[1])
  | | 4)  Compression = **1**
  | |     - Tag 0x0103 (2 bytes, int16u[1])
```
lossy type 1
```
  | | | 34) NEFCompression = **1**
  | | |     - Tag 0x0093 (2 bytes, int16u[1])
```
### D5
```
  | | | 16) SerialNumber = 3000234
  | | |     - Tag 0x001d (8 bytes, string[8]):
  | | |         3838: 33 30 30 30 32 33 34 00                         [3000234.]

  | | | 47) NEFCompression = **3**
  | | |     - Tag 0x0093 (2 bytes, int16u[1]):
  | | |         36c4: 03 00

  | | | 49) NEFLinearizationTable = F0.... .(...r^.....e.... ..-......X-P..
  | | |     - Tag 0x0096 (46 bytes, undef[46]):
  | | |         883c: 46 30 00 02 00 02 00 02 00 02 20 00 b7 28 aa 9d [F0........ ..(..]
  | | |         884c: e0 72 5e 90 1a f6 1e 99 65 82 f0 af bf 20 d2 d0 [.r^.....e.... ..]
  | | |         885c: 2d c8 c7 0c a1 84 c7 58 2d 50 d3 ab 00 00       [-......X-P....]

 | | | 56) ShutterCount = 15042
  | | |     - Tag 0x00a7 (4 bytes, int32u[1]):
  | | |         3730: c2 3a 00 00                                     [.:..]
```
### Z50
```
  | + [SubIFD1 directory with 19 entries]
  | | 0)  SubfileType = 0
  | |     - Tag 0x00fe (4 bytes, int32u[1]):
  | |        460a6: 00 00 00 00                                     [....]
  | | 1)  ImageWidth = 5600
  | |     - Tag 0x0100 (4 bytes, int32u[1]):
  | |        460b2: e0 15 00 00                                     [....]
  | | 2)  ImageHeight = 3728
  | |     - Tag 0x0101 (4 bytes, int32u[1]):
  | |        460be: 90 0e 00 00                                     [....]
  | | 3)  BitsPerSample = 14
  | |     - Tag 0x0102 (2 bytes, int16u[1]):
  | |        460ca: 0e 00                                           [..]
  | | 4)  Compression = **34713**
  | |     - Tag 0x0103 (2 bytes, int16u[1]):
  | |        460d6: 99 87   
```
34713 = Nikon NEF Compressed

### Z7_ii

packed 14 bits
```
  | | | 54) NEFCompression = 10
  | | |     - Tag 0x0093 (2 bytes, int16u[1]):
  | | |         880c: 0a 00      
```
### 2021 - Z9 - high efficiency - TicoRAW

- [TicoRAW technology from intoPIX is behind the Nikon Z9 high-efficiency RAW recording - Nikon Rumors](https://nikonrumors.com/2021/12/07/ticoraw-technology-from-intopix-is-behind-the-nikon-z9-high-efficiency-raw-recording.aspx/)

- [US Patent Application for METHOD AND DEVICE FOR DISPLAY STREAM COMPRESSION Patent Application (Application #20140247999 issued September 4, 2014) - Justia Patents Search](https://patents.justia.com/patent/20140247999)

## References

- Exiftool, Phil Harvey, [Nikon Tags](https://exiftool.org/TagNames/Nikon.html)

- Nikon D1 RAW format, DPReview, page 14, november, 2000, https://www.dpreview.com/reviews/nikond1/14

- NEF file format v0.1, Fabrizio Giudici, 2003, https://hwiegman.home.xs4all.nl/fileformats/nef/NEF.pdf

- D70, may 2004 : [Is the Nikon D70 NEF (RAW) format truly lossless? · Fazal Majid's low-intensity blog](https://blog.majid.info/is-the-nikon-d70-nef-raw-format-truly-lossless/)

- Nikon encrypts D2X WB, PhotoshopNews, 17apr2005, https://photoshopnews.com/2005/04/17/nikon-d2x-white-balance-encryption/

- NEF compression curves, Bill Claff, 28jan2021 (D1->Z7) : https://photonstophotos.net/NikonInfo/NEF_Compression.htm

- NEF version info, Bill Claff, 2Jul2021 (D1->Z7 II) : https://photonstophotos.net/NikonInfo/NEF_Version_Matrix.htm

- http://lclevy.free.fr/nef/ (2009)

- DNGlab
  - https://github.com/dnglab/dnglab/tree/main/rawler/src/decoders/nef
  - https://github.com/dnglab/dnglab/blob/main/rawler/src/decoders/nef.rs
  - https://github.com/dnglab/dnglab/tree/main/rawler/src/formats/tiff
