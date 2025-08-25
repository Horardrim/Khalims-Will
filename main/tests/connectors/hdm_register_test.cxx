#ifdef ENABLE_UNIT_TEST

#include <thread>

#include "hdm_register_test.hxx"

void HdmRegCenConnectorsTest::runTests()
{
    register_.Register();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    register_.unregister();
}

#endif
