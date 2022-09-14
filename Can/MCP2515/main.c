
#include "elephant.h"

uint8_t rx_data[20];
uint8_t len = 0;
uint8_t status = 0;

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    serial_init(9600);
    serial_print("hello world\r\n",13);

    mcp2515_init();
    while (1)
    {
        status = mcp2515_read_status(MCP_CANCTRL);
        len = sprintf(rx_data,"%02x \r\n",status);
        serial_print(rx_data,len);

        serial_print("nghia \r\n",8);
        delay_ms(1000);
    }
    return 1;
}