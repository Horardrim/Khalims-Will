#ifndef HDM_REDIS_CONF_HXX
#define HDM_REDIS_CONF_HXX

#include <string>
#include <cstdlib>

class HdmRedisConfig
{
public:
    static inline const std::string REDIS_HOST = std::getenv("REDIS_HOST");
    static inline const short REDIS_PORT = atoi(std::getenv("REDIS_PORT"));
};

#endif
