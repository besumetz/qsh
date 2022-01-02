#ifndef QSH_SECURITY_HPP
#define QSH_SECURITY_HPP

#include "headers.h"

namespace qsh {

class Security
{
public:
    Security();
    Security(const std::string& entry);
    void entry(const std::string& entry);
    sec_key_t key() const;
    std::string entry() const;
    double price(int ticks) const;
    std::string ticker() const;
    double step() const;

public:
    static sec_key_t get_key(const std::string& cname);
    static sec_key_t get_key(uint64_t ckey, int id);
    static sec_key_t get_key(uint64_t ckey, const std::string& ticker);
    static sec_key_t get_key(uint64_t ckey, const std::string& ticker, const std::string& aux_code);

private:
    void init_key();
    void reset(const std::string& state);

private:
    std::string m_entry;
    std::string m_cname;
    std::string m_ticker;
    std::string m_aux_code;
    int m_id;
    double m_step;
    sec_key_t m_key;
};

}

#endif // QSH_SECURITY_HPP
