#include <iostream>
#include <fstream>
#include <string>

//!!!!
//tento kod jsem mohl napsat ohodne vice citelne pomoci funkci 
//vim ze by to zlepsilo citelnost kodu ale dneska mi to moc nemyslolo a doslo mi to
//az ke konci prace kdy bych opravou kodu zabral hodne casu, takze se timto omlouvam za horsi provedeni(umim to i lepe :) )
//!!!!

using namespace std;

class Lod
{
private:
    int x;
    int y;
    char smer;
    int cilovy_bod_x;
    int cilovy_bod_y;
public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {
    }

    int naviguj(string cesta_soubor, bool druhe_reseni)
    {
        int manhatn = 0, delka;
        string povel;
        string cislo;

        ifstream soubor(cesta_soubor);
        if (!soubor.is_open()) {//kontrola jestli je soubor otevreny
            cerr << "Chyba pri otevirani souboru" << endl;
            return 0;
        }
        if (druhe_reseni = false) {// kontrola jestli se ma provest prvni nebo druha cast
            while (getline(soubor, povel))//dokul je radek ktery se da precist

                for (int i = 1; i < povel.length(); i++) {//zjisteni cisla z prikazu
                    if (i == 1)
                        cislo = povel[i];
                    else
                        cislo += povel[i];
                }
            delka = stoi(cislo);
            switch (povel[0]) {//vyber druhu povelu
            case 'E':
            east: //vystup z goto      zacatek je pri prikazu foward pokud je smer E
                smer = povel[0];
                x += delka;
                manhatn += delka;
                break;
            case 'N':
            north:
                smer = povel[0];
                y += delka;
                manhatn += delka;
                break;
            case 'S':
            south:
                smer = povel[0];
                y -= delka;
                manhatn -= delka;
                break;
            case 'W':
            west:
                smer = povel[0];
                x -= delka;
                manhatn -= delka;
                break;
            case 'F':
                switch (smer) {//podle smeru ve kterem lod je se skoci pomoci goto do funkce která vykonavá tento pohyb
                case 'E':
                    goto east;
                    break;
                case 'N':
                    goto north;
                    break;
                case 'S':
                    goto south;
                    break;
                case 'W':
                    goto west;
                }
                break;
            case 'R':
                int pocet_otocek = delka / 90; 
                for (int i = 0; i < pocet_otocek; i++) {//provadi se do te doby dokud se lod neotoci tolik krat kolikrat bylo zadano
                    switch (smer) {
                    case 'E':
                        smer = 'N';
                        break;
                    case 'N':
                        smer = 'W';
                        break;
                    case 'S':
                        smer = 'E';
                        break;
                    case 'W':
                        smer = 'S';
                    }
                }
                break;
            default://jednoducha korekce pri spatnem zadani prikazu
                printf("chyba ve vybirani akce");
                return 0;
            }
        }




        else {// zde zacina reseni druheh problemu

            while (getline(soubor, povel))
                string cislo;
            for (int i = 1; i < povel.length(); i++) {
                if (i == 1)
                    cislo = povel[i];
                else
                    cislo += povel[i];
            }

            delka = stoi(cislo);
            switch (povel[0]) {//stejne jako v mnulem problemu jen posunujeme bodem namisto lodi
            case 'E':
                cilovy_bod_x += delka;
                break;
            case 'N':
                cilovy_bod_y += delka;
                break;
            case 'S':
                cilovy_bod_y -= delka;
                break;
            case 'W':
                cilovy_bod_x -= delka;
                break;
            case 'F':
                while (delka != 0) {//lod jede v x-sove souradnici do te doby dokud nedojde pocet tahu
                    if(cilovy_bod_x==x)//pokud je na stejne souradnici x sove preskakuje na y kde provadi stejny postup
                    goto preskok;
                    if (cilovy_bod_x > x) {//kontrola jestli lod jede od manhatnu nebo se k nemu priblizuje
                        x++;
                        manhatn++;
                    }
                    else {
                        x--;
                        manhatn--;
                    }
                    delka--;
                preskok:
                    while (delka != 0) {
                        if (cilovy_bod_y > y) {
                            y++;
                            manhatn++;
                        }
                        else {
                            y--;
                            manhatn--;
                        }
                        delka--;
                    }
                    break;
            case 'R':
                int pocet_otocek = delka / 90;
                switch (pocet_otocek) {
                case 1://pokud je pouze posun o 90 stupnu vymeni se x a y souradnice
                skok: 
                    int c, kontrola = 0, kontrola1 = 0;
                    if (cilovy_bod_x < x)//kontrola pokud probehne zmena 1 krat tak zmeni znamenko 
                        kontrola++;
                    if (cilovy_bod_y < y)
                        kontrola1++;
                    c = cilovy_bod_x;
                    cilovy_bod_x = cilovy_bod_y;
                    cilovy_bod_y = c;
                    if (cilovy_bod_x < x)
                        kontrola++;
                    if (cilovy_bod_y < y)
                        kontrola1++;
                    if (kontrola == 1)
                        - cilovy_bod_x;
                    if (kontrola1 == 1)
                        - cilovy_bod_y;
                    break;
                case 2://pouze zmena znamenek pri posunu o 180 stupnu
                    -cilovy_bod_x;
                    -cilovy_bod_y;
                    break;
                case 3://posun o 180 stupnu a pote rotace do case 1 kde se provede rotace o 90 stupnu
                    -cilovy_bod_x;
                    -cilovy_bod_y;
                    goto skok;
                }
                }
                break;
            default:
                printf("chyba ve vybirani akce");
                return 0;
            }
            }
            return abs(manhatn);//funkce vraci absolutni hodnotu manhatnu
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