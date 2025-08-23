#include <iostream>
#include <mutex>

#include <curl/curl.h>

#include "http/hdm_http_srv.hxx"

int main(int argc, char ** argv)
{
    (void) argc, (void) argv;
    CURL *curl = curl_easy_init();
    (void) curl;
    
    #ifdef ENABLE_UNIT_TEST
    std::cout << "unit test is enabled" << std::endl;

    #endif

    HdmHttpSrv srv;
    
    return 0;
}
