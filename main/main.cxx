#include <iostream>
#include <mutex>

volatile bool ON_GOINE_G = false;

#ifdef ENABLE_UNIT_TEST
  #include "tests/http/hdm_http_tests.hxx"
  #include "tests/connectors/hdm_register_test.hxx"
#else
  #include "connectors/hdm_register.hxx"
  #include "connectors/hdm_pg.hxx"
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

    HdmPostgresConnector pg_connector;
    std::cout << "connection of postgres is " << pg_connector.connected() << std::endl;
    ON_GOINE_G = true;

    // http server thread
    HdmHttpSrv httpSrv;
    std::thread([&srv = httpSrv] {
        srv.listen();
    }).detach();

    while (ON_GOINE_G) {
        std::this_thread::sleep_for(std::chrono::seconds(30));
        eurekaConnector.heartbeat();
    }

    httpSrv.stop();
    eurekaConnector.unregister();
#endif

    return 0;
}
