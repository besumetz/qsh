#include "datawriter.hpp"
#include "../utils.h"
#include "../types/leb128.h"
#include "../types/uleb128.h"

namespace qsh
{
    namespace writer
    {
        DataWriter::DataWriter()
            : Out(nullptr)
            , LastMS(0)
            , RecordCount(0)
            , MultiStreamed(false)
        {
        }

        void DataWriter::Init(std::ostream& o, pt::ptime rec_dt, bool multistreamed)
        {
            Out = &o;
            LastMS = utils::datetime_to_millisecs(rec_dt);
            RecordCount = 0;
            MultiStreamed = multistreamed;
        }

        void DataWriter::WriteRecHeader(int sid, pt::ptime dt)
        {
            WriteGrowing(utils::datetime_to_millisecs(dt), LastMS);
            if (MultiStreamed)
                Write((uint8_t)sid);
            ++RecordCount;
        }

        void DataWriter::WriteLeb128(int64_t value)
        {
            leb128::write(*Out, value);
        }

        void DataWriter::WriteULeb128(uint32_t value)
        {
            uleb128::write(*Out, value);
        }

        void DataWriter::WriteGrowing(int64_t value, int64_t& last_value)
        {
            int64_t offset = value - last_value;
            if (offset >= uleb128::Max4BValue || offset < 0)
            {
                uleb128::write(*Out, uleb128::Max4BValue);
                leb128::write(*Out, offset);
            }
            else
                uleb128::write(*Out, (uint32_t)offset);

            last_value = value;
        }

        void DataWriter::WriteString(std::string const& value)
        {
            uint32_t l = (uint32_t)value.length();
            WriteULeb128(l);
            Out->write(value.data(), l);
        }

        void DataWriter::WriteDateTime(pt::ptime value)
        {
            const int64_t csharp_1900_ticks = 599266080000000000L;
            pt::ptime epoch(gr::date(1900, gr::Jan, 1));
            int64_t ticks = (value - epoch).total_microseconds() * 10 + csharp_1900_ticks;
            Write(ticks);
        }

        DataWriter::~DataWriter()
        {
            return;
        }

        /*
        boost::posix_time::ptime read_datetime()
        {
            const int64_t csharp_1900_ticks = 599266080000000000L;
            int64_t ticks;
            m_input->read(utils::pointer_cast<char*>(&ticks), sizeof(ticks));
            ticks -= csharp_1900_ticks;
            pt::ptime epoch(gr::date(1900, gr::Jan, 1));
            return epoch + pt::microseconds(ticks / 10);
        }
        */
    }
}