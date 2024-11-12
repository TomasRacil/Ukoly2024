#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

class Lod
{
private:
    struct Position
    {
        int x = 0;
        int y = 0;
        char direction = 'N';
        void move(char action, int value)
        {
            switch (action)
            {
            case 'N': y += value; break;
            case 'S': y -= value; break;
            case 'E': x += value; break;
            case 'W': x -= value; break;
            case 'F':
                if (direction == 'N') y += value;
                else if (direction == 'S') y -= value;
                else if (direction == 'E') x += value;
                else if (direction == 'W') x -= value;
                break;
            case 'L':
                direction = (direction == 'N') ? 'W' : (direction == 'W') ? 'S' : (direction == 'S') ? 'E' : 'N';
                break;
            case 'R':
                direction = (direction == 'N') ? 'E' : (direction == 'E') ? 'S' : (direction == 'S') ? 'W' : 'N';
                break;
            }
        }
    };

    struct Waypoint
    {
        int x = 10;
        int y = 1;
    };

    void rotateWaypoint(Waypoint& waypoint, char direction, int degrees)
    {
        int tempX = waypoint.x;
        int tempY = waypoint.y;
        int rotations = (degrees / 90) % 4;
        for (int i = 0; i < rotations; ++i)
        {
            if (direction == 'L') {
                waypoint.x = -tempY;
                waypoint.y = tempX;
            }
            else {
                waypoint.x = tempY;
                waypoint.y = -tempX;
            }
            tempX = waypoint.x;
            tempY = waypoint.y;
        }
    }

    void navigateWithWaypoint(const std::vector<std::string>& instructions)
    {
        Position ship;
        Waypoint waypoint;
        for (const auto& instruction : instructions)
        {
            char action = instruction[0];
            int value = std::stoi(instruction.substr(1));
            switch (action)
            {
            case 'N': waypoint.y += value; break;
            case 'S': waypoint.y -= value; break;
            case 'E': waypoint.x += value; break;
            case 'W': waypoint.x -= value; break;
            case 'L': rotateWaypoint(waypoint, 'L', value); break;
            case 'R': rotateWaypoint(waypoint, 'R', value); break;
            case 'F':
                ship.x += waypoint.x * value;
                ship.y += waypoint.y * value;
                break;
            }
        }
        int manhattanDistance = std::abs(ship.x) + std::abs(ship.y);
        std::cout << "Manhattanova vzdalenost s waypointem: " << manhattanDistance << std::endl;
    }

    void navigate(const std::vector<std::string>& instructions)
    {
        Position pos;
        for (const auto& instruction : instructions)
        {
            char action = instruction[0];
            int value = std::stoi(instruction.substr(1));
            pos.move(action, value);
        }
        int manhattanDistance = std::abs(pos.x) + std::abs(pos.y);
        std::cout << "Manhattanova vzdalenost od pocatecniho bodu: " << manhattanDistance << std::endl;
    }

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {
        // pozice lodi definovana ve "struct Position"
    }

    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        std::vector<std::string> instructions;
        std::string line;
        std::ifstream file(cesta_soubor);
        if (!file)
        {
            std::cerr << "Chyba pri otevirani souboru: " << cesta_soubor << std::endl;
            return -1; 
        }
        while (std::getline(file, line))
        {
            instructions.push_back(line);
        }

        if (druhe_reseni)
        {
            navigateWithWaypoint(instructions);
        }
        else
        {
            navigate(instructions);
        }
        return 0;
    }
};

#ifndef __TEST__
int main()
{
    std::vector<std::string> filenames = { "vstup_1.txt", "vstup_2.txt", "vstup_3.txt" };

    for (const auto& filename : filenames)
    {
        Lod lod(0, 0, 'E', 10, 1);
        std::cout << "Zpracovavam " << filename << " bez waypointu:" << std::endl;
        lod.naviguj(filename, false);

        Lod lod2(0, 0, 'E', 10, 1);
        std::cout << "Zpracovavam " << filename << " s waypointem:" << std::endl;
        lod2.naviguj(filename, true);
    }                         
    return 0;
}
#endif __TEST__
