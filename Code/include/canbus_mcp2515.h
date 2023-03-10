#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>


namespace mcp_2515
{
  class mcp_2515_base
  {
    public:
      mcp_2515_base();
      ~mcp_2515_base(){delete hspi;};
      void mcp_2515_init(int bitrate_mode);
      void mcp_2515_set_sendcanframe(int type , canid_t can_id_ , uint8_t dlc ,uint8_t *dataarr );
      void mcp_2515_changemode(int mode_);
      uint32_t convertStrtoLong(const char *s);
      MCP2515::ERROR mcp_2515_sendcanframe();
      can_frame mcp_2515_rececanframe();
      MCP2515::ERROR get_readStatus(){return mcp2515_.readMessage(&frame_send_);};
      MCP2515::ERROR mcp_2515_set_Filter(MCP2515::RXF RXF_num ,bool is_ext , uint32_t ulData = 0x0000);
      MCP2515::ERROR mcp_2515_set_Mask(MCP2515::MASK mask , bool is_ext , uint32_t ulData = 0x0000);
      bool get_configflag(){return is_configmode_;};
      
    private:
      const uint8_t mcp2515_CS_ = 15;
      const uint8_t mcp2515_MISO_ = 12;
      const uint8_t mcp2515_MOSI_ = 13;
      const uint8_t mcp2515_CLK_ = 14;
      static const int spiClk = 1000000; //1Mhz
      SPIClass * hspi = NULL;
      MCP2515 mcp2515_;
      struct can_frame frame_send_; //for send
      struct can_frame frame_rece_; //for rece
      int can_type_ = 0;
      bool is_configmode_ = true;
      
  };
}
