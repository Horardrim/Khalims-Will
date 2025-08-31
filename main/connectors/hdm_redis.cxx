#include "hdm_redis.hxx"
#include "../config/hdm_redis_conf.hxx"

HdmRedisConnector::HdmRedisConnector() :
    redisClient_(nullptr)
{
    redisClient_ = redisConnect(HdmRedisConfig::REDIS_HOST.data(), HdmRedisConfig::REDIS_PORT);
}

HdmRedisConnector::~HdmRedisConnector()
{
    redisFree(redisClient_);
}

void HdmRedisConnector::validate()
{
    redisReply *r = (redisReply*)redisCommand(redisClient_, "PING");
    std::cout << "PING: " << r->str << std::endl;
    freeReplyObject(r);
}
