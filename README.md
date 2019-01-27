# RGBLEDTest

This is a sample code to control an RGB LED matrix video wall panel using a STM32F1 (Bluepill). The code is inefficient, doesn't use DMA and probably unreadable - you have been warned.

## Pinout
| LED-Panel | STM32    |
|-----------|----------|
| R1        |  PA0     |
| G1        |  PA1     |
| B1        |  PA2     |
| R2        |  PA3     |
| G2        |  PA4     |
| B2        |  PA5     |
| A         |  PB3     |
| B         |  PB4     |
| C         |  PB5     |
| D         |  PB6     |
| CLK       |  PA6     |
| STB/Latch |  PB8     |
| ^OE       |  PB7     |

## Generating images

* Create a new image with the correct size (for example 64x32)
* Use colo indexing to get down to the desired number of colors
  * You can use the color index "4-setp-map.txt" included
* Save/Export as C header file (.h)
* edit h-to-php.php and use it to convert the h-file to a precomputed mess of arrays
* save it as logo.h or edit main.c and compile

## Links (German)

* https://www.adlerweb.info/blog/2019/01/27/bitbastelei-318-rgb-led-video-wall-panel-p4/
* https://www.youtube.com/watch?v=NaAsBxi2Evs
