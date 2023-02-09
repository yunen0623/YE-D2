#include "hw_wifi.h"
#include <Arduino.h>
namespace hw_wifi
{
    wifi_commun::wifi_commun():is_connect_(false) , is_timeout_(false)
    {
      
    }
  
    bool wifi_commun::get_is_connect()
    {
        return is_connect_;
    }

    bool wifi_commun::get_is_timeout()
    {
        return is_timeout_;
    }

    void wifi_commun::scan_wifi()
    {
        wifi_scan_ = WiFi.scanNetworks();
        delay(1000);
        if (wifi_scan_ == 0)
        {
          Serial.println("no Wi-Fi networks found");
          is_connect_ = false;
        }
        else
        {
            wifi_commun::connect_wifi();
        }
    }

    void wifi_commun::connect_wifi()
    {
        for(int i  = 0 ; i < wifi_scan_ ; ++i)
        {
            if(WiFi.SSID(i) == "307")
            {
                 WiFi.begin(ssid_, password_);
                 while (WiFi.status() != WL_CONNECTED)
                 {
                    Serial.print(".");
                    if(wifi_commun::timer_duration(20000) == true)
                      return;
                 }
                 Serial.println("WiFi connected!");
                 is_connect_ = true;
            }
            else if (WiFi.SSID(i) == "MY HOME")
            {
                WiFi.begin(homessid_, homepassword_);
                while (WiFi.status() != WL_CONNECTED)
                 {
                    Serial.print(".");
                    if(wifi_commun::timer_duration(20000) == true)
                      return;
                 }
                 Serial.println("WiFi connected!");
                 is_connect_ = true;
            }
            else if(WiFi.SSID(i) == "USUN_NEWGuest")
            {
                WiFi.begin(canpanyssid_, canpanypassword_);
                while (WiFi.status() != WL_CONNECTED)
                 {
                    Serial.print(".");
                    if(wifi_commun::timer_duration(20000) == true)
                      return;
                 }
                 Serial.println("WiFi connected!");
                 is_connect_ = true;
            }
        }
    }

    //重連Wifi , 並在這裡重置Time_out_flag
    void wifi_commun::reconnect_wifi()
    {
        is_timeout_ = false;
        wifi_commun::scan_wifi();
    }
    
    //Timer Out 時間計算
    bool wifi_commun::timer_duration(unsigned long ts)
    {
        if(millis() > time_now + ts)
        {
            time_now = millis();
            is_timeout_ = true;
        }
        return is_timeout_;
    }
}
