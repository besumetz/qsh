#ifndef QSH_ORDLOGENTRY_H
#define QSH_ORDLOGENTRY_H

#include "../headers.h"
#include "types.h"

namespace qsh {

class OrdLogEntry
{
public:
    OrdLogEntry(OrdLogFlags flags, const pt::ptime& datetime, order_id_t order_id,
                int64_t price, qty_t amount, qty_t amount_rest, order_id_t deal_id,
                price_t deal_price, qty_t oi) :
        m_flags(flags),
        m_datetime(datetime),
        m_order_id(order_id),
        m_price(price),
        m_amount(amount),
        m_amount_rest(amount_rest),
        m_deal_id(deal_id),
        m_deal_price(deal_price),
        m_oi(oi)
    {
    }

    OrdLogFlags flags() const { return m_flags; }
    pt::ptime datetime() const { return m_datetime; }
    order_id_t order_id() const { return m_order_id; }
    int64_t price() const { return m_price; }
    qty_t amount() const { return m_amount; }
    qty_t amount_rest() const { return m_amount_rest; }
    order_id_t deal_id() const { return m_deal_id; }
    price_t deal_price() const { return m_deal_price; }
    qty_t oi() const { return m_oi; }

private:
    OrdLogFlags m_flags;
    pt::ptime m_datetime;
    order_id_t m_order_id;
    int64_t m_price;
    qty_t m_amount;
    qty_t m_amount_rest;
    order_id_t m_deal_id;
    price_t m_deal_price;
    qty_t m_oi;

};

}

#endif // QSH_ORDLOGENTRY_H
