#ifdef ENABLE_UNIT_TEST

#ifndef HDM_HTTP_TESTS_HXX
#define HDM_HTTP_TESTS_HXX

#include "http/hdm_http_srv.hxx"

class HdmHttpTest
{
public:
    HdmHttpTest() = default;
    ~HdmHttpTest() = default;

    void runTests();

private:
    HdmHttpSrv  srv_;
};

#endif
#endif
