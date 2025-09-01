#ifdef ENABLE_UNIT_TEST

#ifndef HDM_RABBITMQ_TESTS_HXX
#define HDM_RABBITMQ_TESTS_HXX

#include "connectors/hdm_rabbitmq.hxx"

class HdmRabbitMQConnectorTest
{
public:
    HdmRabbitMQConnectorTest() = default;
    ~HdmRabbitMQConnectorTest() = default;

    void runTests();

private:
    HdmRabbitMQConnector connector_;
};

#endif
#endif
