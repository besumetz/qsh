#ifndef ORDLOGSTREAM_HPP
#define ORDLOGSTREAM_HPP

#include "../../headers.h"
#include "../iqshstream.hpp"
#include "qshstream.hpp"

#ifdef ORDLOG_PROCESSOR_ENABLED
//#include "OrdLogProcessor.h"
#endif

namespace qsh {
namespace reader {
namespace v4 {


class OrdLogStream : public QshStream, public IOrdLogStream
{
public:
    OrdLogStream(DataReader& data_reader);
#ifdef ORDLOG_PROCESSOR_ENABLED
//    OrdLogStream(DataReader& data_reader, OrdLogProcessor* proc);
    void read() override;
#else
    void read(bool push_ordlog_entries, bool push_deals, bool push_quotes) override;
#endif

    void handler(const OrdLogHandler& handler) override;
#ifdef ORDLOG_PROCESSOR_ENABLED
//    void set_OrdLogProcessor(OrdLogProcessor* proc) override;
#else
    void deal_handler(const DealHandler& handler) override;
    void stock_handler(const StockHandler& handler) override;
    std::vector<Quote> quotes() const override;
#endif

private:
    OrdLogHandler m_handler;
#ifdef ORDLOG_PROCESSOR_ENABLED
#else
    DealHandler m_deal_handler;
    StockHandler m_stock_handler;
#endif
    millisec_t m_last_millisecs;
    order_id_t m_last_order_id;
    int64_t m_last_price;
    qty_t m_last_amount;
    qty_t m_last_amount_rest;
    order_id_t m_last_deal_id;
    price_t m_last_deal_price;
    qty_t m_last_oi;
    RawQuotes m_raw_quotes;
#ifdef ORDLOG_PROCESSOR_ENABLED
//    OrdLogProcessor *OrdLogProcessorPtr;
#else
    pt::ptime m_last_stock_push;
    order_id_t m_last_pushed_deal_id;
    pt::time_duration m_stock_push_interval;
    std::vector<Quote> m_quotes;
#endif
};

}
}
}

#endif // ORDLOGSTREAM_HPP
