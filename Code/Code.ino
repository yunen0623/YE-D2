#include "ST_7735.h"
#include "date_time.h"
#include "canbus_mcp2515.h"

ST_7735::ST_Display st_display;
dateandtime::dateandtime dt;
mcp_2515::mcp_2515_base mcp;
// uint8_t arr[8] = {5,6,7,8,1,2,3,4};

void setup() {
  Serial.begin(9600);
  st_display.ST_Init(1);
  dt.get_date_time();
  
  // mcp.mcp_2515_init(7);
  // mcp.mcp_2515_set_canframe(0,0x0F6 , 8 ,arr);
  // mcp.mcp_2515_changemode(2);
}

void loop() {
  dt.update_time();
  st_display.ST_display_time_and_weather_mode(dt.timeinfo_ , dt.get_connect_flag());
  dt.get_weather();
  st_display.ST_display_Weather(dt.temp , dt.h ,dt.weather);

  // mcp.mcp_2515_sendcanframe();
  // mcp.mcp_2515_rececanframe();

  
}
