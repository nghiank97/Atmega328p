
#include "bee.h"

static uint8_t Modbus::cvt_to_ascii(uint8_t b_hex)
{
    if (b_hex < 0x0A)
        return (b_hex + 48);
    else
        return (b_hex + 55);
}

static uint16_t Modbus::split_to_ascii(uint8_t b_hex)
{
    uint8_t h, l;
    uint16_t nibble;
    l = cvt_to_ascii(b_hex & 0x0F);
    h = cvt_to_ascii((b_hex >> 4) & 0x0F);
    return (uint16_t)h * 256 + l;
}

static void Modbus::print(HardwareSerial *port, uint8_t *frame, size_t len)
{
    int i;
    uint16_t nibble;
    uint8_t lrc_error = 0x00;
    port->write(':');
    for (i = 0; i < len; i++)
    {
        nibble = split_to_ascii(frame[i]);
        port->word(nibble);
        lrc_error += frame[i];
    }
    lrc_error = 255 - lrc_error + 1;
    nibble = split_to_ascii(lrc_error);
    port->word(nibble);
    port->write(0x0D);
    port->write(0x0A);
}

static void Modbus::sent_responce(HardwareSerial *port, uint8_t *frame, size_t len)
{
    port->write(':');
    for (size_t i = 0; i < len; i++)
    {
        port->write(frame[i]);
    }
    port->write(0x0D);
    port->write(0x0A);
}

static uint8_t Modbus::cvt_to_hex(uint8_t d_ascii)
{
    if (('0' <= d_ascii) && (d_ascii <= '9'))
        return (d_ascii - 48);
    else if (('a' <= d_ascii) && (d_ascii <= 'f'))
        return (d_ascii - 87);
    else if (('A' <= d_ascii) && (d_ascii <= 'F'))
        return (d_ascii - 55);
    return 0x00;
}

static uint8_t Modbus::merge_to_hex(uint8_t h_nibble, uint8_t l_nibble)
{
    uint8_t result = (cvt_to_hex(h_nibble) << 4) & 0xF0;
    result += cvt_to_hex(l_nibble);
    return result;
}

static bool Modbus::check_lrc(uint8_t *frame, size_t len)
{
    int i;
    uint8_t sum = 0x00;
    uint8_t lrc;
    for (i = 1; i < len - 4; i += 2)
    {
        sum += merge_to_hex(frame[i], frame[i + 1]);
    }
    sum = 255 - sum + 1;
    lrc = merge_to_hex(frame[len - 3], frame[len - 2]);
    if (sum == lrc)
        return true;
    return false;
}

static uint8_t Modbus::get_lrc(uint8_t *frame, size_t len)
{
    int i;
    uint8_t lrc = 0x00;
    for (i = 1; i < len; i += 2)
    {
        lrc += merge_to_hex(frame[i], frame[i + 1]);
    }
    lrc = 255 - lrc + 1;
    return lrc;
}
