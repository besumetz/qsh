#include <boost/iostreams/filter/gzip.hpp>

#include "qshwriter.hpp"
#include "dealsstream_w.hpp"

namespace qsh
{
    namespace writer
    {

        QshWriter::QshWriter(std::string path, bool compress, std::string app_name, std::string comment, pt::ptime rec_dt, uint8_t stream_count)
            : o(nullptr), StreamCount(stream_count)
        {
            file.open(path, std::ios_base::binary);
            //io::filtering_streambuf<io::output> out;
            if (compress) {
                out.push(io::gzip_compressor());
            }
            out.push(file);
            o.rdbuf(&out);
            const char signature[] = "QScalp History Data";
            o.write(signature, std::size(signature) - 1);
            uint8_t ver = 4;
            o.write((char*)&ver, 1);
            dw.Init(o, rec_dt, stream_count > 1);
            dw.WriteString(app_name);
            dw.WriteString(comment);
            dw.WriteDateTime(rec_dt);
            dw.Write(stream_count);
        }

        DealsStreamWriter* QshWriter::CreateDealsStream(Security const& s)
        {
            return new DealsStreamWriter(dw, StreamCount++, s);
        }
        QshWriter::~QshWriter()
        {
            //o.flush();
            //file.flush();
            return;
        }
    }
}