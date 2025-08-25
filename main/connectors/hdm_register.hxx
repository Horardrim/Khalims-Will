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
    HdmRegCenConnector();

    ~HdmRegCenConnector();

    void Register() const;

    void heartbeat() const;

    void unregister() const;

private:
    const std::string registerUrl_;

    const std::string registerAppUrl_;

    CURL *curl_;

    bool performRegister(const std::string& url, const std::string& body) const;
};

#endif
