//jen lodky
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class Lod 
{
private:
    int x, y;   
    int wx, wy; 
    char smer;  
public:
    Lod(int x_start, int y_start, char pocatecni_smer, int wx_start, int wy_start)
        : x(x_start), y(y_start), wx(wx_start), wy(wy_start), smer(pocatecni_smer) {}

    int naviguj(std::string cesta_soubor, bool druhe_reseni) 
    {
        std::ifstream soubor(cesta_soubor);
        if (!soubor.is_open()) 
        {
            std::cerr << "Nepodařilo se otevřít soubor: " << cesta_soubor << std::endl;
            return -1;
        }
        std::string instrukce;
        while (soubor >> instrukce) 
        {
            char akce = instrukce[0];
            int hodnota = std::stoi(instrukce.substr(1));
            if (!druhe_reseni) 
            {
                navigujBezWaypointu(akce, hodnota);
            }
            else 
            {
                navigujSWaypointem(akce, hodnota);
            }
        }
        return std::abs(x) + std::abs(y); 
    }

    void navigujBezWaypointu(char akce, int hodnota) 
    {
        if (akce == 'N') y += hodnota;
        else if (akce == 'S') y -= hodnota;
        else if (akce == 'E') x += hodnota;
        else if (akce == 'W') x -= hodnota;
        else if (akce == 'L' || akce == 'R') 
        {
            otocSmer(hodnota, akce == 'R');
        }
        else if (akce == 'F') 
        {
            pohybVpred(hodnota);
        }
    }

    void navigujSWaypointem(char akce, int hodnota) 
    {
        if (akce == 'N') wy += hodnota;
        else if (akce == 'S') wy -= hodnota;
        else if (akce == 'E') wx += hodnota;
        else if (akce == 'W') wx -= hodnota;
        else if (akce == 'L' || akce == 'R') 
        {
            otocWaypoint(hodnota, akce == 'R');
        }
        else if (akce == 'F') 
        {
            x += wx * hodnota;
            y += wy * hodnota;
        }
    }

    void otocSmer(int stupne, bool doprava) 
    {
        const std::string smery = "NESW";
        int index = smery.find(smer);
        int kroky = (stupne / 90) * (doprava ? 1 : -1);
        index = (index + kroky + 4) % 4;
        smer = smery[index];
    }
    
    void pohybVpred(int hodnota) 
    {
        if (smer == 'N') y += hodnota;
        else if (smer == 'S') y -= hodnota;
        else if (smer == 'E') x += hodnota;
        else if (smer == 'W') x -= hodnota;
    }
    
    void otocWaypoint(int stupne, bool doprava) 
    {
        int kroky = (doprava ? -stupne : stupne) / 90;
        for (int i = 0; i < std::abs(kroky); ++i) 
        {
            int temp = wx;
            wx = kroky > 0 ? -wy : wy;
            wy = kroky > 0 ? temp : -temp;
        }
    }
};
#ifndef __TEST__
int main() {
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << "Manhattan vzdálenost bez waypointu: " << lod.naviguj("vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << "Manhattan vzdálenost s waypointem: " << lod2.naviguj("vstup_1.txt", true) << std::endl;
    return 0;
}
#endif // __TEST__


//  TESTY   cd Ukol_4/cpp && mkdir -p build && cd build && cmake .. && make && ./mytests || exit 1
/*
-- Configuring done
-- Generating done
-- Build files have been written to: /workspaces/Ukoly2024/Ukol_4/cpp/build
Scanning dependencies of target mytests
[ 25%] Building CXX object CMakeFiles/mytests.dir/test.cpp.o
[ 50%] Linking CXX executable mytests
[ 50%] Built target mytests
Scanning dependencies of target advent_lod
[ 75%] Building CXX object CMakeFiles/advent_lod.dir/advent_lod.cpp.o
[100%] Linking CXX executable advent_lod
[100%] Built target advent_lod
Running main() from /build/googletest-YnT0O3/googletest-1.10.0.20201025/googletest/src/gtest_main.cc
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from AdventLod
[ RUN      ] AdventLod.Naviguj_1
[       OK ] AdventLod.Naviguj_1 (1 ms)
[ RUN      ] AdventLod.Naviguj_2
[       OK ] AdventLod.Naviguj_2 (0 ms)
[----------] 2 tests from AdventLod (1 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 2 tests.
*/