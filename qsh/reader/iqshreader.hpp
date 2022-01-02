#ifndef IQSHREADER_HPP
#define IQSHREADER_HPP

#include "../headers.h"

namespace qsh {
namespace reader {

class IQshReader
{
public:
    virtual ~IQshReader() {}
    virtual std::string app_name() const = 0;
    virtual std::string comment() const = 0;
    virtual pt::ptime header_datetime() const = 0;
    virtual pt::ptime datetime() const = 0;
    virtual std::vector<IQshStream*> streams() const = 0;
    virtual size_t streams_count() const = 0;
    virtual bool eof() const = 0;
#ifdef ORDLOG_PROCESSOR_ENABLED
    virtual void read() = 0;
#else
    virtual void read(bool push_ordlog_entries, bool push_deals, bool push_quotes) = 0;
#endif
};

}
}

#endif // IQSHREADER_HPP
