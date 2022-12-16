# PhotoLab v1.0

## Part 1. Implementation of simple filters in PhotoLab v1.0

Implement the PhotoLab v1.0 program:

- The program should provide the ability to:
    - Load an arbitrary image in BMP format
    - Save the result of filtering into a separate file (BMP format)
    - Apply a filter from a pool of ready-made filters:
        - Conversion to grayscale (without convolution)
        - Negative (without convolution)
        - Toning (similar to grayscale conversion, but in shades of the color specified on the palette. The palette must contain at least 16 different colors. The palette is implemented arbitrarily)
- After applying the filtering, the result should be displayed in the user interface along with the original image

- The program provide the ability to apply the following convolution filters to the image:
    - Emboss 
    - Sharpen 
    - Box blur
    - Gaussian blur 
    - Laplacian filter
    - Prewitt filter (Prewitt filter) or Sobel filter (Sobel filter)
- The program should provide the ability to enter an arbitrary filter kernel matrix (up to size 16x16) by hand through a separate dialog window

- The program provide the ability to make adjustments to color correction, such as:
    - changing the brightness and contrast of the image
    - work with saturation for the whole image (by HSL and HSV models)
- The interface for color correction of the original image should provide the ability to set brightness, contrast and the three parameters of the specified saturation model both numerically and by slider.