#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

class Lod
{
private:
    int x, y;
    char smer;
    int cilovy_bod_x, cilovy_bod_y;

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
        : x(x), y(y), smer(smer), cilovy_bod_x(cilovy_bod_x), cilovy_bod_y(cilovy_bod_y)
    {
    }

    int naviguj(string cesta_soubor, bool druhe_reseni)
    {
        ifstream file(cesta_soubor);
        if (!file.is_open())
        {
            cerr << "Nejde otevrit soubor " << cesta_soubor << endl;
            return -1;
        }

        string radek;
        while (getline(file, radek))
        {
            char prikaz = radek[0];
            int krok;
            try
            {
                krok = stoi(radek.substr(1));
            }
            catch (const invalid_argument& e)
            {
                cerr << "Neplatne cislo ve vstupu: " << radek.substr(1) << endl;
                continue;
            }
            catch (const out_of_range& e)
            {
                cerr << "Cislo mimo rozsah ve vstupu: " << radek.substr(1) << endl;
                continue;
            }

            if (!druhe_reseni)
            {
                switch (prikaz)
                {
                case 'N': y += krok; break;
                case 'S': y -= krok; break;
                case 'E': x += krok; break;
                case 'W': x -= krok; break;
                case 'R': otocVpravo(krok); break;
                case 'L': otocVlevo(krok); break;
                case 'F': pohybVpred(krok); break;
                default: cerr << "Neznamy prikaz: " << prikaz << endl; break;
                }
            }
            else
            {
                switch (prikaz)
                {
                case 'N': cilovy_bod_y += krok; break;
                case 'S': cilovy_bod_y -= krok; break;
                case 'E': cilovy_bod_x += krok; break;
                case 'W': cilovy_bod_x -= krok; break;
                case 'R': otocWaypointVpravo(krok); break;
                case 'L': otocWaypointVlevo(krok); break;
                case 'F':
                    x += krok * cilovy_bod_x;
                    y += krok * cilovy_bod_y;
                    break;
                default: cerr << "Neznamy prikaz: " << prikaz << endl; break;
                }
            }
        }
        file.close();
        return abs(x) + abs(y);
    }

private:
    void otocVlevo(int uhel)
    {
        while (uhel > 0)
        {
            switch (smer)
            {
            case 'N': smer = 'W'; break;
            case 'S': smer = 'E'; break;
            case 'E': smer = 'N'; break;
            case 'W': smer = 'S'; break;
            }
            uhel -= 90;
        }
    }

    void otocVpravo(int uhel)
    {
        while (uhel > 0)
        {
            switch (smer)
            {
            case 'N': smer = 'E'; break;
            case 'S': smer = 'W'; break;
            case 'E': smer = 'S'; break;
            case 'W': smer = 'N'; break;
            }
            uhel -= 90;
        }
    }

    void pohybVpred(int krok)
    {
        switch (smer)
        {
        case 'N': y += krok; break;
        case 'S': y -= krok; break;
        case 'E': x += krok; break;
        case 'W': x -= krok; break;
        }
    }

    void otocWaypointVlevo(int uhel)
    {
        while (uhel > 0)
        {
            int temp = cilovy_bod_x;
            cilovy_bod_x = -cilovy_bod_y;
            cilovy_bod_y = temp;
            uhel -= 90;
        }
    }

    void otocWaypointVpravo(int uhel)
    {
        while (uhel > 0)
        {
            int temp = cilovy_bod_x;
            cilovy_bod_x = cilovy_bod_y;
            cilovy_bod_y = -temp;
            uhel -= 90;
        }
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