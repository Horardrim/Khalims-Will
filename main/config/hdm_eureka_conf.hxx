#ifndef HDM_EUREKA_CONF_HXX
#define HDM_EUREKA_CONF_HXX

#include <string>
#include <cstdlib>

class HdmEurekaConfig
{
public:
    static inline std::string EUREKA_HOST = std::getenv("EUREKA_HOST");
    static inline short EUREKA_PORT = atoi(std::getenv("EUREKA_PORT"));
};

#endif
