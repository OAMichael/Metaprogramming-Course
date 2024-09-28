#include <iostream>

#include "TestQual.h"


int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " \"<T1>\" \"<T2>\"" << std::endl;
        return 0;
    }
    std::cout << std::boolalpha << TestQual::testqual(argv[1], argv[2]) << std::endl;
    return 0;
}
