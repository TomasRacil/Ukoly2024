#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Lod
{
private:
    int sever;
    int vychod;
    int stupne;
    int wp_x;
    int wp_y;
public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {
        this->sever = y;
        this->vychod = x;
        // na zaklade vstupniho sm2ru urcime stupne otoceni
        switch(smer){
            case 'N':
                this->stupne = 0;
                break;
            case 'E':
                this->stupne = 90;
                break;
            case 'S':
                this->stupne = 180;
                break;
            case 'W':
                this->stupne = 270;
                break;
        }
        this->wp_x = cilovy_bod_x;
        this->wp_y = cilovy_bod_y;
    }
    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {   
        ifstream file;
        string radek;
        file.open(cesta_soubor);
        // dokud muzeme cist radek tak vzdy cteme po jednom
        while(getline(file,radek))
        {
            char ukol;
            int hod;
            ukol=radek[0];
            hod=stoi(radek.substr(1,radek.length()));
            // druha cast
            if (druhe_reseni)
            {
                // pismena N E S W posunuji waipointem
                switch(ukol){
                    case 'N':
                        wp_y+=hod;
                        break;
                    case 'S':
                        wp_y -= hod;
                        break;
                    case 'E':
                        wp_x += hod;
                        break;
                    case 'W':
                        wp_x -= hod; 
                        break;
                    // L a R prohazuji a neguji x a y souradnice podle stupnu otaceni
                    case 'L':
                        {
                        int px = wp_x;
                        int py = wp_y;
                        switch (hod)
                        {    
                            case 90:
                                wp_x = -py;
                                wp_y = px; 
                                break;
                            case 180:
                                wp_x = -px;
                                wp_y = -py;
                                break;
                            case 270:
                                wp_x = py; 
                                wp_y = -px;
                                break;
                        }
                        break;
                        }
                    case 'R':
                        {
                        int px = wp_x;
                        int py = wp_y;
                        switch (hod)
                        {    
                            case 270:
                                wp_x = -py;
                                wp_y = px; 
                                break;
                            case 180:
                                wp_x = -px;
                                wp_y = -py;
                                break;
                            case 90:
                                wp_x = py; 
                                wp_y = -px;
                                break;
                        }
                        break;
                        }
                    // F posouva lod smerem k waypointu
                    case 'F':
                        sever += wp_y*hod;
                        vychod += wp_x*hod;
                        break;
                }  
            }
            // prvni cast
            else
            {
                // N E S W posunuji lodi podle ve smeru ktery urcuji
                switch(ukol){
                    case 'N':
                        sever+=hod;
                        break;
                    case 'S':
                        sever -= hod;
                        break;
                    case 'E':
                        vychod += hod;
                        break;
                    case 'W':
                        vychod -= hod; 
                        break;
                    // R a L meni promenou stupne a podle toho se lod otaci
                    case 'L':
                        stupne -= hod;
                        if (stupne<0)
                            stupne += 360;
                        break;
                    case 'R':
                        stupne += hod;
                        if (stupne>= 360)
                            stupne -= 360;
                        break;
                    // F posouva lod podle toho kterym smerem je otocena
                    case 'F':
                        switch (stupne)
                        {
                            case 0:
                                sever += hod;
                                break;
                            case 90:
                                vychod += hod;
                                break;
                            case 180:
                                sever -= hod;
                                break;  
                            case 270:
                                vychod -= hod;
                                break;
                        }
                        break;
                }  
            }
            cout << sever << endl << vychod << endl << stupne << endl;
        }
        file.close();
        cout << "vysledek:";
        // vypsani vysledku
        return abs(sever)+abs(vychod);
    }
};

#ifndef __TEST__
int main()
{
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << lod.naviguj("vstup_1.txt", false) << endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << lod2.naviguj("vstup_1.txt", true) << endl;
    return 0;
}
#endif // __TEST__