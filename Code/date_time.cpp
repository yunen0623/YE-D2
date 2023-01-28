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
//        Serial.println(&timeinfo_, "%F %T");
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

    void dateandtime::get_weather()
    {
        String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city_ + "," + countryCode_ + "&APPID=" + openweatherkey_ +"&units=metric" ;
        bufferforJSON_ = httpGETRequest(serverPath.c_str());
        
        ob_json_ = JSON.parse(bufferforJSON_);
        
        if (JSON.typeof(ob_json_) == "undefined") 
        {
          Serial.println("Parsing input failed!");
          is_get_weather_ = false;
          return;
        }
        else
          is_get_weather_ = true;
          
        //Weather Code : Thunderstorm ,  Drizzle  ,  Rain  ,  Snow  , Atmosphere , Clear , Clouds
//        Serial.print("Temperature: ");
//        Serial.println(ob_json_["main"]["temp"]);
//        Serial.print("Humidity: ");
//        Serial.println(ob_json_["main"]["humidity"]);
//        Serial.print("Weather: ");
//        Serial.println(ob_json_["weather"][0]["main"]);

        weather = JSON.stringify(ob_json_["weather"][0]["main"]);
        temp = JSON.stringify(ob_json_["main"]["temp"]);
        h = JSON.stringify(ob_json_["main"]["humidity"]);
    }

    String dateandtime::httpGETRequest(const char* serverName)
    {
      WiFiClient client;
      HTTPClient http;
        
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // Send HTTP POST request
      int httpResponseCode = http.GET();
      
      String payload = "{}"; 
      
      if (httpResponseCode>0) {
//        Serial.print("HTTP Response code: ");
//        Serial.println(httpResponseCode);
        payload = http.getString();
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    
      return payload;
    }
    
}
