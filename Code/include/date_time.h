#include "hw_wifi.h"
#include <Arduino.h>
#include <Arduino_JSON.h>
#include <HTTPClient.h>
namespace dateandtime
{  
  class dateandtime
  {
    public:
      bool get_timeout_flag() {return wc.get_is_timeout();}
      bool get_connect_flag() {return wc.get_is_connect();}
      
      JSONVar get_json_ob() {return ob_json_;}
      
      String weather ; 
      String temp;
      String h;  


      struct tm timeinfo_;
      dateandtime(){};
      ~dateandtime(){};
      void get_date_time(); //獲取ntpServer上的網路時間
      void use_rtc_time(); //使用本地RTC時間
      void update_time(); //更新時間
      void get_weather();//獲取天氣的json object
      String httpGETRequest(const char* serverName);
      
    private:
      hw_wifi::wifi_commun wc;
      const char *ntpServer_ = "pool.ntp.org";
      const long gmtOffset_sec_ = 8 * 3600;
      const int daylightOffset_sec_ = 0;
      bool is_get_time_ = false;
      bool is_get_weather_ = false;
      String city_ = "Taoyuan";
      String countryCode_ = "TW";
      String bufferforJSON_;
      String openweatherkey_ = "fadeb6864879b82d2a7b2ce0717b565f" ; 
      JSONVar ob_json_;
  };
}
