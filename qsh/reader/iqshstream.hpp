#ifndef IQSHSTREAM_HPP
#define IQSHSTREAM_HPP

#include "../headers.h"
#include "../security.hpp"
#include "../types/types.h"

#ifdef ORDLOG_PROCESSOR_ENABLED
//#include "../reader/v4/OrdLogProcessor.h"
#endif

namespace qsh {
namespace reader {

class IQshStream
{
public:
    virtual ~IQshStream() = default;
    virtual StreamType type() const = 0;
#ifdef ORDLOG_PROCESSOR_ENABLED
    virtual void read() = 0;
#else
    virtual void read(bool push_ordlog_entries, bool push_deals, bool push_quotes) = 0;
#endif
};

class ISecurityStream : public IQshStream
{
public:
    virtual ~ISecurityStream() = default;
    virtual Security security() const = 0;
};


using OrdLogHandler = std::function<void(uint64_t, OrdLogEntry const&&)>;
using DealHandler = std::function<void(const Deal&)>;

#ifdef ORDLOG_PROCESSOR_ENABLED
#else
typedef std::function<void(uint64_t, const std::vector<Quote>&)> StockHandler;
#endif

class IOrdLogStream
{
public:
    virtual ~IOrdLogStream() = default;
    virtual void handler(const OrdLogHandler& handler) = 0;
#ifdef ORDLOG_PROCESSOR_ENABLED
//    virtual void set_OrdLogProcessor(v4::OrdLogProcessor* proc) = 0;
#else
    virtual void deal_handler(const DealHandler& handler) = 0;
    virtual void stock_handler(const StockHandler& handler) = 0;
    virtual std::vector<Quote> quotes() const = 0;
#endif
};

class IDealStreamReader
{
public:
    virtual ~IDealStreamReader() = default;
    virtual void handler(const DealHandler& handler) = 0;
};

}
}

#endif // IQSHSTREAM_HPP
