#include "canbus_mcp2515.h"


namespace mcp_2515
{
  mcp_2515_base::mcp_2515_base():
  hspi{new SPIClass(HSPI)} , 
  mcp2515_{mcp2515_CS_ , spiClk , hspi}
  {
    
  }
  
  /**
   * @brief 
   * 
   * @param bitrate_mode 
   */
  void mcp_2515_base::mcp_2515_init(int bitrate_mode)
  {
      mcp2515_.reset();
      switch(bitrate_mode)
      {
          case 0:
            mcp2515_.setBitrate(CAN_5KBPS,MCP_8MHZ);
            break;
          case 1:
            mcp2515_.setBitrate(CAN_10KBPS,MCP_8MHZ);
            break;
          case 2:
            mcp2515_.setBitrate(CAN_20KBPS,MCP_8MHZ);
            break;
          case 3:
            mcp2515_.setBitrate(CAN_40KBPS,MCP_8MHZ);
            break;
          case 4:
            mcp2515_.setBitrate(CAN_50KBPS,MCP_8MHZ);
            break;
          case 5:
            mcp2515_.setBitrate(CAN_80KBPS,MCP_8MHZ);
            break;
          case 6:
            mcp2515_.setBitrate(CAN_100KBPS,MCP_8MHZ);
            break;
          case 7:
            mcp2515_.setBitrate(CAN_125KBPS,MCP_8MHZ);
            break;
          case 8:
            mcp2515_.setBitrate(CAN_200KBPS,MCP_8MHZ);
            break;
          case 9:
            mcp2515_.setBitrate(CAN_250KBPS,MCP_8MHZ);
            break;
          case 10:
            mcp2515_.setBitrate(CAN_500KBPS,MCP_8MHZ);
            break;
          case 11:
            mcp2515_.setBitrate(CAN_1000KBPS,MCP_8MHZ);
            break;
      }
      
  }

 /**
  * @brief 
  * 
  * @param type 0 : STD 1: EXT
  * @param can_id_  11bits / 29bits
  */
  void mcp_2515_base::mcp_2515_set_idtype(int type , canid_t can_id_)
  {
      if (type == 0)
        frame.can_id = can_id_;
      else 
        frame.can_id = can_id_ | CAN_EFF_FLAG;
  }


  /**
   * @brief 
   * 
   * @param mode_ 
   *  0 : config mode can set id , filter ....
   * 1 : need another can controller and reveiver
   * 2 : can send ande receive msg with self
   * 3 : only listen another MCP215 msg
   */
  void mcp_2515_base::mcp_2515_changemode(int mode_)
  {
      switch(mode_)
      {
        case 0 :
          mcp2515_.setConfigMode();
          break;
        case 1 :
          mcp2515_.setNormalMode();
          break;
        case 2 :
          mcp2515_.setLoopbackMode();
          break;
        case 3 :
          mcp2515_.setListenOnlyMode();
          break;
      }
  }
  
  
}
