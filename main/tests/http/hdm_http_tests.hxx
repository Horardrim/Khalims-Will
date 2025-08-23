#ifdef ENABLE_UNIT_TEST

#ifndef HDM_HTTP_TESTS_HXX
#define HDM_HTTP_TESTS_HXX

#include "http/hdm_http_srv.hxx"

class HdmHttpTests
{
public:
    HdmHttpTests() = default;
    ~HdmHttpTests() = default;

    void runTests();

private:
    HdmHttpSrv  srv_;
};

#endif
#endif
