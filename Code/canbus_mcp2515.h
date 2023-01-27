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
      void mcp_2515_set_idtype()
      void mcp_2515_changemode(int mode_);

      
    private:
      const uint8_t mcp2515_CS_ = 15;
      const uint8_t mcp2515_MISO_ = 12;
      const uint8_t mcp2515_MOSI_ = 13;
      const uint8_t mcp2515_CLK_ = 14;
      static const int spiClk = 1000000; //1Mhz
      SPIClass * hspi = NULL;
      MCP2515 mcp2515_;
      struct can_frame frame;

      
  };
}
