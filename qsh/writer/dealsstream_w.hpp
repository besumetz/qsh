#ifndef QSH_DEALSSTREAMWRITER_HPP
#define QSH_DEALSSTREAMWRITER_HPP
#include "../headers.h"
#include "datawriter.hpp"
#include "../security.hpp"
#include "../types/deal.h"

namespace qsh
{
    namespace writer
    {
        class DealsStreamWriter
        {
            DataWriter* dw;
            Security Sec;
            uint8_t sid;

            int64_t lastMilliseconds;
            order_id_t lastId;
            order_id_t lastOrderId;
            int64_t lastPrice;
            qty_t lastVolume;
            qty_t lastOI;

        public:
            DealsStreamWriter(DataWriter& dw_, uint8_t sid_, Security const& sec);
            void Write(pt::ptime dt, Deal const& deal);
            ~DealsStreamWriter();
        };
    }
}
#endif //QSH_DEALSSTREAMWRITER_HPP