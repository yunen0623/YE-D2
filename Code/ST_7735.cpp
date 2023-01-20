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
        tft_.fillScreen(ST7735_BLACK);  //填滿黑色
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

    void ST_Display::ST_display_time_and_weather_mode(struct tm &time_info , bool is_con)
    {
        if(is_con == true)
        {
          ST_Display::ST_display_RGBimage(5 ,35 , 16 , 16 ,clock_img);
          ST_Display::ST_display_RGBimage(11 ,2 , 16 , 16 ,date_img);
          ST_Display::ST_display_RGBimage(100 ,2 , 16 , 16 ,wifi_img);
          tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
          tft_.drawFastHLine(0,20,128,ST7735_WHITE);
          tft_.drawFastHLine(0,21,128,ST7735_WHITE);
          tft_.drawFastHLine(0,22,128,ST7735_WHITE);
          tft_.setTextSize(0.5);
          tft_.setCursor(35, 7); 
          tft_.print(&time_info  ,"%F");
          tft_.setTextSize(2);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.setCursor(26, 35);
          tft_.print(&time_info  ,"%T");
        }
        else
        {
          ST_Display::ST_display_RGBimage(5 ,35 , 16 , 16 ,clock_img);
          ST_Display::ST_display_RGBimage(11 ,2 , 16 , 16 ,date_img);
          ST_Display::ST_display_RGBimage(100 ,2 , 16 , 16 ,wifi_off_img);
          tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
          tft_.drawFastHLine(0,20,128,ST7735_WHITE);
          tft_.drawFastHLine(0,21,128,ST7735_WHITE);
          tft_.drawFastHLine(0,22,128,ST7735_WHITE);
          tft_.setTextSize(0.5);
          tft_.setCursor(35, 7); 
          tft_.print("No connect to Wifi!");
          tft_.setTextSize(2);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.setCursor(26, 35);
          tft_.print("No connect to Wifi!");
        }
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
