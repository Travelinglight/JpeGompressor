JepGompressor
======================
### Authors
Jingda(Kingston) Chen: 301295759 <br>
Jingmin(Sei) Zhu: 

### Environments:
OX X Yosemite 10.10.5 and higher

###Tools:
C++11 <br>
Qt5.5

### Introduction
JpeGompressor was built to reveal the intermediate steps for the lossy part of JPEG encoding/decoding. The lossy part of JPEG encoding includes:

* __color model convertion & subsampling__: to convert color from RGB to YCbCr, and do 4:2:0 chroma subsampling, to reduce independent data
* __DCT transformation__: to decompose the original signal into its DC and AC components
* __quantization__: to reduce the number of distinct output values to a much smaller set

After quantization, the data was further encoded by lossless algorithms and saved into a .jpg file.

On the other hand, when displaying a JPEG encoded image, we need two steps to inverse the lossy part of encoding:

* __IDCT__: to convert DCT transformed data back to YCbCr data
* __color model convertion__: to convert color from YCbCr mode to RGB mode so that colors can be observed.

The JpeGompressor project shows 6 images for an input file: the original image and each result of the above five steps. 

![Alt desc](https://github.com/Travelinglight/JpeGompressor/blob/master/codeStructure.png?raw=true)

### Features
* JpeGompressor allows users to choose an input file from menu bar: File > Open File
* JpeGompressor allows users to choose from different quantization matrices from menu bar: Quantization Matrix. The chosen matrix is displayed in a table and will be used in the quantization.
* JpeGompressor allows users to pick up a 8x8 pixel block in the subsampling result to see the DCT result of that block as well as the quantization result.

### Implementation
The code structure is shown as below:
![Alt desc](https://github.com/Travelinglight/JpeGompressor/blob/master/codeStructure.png?raw=true)
