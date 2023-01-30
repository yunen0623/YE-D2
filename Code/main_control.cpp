#include "esp32-hal-gpio.h"
#include "main_control.h"

namespace control 
{
    controller::controller():allmode_{ALL_MODE::ds_clock} , subcanmode_{SUB_CAN_MODE::can_None} , canmointorfunc_{CAN_Mointor_Func::can_mointor_none}
    {
      pinMode(controller::upbtn_, INPUT_PULLUP);
      pinMode(controller::downbtn_, INPUT_PULLUP);
      pinMode(controller::leftbtn_, INPUT_PULLUP);
      pinMode(controller::rightbtn_, INPUT_PULLUP);
      pinMode(controller::midbtn_, INPUT_PULLUP);
      pinMode(controller::setbtn_, INPUT_PULLUP);
      pinMode(controller::resetbtn_, INPUT_PULLUP);
      
    }

    void controller::core_init()
    {
      dt.get_date_time();
      st_display.ST_Init(1);
    }
    
    void controller::read_controller_single()
    {
      //mid
      if(digitalRead(controller::midbtn_)==LOW)
        controller::is_click_mid_ = true;
      else
        controller::is_click_mid_ = false;
      
      //UP
      if(digitalRead(controller::upbtn_) == LOW)
      {
        if(controller::updown_count_ != -1)
          updown_count_ -=1;
        else
          updown_count_ = -1;                              
      }

      if(digitalRead(controller::downbtn_) == LOW)
      {
        updown_count_ +=1;                                    
      }

      if(digitalRead(controller::leftbtn_) == LOW)
      {
        if(controller::leftright_count_ != -1)
          leftright_count_ -=1;
        else
          leftright_count_ = -1;                              
      }

      if(digitalRead(controller::rightbtn_) == LOW)
      {
        leftright_count_ += 1;                             
      }
    }

    uint32_t controller::set_filtermask_btn()
    { 
      String str1 , str2 , str3 , str4 , res_str = "" ;    
      leftright_count_ , updown_count_ = 0;
      
      while(controller::setting_ok_ == 0) //setting mask
      {
        controller::read_controller_single();
        if(leftright_count_ == 0)
          str1 = hexstr[updown_count_];                            
        else if(leftright_count_ == 1)
          str2 = hexstr[updown_count_];
        else if(leftright_count_ == 2)
          str3 = hexstr[updown_count_];
        else if(leftright_count_ ==3)
          str4 = hexstr[updown_count_];
                
        if(controller::is_click_mid_ == true)
        {
          res_str = str1 + str2 + str3 +str4 ;
          const char *cstr =  res_str.c_str();   
          controller::mcp_.mcp_2515_set_Mask(MCP2515::MASK0 , is_ext_type_ , controller::mcp_.convertStrtoLong(cstr));
          controller::set_mask_id_ = controller::mcp_.convertStrtoLong(cstr);                   
          setting_ok_++;
          break;          
        } 
      } 
      while(controller::setting_ok_ == 1) //setting filter
      { 
        controller::read_controller_single();       
        if(leftright_count_ == 0)
          str1 = hexstr[updown_count_];                            
        else if(leftright_count_ == 1)
          str2 = hexstr[updown_count_];
        else if(leftright_count_ == 2)
          str3 = hexstr[updown_count_];
        else if(leftright_count_ ==3)
          str4 = hexstr[updown_count_];
        if(controller::is_click_mid_ == true)
        {
          res_str = str1 + str2 + str3 +str4 ;
          const char *cstr =  res_str.c_str();   
          controller::mcp_.mcp_2515_set_Filter(MCP2515::RXF0 ,is_ext_type_ , controller::mcp_.convertStrtoLong(cstr));
          controller::set_filter_id_ = controller::mcp_.convertStrtoLong(cstr);            
          setting_ok_ = 0;
          controller::subcanmode_ = SUB_CAN_MODE::can_None; 
          break;         
        }       
      }           
    }

