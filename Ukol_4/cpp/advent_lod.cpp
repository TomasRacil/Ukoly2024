#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Lod
{
private:
    int x=0,y=0;
    int direction = 0;
    //char direction = 'E'; //W,E,N,S
public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {
        this->x = x;
        this->y = y;
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
        //try to open the file
        ifstream file (cesta_soubor, ifstream::in);
        // if (!file.is_open()) {
        //     //file is not open
        //     cerr << "Error opening file\n";
        //     return -1;
        // }
        // if (file.bad()) {
        //     cerr << "Fatal error: badbit is set!\n";
        //     return -1;
        // }

         string instruction;

         while(getline(file, instruction)) {
            int negr = stoi(instruction.substr(1));
            
            switch(instruction[0]) {
                case 'N':
                    y += negr;
                    break;
                case 'S':
                    y -= negr;
                    break;
                case 'E':
                    x += negr;
                    break;
                case 'W':
                    x -= negr;
                    break;
                case 'L':
                    direction = (360 + (direction + negr)) % 360;
                    break;
                case 'R':
                    direction = (360 + (direction - negr)) % 360;
                    break;
                case 'F':
                    switch(direction) {
                        case 90:
                            y += negr;
                            break;
                        case 270:
                            y -= negr;
                            break;
                        case 0:
                            x += negr;
                            break;
                        case 180:
                            x -= negr;
                    }
                    break;
            }
         }

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