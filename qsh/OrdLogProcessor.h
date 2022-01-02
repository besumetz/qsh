#pragma once
//#include <string>
//#include <vector>
#include <optional>
//#include "../qsh/security.hpp"
#include "types/rawquotes.h"
#include "types/ordlogentry.h"
//#include "Types.h"


namespace qsh
{
    class OrdLogProcessor
    {
        //int64_t m_last_millisecs;
        //int64_t m_last_order_id;
        //int m_last_price;
        //int m_last_amount;
        //int m_last_amount_rest;
        //int64_t m_last_deal_id;
        //int m_last_deal_price;
        //int m_last_oi;
        qsh::RawQuotes m_raw_quotes;
        //pt::ptime m_last_stock_push;
        //int64_t m_last_pushed_deal_id;
        bool EnableGetQuotes;
        bool UseQuotes;
        qsh::order_id_t m_last_deal_id2;
        qsh::Deal LastDeal;
    public:
        OrdLogProcessor();
        OrdLogProcessor(OrdLogProcessor const&) = delete;
        OrdLogProcessor& operator =(OrdLogProcessor&) = delete;

        std::optional<qsh::Deal> AcceptOrdLogEntry(uint64_t sec_key, qsh::OrdLogEntry const& ord_log_entry);
        std::vector<qsh::Quote> GetQuotes(size_t q_count);
        void Init(bool use_quotes);
    };

    //struct LoadDealsResult
    //{
    //    std::vector<qsh::Deal> Deals;
    //    qsh::StreamType StreamType;
    //    qsh::Security Sec;
    //};

    //std::vector<qsh::OrdLogEntry> LoadOrdLogFromFile(std::string const& path, size_t reserve);
    //LoadDealsResult LoadDealsFromQshFile(std::string const& path, size_t reserve);
}//namespace qsh

