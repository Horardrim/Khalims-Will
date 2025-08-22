#include <iostream>
#include <curl/curl.h>

int main(int argc, char ** argv)
{
    (void) argc, (void) argv;
    CURL *curl = curl_easy_init();
    (void) curl;
    
    #ifdef ENABLE_UNIT_TEST
    std::cout << "unit test is enabled" << std::endl;

    #endif
    return 0;
}
