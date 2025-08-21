#include <iostream>

int main(int argc, char ** argv)
{
    (void) argc, (void) argv;
    #ifdef ENABLE_UNIT_TEST
    std::cout << "unit test is enabled" << std::endl;

    #endif
    return 0;
}
