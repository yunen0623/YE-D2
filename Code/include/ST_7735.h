#include "WString.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/Org_01.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <SPI.h>
#include <Arduino.h>
//#include <Arduino_JSON.h>
#include "image.h"
namespace ST_7735
{
  class ST_Display
  {
    public:
      ST_Display();
      void ST_Init(int rotation);
      void ST_Printtxt(String str , uint16_t color , int x, int y);
      void ST_display_time();
      void ST_display_Weather(String t , String h ,String w);
      void ST_display_eye_icon(); 
      void ST_display_time_and_weather_mode(struct tm &time_info , bool is_con);
      void ST_display_RGBimage(int x , int y,int h ,int w ,const unsigned char *img);
      void ST_display_menu(int &menu_index);
      void ST_display_cansubmenu(int &menu_index);
      void ST_display_setcanid(int click_count , int leri_count,bool is_ext_ty , String *canid_str);
      void ST_display_changemode(int mode);
      void ST_display_setfiltermask(int click_count , int leri_count,String *Filter_str , String *Mask_str);
      void ST_display_cannonitor(int &menu_index , String can_id , String dlc , uint8_t *can_data , String can_filter , String can_mask);
      void ST_display_clear();
    private:
      const int ST_SDA_ = 23;  //MOSI 13
      const int ST_SCK_ = 18;  //CLK 14
      const int ST_CS_ = 5;   //CS 15
      const int ST_DC_ = 2;   //ST7735 A0 35
      const int ST_RST_ = 4;   //RST Pin  4
      void append(char* s, char* buffer);
      Adafruit_ST7735 tft_;
  };
}
