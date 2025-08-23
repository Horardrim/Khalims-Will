#include <iostream>
#include <mutex>

#include <curl/curl.h>

#include "http/hdm_http_srv.hxx"

#ifdef ENABLE_UNIT_TEST
#include "tests/http/hdm_http_tests.hxx"
#endif

int main(int argc, char ** argv)
{
    (void) argc, (void) argv;
    CURL *curl = curl_easy_init();
    (void) curl;
    
    #ifdef ENABLE_UNIT_TEST

    std::cout << "current cplusplus standard is:" << std::endl;
    std::cout << __cplusplus << std::endl;
    HdmHttpTests httpTests;
    httpTests.runTests();

    #endif

    HdmHttpSrv srv;
    
    return 0;
}
