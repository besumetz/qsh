#ifndef RAWQUOTES_H
#define RAWQUOTES_H

//#define QUOTES_USE_VECTOR

#include "../headers.h"
#include "quote.h"

namespace qsh {

class RawQuotes
{
public:
    RawQuotes();
    void clear();
    qty_t& operator[] (quotes_price_t key);
    void remove(quotes_price_t key);
    std::vector<Quote> quotes(size_t limit);

private:
    std::map<quotes_price_t, qty_t, std::greater<quotes_price_t>> m_quotes;
};

/*
class RawQuotes2
{
public:
    RawQuotes2();
    void clear();
    int& operator[] (int key);
    void remove(int key);
    std::vector<Quote> quotes(size_t limit);

private:
    std::vector<int> m_quotes;
};
*/
}

#endif // RAWQUOTES_H
