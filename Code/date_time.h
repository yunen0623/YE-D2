#include "hw_wifi.h"
#include <Arduino.h>

namespace dateandtime
{
  class dateandtime
  {
    public:
      struct tm timeinfo_;
      dateandtime(){};
      ~dateandtime(){};
      void get_date_time(); //獲取ntpServer上的網路時間
      void use_rtc_time(); //使用本地RTC時間
      void update_time(); //更新時間
    private:
      hw_wifi::wifi_commun wc;
      const char *ntpServer_ = "pool.ntp.org";
      const long gmtOffset_sec_ = 8 * 3600;
      const int daylightOffset_sec_ = 0;
      bool is_get_time_ = false;
      
  };
}
