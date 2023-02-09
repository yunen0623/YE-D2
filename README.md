# YE-D2
Intelligent display with CAN-Bus detection
use multiple SPI bus interfaces

------------


### Requirements
* ESP32
![ESP32](https://i.imgur.com/kXR15by.jpg)

* ST7735 128*128
![ST7735](https://i.imgur.com/kUo0aSN.jpg)

* Five-way button module
![Five-way](https://i.imgur.com/KEoH7Eo.jpg)

* MCP2515
![MCP2515](https://i.imgur.com/qUU136F.jpg)


* A 3D Printer
files in Cura/
![1](https://i.imgur.com/wLFCAet.jpg)
![2](https://i.imgur.com/qxDi1ua.jpg)

------------


### Library
* Adafruit_GFX
* Adafruit_SSD1306
* SPI
* Arduino_JSON
* HTTPClient
* mcp2515

### Connection table
| ESP32  | ST7735 |
| :--------: |:-------:|
| 5V       | VDD     |
| GND      | GND     |
| 18     | SCK     |
| 23     | SDA     |
| 5     | CS     |
| 2     | DC     |
| 4    | RST     |

| ESP32  | Btn |
| :--------: |:-------:|
| GND      | COM     |
| 27     | up     |
| 26     | down     |
| 25     | left     |
| 33     | right     |
| 32    | mid     |

| ESP32  | MCP2515 |
| :--------: |:-------:|
| 5V       | VDD     |
| GND      | GND     |
| 12     | MISO     |
| 13     | MOSI     |
| 15     | CS     |
| 14     | CLK     |


------------
### Code Introduction
In this project, two SPI interfaces are used, VSPI and HSPI, and it is worth mentioning that the default SPI is VSPI, and to use HSPI, you must pass in the pins and start it at the end with **hspi->begin**.

```cpp
mcp_2515_base::mcp_2515_base():hspi{new SPIClass(HSPI)} ,mcp2515_{mcp2515_CS_ , spiClk , hspi}
{
	hspi->begin();
}
```

To display RGB images on the ST7735, a code was written to convert the RGB images and display them on the LCD.
**(x ,y is St7735 xy , h and w is for image)**

```cpp
void ST_Display::ST_display_RGBimage(int x , int y,int h ,int w ,const unsigned char *img)
    {
        int buffidx=0;
        int rh = y + h;
        int rw = x + w;
        for (int i = y ; i <rh; i++) 
        { 
          for (int k = x; k<rw; k++) 
          {
            tft_.drawPixel(k, i, pgm_read_word(img + buffidx));
            buffidx++;
          } 
        }
    }
```

In the ST7735 library there is a filscreen function to clear the screen, but he is a one-by-one clear and slow, you can use the SetTextColor ( color1 , color2 ) method to quickly change the font, color1 is the display font color (foreground color), color2 is the background color
```cpp
setTextColor(ST7735_WHITE, ST7735_BLACK);
```

### Final Result
1. Clock
![Imgur](https://i.imgur.com/Y6HpYJo.jpg)

2. Menu
![Imgur](https://i.imgur.com/fDCmZzl.jpg)

3. CanBus Menu
![Imgur](https://i.imgur.com/agydCLP.jpg)

4. Set Mask and Filter
![Imgur](https://i.imgur.com/BHJw0da.jpg)

5. Change MCP2515 Mode
![Imgur](https://i.imgur.com/a9cV5jh.jpg)

6. CANBus Monitor
![Imgur](https://i.imgur.com/9nWLJBd.jpg)


2023-02-09 15:38:57 星期四