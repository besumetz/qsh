#ifndef DEALSTREAAM_R_HPP
#define DEALSTREAAM_R_HPP

#include "../../headers.h"
#include "../iqshstream.hpp"
#include "qshstream.hpp"


namespace qsh {
    namespace reader {
        namespace v4 {


            class DealStreamReader : public QshStream, public IDealStreamReader
            {
            public:
                DealStreamReader(DataReader& data_reader);
#ifdef ORDLOG_PROCESSOR_ENABLED
                //    OrdLogStream(DataReader& data_reader, OrdLogProcessor* proc);
                void read() override;
#else
                void read(bool push_ordlog_entries, bool push_deals, bool push_quotes) override;
#endif

                void handler(const DealHandler& handler) override;

            private:
                DealHandler m_handler;
                uint64_t lastMilliseconds;
                order_id_t lastId;
                order_id_t lastOrderId;
                int lastPrice;
                int lastVolume;
                int lastOI;
            };
        }
    }
}

#endif // !DEALSTREAAM_R_HPP
