#include "esp32-hal.h"
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
//        tft_.setCursor(2 , 40);
//        tft_.println("Try to search  Wifi");
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
          tft_.print("No Wifi!");
          tft_.setTextSize(2);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.setCursor(26, 35);
          tft_.print("No Wifi!");
          tft_.setTextSize(2);
          tft_.setCursor(65, 75);
          tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
          tft_.print("No Wifi!");
          tft_.setCursor(65, 100);
          tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
          tft_.print("No Wifi!");
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

    void ST_Display::ST_display_Weather(String t , String h ,String w)
    {
        String t_ = t;
        String w_ = w;
        t_.remove(2,3);
        
        
        tft_.drawFastHLine(0,62,128,ST7735_WHITE);
        tft_.drawFastHLine(0,63,128,ST7735_WHITE);
        tft_.setTextSize(2);
        tft_.setCursor(65, 75);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
        tft_.print("T:" + t_ + "C");
        tft_.setCursor(65, 100);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
        tft_.print("H:" + h + "%");

        if(w == "\"Clouds\"")
          ST_Display::ST_display_RGBimage(2 ,65 , 60 , 60 ,could_img);
        else if (w == "\"Thunderstorm\"")
          ST_Display::ST_display_RGBimage(2 ,65 , 60 , 60 ,thunderstorm_img);
        else if (w == "\"Drizzle\"" || w == "\"Rain\"" )
          ST_Display::ST_display_RGBimage(2 ,65 , 60 , 60 ,rain_img);
        else if (w == "\"Snow\"")
          ST_Display::ST_display_RGBimage(2 ,65 , 60 , 60 ,snow_img);
        else if (w == "\"Clear\"")
          ST_Display::ST_display_RGBimage(2 ,65 , 60 , 60 ,clear_img);
    }


  void ST_Display::ST_display_clear()
  {
    tft_.fillScreen(ST7735_BLACK);    
  }
  
  void ST_Display::ST_display_menu(int &menu_index)
  {
    switch(menu_index)
    {
      case -1 : //is init menu
      tft_.setTextSize(2);
      tft_.setCursor(10, 5);
      tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft_.print("  Clock");
      tft_.setCursor(10, 25);
      tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
      tft_.print("  CanBus");       
      break;
          
      case 0 :   //clock mode
      tft_.setTextSize(2);
      tft_.setCursor(10, 5);
      tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft_.print("> Clock");
      delay(200);
      tft_.setCursor(10, 5);
      tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
      tft_.print("> Clock");
      delay(200);
      tft_.setCursor(10, 25);
      tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
      tft_.print("  CanBus");    
      break;

      case 1 :  //can bus mode
      tft_.setTextSize(2);
      tft_.setCursor(10, 5);
      tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft_.print("  Clock");
      delay(200);
      tft_.setCursor(10, 25);
      tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
      tft_.print("> CanBus");
      tft_.setCursor(10, 5);
      tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
      tft_.print("> CanBus");
      delay(200);  
      break;
    }
  }
  
  void ST_Display::ST_display_cansubmenu(int &menu_index)
  {
      switch(menu_index)
      {
        case -1:
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  SetCANID");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Set F/M");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  CANmode");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Monitor");      
        break;        
        case 0 :  //set can id
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("> SetCANID");
        delay(200);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
        tft_.print("> SetCANID");
        delay(200);
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Set F/M");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  CANmode");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Monitor"); 
        break;        
        case 1 :  //set can mask filter
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  SetCANID");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("> Set F/M");
        delay(200);
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);    
        tft_.print("> Set F/M");
        delay(200);
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  CANmode");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Monitor"); 
        break;        
        case 2 : //set change mode
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  SetCANID");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Set F/M");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("> CANmode");
        delay(200);
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);    
        tft_.print("> CANmode");
        delay(200);   
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Monitor"); 
        break;                
        case 3 : //set can monitor
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  SetCANID");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Set F/M");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  CANmode");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("> Monitor");
        delay(200);
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);    
        tft_.print("> Monitor");
        delay(200); 
        break;        
      }
  }

  void ST_Display::ST_display_cannonitor(int &menu_index , String can_id , String dlc , uint8_t *can_data , String can_filter , String can_mask)
  {
    // tft_.drawRoundRect(0,2,60,20,3,ST7735_WHITE);
    // // tft_.fillRoundRect(0,2,60,20,3,ST7735_WHITE);
    // tft_.setTextSize(2);        
    // tft_.setCursor(7,4);
    // tft_.setTextColor(ST7735_WHITE);
    // tft_.print("send");
    String res_str , str1;


    tft_.drawRoundRect(64,2,60,20,3,ST7735_WHITE);
    // tft_.fillRoundRect(64,2,60,20,3,ST7735_WHITE);
    tft_.setTextSize(2);        
    tft_.setCursor(72,4);
    tft_.setTextColor(ST7735_WHITE);
    tft_.print("back");
   
    tft_.setTextSize(1.5);
    tft_.setCursor(2,27);
    tft_.setTextColor(ST7735_WHITE);
    tft_.print("CAN-ID: " + can_id);

    tft_.setTextSize(1.5);
    tft_.setCursor(2,47);
    tft_.setTextColor(ST7735_WHITE);
    tft_.print("dlc: " + dlc);

    tft_.setTextSize(1.5);
    tft_.setCursor(2,67);
    tft_.setTextColor(ST7735_WHITE);
    tft_.print("filter: " + can_filter);

    tft_.setTextSize(1.5);
    tft_.setCursor(2,87);
    tft_.setTextColor(ST7735_WHITE);
    tft_.print("mask: " + can_mask);

    tft_.setTextSize(1.5);
    tft_.setCursor(2,107);
    tft_.setTextColor(ST7735_WHITE);
    tft_.print("data: ");
    for(int i = 0 ; i < dlc.toInt(); i ++)
    {
      str1 = can_data[i];
      res_str = res_str + str1 + " ";          
    }
    tft_.setTextSize(1.5);
    tft_.setCursor(35,107);
    tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft_.print(res_str);
    res_str = "";
    if(menu_index == -1)
    {
      tft_.drawRoundRect(0,2,60,20,3,ST7735_WHITE);
      // tft_.fillRoundRect(0,2,60,20,3,ST7735_WHITE);
      tft_.setTextSize(2);        
      tft_.setCursor(7,4);
      tft_.setTextColor(ST7735_WHITE);
      tft_.print("send");

      tft_.drawRoundRect(64,2,60,20,3,ST7735_WHITE);
      // tft_.fillRoundRect(64,2,60,20,3,ST7735_WHITE);
      tft_.setTextSize(2);        
      tft_.setCursor(72,4);
      tft_.setTextColor(ST7735_WHITE);
      tft_.print("back");
    }        
    else if(menu_index == 0) //send mode
    {
      tft_.drawRoundRect(0,2,60,20,3,ST77XX_CYAN);
      // tft_.fillRoundRect(0,2,60,20,3,ST7735_WHITE);
      tft_.setTextSize(2);        
      tft_.setCursor(7,4);
      tft_.setTextColor(ST77XX_CYAN);
      tft_.print("send");
      delay(200);
      tft_.drawRoundRect(0,2,60,20,3,ST7735_WHITE);
      // tft_.fillRoundRect(0,2,60,20,3,ST7735_WHITE);
      tft_.setTextSize(2);        
      tft_.setCursor(7,4);
      tft_.setTextColor(ST7735_WHITE);
      tft_.print("send");
      delay(200);       
    }
    else if(menu_index == 1)
    {
      tft_.drawRoundRect(0,2,60,20,3,ST7735_WHITE);
      // tft_.fillRoundRect(0,2,60,20,3,ST7735_WHITE);
      tft_.setTextSize(2);        
      tft_.setCursor(7,4);
      tft_.setTextColor(ST7735_WHITE);
      tft_.print("send");
      delay(200);
      tft_.drawRoundRect(0,2,60,20,3,ST77XX_CYAN);
      // tft_.fillRoundRect(0,2,60,20,3,ST7735_WHITE);
      tft_.setTextSize(2);        
      tft_.setCursor(7,4);
      tft_.setTextColor(ST77XX_CYAN);
      tft_.print("send");
      delay(200);  
    }    
  }

  void ST_Display::ST_display_setcanid(int click_count , int leri_count,bool is_ext_ty , String *canid_str)
  {
    tft_.drawFastHLine(22,85,78,ST7735_WHITE);
    tft_.drawFastHLine(22,105,78,ST7735_WHITE);
    tft_.drawFastVLine(22,85,20,ST7735_WHITE);
    tft_.drawFastVLine(42,85,20,ST7735_WHITE);
    tft_.drawFastVLine(62,85,20,ST7735_WHITE);
    tft_.drawFastVLine(82,85,20,ST7735_WHITE);
    tft_.drawFastVLine(100,85,20,ST7735_WHITE);
    
    tft_.drawFastHLine(0,23,128,ST7735_WHITE);
    tft_.drawFastHLine(0,24,128,ST7735_WHITE);
    tft_.setTextSize(2);        
    tft_.setCursor(27,3);
    tft_.setTextColor(ST77XX_WHITE);
    tft_.print("ID type");
    tft_.drawFastHLine(0,50,128,ST7735_WHITE);
    tft_.drawFastHLine(0,51,128,ST7735_WHITE);
    tft_.drawFastHLine(0,74,128,ST7735_WHITE);
    tft_.drawFastHLine(0,75,128,ST7735_WHITE);
    tft_.setTextSize(2);        
    tft_.setCursor(25,56);
    tft_.setTextColor(ST77XX_WHITE);
    tft_.print("CAN ID");
    if(click_count == 0)
    {
      tft_.setCursor(28,88);
      tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
      tft_.print(canid_str[0]);
      tft_.setCursor(48,88);
      tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
      tft_.print(canid_str[1]);
      tft_.setCursor(68,88);
      tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
      tft_.print(canid_str[2]);
      tft_.setCursor(87,88);
      tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
      tft_.print(canid_str[3]);
      
      if (is_ext_ty == false)
      {
        tft_.setCursor(47,32);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("STD");
        delay(200);
        tft_.setCursor(47,32);
        tft_.setTextColor(ST77XX_CYAN);
        tft_.print("STD");
        delay(200);
      }
      else
      {
        tft_.setCursor(47,32);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("EXT");
        delay(200);
        tft_.setCursor(47,32);
        tft_.setTextColor(ST77XX_CYAN);
        tft_.print("EXT");
        delay(200);     
      }
    }
    else if(click_count == 1)
    {
      if (is_ext_ty == false)
      {
        tft_.setCursor(47,32);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("STD");
      }
      else
      {
        tft_.setCursor(47,32);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("EXT");    
      }      
              
      switch(leri_count)
      {
        case -1 :
        tft_.setCursor(28,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[0]);
        tft_.setCursor(48,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[1]);
        tft_.setCursor(68,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[2]);
        tft_.setCursor(87,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[3]);
        break;
        case 0:
        tft_.setCursor(28,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[0]);
        delay(200);
        tft_.setCursor(28,88);
        tft_.setTextColor(ST7735_ORANGE , ST7735_BLACK);
        tft_.print(canid_str[0]);
        delay(200);
        tft_.setCursor(48,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[1]);
        tft_.setCursor(68,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[2]);
        tft_.setCursor(87,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[3]);
        break;
        case 1:
        tft_.setCursor(28,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[0]);
        tft_.setCursor(48,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[1]);
        delay(200);
        tft_.setCursor(48,88);
        tft_.setTextColor(ST7735_ORANGE , ST7735_BLACK);
        tft_.print(canid_str[1]);
        delay(200);
        tft_.setCursor(68,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[2]);
        tft_.setCursor(87,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[3]);
        break;
        case 2:
        tft_.setCursor(28,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[0]);
        tft_.setCursor(48,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[1]);
        tft_.setCursor(68,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[2]);
        delay(200);
        tft_.setCursor(68,88);
        tft_.setTextColor(ST7735_ORANGE , ST7735_BLACK);
        tft_.print(canid_str[2]);
        delay(200);
        tft_.setCursor(87,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[3]);
        break;
        case 3:
        tft_.setCursor(28,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[0]);
        tft_.setCursor(48,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[1]);
        tft_.setCursor(68,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[2]);
        tft_.setCursor(87,88);
        tft_.setTextColor(ST7735_WHITE , ST7735_BLACK);
        tft_.print(canid_str[3]);
        delay(200);
        tft_.setCursor(87,88);
        tft_.setTextColor(ST7735_ORANGE , ST7735_BLACK);
        tft_.print(canid_str[3]);
        delay(200);
        break;            
      }        
    }       
  }

  void ST_Display::ST_display_changemode(int updown)
  {
    switch(updown)
    {
      case -1:
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  Config");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Normal");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Loopback");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Listen");      
        break;        
        case 0 :  //set can id
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("> Config");
        delay(200);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);
        tft_.print("> Config");
        delay(200);
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Normal");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Loopback");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Listen"); 
        break;        
        case 1 :  //set can mask filter
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  Config");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("> Normal");
        delay(200);
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);    
        tft_.print("> Normal");
        delay(200);
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Loopback");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Listen"); 
        break;        
        case 2 : //set change mode
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  Config");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Normal");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("> Loopback");
        delay(200);
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);    
        tft_.print("> Loopback");
        delay(200);   
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Listen"); 
        break;                
        case 3 : //set can monitor
        tft_.setTextSize(2);
        tft_.setCursor(10, 5);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft_.print("  Config");
        tft_.setCursor(10, 25);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Normal");
        tft_.setCursor(10, 45);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("  Loopback");  
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_WHITE, ST7735_BLACK);    
        tft_.print("> Listen");
        delay(200);
        tft_.setCursor(10, 65);
        tft_.setTextColor(ST7735_BLUE, ST7735_BLACK);    
        tft_.print("> Listen");
        delay(200); 
        break;      
    }
  }
  
  void ST_Display::ST_display_setfiltermask(int click_count , int leri_count,String *Filter_str , String *Mask_str)
  {
    String f1,f2,f3,f4,m1,m2,m3,m4;    
    tft_.drawFastHLine(0,23,128,ST7735_WHITE);
    tft_.drawFastHLine(0,24,128,ST7735_WHITE);
    tft_.setTextSize(2);        
    tft_.setCursor(27,3);
    tft_.setTextColor(ST77XX_WHITE);
    tft_.print("ID type");

    tft_.drawFastHLine(0,70,128,ST7735_WHITE);
    tft_.drawFastHLine(0,71,128,ST7735_WHITE);
    tft_.drawFastHLine(0,94,128,ST7735_WHITE);
    tft_.drawFastHLine(0,95,128,ST7735_WHITE);
    tft_.setTextSize(2);        
    tft_.setCursor(25,76);
    tft_.setTextColor(ST77XX_WHITE);
    tft_.print("CAN ID");
    
    //上半部方框
    tft_.drawFastHLine(22,36,78,ST7735_WHITE);
    tft_.drawFastHLine(22,56,78,ST7735_WHITE);
    
    tft_.drawFastVLine(22,36,20,ST7735_WHITE);
    tft_.drawFastVLine(42,36,20,ST7735_WHITE);
    tft_.drawFastVLine(62,36,20,ST7735_WHITE);
    tft_.drawFastVLine(82,36,20,ST7735_WHITE);
    tft_.drawFastVLine(100,36,20,ST7735_WHITE);
    
    //下半部方框
    tft_.drawFastHLine(22,105,78,ST7735_WHITE);
    tft_.drawFastHLine(22,125,78,ST7735_WHITE);
    
    tft_.drawFastVLine(22,105,20,ST7735_WHITE);
    tft_.drawFastVLine(42,105,20,ST7735_WHITE);
    tft_.drawFastVLine(62,105,20,ST7735_WHITE);
    tft_.drawFastVLine(82,105,20,ST7735_WHITE);
    tft_.drawFastVLine(100,105,20,ST7735_WHITE);

    if(click_count == -1) //default status display
    {
      tft_.setTextSize(2);        
      tft_.setCursor(28,39);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");
      tft_.setTextSize(2);        
      tft_.setCursor(48,39);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");
      tft_.setTextSize(2);        
      tft_.setCursor(68,39);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");
      tft_.setTextSize(2);        
      tft_.setCursor(87,39);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");
      tft_.setTextSize(2);        
      tft_.setCursor(28,108);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");
      tft_.setTextSize(2);        
      tft_.setCursor(48,108);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");
      tft_.setTextSize(2);        
      tft_.setCursor(68,108);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");
      tft_.setTextSize(2);        
      tft_.setCursor(87,108);
      tft_.setTextColor(ST77XX_WHITE);
      tft_.print("0");      
    }
    else if(click_count == 0) //set mask display
    {
      //Mask
      switch(leri_count)
      {
        //Filter 
        tft_.setTextSize(2);        
        tft_.setCursor(28,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("0");
        tft_.setTextSize(2);        
        tft_.setCursor(48,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("0");
        tft_.setTextSize(2);        
        tft_.setCursor(68,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("0");
        tft_.setTextSize(2);        
        tft_.setCursor(87,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print("0"); 
        //Mask        
        case -1:
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Mask_str[0]);
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[3]);        
          break;
        case 0 :
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Mask_str[0]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST7735_ORANGE , ST7735_BLACK);
          tft_.print(Mask_str[0]);
          delay(200);          
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[3]);
          m1 = Mask_str[0];  
          break;
        case 1 :
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Mask_str[0]);       
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[1]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.print(Mask_str[1]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[3]);
          m2 = Mask_str[1]; 
        break;
        case 2 :
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Mask_str[0]);       
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[2]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.print(Mask_str[2]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[3]);
          m3 = Mask_str[2]; 
        break;
        case 3:
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Mask_str[0]);       
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Mask_str[3]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.print(Mask_str[3]);
          delay(200);
          m4 = Mask_str[3];          
        break;
      }                   
    }
    else if(click_count == 1) //set filter display
    {
      switch(leri_count)
      {
        //Filter 
        tft_.setTextSize(2);        
        tft_.setCursor(28,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print(m1);
        tft_.setTextSize(2);        
        tft_.setCursor(48,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print(m2);
        tft_.setTextSize(2);        
        tft_.setCursor(68,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print(m3);
        tft_.setTextSize(2);        
        tft_.setCursor(87,108);
        tft_.setTextColor(ST77XX_WHITE);
        tft_.print(m4);
        case -1:
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Filter_str[0]);
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[3]); 
        break;
        case 0 :
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Filter_str[0]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST7735_ORANGE , ST7735_BLACK);
          tft_.print(Filter_str[0]);
          delay(200);          
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[3]);
          f1 = Filter_str[0];
        break;
        case 1 :
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Filter_str[0]);       
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[1]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.print(Filter_str[1]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[3]);
          f2 = Filter_str[1]; 
        break;
        case 2 :
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Filter_str[0]);       
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[2]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.print(Filter_str[2]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[3]);
          f3 = Filter_str[2]; 
        break;
        case 3:
          tft_.setTextSize(2);        
          tft_.setCursor(28,39);
          tft_.setTextColor(ST77XX_WHITE , ST7735_BLACK);
          tft_.print(Filter_str[0]);       
          tft_.setTextSize(2);        
          tft_.setCursor(48,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[1]);
          tft_.setTextSize(2);        
          tft_.setCursor(68,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[2]);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST77XX_WHITE, ST7735_BLACK);
          tft_.print(Filter_str[3]);
          delay(200);
          tft_.setTextSize(2);        
          tft_.setCursor(87,39);
          tft_.setTextColor(ST7735_ORANGE, ST7735_BLACK);
          tft_.print(Filter_str[3]);
          delay(200);
          f4 = Filter_str[3];
        break;
      }          
    }

  }

  
}
