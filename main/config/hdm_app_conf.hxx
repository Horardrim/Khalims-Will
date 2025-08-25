#ifndef HDM_APP_CONF_HXX
#define HDM_APP_CONF_HXX

#include <string>
#include <cstdlib>

class HdmAppConfig
{
public:
    static inline std::string APP_NAME = std::getenv("APPLICATION_NAME");

    static inline short APP_PORT = 8080;
};

#endif
