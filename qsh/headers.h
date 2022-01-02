#ifndef QSH_HEADERS_H
#define QSH_HEADERS_H

#include <memory>
#include <string>
#include <istream>
#include <vector>
#include <map>
#include <functional>

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#define ORDLOG_PROCESSOR_ENABLED

namespace qsh {
    using sec_key_t = uint64_t;
    using price_t = double;
    using quotes_price_t = int64_t;
    using order_id_t = int64_t;
    using qty_t = int64_t;
    using millisec_t = int64_t;
    namespace io = boost::iostreams;
    namespace pt = boost::posix_time;
    namespace gr = boost::gregorian;
    namespace reader {
        class IQshReader;
        class IQshStream;
        class ISecurityStream;
        class QshReader;
        namespace v4 {
            class DataReader;
            class QshReaderImpl;
            class QshStream;
            class OrdLogStream;
            class DealStreamReader;
#ifdef ORDLOG_PROCESSOR_ENABLED
            //class OrdLogProcessor;
            //class IOrdLogEntryHandler;
            //class IDealHandler;
#else
#endif
        }
    }
    namespace writer {
        class QshWriter;
        class DataWriter;
        class DealsStreamWriter;
    }
    enum class StreamType;
    class Security;
    class OrdLogEntry;
    enum class DealFlags;
    enum class OrderFlags;
    enum class AuxInfoFlags;
    enum class OrdLogEntryFlags;
    enum class OrdLogFlags;
    class RawQuotes;
    struct Quote;
    enum class QuoteType;
    struct Deal;
    enum class DealType;
}

#endif // QSH_HEADERS_H
