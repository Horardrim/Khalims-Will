#include <iostream>
#include "utils/util.hxx"

int main(int argc, char ** argv)
{
    (void) argc, (void) argv;
    HdmUtil * u = new HdmUtil();
    (void) u;
    
    #ifdef ENABLE_UNIT_TEST
    std::cout << "unit test is enabled" << std::endl;

    #endif
    return 0;
}