    uint32_t controller::set_canidandtype_btn()
    {
      String str1 , str2 , str3 , str4 , res_str = "" ;
      leftright_count_ , updown_count_ = 0; 
      int type = 0; 
      while(controller::setting_ok_ == 0)
      {
        controller::read_controller_single();
        if(updown_count_ == 0)
        {
          is_ext_type_ = false;
          type = 0;  //std        
        }
        else if(updown_count_ == 1)
        {
          is_ext_type_ = true;
          type = 1;
        }
        if(controller::is_click_mid_ == true)
        { 
          setting_ok_++;
          break;          
        }                      
      }           
      while(controller::setting_ok_ == 1)
      {
        controller::read_controller_single();
        if(leftright_count_ == 0)
          str1 = hexstr[updown_count_];                            
        else if(leftright_count_ == 1)
          str2 = hexstr[updown_count_];
        else if(leftright_count_ == 2)
          str3 = hexstr[updown_count_];
        else if(leftright_count_ ==3)
          str4 = hexstr[updown_count_];
        if(controller::is_click_mid_ == true)
        {        
          res_str = str1 + str2 + str3 +str4 ;
          const char *cstr =  res_str.c_str();           
          controller::mcp_.mcp_2515_set_canframe(type , controller::mcp_.convertStrtoLong(cstr) , 8 , default_data );
          controller::set_can_id_ = controller::mcp_.convertStrtoLong(cstr);
          setting_ok_ = 0;
          controller::subcanmode_ = SUB_CAN_MODE::can_None; 
          break;        
        }  
      }
    }

    void controller::set_canmode_btn(int &modee)
    {        
      modee = updown_count_;
      if(controller::is_click_mid_ == true)
      {
        controller::mcp_.mcp_2515_changemode(modee);
        modee = 0;
        controller::subcanmode_ = SUB_CAN_MODE::can_None;         
      }
    }
    //////////應該在按下click後先清畫面再顯示////////////////////
    void controller::core_controller()
    {
      controller::read_controller_single();
      switch(controller::allmode_)
      {
        case ALL_MODE::ds_clock :
          dt.update_time();
          st_display.ST_display_time_and_weather_mode(dt.timeinfo_ , dt.get_connect_flag());
          dt.get_weather();
          st_display.ST_display_Weather(dt.temp , dt.h ,dt.weather);
          if(controller::is_click_mid_ == true)
            controller::allmode_ = ALL_MODE::ds_menu;          
        break;
                
        case ALL_MODE::ds_None :
          if(controller::is_click_mid_ == true)
            controller::allmode_ = ALL_MODE::ds_menu;          
        break;
        
        case ALL_MODE::ds_menu:
          if(controller::updown_count_ == 0)
          {
            if(controller::is_click_mid_ == true)
            {
              controller::allmode_ = ALL_MODE::ds_clock;
              controller::updown_count_ = -1;                              
            }                   
          }          
          else if(controller::updown_count_ == 1)
          {
            if(controller::is_click_mid_ == true)
            {
              controller::allmode_ = ALL_MODE::ds_canbus;
              controller::updown_count_ = -1;               
            }              
          }
        break;
        
        case ALL_MODE::ds_canbus:
          if(controller::updown_count_ == 0 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_frame_id_type;
            controller::updown_count_ = -1;            
          }
          else if(controller::updown_count_ == 1 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_setfilterandmask;
            controller::updown_count_ = -1;                          
          }
          else if(controller::updown_count_ == 2 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_changemode;
            controller::updown_count_ = -1;                          
          }
          else if(controller::updown_count_ == 3 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_Monitor;
            controller::updown_count_ = -1;
            controller::leftright_count_ = -1;                          
          }

          switch(controller::subcanmode_)
          {
            case SUB_CAN_MODE::can_frame_id_type:
              controller::set_canidandtype_btn();             
              break;             
            case SUB_CAN_MODE::can_setfilterandmask:
              controller::set_filtermask_btn();
              break;
            case SUB_CAN_MODE::can_changemode:
              controller::set_canmode_btn(can_mode_);
              break;          
            case SUB_CAN_MODE::can_Monitor:
              frame_rece_ = controller::mcp_.mcp_2515_rececanframe();  //always receive message
              if(leftright_count_ == 0 && is_click_mid_ == true)  //send message
              {
                controller::mcp_.mcp_2515_sendcanframe();                                     
              }
              else if(leftright_count_ == 1 && is_click_mid_ == true) //back to menu
              {                                    
                updown_count_ = -1 ;                
                leftright_count_ = -1;
                controller::subcanmode_ = SUB_CAN_MODE::can_None;
              }                                            
              break;
          }
        break;
      }
    }


    
}