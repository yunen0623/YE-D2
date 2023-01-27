#include "ST_7735.h"
#include "date_time.h"
ST_7735::ST_Display st_display;
dateandtime::dateandtime dt;

void setup() {
  Serial.begin(9600);
  st_display.ST_Init(1);
  dt.get_date_time();
}

void loop() {
  dt.update_time();
  st_display.ST_display_time_and_weather_mode(dt.timeinfo_ , dt.get_connect_flag());
  dt.get_weather();
  st_display.ST_display_Weather(dt.temp , dt.h ,dt.weather);
}
