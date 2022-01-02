#ifndef QSH_QUOTE_H
#define QSH_QUOTE_H

#include "../headers.h"
namespace qsh {

enum class QuoteType
{
    Ask,
    Bid
};

struct Quote
{
    quotes_price_t price;
    qty_t volume;
    QuoteType type;

    Quote() :
        price(0),
        volume(0),
        type(QuoteType::Ask)
    {}

    Quote(quotes_price_t _price, qty_t _volume, QuoteType _type) :
        price(_price),
        volume(_volume),
        type(_type)
    {}
};

}

#endif // QSH_QUOTE_H
