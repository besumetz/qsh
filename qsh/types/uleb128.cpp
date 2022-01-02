#include "uleb128.h"
#include "../exceptions/endofstreamexception.h"

uint32_t uleb128::read(std::istream& input)
{
    uint32_t value = 0;
    uint32_t shift = 0;
    while (true)
    {
        unsigned char byte = 0;
        input.read((char*)(&byte), 1);
        if (input.eof())
        {
            throw qsh::EndOfStreamException();
        }
        value |= ((static_cast<int64_t>(byte & 0x7f)) << shift);
        if((byte & 0x80) == 0)
        {
            return value;
        }
        shift += 7;
    }
}

void uleb128::write(std::ostream& output, uint32_t value)
{
    while (value > 127)
    {
        uint8_t byte = value | 0x80;
        //stream.WriteByte((byte)(value | 0x80));
        output.write((char*)&byte, 1);
        value >>= 7;
    }

    //stream.WriteByte((byte)value);
    uint8_t byte = (uint8_t)value;
    output.write((char*)&byte, 1);
}

