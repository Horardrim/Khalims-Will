#ifdef ENABLE_UNIT_TEST

#ifndef HDM_REGISTER_TESTS_HXX
#define HDM_REGISTER_TESTS_HXX

#include "connectors/hdm_register.hxx"

class HdmRegCenConnectorsTest
{
public:
    HdmRegCenConnectorsTest() = default;

    ~HdmRegCenConnectorsTest() = default;

    void runTests();

private:
    HdmRegCenConnector register_;
};

#endif
#endif
