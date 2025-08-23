#include "hdm_http_srv.hxx"

#include "api/hdm_app_info_api.hxx"

HdmHttpSrv::HdmHttpSrv()
{
    registerAPI<HdmAppInfoAPI>();
}

void HdmHttpSrv::listen()
{
    srv_.listen(HTTP_HOST, 8088);
}

void HdmHttpSrv::stop()
{
    srv_.stop();
}
