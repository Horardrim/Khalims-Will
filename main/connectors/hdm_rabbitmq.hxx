#ifndef HDM_RABBITMQ_HXX
#define HDM_RABBITMQ_HXX

#include <iostream>
#include <mutex>

#include <amqp.h>
#include <amqp_tcp_socket.h>

class HdmRabbitMQConnector
{
public:
    HdmRabbitMQConnector() = default;
    ~HdmRabbitMQConnector();

    void connect();

private:
    amqp_connection_state_t conn_;
    std::mutex mtx_;
};

#endif
