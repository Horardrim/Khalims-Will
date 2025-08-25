#ifndef HDM_APP_INFO_API_HXX
#define HDM_APP_INFO_API_HXX

#include "httplib.h"

extern bool ON_GOINE_G;

class HdmAppInfoAPI
{
public:
    HdmAppInfoAPI() = delete;
    ~HdmAppInfoAPI() = delete;
    static void registerAPI(httplib::Server & srv);

private:
    static inline auto REGISTER_HEALTH_API = [](const auto& req, auto& res) {
        (void) req;
        res.set_content("{status:\"UP\"}", "text/plain");
    };

    static inline auto REGISTER_INFO_API = [](const auto& req, auto& res) {
        res.set_content("{\"echo\":" + req.body + "}", "application/json");
    };

    static inline auto STOP_SERVICE_API = [](const auto& req, auto& res) {
        (void) req;
        if (!ON_GOINE_G)
        {
            res.set_content("{\"message\": \"service has already been stopped\"}", "application/json");
        }
        else
        {
            ON_GOINE_G = false;
        }
        res.status = 200;
    };
};

void HdmAppInfoAPI::registerAPI(httplib::Server & srv)
{
    srv.Get("/health", HdmAppInfoAPI::REGISTER_HEALTH_API);
    srv.Get("/info", HdmAppInfoAPI::REGISTER_INFO_API);
    srv.Put("/stop", HdmAppInfoAPI::STOP_SERVICE_API);
}

#endif
