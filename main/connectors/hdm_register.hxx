#ifndef HDM_REGISTER_HXX
#define HDM_REGISTER_HXX

#include <string>
#include <iostream>

#include <curl/curl.h>

#include "../config/hdm_eureka_conf.hxx"
#include "../config/hdm_app_conf.hxx"

class HdmRegCenConnector
{
public:
    HdmRegCenConnector() = default;

    ~HdmRegCenConnector() = default;

    void connect();

    void heartbeat() const;

private:
    std::string registerCenterUrl_;

    void registerWithUrl(const std::string& url, const short& port);

    void unregisterWithUrl(const std::string& url, const short& port) const;

    bool perform(const std::string& method, const std::string& url, const std::string& body) const;
};

#endif
