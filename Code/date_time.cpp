#include "date_time.h"

#include <Arduino.h>
namespace dateandtime
{ 
    void dateandtime::get_date_time()
    {
        wc.scan_wifi();
        configTime(gmtOffset_sec_, daylightOffset_sec_, ntpServer_);
        if (!getLocalTime(&timeinfo_))
        {
            Serial.println("Failed to obtain time");
            is_get_time_ = false;
            return;
        }
        is_get_time_ = true;
    }

    void dateandtime::update_time()
    {
        getLocalTime(&timeinfo_);
        Serial.println(&timeinfo_, "%F %T");
    }

    void dateandtime::use_rtc_time()
    {
       if(is_get_time_ == false)
        return;
       else
       {
          WiFi.disconnect(true);
          WiFi.mode(WIFI_OFF);
          Serial.println("Wifi is already disconect!");
       }
    }
    
}
