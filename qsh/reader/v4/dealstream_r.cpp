#include "dealstream_r.hpp"
#include "../../types/flags.h"
namespace qsh
{
    namespace reader
    {
        namespace v4
        {
            DealStreamReader::DealStreamReader(DataReader& data_reader)
                : QshStream(data_reader, StreamType::Deals)
                , m_handler(nullptr)
                , lastMilliseconds(0)
                , lastId(0)
                , lastOrderId(0)
                , lastPrice(0)
                , lastVolume(0)
                , lastOI(0)
            {
            }

            void DealStreamReader::read()
            {
                uint8_t flags = m_data_reader->read_byte();

                // ------------------------------------------------------------

                if ((flags & (uint8_t)DealFlags::DateTime) != 0)
                    lastMilliseconds = m_data_reader->read_growing(lastMilliseconds);

                if ((flags & (uint8_t)DealFlags::Id) != 0)
                    lastId = m_data_reader->read_growing(lastId);

                if ((flags & (uint8_t)DealFlags::OrderId) != 0)
                    lastOrderId += m_data_reader->read_leb128();

                if ((flags & (uint8_t)DealFlags::Price) != 0)
                    lastPrice += (int)m_data_reader->read_leb128();

                double price = security().step() * lastPrice;

                if ((flags & (uint8_t)DealFlags::Volume) != 0)
                    lastVolume = (int)m_data_reader->read_leb128();

                if ((flags & (uint8_t)DealFlags::OI) != 0)
                    lastOI += (int)m_data_reader->read_leb128();

                // ------------------------------------------------------------

                if (m_handler)
                    m_handler(Deal(
                        security().key(),
                        lastId,
                        price,
                        lastVolume,
                        (DealType)(flags & (uint8_t)DealFlags::Type),
                        lastOI,
                        utils::datetime_from_millisecs(lastMilliseconds)));
            }
            void DealStreamReader::handler(const DealHandler& handler)
            {
                m_handler = handler;
            }
        }
    }

}