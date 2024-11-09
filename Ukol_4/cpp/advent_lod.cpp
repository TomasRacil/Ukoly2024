#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

class Lod
{
private:
    int x=0,y=0;                //position of the ship
    int direction = 0;          //direction in degrees

    int waypoint_x, waypoint_y; //position of the waypoint
public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y) : x(x), y(y), waypoint_x(cilovy_bod_x), waypoint_y(cilovy_bod_y)
    {
        switch (smer){
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
        }
    }
    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        ifstream file(cesta_soubor, ifstream::in);
        if (!file.is_open()) {
            cerr << "Error opening file\n";
            return -1;
        }
        if (file.bad()) {
            cerr << "Error: badbit is set!\n";
            return -1;
        }
        
        //store instruction read from file
        string instruction;

        if (druhe_reseni) {


            while(getline(file, instruction)) {
                //pro kazdou instrukci v souboru

                int steps = stoi(instruction.substr(1));
                int new_x; int new_y;

                switch(instruction[0]) {
                    case 'N':
                        waypoint_y += steps;
                        break;
                    case 'S':
                        waypoint_y -= steps;
                        break;
                    case 'W':
                        waypoint_x -= steps;
                        break;
                    case 'E':
                        waypoint_x += steps;
                        break;
                    case 'R':
                        //multiplying 2d vector(point) by rotation matrix:
                        //  (cos(a)*x - sin(a)*y)
                        //  (sin(a)*x + cos(a)*y)
                        //where a is angle of rotation around origin
                        
                        //flip steps sign if rotation is clockwise, then rotate (no break)
                        steps *= -1;
                    case 'L':
                        new_x = int(cos(DEG_TO_RAD(steps))) * waypoint_x - int(sin(DEG_TO_RAD(steps))) * waypoint_y;
                        new_y = int(sin(DEG_TO_RAD(steps))) * waypoint_x + int(cos(DEG_TO_RAD(steps))) * waypoint_y;
                        waypoint_x = new_x; waypoint_y = new_y;
                        break;
                    case 'F':
                        x += waypoint_x * steps;
                        y += waypoint_y * steps;
                        break;
                }

                           printf("Ship:\t[%d,%d], ", x,y);                    printf("Waypoint: [%d,%d]\n", waypoint_x, waypoint_y); 

            }
        }
        else {
            while(getline(file, instruction)) {
                int steps = stoi(instruction.substr(1));
            
                switch(instruction[0]) {
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
                    case 'R':
                        steps *= -1;
                    case 'L':
                        direction = (360 + (direction + steps)) % 360;
                        break;
                    case 'F':
                        switch(direction) {
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
