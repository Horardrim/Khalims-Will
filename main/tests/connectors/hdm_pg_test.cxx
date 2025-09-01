#ifdef ENABLE_UNIT_TEST

#include <iostream>

#include "hdm_pg_test.hxx"

void HdmPostgresConnectorTest::runTests()
{
    std::cout << "postgresql connection status: " << (connector_.connected() == false) << std::endl;
}

#endif
