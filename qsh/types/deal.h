#ifndef QSH_DEAL_H
#define QSH_DEAL_H

#include "../headers.h"

namespace qsh {

enum class DealType
{
    Unknown,
    Buy,
    Sell
};

struct Deal
{
    sec_key_t sec_key;
    order_id_t id;
    price_t price;
    qty_t volume;
    DealType type;
    qty_t oi;
    pt::ptime datetime;

    Deal() :
        sec_key(-1),
        id(0),
        price(0),
        volume(0),
        type(DealType::Buy),
        oi(0),
        datetime()
    {}

    Deal(sec_key_t _sec_key, order_id_t _id, price_t _price, qty_t _volume,
         DealType _type, qty_t _oi, const pt::ptime& _datetime) :
        sec_key(_sec_key),
        id(_id),
        price(_price),
        volume(_volume),
        type(_type),
        oi(_oi),
        datetime(_datetime)
    {}
};

bool operator == (Deal const& l, Deal const& r);
bool operator != (Deal const& l, Deal const& r);

}

#endif // QSH_DEAL_H
