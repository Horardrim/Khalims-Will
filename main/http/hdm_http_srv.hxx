#ifndef HDM_HTTP_SRV_HXX
#define HDM_HTTP_SRV_HXX

#include "httplib.h"

class HdmHttpSrv
{
public:
    HdmHttpSrv();

    ~HdmHttpSrv() = default;

    void listen();

    void stop();

private:
    httplib::Server srv_;

    static inline auto HTTP_HOST = "0.0.0.0";

    template <typename... Args>
    void registerAPI()
    {
        (Args::registerAPI(srv_), ...);
    }
};

#endif
