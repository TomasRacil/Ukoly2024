#include <iostream>
#include <fstream>
using namespace std;


class Lod
{
private:
    int x;
    int y;
    char smer;
    int cilovy_bod_x;
    int cilovy_bod_y;
//lod se hybe
    void cast1(char akce, int hodnota)
    {
        switch (akce)
        {
        case 'N':
            y += hodnota;
            break;
        case 'S':
            y -= hodnota;
            break;
        case 'E': 
            x += hodnota;
            break;
        case 'W':  
            x -= hodnota;
            break;
        case 'L':
            switch (hodnota)
            {
            case 90:
                if (smer == 'N')
                {
                    smer = 'W';
                }
                else if (smer == 'W')
                {
                    smer = 'S';
                }
                else if (smer == 'S')
                {
                    smer = 'E';
                }
                else if (smer == 'E')
                {
                    smer = 'N';
                }
                break;
            case 180:
                if (smer == 'N')
                {
                    smer = 'S';
                }
                else if (smer == 'W')
                {
                    smer = 'E';
                }
                else if (smer == 'S')
                {
                    smer = 'N';
                }
                else if (smer == 'E')
                {
                    smer = 'W';
                }
                break;
            case 270:
                if (smer == 'N')
                {
                    smer = 'E';
                }
                else if (smer == 'E')
                {
                    smer = 'S';
                }
                else if (smer == 'S')
                {
                    smer = 'W';
                }
                else if (smer == 'W')
                {
                    smer = 'N';
                }
            break;
            }
        break;
        case 'R':
            switch (hodnota)
            {
            case 90:
                if (smer == 'N')
                {
                    smer = 'E';
                }
                else if (smer == 'E')
                {
                    smer = 'S';
                }
                else if (smer == 'S')
                {
                    smer = 'W';
                }
                else if (smer == 'W')
                {
                    smer = 'N';
                }
                break;
            case 180:
                if (smer == 'N')
                {
                    smer = 'S';
                }
                else if (smer == 'E')
                {
                    smer = 'W';
                }
                else if (smer == 'S')
                {
                    smer = 'N';
                }
                else if (smer == 'W')
                {
                    smer = 'E';
                }
                break;
            case 270:
                if (smer == 'N')
                {
                    smer = 'W';
                }
                else if (smer == 'W')
                {
                    smer = 'S';
                }
                else if (smer == 'S')
                {
                    smer = 'E';
                }
                else if (smer == 'E')
                {
                    smer = 'N';
                }
                break;
            }
        break;
        case 'F':
            switch (smer)
            {
            case 'N':
                y += hodnota;
                break;
            case 'S':
                y -= hodnota;
                break;
            case 'E':
                x += hodnota;
                break;
            case 'W':
                x -= hodnota;
                break;
            }
        break; 
        }
    }
    //lod se hybe podle ciloveho bodu
    void cast2(char akce, int hodnota)
    {
        int pom,pom2;
        switch (akce)
        {
        case 'N':
            cilovy_bod_y += hodnota;
            break;
        case 'S':
            cilovy_bod_y -= hodnota;
            break;
        case 'E':
            cilovy_bod_x += hodnota;
            break;
        case 'W':   
            cilovy_bod_x -= hodnota;
            break;
        case 'L':
            switch (hodnota)
            {
            case 90:
                pom = cilovy_bod_x;
                cilovy_bod_x = -cilovy_bod_y;
                cilovy_bod_y = pom;
                break;
            case 180:
                cilovy_bod_x = -cilovy_bod_x;
                cilovy_bod_y = -cilovy_bod_y;
                break;
            case 270:
                pom2 = cilovy_bod_x;
                cilovy_bod_x = cilovy_bod_y;
                cilovy_bod_y = -pom2;
                break;
            }
            break;
        case 'R':
            switch (hodnota)
            {
            case 90:
                pom = cilovy_bod_x;
                cilovy_bod_x = cilovy_bod_y;
                cilovy_bod_y = -pom;
                break;
            case 180:
                cilovy_bod_x = -cilovy_bod_x;
                cilovy_bod_y = -cilovy_bod_y;
                break;
            case 270:
                pom2 = cilovy_bod_x;
                cilovy_bod_x = -cilovy_bod_y;
                cilovy_bod_y = pom2;
                break;
            }
            break;
        case 'F':
            x += hodnota * cilovy_bod_x;
            y += hodnota * cilovy_bod_y;
            break;
        break;
        }
        
    }
public:
    //konstruktor
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y): x(x), y(y), smer(smer), cilovy_bod_x(cilovy_bod_x), cilovy_bod_y(cilovy_bod_y) {}
    
    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        ifstream cesta(cesta_soubor);
        if (!cesta.is_open())
        {
            return -1;
        }
        string radek;
        int puvodni_x = x;
        int puvodni_y = y;
        while (std::getline(cesta, radek))
        {
            char akce = radek[0];
            int hodnota = std::stoi(radek.substr(1));
            if (!druhe_reseni)
            {
                cast1(akce, hodnota);
            }
            else
            {
                cast2(akce, hodnota);
            }

        }
        return abs(x - puvodni_x) + abs(y - puvodni_y);
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