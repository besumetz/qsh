#ifndef ULEB128_H
#define ULEB128_H

#include <istream>

class uleb128
{
public:
    static const uint32_t Max1BValue = 127;
    static const uint32_t Max2BValue = 16383;
    static const uint32_t Max3BValue = 2097151;
    static const uint32_t Max4BValue = 268435455;

    static uint32_t read(std::istream& input);
    static void write(std::ostream& output, uint32_t value);
};

#endif // ULEB128_H
