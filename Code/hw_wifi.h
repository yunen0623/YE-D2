#include <WiFi.h>
#include <AsyncTimer.h>
#include <Arduino.h>
namespace hw_wifi
{
   class wifi_commun
   {
      public:
          wifi_commun();
          ~wifi_commun(){};
          bool get_is_connect();
          bool get_is_timeout();
          void connect_wifi();
          void reconnect_wifi();
          void scan_wifi();
          bool timer_duration(unsigned long ts = 20000);
          
      private:
        
          int wifi_scan_ = 0;
          const char *ssid_ = "307";    
          const char *password_ = "0912222363"; 
         
          const char *homessid_ = "MY HOME";    
          const char *homepassword_ = "0932326831";
          
          const char *canpanyssid_ = "USUN_NEWGuest";    
          const char *canpanypassword_ = "Usun3498"; 
         
          bool is_connect_ = false;
          bool is_timeout_ = false;

          unsigned long time_now = 0; 
//          unsigned long period=20000; //計時的時間
   };
  
}
