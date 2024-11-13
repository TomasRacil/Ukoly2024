#include <iostream>
#include <fstream>

class Lod
{
private:
public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {
    }
    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
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