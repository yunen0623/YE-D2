#include "canbus_mcp2515.h"


namespace mcp_2515
{
  mcp_2515_base::mcp_2515_base():
  hspi{new SPIClass(HSPI)} , 
  mcp2515_{mcp2515_CS_ , spiClk , hspi}
  {
    
  }
  
  
  /* init MCP2515 to set bitrate
   * @parm: bitrate_mode 
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
  //change MCP2515 Mode
  /*
   * @parm:
   * 0 : config mode can set id , filter ....
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
