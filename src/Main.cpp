#include <iostream>
#include "Session.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "usage cTrace <./config1.json>" << std::endl;
        return 0;
    }
    Session sess(argv[1]);
    sess.simulate();
    return 0;
}

