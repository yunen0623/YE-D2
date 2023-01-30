#include "ST_7735.h"
#include "date_time.h"
#include "canbus_mcp2515.h"
ST_7735::ST_Display st_display;
dateandtime::dateandtime dt;
mcp_2515::mcp_2515_base mcp;
uint8_t arr[8] = {5,6,7,8,1,2,3,4};
int test = 0;

// /**core control test**/
// #include "main_control.h"
// control::controller ct;


void setup() {
  Serial.begin(9600);
  /***The First Test */  
  // dt.get_date_time();
  st_display.ST_Init(1);
  // mcp.mcp_2515_init(7);
  // mcp.mcp_2515_set_canframe(0,0x0F6 , 8 ,arr);
  // mcp.mcp_2515_changemode(2);
  
  


  // /**core control test**/
  // ct.core_init();
  
}

void loop() {
  /***The First Test */
  // dt.update_time();
  // st_display.ST_display_time_and_weather_mode(dt.timeinfo_ , dt.get_connect_flag());
  // dt.get_weather();
  // st_display.ST_display_Weather(dt.temp , dt.h ,dt.weather);
  // mcp.mcp_2515_sendcanframe();
  // mcp.mcp_2515_rececanframe();
  
  // st_display.ST_display_cansubmenu(test);
  st_display.ST_display_cannonitor(test,"0x1234","8",arr, "0x0000","0x0000");
  Serial.println(test);
  /**core control test**/
  // ct.core_controller();
}
