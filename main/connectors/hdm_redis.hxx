#ifndef HDM_REDIS_HXX
#define HDM_REDIS_HXX

#include <hiredis/hiredis.h>
#include <mutex>
#include <iostream>

class HdmRedisConnector
{
public:
    HdmRedisConnector();
    ~HdmRedisConnector();
    void validate();

private:
    redisContext *redisClient_;
    std::mutex mtx_;
};

#endif
