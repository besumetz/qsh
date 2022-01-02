#ifndef QSH_WRITER_HPP
#define QSH_WRITER_HPP
#include <fstream>
#include <boost/iostreams/filtering_streambuf.hpp>

#include "../headers.h"
#include "../security.hpp"
#include "datawriter.hpp"


namespace qsh
{
    namespace writer
    {
        class QshWriter
        {
            std::ofstream file;
            std::ostream o;
            io::filtering_streambuf<io::output> out;
            DataWriter dw;
            uint8_t StreamCount;
        public:
            QshWriter(std::string path, bool compress, std::string app_name, std::string comment, pt::ptime rec_dt, uint8_t stream_count);
            DealsStreamWriter* CreateDealsStream(Security const& s);
            ~QshWriter();
        };

    }
}
#endif //QSH_WRITER_HPP