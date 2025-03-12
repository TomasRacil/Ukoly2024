#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib> // Pro std::abs

class Lod
{
private:
    int x, y;             // pozice lodi
    char direction;       // smer lodi (N, E, S, W)
    int waypoint_x, waypoint_y; // souřadnice waypointu

    // Pohyb lodi podle zadání N, S, E, W
    void moveLod(char action, int value)
    {
        switch (action)
        {
        case 'N': y += value; break;
        case 'S': y -= value; break;
        case 'E': x += value; break;
        case 'W': x -= value; break;
        }
    }

    // Otočení lodi -změna směru
    void rotateLod(char action, int degrees)
    {
        std::string directions = "NESW";
        int index = directions.find(direction); // najdi aktuální směr
        int steps = degrees / 90; // rozdělíme stupně na 90 (např. 180, 270)
        if (action == 'R')
        {
            index = (index + steps) % 4;
        }
        else if (action == 'L')
        {
            index = (index - steps + 4) % 4;
        }
        direction = directions[index];
    }

    // Zpracování jednoho zadání pro loď (bez waypointu)
    void processLodInstruction(char action, int value)
    {
        switch (action)
        {
        case 'N': case 'S': case 'E': case 'W':
            moveLod(action, value);
            break;
        case 'L': case 'R':
            rotateLod(action, value); // otočení lodi vpravo/vlevo
            break;
        case 'F':
            moveLod(direction, value); // posunutí v aktuálním směru
            break;
        }
    }

    // Pohyb waypointu
    void moveWaypoint(char action, int value)
    {
        switch (action)
        {
        case 'N': waypoint_y += value; break; // osa y sever
        case 'S': waypoint_y -= value; break; // osa y jih
        case 'E': waypoint_x += value; break; // osa x východ
        case 'W': waypoint_x -= value; break; // osa x západ
        }
    }

    // Otočení waypointu kolem lodi
    void rotateWaypoint(char action, int degrees)
    {
        int steps = (degrees / 90) % 4; // otočení o násobky 90°
        while (steps--)
        {
            int temp = waypoint_x;
            if (action == 'R') // když je pokyn R, prohodí se hodnoty souřadnic
            {
                waypoint_x = waypoint_y;
                waypoint_y = -temp;
            }
            else if (action == 'L') // když je L, prohodí se hodnoty opačně
            {
                waypoint_x = -waypoint_y;
                waypoint_y = temp;
            }
        }
    }

    // Zpracování zadání pro waypoint
    void processWaypointInstruction(char action, int value)
    {
        switch (action)
        {
        case 'N': case 'S': case 'E': case 'W':
            moveWaypoint(action, value); // posun waypointu
            break;
        case 'L': case 'R':
            rotateWaypoint(action, value); // otočení waypointu
            break;
        case 'F': // loď se posune o daný počet kroků ve směru daném waypointem
            x += value * waypoint_x;
            y += value * waypoint_y;
            break;
        }
    }

public:
    // Konstruktor, který nastaví počáteční pozici lodi a waypointu
    Lod(int x, int y, char direction, int waypoint_x, int waypoint_y)
        : x(x), y(y), direction(direction), waypoint_x(waypoint_x), waypoint_y(waypoint_y) {}

    // Hlavní funkce pro navigaci podle souboru a typu navigace (s nebo bez waypointu)
    int naviguj(const std::string& filepath, bool useWaypoint)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cerr << "Soubor se mepodařilo otevřít: " << filepath << std::endl;
            return -1; // když se soubor nepodaří otevřít
        }

        std::string instruction;
        while (std::getline(file, instruction)) // čtení řádku
        {
            char action = instruction[0];
            int value = std::stoi(instruction.substr(1)); // hodnota instrukce

            if (useWaypoint) // pokud používáme waypoint
            {
                processWaypointInstruction(action, value);
            }
            else // bez waypointu
            {
                processLodInstruction(action, value);
            }
        }

        file.close();
        return std::abs(x) + std::abs(y); // Manhattanova vzdálenost
    }
};

int main()
{
    // Testování bez waypointu
    Lod lod1(0, 0, 'E', 10, 1);
    std::cout << "Manhattanova vzdálenost bez waypointu: "
              << lod1.naviguj("input.txt", false) << std::endl;

    // Testování s waypointem
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << "Manhattanova vzdálenost s waypointem: "
              << lod2.naviguj("input.txt", true) << std::endl;

    return 0;
}
