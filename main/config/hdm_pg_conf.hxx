#ifndef HDM_PG_CONF_HXX
#define HDM_PG_CONF_HXX

#include <string>
#include <cstdlib>

class HdmPostgresConfig
{
private:
    // host followed by host name, IPv4 and IPv6
    static inline const std::string PG_HOST = std::string("host=") + std::getenv("POSTGRES_HOST") + " ";
    static inline const std::string PG_PORT = std::string("port=") + std::getenv("POSTGRES_PORT") + " ";
    static inline const std::string PG_DATABASE = std::string("dbname=") + std::getenv("POSTGRES_DATABASE") + " ";
    static inline const std::string PG_USERNAME = std::string("user=") + std::getenv("POSTGRES_USERNAME") + " ";
    static inline const std::string PG_PASSWD = std::string("password=") + std::getenv("POSTGRES_PASSWD");

public:
    static inline const std::string PG_CONNECT_INFO = PG_HOST + PG_PORT + PG_DATABASE + PG_USERNAME + PG_PASSWD;
};

#endif
