#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Lod
{
private:
    int x = 0, y = 0;
    char smer = 'N';
    int cil_x, cil_y;
// funkce pro rotaci lodi do prava    
void rotateR(int angle){
    // rotuju lod do prava, po kazde rotaci odectu 90, tak dojdu do finalni polohy
    while (angle > 0)
    {
        switch (smer)
        {
        case 'N': smer = 'E'; break;
        case 'E': smer = 'S'; break;
        case 'S': smer = 'W'; break;
        case 'W': smer = 'N'; break;
        default: cerr << "Neznamy smer: " << smer << endl; break;
        }
        angle -= 90;
    }
    
}
// funkce pro rotaci lodi do leva
void rotateL(int angle){
    // stejen jako u rotace do prava, akorat rotuju do leva
    while (angle > 0)
    {
        switch (smer)
        {
        case 'N': smer = 'W'; break;
        case 'W': smer = 'S'; break;
        case 'S': smer = 'E'; break;
        case 'E': smer = 'N'; break;
        default: cerr << "Neznamy smer: " << smer << endl; break;
        }
        angle -= 90;
    }
}
// funkce pro presunu lodi dopredu
void foreward(int step){
    // podle smeru lodi prictu nebo odectu posun(step), tim posunu lod do daneho smeru
    switch(smer){
        case 'N': y += step; break;
        case 'S': y -= step; break;
        case 'E': x += step; break;
        case 'W': x -= step; break;
    }
}
// funkce pro rotaci ciloveho vaipointu
void rotateVaipointR(int angle){
    // stejne jako u ostatnich rotaci, pouzivam temporary int pro ulozeni souradnice x
    while (angle > 0)
    {
        int tmp = cil_x;
        cil_x = cil_y;
        cil_y = -tmp;
        angle -= 90;    
    }
    
}
void rotateVaipointL(int angle){
    // stejne jako u predchozi rotace
    while (angle > 0)
    {
        int tmp = cil_x;
        cil_x = -cil_y;
        cil_y = tmp;
        angle -= 90;    
    }
}
public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y): x(x), y(y), smer(smer), cil_x(cilovy_bod_x), cil_y(cilovy_bod_y){}
    int naviguj(string cesta_soubor, bool druhe_reseni){
        ifstream file(cesta_soubor);
        if (!file.is_open()){ // overeni jestli jsem otevrel soubor
            return -1;
        }
        string line;
        while (getline(file, line)){
            char tmp = line[0];
            int step;
            try{
                step = stoi(line.substr(1)); // pomoci funkce stoi ziskam cislo, hodnotu o kolik posunout, otocit,...
            }
            catch (const invalid_argument& ia){
                cerr << "Invalid number: " << line.substr(1) << endl;
                continue;
            }
            // pro prvni reseni
            if (!druhe_reseni)
            {
                switch (tmp)
                {
                case 'N': y += step; break;
                case 'S': y -= step; break;
                case 'E': x += step; break;
                case 'W': x -= step; break;
                case 'R': rotateR (step); break;
                case 'L': rotateL (step); break;
                case 'F': foreward (step); break;
                default: cerr << "Neznamy prikaz: " << tmp << endl; break;
                }
            } else{ // pro druhe reseni
                switch (tmp)
                {
                    case 'N': cil_y += step; break;
                    case 'S': cil_y -= step; break;
                    case 'E': cil_x += step; break;
                    case 'W': cil_x -= step; break;
                    case 'R': rotateVaipointR (step); break;
                    case 'L': rotateVaipointL (step); break;
                    case 'F': 
                        x += step * cil_x;
                        y += step * cil_y; break;
                    default: cerr << "Neznamy prikaz: " << tmp << endl; break;
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
    cout << lod.naviguj("vstup_1.txt", false) << endl;
    Lod lod2(0, 0, 'E', 10, 1);
    cout << lod2.naviguj("vstup_1.txt", true) << endl;
    return 0;
}
#endif // __TEST__
