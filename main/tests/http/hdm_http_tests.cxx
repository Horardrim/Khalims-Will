#ifdef ENABLE_UNIT_TEST

#include <thread>

#include "hdm_http_tests.hxx"

void HdmHttpTests::runTests()
{
    std::thread([&srv = srv_] {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        srv.stop();
    }).detach();

    srv_.listen(); 
}

#endif
