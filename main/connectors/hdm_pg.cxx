#include "hdm_pg.hxx"

HdmPostgresConnector::HdmPostgresConnector()
{
    try
    {   
        conn_ = std::make_unique<pqxx::connection>(HdmPostgresConfig::PG_CONNECT_INFO);
    }
    catch (const pqxx::broken_connection& e)
    {   
        std::cerr << "connect info: " << HdmPostgresConfig::PG_CONNECT_INFO << std::endl;
        std::cerr << "postgres connect failed during inialization." << e.what() << std::endl;
    }
}

HdmPostgresConnector::~HdmPostgresConnector()
{
    if (conn_.get() == nullptr)
    {
        conn_.get()->close();
    }
}

bool HdmPostgresConnector::connected() const
{
    return conn_.get() != nullptr && (*conn_).is_open();
}

void HdmPostgresConnector::open()
{
    try {
        conn_.reset(new pqxx::connection(HdmPostgresConfig::PG_CONNECT_INFO));
    } catch (const pqxx::broken_connection& e) {
        throw std::runtime_error(std::string("PostgreSQL connect failed: ") + e.what());
    }
}
