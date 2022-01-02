#include "deal.h"

namespace qsh {
    bool operator==(Deal const& l, Deal const& r)
    {
        return
            l.datetime == r.datetime &&
            l.id == r.id &&
            l.oi == r.oi &&
            l.price == r.price &&
            l.sec_key == r.sec_key &&
            l.type == r.type &&
            l.volume == r.volume;
    }
    bool operator!=(Deal const& l, Deal const& r)
    {
        return
            l.datetime != r.datetime ||
            l.id != r.id ||
            l.oi != r.oi ||
            l.price != r.price ||
            l.sec_key != r.sec_key ||
            l.type != r.type ||
            l.volume != r.volume;
    }
}

