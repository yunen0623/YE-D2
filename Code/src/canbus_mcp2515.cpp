#include "WString.h"
#include "stdint.h"
#include "canbus_mcp2515.h"


namespace mcp_2515
{
mcp_2515_base::mcp_2515_base():
  hspi{new SPIClass(HSPI)} ,
  mcp2515_{mcp2515_CS_ , spiClk , hspi}
{
  hspi->begin();
}

/**
   @brief

   @param bitrate_mode
*/
void mcp_2515_base::mcp_2515_init(int bitrate_mode)
{
  mcp2515_.reset();
  switch (bitrate_mode)
  {
    case 0:
      mcp2515_.setBitrate(CAN_5KBPS, MCP_8MHZ);
      break;
    case 1:
      mcp2515_.setBitrate(CAN_10KBPS, MCP_8MHZ);
      break;
    case 2:
      mcp2515_.setBitrate(CAN_20KBPS, MCP_8MHZ);
      break;
    case 3:
      mcp2515_.setBitrate(CAN_40KBPS, MCP_8MHZ);
      break;
    case 4:
      mcp2515_.setBitrate(CAN_50KBPS, MCP_8MHZ);
      break;
    case 5:
      mcp2515_.setBitrate(CAN_80KBPS, MCP_8MHZ);
      break;
    case 6:
      mcp2515_.setBitrate(CAN_100KBPS, MCP_8MHZ);
      break;
    case 7:
      mcp2515_.setBitrate(CAN_125KBPS, MCP_8MHZ);
      break;
    case 8:
      mcp2515_.setBitrate(CAN_200KBPS, MCP_8MHZ);
      break;
    case 9:
      mcp2515_.setBitrate(CAN_250KBPS, MCP_8MHZ);
      break;
    case 10:
      mcp2515_.setBitrate(CAN_500KBPS, MCP_8MHZ);
      break;
    case 11:
      mcp2515_.setBitrate(CAN_1000KBPS, MCP_8MHZ);
      break;
  }

}

/**
   @brief

   @param type 0 : STD 1: EXT
   @param can_id_  11bits / 29bits
   @param dlc data len (max is 8 bytes)
   @param dataarr the data pointer
*/
void mcp_2515_base::mcp_2515_set_sendcanframe(int type , canid_t can_id_ , uint8_t dlc , uint8_t *dataarr )
{
  if (type == 0)
  {
    frame_send_.can_id = can_id_;
    can_type_ = 0;
  }
  else
  {
    frame_send_.can_id = can_id_ | CAN_EFF_FLAG;
    can_type_ = 1;
  }


  frame_send_.can_dlc = dlc;
  for (int i = 0 ; i < dlc ; i++)
  {
    frame_send_.data[i] = dataarr[i];
  }
}

/**
   @brief

   @param mode_
   0 : config mode can set id , filter ....
   1 : need another can controller and reveiver
   2 : can send ande receive msg with self
   3 : only listen another MCP215 msg
*/
void mcp_2515_base::mcp_2515_changemode(int mode_)
{
  switch (mode_)
  {
    case 0 :
      mcp2515_.setConfigMode();
      mcp_2515_base::is_configmode_ = true;
      Serial.println("config flag : " + String(is_configmode_));  
      Serial.println("is config mode");          
      break;
    case 1 :
      mcp2515_.setNormalMode();
      mcp_2515_base::is_configmode_ = false;
      Serial.println("config flag : " + String(is_configmode_));  
      Serial.println("is Normal mode");
      break;
    case 2 :
      mcp2515_.setLoopbackMode();
      mcp_2515_base::is_configmode_ = false;
      Serial.println("config flag : " + String(is_configmode_));  
      Serial.println("is loopback mode");
      break;
    case 3 :
      mcp2515_.setListenOnlyMode();
      mcp_2515_base::is_configmode_ = false;
      Serial.println("config flag : " + String(is_configmode_));  
      Serial.println("is listenonly mode");
      break;
  }
}

/**
   @brief

   @param s
   @return uint32_t  convert result
*/
uint32_t mcp_2515_base::convertStrtoLong(const char *s)
{
  uint32_t x = 0;
  for (;;) {
    char c = *s;
    if (c >= '0' && c <= '9')
    {
      x *= 16;
      x += c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
      x *= 16;
      x += (c - 'A') + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
      x *= 16;
      x += (c - 'a') + 10;
    }
    else break;
    s++;
  }
  return x;
}
/**
   @brief if after set canframe then use this func to senddata on bus

*/
MCP2515::ERROR mcp_2515_base::mcp_2515_sendcanframe()
{
  return mcp2515_.sendMessage(&frame_send_);
}
/**
   @brief

*/
can_frame mcp_2515_base::mcp_2515_rececanframe()
{
  if (mcp2515_.readMessage(&frame_send_) == MCP2515::ERROR_OK)
  {
    Serial.println("Receive Messages");
    if (can_type_ == 0 )
      Serial.println("CAN-Type : STD");
    else
      Serial.println("CAN-Type : EXT");
    Serial.print("CAN ID : ");
    Serial.println(frame_send_.can_id , HEX);
    Serial.print("CAN DLC : ");
    Serial.println(frame_send_.can_dlc , HEX);
    Serial.print("CAN Data : ");
    for (int i = 0 ; i < frame_send_.can_dlc ; i++)
    {
      Serial.print( frame_send_.data[i] , HEX);
      Serial.print(" ");
    }
    Serial.println("");
    return frame_send_;
  }
  else {
  return frame_send_;
  }  
}
/**
  @param RXF_nun is RXFilter num 0-5
  @param is_ext if true , then set EXT
  @param ulData is Filter Data 
*/
MCP2515::ERROR mcp_2515_base::mcp_2515_set_Filter(MCP2515::RXF RXF_num ,bool is_ext , uint32_t ulData  )
{
  if(is_configmode_ == true)  
    return mcp2515_.setFilter(RXF_num, is_ext,ulData);
  else
    return MCP2515::ERROR_FAIL;
}
/**
  @param RXF_nun is RXFilter num 0-5
  @param is_ext if true , then set EXT
  @param ulData is Filter Data 
*/
MCP2515::ERROR mcp_2515_base::mcp_2515_set_Mask(MCP2515::MASK mask , bool is_ext , uint32_t ulData)
{
  if(is_configmode_ == true)   
    return mcp2515_.setFilterMask(mask, is_ext, ulData) ;
  else
    return MCP2515::ERROR_FAIL;
}

}
