#ifndef QSH_DATAWRITER_HPP
#define QSH_DATAWRITER_HPP
#include <string>
#include "../headers.h"
#include <iostream>

namespace qsh
{
    namespace writer
    {
        class DataWriter
        {
            std::ostream* Out;
            int64_t LastMS;
            int64_t RecordCount;
            bool MultiStreamed;
        public:
            DataWriter();
            void Init(std::ostream& o, pt::ptime rec_dt, bool multistreamed);
            void WriteRecHeader(int sid, pt::ptime dt);
            void WriteLeb128(int64_t value);
            void WriteULeb128(uint32_t value);
            void WriteGrowing(int64_t value, int64_t& last_value);
            void WriteString(std::string const& value);
            void WriteDateTime(pt::ptime value);

            template <typename T>
            void Write(T value)
            {
                Out->write((char*)&value, sizeof(T));
            }
            ~DataWriter();
        };
    }
}
#endif //QSH_DATAWRITER_HPP