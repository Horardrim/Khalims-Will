#ifdef ENABLE_UNIT_TEST

#ifndef HDM_PG_TESTS_HXX
#define HDM_PG_TESTS_HXX

#include "connectors/hdm_pg.hxx"

class HdmPostgresConnectorTest
{
public:
    HdmPostgresConnectorTest() = default;
    ~HdmPostgresConnectorTest() = default;

    void runTests();

private:
    HdmPostgresConnector connector_;
};

#endif
#endif
