#include "ST_7735.h"
#include <Arduino.h>
namespace ST_7735
{
    ST_Display::ST_Display():tft_{Adafruit_ST7735(ST_CS_, ST_DC_, ST_SDA_, ST_SCK_ , ST_RST_)}
    {
        
    }

    void ST_Display::ST_Init(int rotation)
    {
        tft_.setTextWrap(false);
        tft_.initR(INITR_144GREENTAB);
        tft_.fillScreen(ST7735_WHITE);  //填滿黑色
        tft_.setRotation(rotation);  //螢幕轉向
//        tft_.setFont(&FreeSerif12pt7b);  //字型
    }


    /*ST77XX_BLACK 0x0000
      ST77XX_WHITE 0xFFFF
      ST77XX_RED 0xF800
      ST77XX_GREEN 0x07E0
      ST77XX_BLUE 0x001F
      ST77XX_CYAN 0x07FF
      ST77XX_MAGENTA 0xF81F
      ST77XX_YELLOW 0xFFE0
      ST77XX_ORANGE 0xFC00
     */
    void ST_Display::ST_Printtxt(String str , uint16_t color , int x, int y)
    {
       // tft_.fillScreen(ST77XX_BLACK);
        tft_.setCursor(x, y);  
        tft_.setTextColor(color);
        tft_.print(str);
    }

    void ST_Display::ST_display_time_and_weather_mode(struct tm &time_info)
    {
        tft_.setTextColor(ST7735_BLACK, ST7735_WHITE);
//        tft_.fillScreen(ST7735_BLACK);  //填滿黑色 , 不要用填滿的方式清除畫面
        tft_.drawFastHLine(0,20,128,ST7735_BLACK);
        tft_.drawFastHLine(0,21,128,ST7735_BLACK);
        tft_.drawFastHLine(0,22,128,ST7735_BLACK);
//        tft_.drawFastHLine(0,53,128,ST7735_BLACK);
        tft_.setTextSize(0.5);
        tft_.setCursor(35, 7); 
        tft_.print(&time_info  ,"%F");
        tft_.setTextSize(2);
        tft_.setTextColor(ST7735_BLUE, ST7735_WHITE);
        tft_.setCursor(26, 35);
        tft_.print(&time_info  ,"%T");
//        tft_.setCursor(0, 80);
//        tft_.drawBitmap(16,16,gImage_clock , 128,128,1);
    }
    //x ,y is St7735 xy , h and w is for image
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
}
