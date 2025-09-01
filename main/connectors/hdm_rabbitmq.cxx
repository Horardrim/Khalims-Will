

#include "hdm_rabbitmq.hxx"
#include "../config/hdm_rabbitmq_conf.hxx"

HdmRabbitMQConnector::~HdmRabbitMQConnector()
{
    amqp_channel_close(conn_, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn_, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn_);
}

void HdmRabbitMQConnector::connect()
{
    // socket 会在amqp_destroy_connection时被释放
    conn_ = amqp_new_connection();
    amqp_socket_t *rabbitmqSocket = amqp_tcp_socket_new(conn_);
    if (rabbitmqSocket == nullptr)
    {
        std::cerr << "failed to create amqp tcp socket" << std::endl;
        return;
    }

    // try to connect rabbit mq.
    if (amqp_socket_open(rabbitmqSocket, HdmRabbitMQConfig::RABBITMQ_HOST.data(), HdmRabbitMQConfig::RABBITMQ_PORT))
    {
        std::cerr << "failed to connect to rabbitMQ host: " << HdmRabbitMQConfig::RABBITMQ_HOST <<
            " port: " << HdmRabbitMQConfig::RABBITMQ_PORT << std::endl;
        return;
    }

    // login rabbitmq with given virtaul host, user and password
    amqp_rpc_reply_t r = amqp_login(conn_, HdmRabbitMQConfig::RABBITMQ_VIRTUAL_HOST.data(),
        0, 131072, 0, AMQP_SASL_METHOD_PLAIN,
        HdmRabbitMQConfig::RABBITMQ_USER.data(),
        HdmRabbitMQConfig::RABBITMQ_PASSWD.data());

    // error handling of rabbit mq login
    if (r.reply_type != AMQP_RESPONSE_NORMAL)
    {
        std::cerr << "failed to login with virtual host: " << HdmRabbitMQConfig::RABBITMQ_VIRTUAL_HOST
            << " user:" << HdmRabbitMQConfig::RABBITMQ_USER
            << " password:" << HdmRabbitMQConfig::RABBITMQ_PASSWD
            << std::endl;
        return;
    }

    std::cout << "RabbitMQ is ready!" << std::endl;
}
