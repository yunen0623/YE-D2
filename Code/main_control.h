#include "stdint.h"
#include "Arduino.h"
#include "canbus_mcp2515.h"
#include "ST_7735.h"
#include "date_time.h"
namespace control 
{
  enum class ALL_MODE  //main menu
    {
        ds_None,
        ds_menu,
        ds_clock,
        ds_canbus,
        ds_sleepmode,
    };

  enum class SUB_CAN_MODE  //CAN sub menu
  {
      can_None,
      can_setfilterandmask,
      can_changemode,
      can_frame_id_type,
      can_Monitor
      
  };     
  
  enum class CAN_Mointor_Func //CAN mointor func
  {
      can_mointor_none,
      can_send_frame,
      can_rece_frame,
      can_backmenu
  };

  
    class controller
    {
      public:
        controller();
        ~controller(){};
        void read_controller_single();
        void core_controller();
        uint32_t set_filtermask_btn();
        uint32_t set_canidandtype_btn();
        void set_canmode_btn(int &modee);
        void core_init();
        
      private:
        const int upbtn_ =  27;
        const int downbtn_ = 26 ;
        const int leftbtn_ = 25 ;
        const int rightbtn_ = 33 ;
        const int midbtn_ = 32 ;
        const int setbtn_ = 35 ;
        const int resetbtn_ = 34 ;
        ALL_MODE allmode_;
        SUB_CAN_MODE subcanmode_;
        CAN_Mointor_Func canmointorfunc_;
        /**here is about control**/
        int updown_count_ , leftright_count_ = -1 ; //btn  count
        bool is_click_mid_ = false;

        /**here is  about can frame**/
        int can_mode_ = -1; //MCP2515模式 0 1 2 3     
        int can_type_choose = -1; //choose std or ext type
        int setting_ok_ = 0; //check type , id / filter , mask is setting ok 
        uint8_t default_data[8]= {1,2,3,4,5,6,7,8};
        bool is_ext_type_ = false;  
        int dlc_ = 8;
        MCP2515::RXF rxfid_;
        MCP2515::MASK maskid_;
        uint32_t set_can_id_ = 0x0000;
        uint32_t set_filter_id_ = 0x0000;
        uint32_t set_mask_id_ = 0x0000;
        
        mcp_2515::mcp_2515_base mcp_;
        ST_7735::ST_Display st_display;
        dateandtime::dateandtime dt;
        String temp_;
        struct can_frame frame_rece_; //for read candata frame
        const String hexstr[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
        
              
    };
}