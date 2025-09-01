#ifndef HDM_RABBITMQ_CONF_HXX
#define HDM_RABBITMQ_CONF_HXX

#include <string>
#include <cstdlib>

class HdmRabbitMQConfig
{
public:
    static inline const std::string RABBITMQ_HOST = std::getenv("RABBITMQ_HOST");
    static inline const short RABBITMQ_PORT = atoi(std::getenv("RABBITMQ_PORT"));
    static inline const std::string RABBITMQ_USER = std::getenv("RABBITMQ_USER");
    static inline const std::string RABBITMQ_PASSWD = std::getenv("RABBITMQ_PASSWD");
    static inline const std::string RABBITMQ_VIRTUAL_HOST = "/";
};

#endif
