/**core control test**/
#include "main_control.h"
control::controller ct;

struct Button {
    const uint8_t PIN;
    bool pressed;
};

Button btn_up = {27 , false};
Button btn_down = {26 , false};
Button btn_left = {25 , false};
Button btn_right = {33 , false};
Button btn_mid = {32 , false};
unsigned long button_time = 0;  
unsigned long last_button_time_up_ , last_button_time_down_ , last_button_time_left_ , last_button_time_right_ , last_button_time_mid_  = 0; 
//Here is about ISR
void IRAM_ATTR isr_up()
{
  button_time = millis();
  if (button_time - last_button_time_up_ > 250)
  {
    btn_up.pressed = true;
    last_button_time_up_ = button_time;
  }
}      
void IRAM_ATTR isr_down()
{
  button_time = millis();
  if (button_time - last_button_time_down_ > 250)
  {
    btn_down.pressed = true;
    last_button_time_down_ = button_time;
  }
}
void IRAM_ATTR isr_left()
{
  button_time = millis();
  if (button_time - last_button_time_left_ > 250)
  {
    btn_left.pressed = true;
    last_button_time_left_ = button_time;
  }
}
void IRAM_ATTR isr_right()
{
  button_time = millis();
  if (button_time - last_button_time_right_ > 250)
  {
    btn_right.pressed = true;
    last_button_time_right_ = button_time;
  }
}
void IRAM_ATTR isr_mid()
{
  button_time = millis();
  if (button_time - last_button_time_mid_ > 250)
  {
    btn_mid.pressed = true;
    last_button_time_mid_ = button_time;
  }
}

void setup() {
  Serial.begin(9600);
  
  /**core control test**/
  ct.core_init();
  
  attachInterrupt(btn_up.PIN, isr_up, FALLING); //up ISR
  attachInterrupt(btn_down.PIN, isr_down, FALLING); //down ISR
  attachInterrupt(btn_left.PIN, isr_left, FALLING); //left ISR
  attachInterrupt(btn_right.PIN, isr_right, FALLING); //Right ISR
  attachInterrupt(btn_mid.PIN, isr_mid, FALLING); //mid ISR
}


void loop() {
  /**core control test**/
  if (btn_mid.pressed) 
  {
    ct.set_midcount(btn_mid.pressed);
    btn_mid.pressed = false;
  }
  else
  {
    ct.set_midcount(btn_mid.pressed);
  }  

  if(btn_up.pressed)
  {
    ct.set_upcount();
    btn_up.pressed = false;
  }  

  if(btn_down.pressed)
  {
    ct.set_downcount();
    btn_down.pressed = false;
  } 

  if(btn_left.pressed)
  {
    ct.set_leftcount();
    btn_left.pressed = false;
  } 

  if(btn_right.pressed)
  {
    ct.set_rightcount();
    btn_right.pressed = false;
  } 

  
  ct.core_controller();
}
