#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class Ship 
{
private:
    int x, y; // pozice lodi
    char direction; // směr lodi (N, E, S, W)
    int waypoint_x, waypoint_y; // souřadnice waypointu

    // posun lodi na základě akce (N, S, E, W)
    void moveShip(char action, int value) 
    {
        switch (action) 
        {
        case 'N': y += value; break; // pro sever a jih osa y
        case 'S': y -= value; break;
        case 'E': x += value; break; // pro východ západ osa x
        case 'W': x -= value; break;
        }
    }

    // otočení lodi (změna směru) 
    void rotateShip(char action, int degrees) 
    {
        std::string directions = "NESW";
        int index = directions.find(direction); // vyhledá aktuální směr
        int steps = degrees / 90; // stupně budou násovkem 90 (např. 180,270)
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

    // Zpracování jedné instrukce pro loď (bez waypointu)
    void processShipInstruction(char action, int value) 
    {
        switch (action) 
        {
        case 'N': case 'S': case 'E': case 'W':
            moveShip(action, value);
            break;
        case 'L': case 'R':
            rotateShip(action, value); // otočení lodi vpravo/vlevo
            break;
        case 'F':
            moveShip(direction, value); // posun v aktuálním směru
            break;
        }
    }

    // posun waypointu
    void moveWaypoint(char action, int value) {
        switch (action) {
        case 'N': waypoint_y += value; break; //osa y sever
        case 'S': waypoint_y -= value; break; //osa y jih
        case 'E': waypoint_x += value; break; // osa x východ
        case 'W': waypoint_x -= value; break; // osa x západ
        }
    }

    // otočení waypointu kolem lodi doleva/doprava
    void rotateWaypoint(char action, int degrees) 
    {
        int steps = (degrees / 90) % 4; // zase použití násobku 90
        while (steps--) 
        {
            if (action == 'R') // když je pokyn R, prohodí se hodnoty souřadnic
            { 
                int temp = waypoint_x;
                waypoint_x = waypoint_y;
                waypoint_y = -temp;
            }
            else if (action == 'L') 
            {
                int temp = waypoint_x;
                waypoint_x = -waypoint_y; // když je L, prohodí se druhým směrem
                waypoint_y = temp;
            }
        }
    }

    // zpracování pokynů pro směr a počet kroků v tom směru
    void processWaypointInstruction(char action, int value) 
    {
        switch (action) 
        {
        case 'N': case 'S': case 'E': case 'W':
            moveWaypoint(action, value); // když je pokyn (N,S,W,E), waypoint se posune
            break;
        case 'L': case 'R':
            rotateWaypoint(action, value); // když je (R,L) vytočí se waypoint kolem lodi
            break;
        case 'F': // loď se posune o daný počet kroků ve směru daném waypointem
            x += value * waypoint_x;
            y += value * waypoint_y;
            break;
        }
    }

public:
    // počáteční souřadnice, směr a waypoint
    Ship(int x, int y, char direction, int waypoint_x, int waypoint_y)
        : x(x), y(y), direction(direction), waypoint_x(waypoint_x), waypoint_y(waypoint_y) {}

    // zpracování navigačního souboru a Manhattanova vzdálenosti
    int navigate(const std::string& filepath, bool useWaypoint) // cesta k souboru
    {
        std::ifstream file(filepath);
        if (!file.is_open()) 
        {
            std::cerr << "Failed to open file: " << filepath << std::endl;
            return -1; // když se soubor nepodaří otevřít funkce selže
        }

        std::string instruction;
        while (std::getline(file, instruction)) // čtení instrukcí pro směr a počet kroků
        {
            char action = instruction[0];
            int value = std::stoi(instruction.substr(1));

            if (useWaypoint) // navigace pomocí waypointu
            {
                processWaypointInstruction(action, value);
            }
            else // podle směru lodi
            {
                processShipInstruction(action, value);
            }
        }

        file.close();
        return std::abs(x) + std::abs(y); // manhattanova vzdálenost absolutní hodnota
    }
};


int main() 
{
    Ship ship1(0, 0, 'E', 10, 1);
    std::cout << "Manhattanova vzdálenost bez waypointu"
        << ship1.navigate("input.txt", false) << std::endl;

    Ship ship2(0, 0, 'E', 10, 1);
    std::cout << "Manhattanova vzdálenost s waypointem"
        << ship2.navigate("input.txt", true) << std::endl;

    return 0;
}
