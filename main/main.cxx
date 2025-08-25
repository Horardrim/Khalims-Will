#include <iostream>
#include <mutex>

#ifdef ENABLE_UNIT_TEST
  #include "tests/http/hdm_http_tests.hxx"
  #include "tests/connectors/hdm_register_test.hxx"
#else
  #include "connectors/hdm_register.hxx"
  #include "http/hdm_http_srv.hxx"
#endif

int main(int argc, char ** argv)
{
#ifdef ENABLE_UNIT_TEST

    std::cout << "current cplusplus standard is:" << std::endl;
    std::cout << __cplusplus << std::endl;

    HdmHttpTest httpTest;
    httpTest.runTests();

    HdmRegCenConnectorsTest registerCenterTest;
    registerCenterTest.runTests();

#else
    (void) argc, (void) argv;
    HdmRegCenConnector eurekaConnector;
    eurekaConnector.Register();

    HdmHttpSrv httpSrv;
    std::thread([&srv = httpSrv] {
        srv.listen();
    }).detach();

    std::this_thread::sleep_for(std::chrono::seconds(10));
    httpSrv.stop();
    eurekaConnector.unregister();
#endif

    return 0;
}
