#include <iostream>
#include <fstream>

class Lod {
private:
    int x, y;   // lokace lodi
    char smer;          
    int waypoint_x, waypoint_y; 

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
        : x(x), y(y), smer(smer), waypoint_x(cilovy_bod_x), waypoint_y(cilovy_bod_y) {}
    int naviguj(std::string cesta_soubor, bool druhe_reseni) {
        std::ifstream soubor(cesta_soubor);
        if (!soubor.is_open()) {
            std::cout << "Chyba s vstupním souborem.";
            return -1;
        }
        else {
            
        }

        std::string instrukce;
        while (std::getline(soubor, instrukce)) {
            char akce = instrukce[0];   // první část vstupu
            int hodnota = std::stoi(instrukce.substr(1));   // druhá část vstupu

            if (druhe_reseni) {
                zpracujInstrukciWaypoint(akce, hodnota);    //1
            } else {
                zpracujInstrukciLod(akce, hodnota);     //2
            }
        }
        soubor.close();
        return std::abs(x) + std::abs(y);   // NewYorkská vzdálenost 
    }

private:
    void posunWaypoint(char akce, int hodnota) {
        switch (akce) {
            case 'N': waypoint_y += hodnota; break;
            case 'S': waypoint_y -= hodnota; break;
            case 'E': waypoint_x += hodnota; break;
            case 'W': waypoint_x -= hodnota; break;
        }
    }
    void otocWaypoint(char akce, int stupne) {
        int kroky = stupne / 90; 
        while (kroky--) {       // otočení doprava a doleva je vlastně také jenom otočení o 90 nebo -90
            if (akce == 'R') {
                int temp = waypoint_x;
                waypoint_x = waypoint_y;
                waypoint_y = -temp;
            } else if (akce == 'L') {
                int temp = waypoint_x;
                waypoint_x = -waypoint_y;
                waypoint_y = temp;
            }
        }
    }

    void zpracujInstrukciWaypoint(char akce, int hodnota) { //1
        switch (akce) {
            case 'N': case 'S': case 'E': case 'W':
                posunWaypoint(akce, hodnota);
                break;
            case 'L': case 'R':
                otocWaypoint(akce, hodnota);
                break;
            case 'F':
                x += hodnota * waypoint_x;
                y += hodnota * waypoint_y;
                break;
        }
    }

    void posunLod(char akce, int hodnota) { //3
        switch (akce) {
            case 'N': y += hodnota; break;
            case 'S': y -= hodnota; break;
            case 'E': x += hodnota; break;
            case 'W': x -= hodnota; break;
        }
    }

    void otocLod(char akce, int stupne) {       //4
        std::string smerove_body = "NESW"; 
        int index = smerove_body.find(smer);
        int kroky = stupne / 90;
        
        if (akce == 'R') {
            index = (index + kroky) % 4;
        } else if (akce == 'L') {
            index = (index - kroky + 4) % 4;
        }
        
        smer = smerove_body[index];
    }

    void zpracujInstrukciLod(char akce, int hodnota) {      //2
        switch (akce) {
            case 'N': case 'S': case 'E': case 'W':
                posunLod(akce, hodnota);        
                break;
            case 'L': case 'R':
                otocLod(akce, hodnota);     //3,4
                break;
            case 'F':
                posunLod(smer, hodnota);
                break;
        }
    }
};

#ifndef __TEST__
int main()
{
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << lod.naviguj("vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << lod2.naviguj("vstup_1.txt", true) << std::endl;
    return 0;
}
#endif // __TEST__


/*
cd Ukol_3/cpp
make build
cd build 

cmake ..
make
./mytests
*/

/*
Running main() from /build/googletest-YnT0O3/googletest-1.10.0.20201025/googletest/src/gtest_main.cc
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from AdventLod
[ RUN      ] AdventLod.Naviguj_1
[       OK ] AdventLod.Naviguj_1 (0 ms)
[ RUN      ] AdventLod.Naviguj_2
[       OK ] AdventLod.Naviguj_2 (0 ms)
[----------] 2 tests from AdventLod (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
*/
