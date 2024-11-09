#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

//macro that converts degrees to radians
#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

class Lod {
private:
    int x=0,y=0;                //position of the ship
    int direction = 0;          //direction of the ship represented in degrees

    int waypoint_x, waypoint_y; //position of the waypoint

    void rotate_waypoint(int angle) {
        //multiplying 2d vector by rotation matrix:
        //  (cos(a)*x - sin(a)*y)
        //  (sin(a)*x + cos(a)*y)
        //where a is angle of rotation around origin
        //That's why you need to know math...
        int new_x = int(cos(DEG_TO_RAD(angle))) * waypoint_x - int(sin(DEG_TO_RAD(angle))) * waypoint_y;
        int new_y = int(sin(DEG_TO_RAD(angle))) * waypoint_x + int(cos(DEG_TO_RAD(angle))) * waypoint_y;
        waypoint_x = new_x; waypoint_y = new_y;
    }


    //moves waypoint or ship, depending on druhe_reseni
    void move(bool druhe_reseni, int steps, char instruction) {

        //difference in x and y coordinates
        int dx=0,dy=0;

        //set dx, dy
        switch(instruction) {
            case 'N':
                dy = steps;
                break;
            case 'S':
                dy = -steps;
                break;
            case 'W':
                dx = -steps;
                break;
            case 'E':
                dx = steps;
                break;
            case 'F':
                if (druhe_reseni) {
                    //move ship and return, so the waypoint position isn't changed
                    x += waypoint_x * steps;
                    y += waypoint_y * steps;
                    return;
                }
                else {
                    //set dx and dy according to current direction of the ship
                    switch(direction) {
                        case 90:
                            dy = steps;
                            break;
                        case 270:
                            dy = -steps;
                            break;
                        case 0:
                            dx = steps;
                            break;
                        case 180:
                            dx = -steps;
                    }
                }
        }

        //update coordinates of ship or waypoint
        if (druhe_reseni) {
            waypoint_x += dx;
            waypoint_y += dy;
        }
        else {
            x += dx;
            y += dy;
        }
    }

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
        //open the file, return -1 of the opening fails
        ifstream file(cesta_soubor, ifstream::in);
        if (!file.is_open()) {
            cerr << "Error opening file\n";
            return -1;
        }
        if (file.bad()) {
            cerr << "Error: badbit is set!\n";
            return -1;
        }
        
        //string to store instruction read from file
        string instruction;

            //for each instruction in the file
            while(getline(file, instruction)) {

                //convert the number after instruction letter to integer and assign it to steps variable
                int steps = stoi(instruction.substr(1));

                switch(instruction[0]) {
                    case 'R':      
                        //flip steps (=rotation angle) sign if rotation is clockwise, then rotate
                        steps *= -1;

                        //surpress -Wimplicit-fallthrough option
                        [[fallthrough]];
                    case 'L':
                        //rotate waypoint or ship
                        if (druhe_reseni) {
                            rotate_waypoint(steps);
                        }
                        else {
                            //rotate ship, rotation is capped in interval <0,360> degrees
                            direction = (360 + (direction + steps)) % 360;
                        }
                        break;
                    default:
                        //move ship or waypoint
                        move(druhe_reseni, steps, instruction[0]);
                }
            }
        file.close();

        //return manhattan distance
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
