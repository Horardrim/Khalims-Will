#ifdef ENABLE_UNIT_TEST

#ifndef HDM_REDIS_TESTS_HXX
#define HDM_REDIS_TESTS_HXX

#include "connectors/hdm_redis.hxx"

class HdmRedisConnectorTest
{
public:
    HdmRedisConnectorTest() = default;
    ~HdmRedisConnectorTest() = default;

    void runTests();

private:
    HdmRedisConnector connector_;
};

#endif
#endif
