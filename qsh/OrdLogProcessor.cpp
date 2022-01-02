#include "OrdLogProcessor.h"
#include "../qsh/qsh.hpp"
#include "Cfg.h"


namespace qsh
{
    OrdLogProcessor::OrdLogProcessor() :
        //m_last_deal_id(0),
        //m_last_pushed_deal_id(0),
        EnableGetQuotes(false),
        UseQuotes(false),
        m_last_deal_id2(0)
    {
    }

    template <typename T>
    void raw_copy(T* src, T* dst)
    {
        memcpy(dst, src, sizeof(T));
    }

    //qsh::Deal* OrdLogProcessor::AcceptOrdLogEntry(u_int64_t sec_key, qsh::OrdLogEntry const& ord_log_entry)
    std::optional<qsh::Deal>  OrdLogProcessor::AcceptOrdLogEntry(uint64_t sec_key, qsh::OrdLogEntry const &ord_log_entry)
    {
        std::optional<qsh::Deal> ret_deal;

        qsh::OrdLogFlags ordLogFlags = ord_log_entry.flags();
        bool is_add = ((ordLogFlags & qsh::OrdLogFlags::Add) != 0);
        bool is_fill = ((ordLogFlags & qsh::OrdLogFlags::Fill) != 0);

        bool is_buy = ((ordLogFlags & qsh::OrdLogFlags::Buy) != 0);
        bool is_sell = ((ordLogFlags & qsh::OrdLogFlags::Sell) != 0);

        if ((ordLogFlags & qsh::OrdLogFlags::SessIdChanged) != 0)
        {
            m_raw_quotes.clear();
        }

        if (!(is_buy ^ is_sell)
            || ((ordLogFlags & qsh::OrdLogFlags::NonSystem) != 0)
            || ((ordLogFlags & qsh::OrdLogFlags::NonZeroReplAct) != 0))
        {
            return ret_deal;
        }

        if (UseQuotes)
        {
            qsh::qty_t quantity = m_raw_quotes[ord_log_entry.price()];

            if (is_add ? is_sell : is_buy)
                quantity += ord_log_entry.amount();
            else
                quantity -= ord_log_entry.amount();

            if (quantity == 0)
                m_raw_quotes.remove(ord_log_entry.price());
            else
                m_raw_quotes[ord_log_entry.price()] = quantity;

            if ((ordLogFlags & qsh::OrdLogFlags::EndOfTransaction) != 0)
            {
                EnableGetQuotes = true;
            }
            else
            {
                EnableGetQuotes = false;
            }
        }

        //if (OrdLogEntryHandler)
        //{
        //    OrdLogEntryHandler->AcceptOrdLogEntry(sec_key, ord_log_entry);
        //}

        //if (DealHandler && m_last_pushed_deal_id < ord_log_entry.deal_id())
        /*
        Сделку отправляем по факту завершения сделки у не неиницилизатора (по второй сделке с тем же номером)
        */

        //qsh::Deal* ret_deal = nullptr;
        if (m_last_deal_id2 && m_last_deal_id2 == ord_log_entry.deal_id())
        {
             LastDeal = qsh::Deal(sec_key,
                ord_log_entry.deal_id(),
                ord_log_entry.deal_price(),
                ord_log_entry.amount(),
//                is_sell ? qsh::DealType::Sell : qsh::DealType::Buy, //это если отправлять по первой сделке
                is_sell ? qsh::DealType::Buy : qsh::DealType::Sell, //так как отправляем по второй сделке
                ord_log_entry.oi(),
                ord_log_entry.datetime());
            ret_deal = LastDeal;
//            m_last_pushed_deal_id = ord_log_entry.deal_id();
        }
        m_last_deal_id2 = ord_log_entry.deal_id();
        return ret_deal;
    }

    std::vector<qsh::Quote> OrdLogProcessor::GetQuotes(size_t q_count)
    {
        if (EnableGetQuotes)
            return m_raw_quotes.quotes(q_count);
        else
            return std::vector<qsh::Quote>();

    }

    void OrdLogProcessor::Init(bool use_quotes)
    {
        UseQuotes = use_quotes;
        m_raw_quotes.clear();
        //m_last_pushed_deal_id = 0;
        EnableGetQuotes = false;
        m_last_deal_id2 = 0;
    }

} //namespace afbt