#include <iostream>
#include <fstream>

class Lod
{
private:
    int x, y;                
    char smer;               
    int cilovy_bod_x, cilovy_bod_y; 

    void otoceni(int uhel, bool doprava)
    {
        if (!doprava) uhel = 360 - uhel;
        uhel %= 360;

        int bod_x = cilovy_bod_x;
        int bod_y = cilovy_bod_y;

        if (uhel == 90) {
            bod_x=cilovy_bod_y;
            bod_y= -cilovy_bod_x;
        } else if(uhel == 180) {
            bod_x=-cilovy_bod_x;
            bod_y=-cilovy_bod_y;
        } else if(uhel == 270) {
            bod_x=-cilovy_bod_y;
            bod_y=cilovy_bod_x;
        }

        cilovy_bod_x = bod_x;
        cilovy_bod_y = bod_y;
    }

    void smerlodi(char smer, int hodnota)
    {
        if(smer == 'N') 
            y+= hodnota;
        else if(smer == 'S')
            y-= hodnota;
        else if(smer == 'E')
            x+= hodnota;
        else if(smer == 'W')
            x-= hodnota;
    }

    void pohyblodi(int hodnota)
    {
        smerlodi(smer, hodnota);
    }

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
        : x(x), y(y), smer(smer), cilovy_bod_x(cilovy_bod_x), cilovy_bod_y(cilovy_bod_y){}

    int naviguj(const std::string &cesta_soubor, bool druhe_reseni)
    {
        std::ifstream soubor(cesta_soubor);
        if (!soubor.is_open()) return -1;

        char akce;
        int hodnota;
        while (soubor >> akce >> hodnota)
        {
            if (!druhe_reseni) 
            {
                if(akce == 'N' || akce == 'S' || akce == 'E' || akce == 'W') {
                    smerlodi(akce, hodnota);
                } else if (akce == 'L') {
                    smer = "NESW"[(index_smeru() - hodnota / 90 + 4) % 4];
                } else if(akce == 'R') {
                    smer = "NESW"[(index_smeru() + hodnota / 90) % 4];
                } else if(akce == 'F') {
                    pohyblodi(hodnota);
                }
            } 
            else 
            {
                if (akce== 'N') 
                    cilovy_bod_y += hodnota;
                else if (akce == 'S') 
                    cilovy_bod_y -= hodnota;
                else if (akce == 'E') 
                    cilovy_bod_x += hodnota;
                else if (akce == 'W') 
                    cilovy_bod_x -= hodnota;
                else if (akce == 'L') 
                    otoceni(hodnota, false);
                else if (akce== 'R') 
                    otoceni(hodnota, true);
                else if (akce == 'F') {
                    x += hodnota * cilovy_bod_x;
                    y += hodnota * cilovy_bod_y;
                }
            }
        }
        soubor.close();
        return (x<0?-x:x)+(y<0?-y:y);
    }

    int index_smeru() const
    {
        if(smer == 'N')
            return 0;
        if(smer == 'E')
            return 1;
        if(smer == 'S')
            return 2;
        if(smer == 'W')
            return 3;
        return 0;
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
