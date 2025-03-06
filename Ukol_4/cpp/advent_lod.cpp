#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

class Lod {
private:
    int x, y;
    int smer;
    int waypoint_x;
    int waypoint_y;
public:
    Lod(int x, int y, char startSmer, int cilovy_bod_x, int cilovy_bod_y)
        : x(x), y(y), waypoint_x(cilovy_bod_x), waypoint_y(cilovy_bod_y)
    {
        switch (startSmer) {
            case 'N': smer = 0; break;
            case 'E': smer = 1; break;
            case 'S': smer = 2; break;
            case 'W': smer = 3; break;
            default:  smer = 1; break;
        }
    }
    int naviguj(std::string cesta_soubor, bool druhe_reseni) {
        if (cesta_soubor.size() >= 3 && cesta_soubor.substr(0, 3) == "../") {
            cesta_soubor = cesta_soubor.substr(3);
        }
        std::ifstream infile(cesta_soubor);
        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty())
                continue;
            char action = line[0];
            int value = std::stoi(line.substr(1));
            if (!druhe_reseni) {
                if (action == 'N')
                    y += value;
                else if (action == 'S')
                    y -= value;
                else if (action == 'E')
                    x += value;
                else if (action == 'W')
                    x -= value;
                else if (action == 'L') {
                    int steps = value / 90;
                    smer = (smer - steps + 4) % 4;
                }
                else if (action == 'R') {
                    int steps = value / 90;
                    smer = (smer + steps) % 4;
                }
                else if (action == 'F') {
                    if (smer == 0)
                        y += value;
                    else if (smer == 1)
                        x += value;
                    else if (smer == 2)
                        y -= value;
                    else if (smer == 3)
                        x -= value;
                }
            } else {
                if (action == 'N')
                    waypoint_y += value;
                else if (action == 'S')
                    waypoint_y -= value;
                else if (action == 'E')
                    waypoint_x += value;
                else if (action == 'W')
                    waypoint_x -= value;
                else if (action == 'L' || action == 'R') {
                    int steps = (value / 90) % 4;
                    if (action == 'R')
                        steps = (4 - steps) % 4;
                    for (int i = 0; i < steps; i++) {
                        int temp = waypoint_x;
                        waypoint_x = -waypoint_y;
                        waypoint_y = temp;
                    }
                }
                else if (action == 'F') {
                    x += value * waypoint_x;
                    y += value * waypoint_y;
                }
            }
        }
        return std::abs(x) + std::abs(y);
    }
};

#ifndef __TEST__

int main() {
    std::vector<std::string> files = {"vstup_1.txt", "vstup_2.txt", "vstup_3.txt"};
    for (const auto &file : files) {
        Lod lod1(0, 0, 'E', 10, 1);
        int result1 = lod1.naviguj(file, false);
        Lod lod2(0, 0, 'E', 10, 1);
        int result2 = lod2.naviguj(file, true);
        std::cout << "soubor: " << file << "\n";
        std::cout << "prima navigace: " << result1 << "\n";
        std::cout << "navigace s waypointem: " << result2 << "\n";
        std::cout << "\n";
    }
    return 0;
}
#endif // __TEST__
