#ifndef HDM_PG_HXX
#define HDM_PG_HXX

#include <iostream>
#include <mutex>

#include <pqxx/pqxx>

#include "../config/hdm_pg_conf.hxx"

class HdmPostgresConnector
{
public:
    HdmPostgresConnector();

    ~HdmPostgresConnector();

    HdmPostgresConnector(const HdmPostgresConnector &) = delete;

    HdmPostgresConnector & operator=(const HdmPostgresConnector &) = delete;

    HdmPostgresConnector(HdmPostgresConnector&&) noexcept = default;

    HdmPostgresConnector& operator=(HdmPostgresConnector&&) noexcept = default;

    bool connected() const;

    template <typename Func>
    auto with_tx(Func&& f) -> decltype(f(std::declval<pqxx::work&>())) {
        std::lock_guard<std::mutex> lk(mtx_);
        try {
            if (!conn_ || !conn_->is_open())
            {   
                open();      // 断线重连
            }
            pqxx::work tx(*conn_);
            auto ret = f(tx);
            tx.commit();
            return ret;
        } catch (const pqxx::broken_connection&) {
            // 网络/服务器断，尝试一次重连
            open();
            throw;                                       // 重新抛出让调用者知道
        }
    }

private:
    std::unique_ptr<pqxx::connection> conn_;

    std::mutex mtx_;

    void open();
};

#endif
