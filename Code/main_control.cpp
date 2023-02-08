#include "HardwareSerial.h"
#include "WString.h"
#include "esp32-hal.h"
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
      mcp_.mcp_2515_init(7);
      st_display.ST_Init(1);
    }
    
    void controller::set_upcount()
    {
      switch (allmode_) 
          {
            case ALL_MODE::ds_clock:
            case ALL_MODE::ds_None:
            break;
            
            case ALL_MODE::ds_menu:
            if(controller::updown_count_ != -1)
            {
                updown_count_--;             
            }
            else if(updown_count_ == -1)
            {
              //do nothing
            }            
            break;
            
            case ALL_MODE::ds_canbus:
            if(subcanmode_ == SUB_CAN_MODE::can_None)
            {
              if(updown_count_ != -1)
              {
                updown_count_--;
              }
              else if(updown_count_ == -1) 
              {
                //
              }                    
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_changemode)
            {
              if(updown_count_ != -1)
              {
                updown_count_--;
              }
              else if(updown_count_ == -1) 
              {
                //
              }  
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
            {
              if(setting_ok_ == 0)
              {
                if(updown_count_ != -1)
                {
                  updown_count_--;
                }
                else if(updown_count_ == -1) 
                {
                  //
                }  
              }
              else if (setting_ok_ == 1)
              {
                if(updown_count_ != -1)
                {
                  updown_count_--;
                }
                else if(updown_count_ == -1) 
                {
                  //
                }  
              }      
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
            {
              if(setting_ok_ == 0)
              {
                if(updown_count_ != -1)
                {
                  updown_count_--;
                }
                else if(updown_count_ == -1) 
                {
                  //
                }  
              }
              else if (setting_ok_ == 1)
              {
                if(updown_count_ != -1)
                {
                  updown_count_--;
                }
                else if(updown_count_ == -1) 
                {
                  //
                }  
              }               
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
            {
              //do nothing
            }
            break;            
          }        
    }

    
    void controller::set_downcount()
    {
      switch (allmode_) 
      {
        case ALL_MODE::ds_clock:
        case ALL_MODE::ds_None:
        break;
        
        case ALL_MODE::ds_menu:
        if(updown_count_ < 3)
        {
          updown_count_++;
        }
        else if(updown_count_ == 3)
        {
          //do nothing
        }
        break;
        
        case ALL_MODE::ds_canbus:
        if(subcanmode_ == SUB_CAN_MODE::can_None)
        {
          if(updown_count_ < 3)
          {
            updown_count_++;
          }
          else if(updown_count_ == 3)
          {
            //do nothing
          }              
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_changemode)
        {
          if(updown_count_ < 3)
          {
            updown_count_++;
          }
          else if(updown_count_ == 3)
          {
            //do nothing
          }
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
        {
          if(setting_ok_ == 0)
          {
            if(updown_count_ <16)
              updown_count_++;
            else if(updown_count_ == 16){}
              //do nothing
          }
          else if (setting_ok_ == 1)
          {
            if(updown_count_ <16)
              updown_count_++;
            else if(updown_count_ == 16){}
              //do nothing
          }      
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
        {
          if(setting_ok_ == 0)
          {
            if(updown_count_ <16)
              updown_count_++;
            else if(updown_count_ == 16){}
              //do nothing
          }
          else if (setting_ok_ == 1)
          {
            if(updown_count_ <16)
              updown_count_++;
            else if(updown_count_ == 16){}
              //do nothing
          }               
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
        {
          //do nothing
        }
        break;
      }                   
    }

    
    void controller::set_leftcount()
    {
      switch(allmode_)
      {
        case ALL_MODE::ds_clock:
        case ALL_MODE::ds_None:
        case ALL_MODE::ds_menu:
        break;

        case ALL_MODE::ds_canbus:
        if(subcanmode_ == SUB_CAN_MODE::can_None || subcanmode_ == SUB_CAN_MODE::can_changemode)
        {
          //do nothing              
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
        {
          if(leftright_count_ != -1)                            
            leftright_count_ -=1;
          else {}
        } 
        else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
        {
          if(setting_ok_ == 0)
          {
            if(leftright_count_ >0)
            {
              leftright_count_ -=1;
            }
            else
              leftright_count_ = 0;
          }
            
          else if(setting_ok_ == 1)
          {
            if(leftright_count_ != -1)                            
              leftright_count_ -=1;
            else 
            {
              
            }
          }
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
        {
          if(leftright_count_ != -1)                            
            leftright_count_ -=1;
          else {}
        }           
      }
    }

    
    void controller::set_rightcount()
    {
      switch(allmode_)
      {
        case ALL_MODE::ds_clock:
        case ALL_MODE::ds_None:
        case ALL_MODE::ds_menu:
        break;
        
        case ALL_MODE::ds_canbus:
        if(subcanmode_ == SUB_CAN_MODE::can_None || subcanmode_ == SUB_CAN_MODE::can_changemode)
        {
          //do nothing              
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
        {
          if(leftright_count_ < 3 )
            leftright_count_ += 1; 
          else {}
            //do nothing
        } 
        else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
        {
          if(setting_ok_ == 0)
          {
            if(leftright_count_ < 0)
              leftright_count_ += 1;
            else
              leftright_count_ = 1;
          }
          else if(setting_ok_ == 1)
          {
            if(leftright_count_ < 3 )
              leftright_count_ += 1; 
            else {}
              //do nothing 
          }
        }
        else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
        {
          if(leftright_count_ < 1 )
            leftright_count_ += 1; 
          else {}
            //do nothing
        }           
      }      
    }

    
    void controller::set_midcount(bool click)
    {
      is_click_mid_ = click;
    }


    void controller::read_controller_single()
    {
        //mid
      if(digitalRead(controller::midbtn_)==LOW)
      {
          controller::is_click_mid_ = true;
          delay(100);   
      }
      else
      {
        controller::is_click_mid_ = false;
        delay(100);
      }

      //UP
      if(digitalRead(controller::upbtn_) == LOW)
      {
        if(controller::updown_count_ != -1)
        {
          switch (allmode_) 
          {
            case ALL_MODE::ds_clock:
            case ALL_MODE::ds_None:
            break;
            
            case ALL_MODE::ds_menu:
            if(controller::updown_count_ != -1)
            {
                updown_count_--;             
            }
            else if(updown_count_ == -1)
            {
              //do nothing
            }            
            break;
            
            case ALL_MODE::ds_canbus:
            if(subcanmode_ == SUB_CAN_MODE::can_None)
            {
              if(updown_count_ != -1)
              {
                updown_count_--;
              }
              else if(updown_count_ == -1) 
              {
                //
              }                    
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_changemode)
            {
              updown_count_--;
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
            {
              if(setting_ok_ == 0)
              {
                updown_count_--;
              }
              else if (setting_ok_ == 1)
              {
                updown_count_--;
              }      
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
            {
              if(setting_ok_ == 0)
              {
                updown_count_--;
              }
              else if (setting_ok_ == 1)
              {
                updown_count_--;
              }               
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
            {
              //do nothing
            }
            break;            
          }        
        }
        else
        {
          updown_count_ = -1;          
        }                             
      }

      if(digitalRead(controller::downbtn_) == LOW)
      {
        switch (allmode_) 
          {
            case ALL_MODE::ds_clock:
            case ALL_MODE::ds_None:
            break;
            case ALL_MODE::ds_menu:
            if(updown_count_ < 3)
            {
              updown_count_++;
            }
            else if(updown_count_ == 3)
            {
              //do nothing
            }
            break;
            case ALL_MODE::ds_canbus:
            if(subcanmode_ == SUB_CAN_MODE::can_None)
            {
              if(updown_count_ < 3)
              {
                updown_count_++;
              }
              else if(updown_count_ == 3)
              {
                //do nothing
              }              
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_changemode)
            {
              if(updown_count_ < 3)
              {
                updown_count_++;
              }
              else if(updown_count_ == 3)
              {
                //do nothing
              }
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
            {
              if(setting_ok_ == 0)
              {
                if(updown_count_ <16)
                  updown_count_++;
                else if(updown_count_ == 16){}
                  //do nothing
              }
              else if (setting_ok_ == 1)
              {
                if(updown_count_ <16)
                  updown_count_++;
                else if(updown_count_ == 16){}
                  //do nothing
              }      
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
            {
              if(setting_ok_ == 0)
              {
                if(updown_count_ <16)
                  updown_count_++;
                else if(updown_count_ == 16){}
                  //do nothing
              }
              else if (setting_ok_ == 1)
              {
                if(updown_count_ <16)
                  updown_count_++;
                else if(updown_count_ == 16){}
                  //do nothing
              }               
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
            {
              //do nothing
            }
            break;
          }                                                  
    }

      if(digitalRead(controller::leftbtn_) == LOW)
      {
        if(controller::leftright_count_ != -1)
        {
          switch(allmode_)
          {
            case ALL_MODE::ds_clock:
            case ALL_MODE::ds_None:
            case ALL_MODE::ds_menu:
            break;
            case ALL_MODE::ds_canbus:
            if(subcanmode_ == SUB_CAN_MODE::can_None || subcanmode_ == SUB_CAN_MODE::can_changemode)
            {
              //do nothing              
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
            {
              if(leftright_count_ != -1)                            
                leftright_count_ -=1;
              else {}
            } 
            else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
            {
              if(setting_ok_ == 0)
              {
                if(leftright_count_ >0)
                {
                  leftright_count_ -=1;
                }
                else
                  leftright_count_ = 0;
              }
                
              else if(setting_ok_ == 1)
              {
                if(leftright_count_ != -1)                            
                  leftright_count_ -=1;
                else 
                {
                  
                }
              }
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
            {
              if(leftright_count_ != -1)                            
                leftright_count_ -=1;
              else {}
            }           
          }
        }
        else
        {
          leftright_count_ = -1;           
        }                                 
      }

      if(digitalRead(controller::rightbtn_) == LOW)
      {
        switch(allmode_)
          {
            case ALL_MODE::ds_clock:
            case ALL_MODE::ds_None:
            case ALL_MODE::ds_menu:
            break;
            case ALL_MODE::ds_canbus:
            if(subcanmode_ == SUB_CAN_MODE::can_None || subcanmode_ == SUB_CAN_MODE::can_changemode)
            {
              //do nothing              
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_setfilterandmask)
            {
              if(leftright_count_ < 3 )
                leftright_count_ += 1; 
              else {}
                //do nothing
            } 
            else if(subcanmode_ == SUB_CAN_MODE::can_frame_id_type)
            {
              if(setting_ok_ == 0)
              {
                if(leftright_count_ < 0)
                  leftright_count_ += 1;
                else
                  leftright_count_ = 1;
              }
              else if(setting_ok_ == 1)
              {
                if(leftright_count_ < 3 )
                leftright_count_ += 1; 
                else {}
                  //do nothing 
              }
            }
            else if(subcanmode_ == SUB_CAN_MODE::can_Monitor)
            {
              if(leftright_count_ < 1 )
                leftright_count_ += 1; 
              else {}
                //do nothing
            }           
          }
                                    
      }
    }

    uint32_t controller::set_filtermask_btn()
    { 
      
      if(controller::setting_ok_ == 0) //setting mask
      {
        if(leftright_count_ == 0)
        {
          str1 = hexstr[updown_count_];
          temp_[0] = hexstr[updown_count_];
        }                            
        else if(leftright_count_ == 1)
        {
          str2 = hexstr[updown_count_];
          temp_[1] = hexstr[updown_count_];
        } 
        else if(leftright_count_ == 2)
        {
          str3 = hexstr[updown_count_];
          temp_[2] = hexstr[updown_count_];
        } 
        else if(leftright_count_ ==3)
        {
          str4 = hexstr[updown_count_];
          temp_[3] = hexstr[updown_count_];
        } 

        temp_str = str1 + str2 + str3 +str4 ;
        mask_id_str_ = str1 + str2 + str3 +str4;
        st_display.ST_display_setfiltermask(setting_ok_, leftright_count_ , temp_, temp_);                        
        if(controller::is_click_mid_ == true && leftright_count_ == 3)
        {
          res_str = str1 + str2 + str3 +str4 ;
          const char *cstr =  res_str.c_str();   
          controller::mcp_.mcp_2515_set_Mask(MCP2515::MASK0 , is_ext_type_ , controller::mcp_.convertStrtoLong(cstr));
          controller::set_mask_id_ = controller::mcp_.convertStrtoLong(cstr); 
          Serial.println("mask id :" + String(set_mask_id_));
          leftright_count_ = 0;
          updown_count_ = 0;  
          temp_[0] = "0";
          temp_[1] = "0";
          temp_[2] = "0";
          temp_[3] = "0";                
          setting_ok_++;     
        } 
        
      } 
      else if(controller::setting_ok_ == 1) //setting filter
      { 
              
        if(leftright_count_ == 0)
        {
          str1 = hexstr[updown_count_];
          temp_[0] = hexstr[updown_count_];
        }                            
        else if(leftright_count_ == 1)
        {
          str2 = hexstr[updown_count_];
          temp_[1] = hexstr[updown_count_];
        } 
        else if(leftright_count_ == 2)
        {
          str3 = hexstr[updown_count_];
          temp_[2] = hexstr[updown_count_];
        } 
        else if(leftright_count_ ==3)
        {
          str4 = hexstr[updown_count_];
          temp_[3] = hexstr[updown_count_];
        } 

        temp_str = str1 + str2 + str3 +str4 ;
        filter_id_str_ = str1 + str2 + str3 +str4;
        st_display.ST_display_setfiltermask(setting_ok_, leftright_count_ , temp_, temp_);    
        if(controller::is_click_mid_ == true && leftright_count_ == 3)
        {
          res_str = str1 + str2 + str3 +str4 ;
          const char *cstr =  res_str.c_str();   
          controller::mcp_.mcp_2515_set_Filter(MCP2515::RXF0 ,is_ext_type_ , controller::mcp_.convertStrtoLong(cstr));
          controller::set_filter_id_ = controller::mcp_.convertStrtoLong(cstr);    
          Serial.println("filter id :" + String(set_filter_id_));        
          setting_ok_ = 0;
          temp_[0] = "0";
          temp_[1] = "0";
          temp_[2] = "0";
          temp_[3] = "0";
          st_display.ST_display_clear();
          controller::subcanmode_ = SUB_CAN_MODE::can_None;         
        }
           
      }           
    }

    uint32_t controller::set_canidandtype_btn()
    {  
      if(controller::setting_ok_ == 0)
      {  
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
        if(controller::is_click_mid_ == true && updown_count_ != -1)
        { 
          leftright_count_ = 0;
          updown_count_ = 0;
          setting_ok_++;                
        }
        temp_str = str1 + str2 + str3 +str4 ;
        st_display.ST_display_setcanid(setting_ok_ , leftright_count_, is_ext_type_ , &temp_str);                      
      }           
      else if(controller::setting_ok_ == 1) 
      {
        if(leftright_count_ == 0)
        {
          str1 = hexstr[updown_count_];
          temp_[0] = hexstr[updown_count_];
        }                            
        else if(leftright_count_ == 1)
        {
          str2 = hexstr[updown_count_];
          temp_[1] = hexstr[updown_count_];
        } 
        else if(leftright_count_ == 2)
        {
          str3 = hexstr[updown_count_];
          temp_[2] = hexstr[updown_count_];
        } 
        else if(leftright_count_ ==3)
        {
          str4 = hexstr[updown_count_];
          temp_[3] = hexstr[updown_count_];
        }          
        temp_str = str1 + str2 + str3 +str4 ;       
        st_display.ST_display_setcanid(setting_ok_ , leftright_count_, is_ext_type_ , temp_);
        if(controller::is_click_mid_ == true&& leftright_count_ == 3)
        {        
          res_str = str1 + str2 + str3 +str4 ;
          const char *cstr =  res_str.c_str();           
          controller::mcp_.mcp_2515_set_sendcanframe(type , controller::mcp_.convertStrtoLong(cstr) , 8 , default_data ); 
          Serial.println("Set CanID : " + String(mcp_.convertStrtoLong(cstr)));
          delay(50);          
          temp_[0] = "0";
          temp_[1] = "0";
          temp_[2] = "0";
          temp_[3] = "0";
          setting_ok_ = 0;
          st_display.ST_display_clear();
          controller::subcanmode_ = SUB_CAN_MODE::can_None;         
        }    
      }
    }

    void controller::set_canmode_btn(int &modee)
    {  
      st_display.ST_display_changemode(can_mode_);             
      modee = updown_count_;
      if(controller::is_click_mid_ == true && updown_count_ != -1)
      {
        controller::mcp_.mcp_2515_changemode(modee);
        modee = 0;
        st_display.ST_display_clear();
        controller::subcanmode_ = SUB_CAN_MODE::can_None;         
      }
    }
    
    //////////應該在按下click後先清畫面再顯示////////////////////
    void controller::core_controller()
    {
      // controller::read_controller_single();
      switch(controller::allmode_)
      {
        case ALL_MODE::ds_clock :
          dt.update_time();
          st_display.ST_display_time_and_weather_mode(dt.timeinfo_ , dt.get_connect_flag());
          dt.get_weather();
          st_display.ST_display_Weather(dt.temp , dt.h ,dt.weather);
          if(controller::is_click_mid_ == true)
          {
            st_display.ST_display_clear();
            
            updown_count_  = -1;
            controller::allmode_ = ALL_MODE::ds_menu;
            break;
          }                
        
                
        case ALL_MODE::ds_None :
          if(controller::is_click_mid_ == true)
          {
            st_display.ST_display_clear();
            
            updown_count_  = -1;            
            controller::allmode_ = ALL_MODE::ds_menu;       
          }                    
        break;
        
        case ALL_MODE::ds_menu:
          
          if(controller::updown_count_ == -1)
          {
            st_display.ST_display_menu(updown_count_);
          }
          else if(controller::updown_count_ == 0)
          {
            st_display.ST_display_menu(updown_count_);
            if(controller::is_click_mid_ == true)
            {
              updown_count_  = -1;
              st_display.ST_display_clear();
              delay(50);
              controller::allmode_ = ALL_MODE::ds_clock;     
              break;                          
            }                   
          }          
          else if(controller::updown_count_ == 1)
          {
            st_display.ST_display_menu(updown_count_);
            if(controller::is_click_mid_ == true)
            {
              updown_count_  = -1;
              st_display.ST_display_clear(); 
              delay(50);
              controller::allmode_ = ALL_MODE::ds_canbus;
              break;               
            }              
          }
         
        case ALL_MODE::ds_canbus:
          if(subcanmode_ == SUB_CAN_MODE::can_None && allmode_ == ALL_MODE::ds_canbus)
          {           
            st_display.ST_display_cansubmenu(updown_count_);        
          } 
                   
          if(controller::updown_count_ == 0 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_frame_id_type;
            leftright_count_ = 0; 
            controller::updown_count_ = -1; 
            st_display.ST_display_clear();  
            delay(50);  
          }
          else if(controller::updown_count_ == 1 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_setfilterandmask;
            leftright_count_ = 0;             
            updown_count_ = 0;
            st_display.ST_display_clear(); 
            delay(50);                        
          }
          else if(controller::updown_count_ == 2 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_changemode;
            controller::updown_count_ = -1;
            st_display.ST_display_clear();
            delay(50);                                     
          }
          else if(controller::updown_count_ == 3 && controller::is_click_mid_ == true && controller::subcanmode_ == SUB_CAN_MODE::can_None)
          {
            controller::subcanmode_ = SUB_CAN_MODE::can_Monitor;
            controller::updown_count_ = -1;
            controller::leftright_count_ = -1;
            st_display.ST_display_clear(); 
            delay(50);                    
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
              Serial.println(String(frame_rece_.can_id));            
              if(mcp_.get_readStatus() == MCP2515::ERROR_OK)
              {
                frame_rece_ = controller::mcp_.mcp_2515_rececanframe();  //always receive message               
              }
              char outputString[9];
              itoa(frame_rece_.can_id, outputString, 16);   
              Serial.println("Convert :" + String(outputString));                          
              st_display.ST_display_cannonitor(leftright_count_ , outputString , String(frame_rece_.can_dlc) , frame_rece_.data , filter_id_str_ , mask_id_str_);
              
                            
              if(leftright_count_ == 0 && is_click_mid_ == true)  //send message
              {
                controller::mcp_.mcp_2515_sendcanframe();                                     
              }
              else if(leftright_count_ == 1 && is_click_mid_ == true) //back to menu
              { 
                st_display.ST_display_clear();  
                controller::subcanmode_ = SUB_CAN_MODE::can_None;   
                controller::allmode_ = ALL_MODE::ds_menu;                               
                updown_count_ = -1 ;                
                leftright_count_ = -1;     
              }                                            
              break;
          }
        break;
      }
    }


    
}