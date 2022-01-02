#include "dealsstream_w.hpp"
#include "../types/streamtype.h"
#include "../utils.h"
#include "../types/flags.h"

namespace qsh
{
    namespace writer
    {
        DealsStreamWriter::DealsStreamWriter(DataWriter& dw_, uint8_t sid_, Security const& sec)
            : dw(&dw_)
            , Sec(sec)
            , sid(sid_)
            , lastMilliseconds(0)
            , lastId(0)
            , lastOrderId(0)
            , lastPrice(0)
            , lastVolume(0)
            , lastOI(0)
        {
            dw->Write((uint8_t)StreamType::Deals);
            dw->WriteString(Sec.entry());
        }

        void DealsStreamWriter::Write(pt::ptime dt, Deal const& deal)
        {
            dw->WriteRecHeader(sid, dt);
            auto ms = utils::datetime_to_millisecs(deal.datetime);

            if (!(deal.type == DealType::Buy || deal.type == DealType::Sell))
                throw std::exception("EEE");
            uint8_t flags = (uint8_t)deal.type & (uint8_t)DealFlags::Type;

            if (lastMilliseconds != ms)
                flags |= (uint8_t)DealFlags::DateTime;

            if (deal.id != 0)
                flags |= (uint8_t)DealFlags::Id;

            //if (lastOrderId != deal.OrderId)
            //    flags |= (uint8_t)DealFlags::OrderId;

            int64_t price = (int64_t)std::round(deal.price / Sec.step());

            if (lastPrice != price)
                flags |= (uint8_t)DealFlags::Price;

            if (lastVolume != deal.volume)
                flags |= (uint8_t)DealFlags::Volume;

            if (lastOI != deal.oi)
                flags |= (uint8_t)DealFlags::OI;

            dw->Write(flags);

            if ((flags & (uint8_t)DealFlags::DateTime) != 0)
                dw->WriteGrowing(ms, lastMilliseconds);

            if ((flags & (uint8_t)DealFlags::Id) != 0)
                dw->WriteGrowing(deal.id, lastId);

            //if ((flags & (uint8_t)DealFlags::OrderId) != 0)
            //{
            //    dw->WriteLeb128(deal.OrderId - lastOrderId);
            //    lastOrderId = deal.OrderId;
            //}


            if ((flags & (uint8_t)DealFlags::Price) != 0)
            {
                dw->WriteLeb128((long)price - (long)lastPrice);
                lastPrice = price;
            }

            if ((flags & (uint8_t)DealFlags::Volume) != 0)
            {
                dw->WriteLeb128((long)deal.volume);
                lastVolume = deal.volume;
            }

            if ((flags & (uint8_t)DealFlags::OI) != 0)
            {
                dw->WriteLeb128((long)deal.oi - (long)lastOI);
                lastOI = deal.oi;
            }
        }

        DealsStreamWriter::~DealsStreamWriter()
        {
            return;
        }
    }
}