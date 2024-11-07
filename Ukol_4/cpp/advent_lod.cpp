#include <iostream>
#include <fstream>
#include <string>



using namespace std;


class Lod
{
private:
    int x, y;
    char direction = 0;


public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {
        //konstruktory
        this->x = x;
        this->y = y;
        switch (smer) {
        case 'E':
            direction = 0;
            break;
        case 'W':
            direction = 180;
            break;
        case 'N':
            direction = 90;
            break;
        case 'S':
            direction = 270;
            break;


        }

    }
    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        ifstream file(cesta_soubor, ifstream::in);
       if (!file.is_open()) {
            cerr << "Soubor se neotvrel\n";
            return -1;
        }

            if (file.bad()) {
                cerr << "Soubor je vadny\n";
                return -1;

        }

            string instruction;


            while (getline(file, instruction)){
                int steps = stoi(instruction.substr(1));





                switch (instruction[0]) {
                case 'N':
                    y += steps;
                    break;
                case 'S':
                    y -= steps;
                    break;
                case 'E':
                    x += steps;
                    break;
                case 'W':
                    x -= steps;
                    break;
                case 'L':
                    direction = (360 + (direction + steps)) % 360;

                    break;
                case 'R':
                    direction = (360 + (direction - steps)) % 360;
                    break;
                case 'F':
                    switch (direction) {
                    case 90:
                        y += steps;
                        break;
                    case 270:
                        y -= steps;
                        break;
                    case 0:
                        x += steps;
                        break;
                    case 180:
                        x -= steps;
                        break;

                    }
                    break;


                }

                return abs(x) + abs(y);



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