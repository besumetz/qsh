#include "exception.h"
#include <cstring>

Exception::Exception()
{
}

Exception::Exception(const char* msg)
{
#pragma warning(suppress : 4996)
    strcpy(m_msg, msg);
}

const char* Exception::what() const noexcept
{
    return m_msg;
}

