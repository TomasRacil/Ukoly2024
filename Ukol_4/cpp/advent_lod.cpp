#include <cmath>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <cmath>



using namespace std;


class Lod
{
private:
    int x, y;
    int direction = 0;      //0 = vychod, 90 sever,....
    int waypoint_x, waypoint_y;     //souradnice pohybujiciho bodu



public:
    //nasleduje konstruktor tridy Lod, ktery inicializuje lod
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {

        this->x = x;        //this->x odkazuje na promennou, ktera je clenem tridy, a x na prave strane je parametr konstruktoru
        this->y = y;

        waypoint_x = cilovy_bod_x;
        waypoint_y = cilovy_bod_y;


        switch (smer) {     //prevod svetovych stran na uhly ve stupnich
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
        //bool parametr urcuje, zda se ma lod pohybovat podle zakladni navigace, nebo podle nav.s waypointem
        //input file  stream, slouzi ke cteni souboru,
        //file je nazev promenne,
        //cesta_soubor je parametr typu string, obsahuje cestu k souboru, ktery chceme otevrit, obsahuje instrukce
        ifstream file(cesta_soubor);
        //, ifstream::in);
        if (!file.is_open()) {
            cerr << "Soubor se neotevrel\n";
            return -1;
        }

        if (file.bad()) {
            cerr << "Soubor je vadny\n";
            return -1;

        }

        string instruction;     //promenna pro uchovani instrukce

        if (druhe_reseni) {     //navigace s waypointem, pokud je druhe_reseni == true

            while (getline(file, instruction)) {
                //ulozi kazdy radek do instrukce
                int steps = stoi(instruction.substr(1));        //podretezec retezce instrukce
                int  novy_x, novy_y;        //nove souradnice pro otaceni o urcity uhel

                switch (instruction[0]) {       //prvni znak retezce
                case 'N':
                    waypoint_y = waypoint_y + steps;
                    break;
                case 'S':
                    waypoint_y = waypoint_y - steps;
                    break;
                case 'W':
                    waypoint_x = waypoint_x - steps;
                    break;
                case 'E':
                    waypoint_x = waypoint_x + steps;
                    break;
                case 'R':
                    steps *= -1;
                    novy_x = int(cos(steps * (M_PI/180))) * waypoint_x - int(sin(steps * (M_PI/180))) * waypoint_y;
                    novy_y = int(sin(steps * (M_PI/180))) * waypoint_x + int(cos(steps * (M_PI/180))) * waypoint_y;
                    waypoint_x = novy_x;
                    waypoint_y = novy_y;
                    break;
                    case 'L':
                    novy_x = int(cos(steps * (M_PI/180))) * waypoint_x - int(sin(steps * (M_PI/180))) * waypoint_y;
                    novy_y = int(sin(steps * (M_PI/180))) * waypoint_x + int(cos(steps * (M_PI/180))) * waypoint_y;
                    waypoint_x = novy_x;
                    waypoint_y = novy_y;
                    break;
                case 'F':
                    x += waypoint_x * steps;
                    y += waypoint_y * steps;

                    break;
                }
            }
        }
        else
        {
            while (getline(file, instruction)) {
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
            }
        }

        file.close();


        return abs(x) + abs(y);





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