// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>  

int soucet(const std::vector<int>& cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

int soucin(const std::vector<int>& cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 1, std::multiplies<int>());
}

double prumer(const std::vector<int>& cisla)
{
    if (cisla.empty()) {
        throw std::invalid_argument("Prázdný seznam");
    }
    int soucet = std::accumulate(cisla.begin(), cisla.end(), 0);
    return static_cast<double>(soucet) / cisla.size();
}

double median(const std::vector<int>& cisla)
{
    if (cisla.empty()) {
        throw std::invalid_argument("Prázdný seznam");
    }
    std::vector<int> sorted_cisla = cisla;
    std::sort(sorted_cisla.begin(), sorted_cisla.end());
    size_t size = sorted_cisla.size();

    if (size % 2 != 0) {
        return sorted_cisla[size / 2];
    } else {
        return (sorted_cisla[size / 2 - 1] + sorted_cisla[size / 2]) / 2.0;
    }
}

#ifndef __TEST__
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    // TODO: Načtěte čísla ze vstupu do vektoru cisla

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__


// TESTY    cd Ukol_1/cpp && mkdir -p build && cd build && cmake .. && make && ./mytests || exit 1
/*
-- The C compiler identification is GNU 10.2.1
-- The CXX compiler identification is GNU 10.2.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /usr/lib/x86_64-linux-gnu/libgtest.a  
-- Configuring done
-- Generating done
-- Build files have been written to: /workspaces/Ukoly2024/Ukol_1/cpp/build
Scanning dependencies of target mytests
[ 25%] Building CXX object CMakeFiles/mytests.dir/test.cpp.o
[ 50%] Linking CXX executable mytests
[ 50%] Built target mytests
Scanning dependencies of target vypocty
[ 75%] Building CXX object CMakeFiles/vypocty.dir/vypocty.cpp.o
[100%] Linking CXX executable vypocty
[100%] Built target vypocty
Running main() from /build/googletest-YnT0O3/googletest-1.10.0.20201025/googletest/src/gtest_main.cc
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from TestyFunkci
[ RUN      ] TestyFunkci.Soucet
[       OK ] TestyFunkci.Soucet (0 ms)
[ RUN      ] TestyFunkci.Soucin
[       OK ] TestyFunkci.Soucin (0 ms)
[ RUN      ] TestyFunkci.Prumer
[       OK ] TestyFunkci.Prumer (0 ms)
[ RUN      ] TestyFunkci.Median
[       OK ] TestyFunkci.Median (0 ms)
[----------] 4 tests from TestyFunkci (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
*/