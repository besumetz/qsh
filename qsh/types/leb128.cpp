#include "leb128.h"
#include "../exceptions/endofstreamexception.h"

int64_t leb128::read(std::istream& input)
{
    int64_t value = 0;
    uint32_t shift = 0;
    while (true)
    {
        unsigned char byte = 0;
        input.read((char*)&byte, 1);
        if (input.eof())
        {
            throw qsh::EndOfStreamException();
        }
        value |= ((static_cast<int64_t>(byte & 0x7f)) << shift);
        shift += 7;
        if((byte & 0x80) == 0)
        {
            if((shift < sizeof(int64_t) * 8) && ((byte & 0x40) != 0))
            {
                value |= -((static_cast<int64_t>(1)) << shift);
            }
            return value;
        }
    }
}

void leb128::write(std::ostream& output, int64_t value)
{
    if (value >= 0)
        for (; ; )
        {
            int b = (int)(value & 0x7f);
            value >>= 7;

            if (value == 0 && (b & 0x40) == 0)
            {
                uint8_t byte = (uint8_t)b;
                output.write((char*)&byte, 1);//WriteByte((byte)b);
                return;
            }

            //stream.WriteByte((byte)(b | 0x80));
            uint8_t byte = b | 0x80;
            output.write((char*)(&byte), 1);
        }
    else
        for (; ; )
        {
            int b = (int)(value & 0x7f);
            value >>= 7;

            if (value == -1 && (b & 0x40) != 0)
            {
                //stream.WriteByte((byte)b);
                uint8_t byte = (uint8_t)b;
                output.write((char*)&byte, 1);
                return;
            }

            //stream.WriteByte((byte)(b | 0x80));
            uint8_t byte = b | 0x80;
            output.write((char*)&byte, 1);
        }
}