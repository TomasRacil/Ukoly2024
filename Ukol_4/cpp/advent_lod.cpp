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
        int direction = 0; // Směr lodi (0 = východ, 90 = sever, 180 = západ, 270 = jih)

        void move(char action, int value)
        {
            switch (action)
            {
            case 'N':
                y += value;
                break;
            case 'S':
                y -= value;
                break;
            case 'E':
                x += value;
                break;
            case 'W':
                x -= value;
                break;
            case 'F':
                switch (direction)
                {
                case 0: 
                    x += value;
                    break;
                case 90: 
                    y += value;
                    break;
                case 180: 
                    x -= value;
                    break;
                case 270: 
                    y -= value;
                    break;
                }
                break;
            case 'L':
                direction = (direction + value) % 360;
                break;
            case 'R':
                direction = (direction - value + 360) % 360;
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
            if (direction == 'L')
            {
                waypoint.x = -tempY;
                waypoint.y = tempX;
            }
            else
            {
                waypoint.x = tempY;
                waypoint.y = -tempX;
            }
            tempX = waypoint.x;
            tempY = waypoint.y;
        }
    }

    void navigateWithWaypoint(const std::vector<std::string>& instructions, const std::string& filename)
    {
        Position ship;
        Waypoint waypoint;
        for (const auto& instruction : instructions)
        {
            char action = instruction[0];
            int value = std::stoi(instruction.substr(1));
            switch (action)
            {
            case 'N':
                waypoint.y += value;
                break;
            case 'S':
                waypoint.y -= value;
                break;
            case 'E':
                waypoint.x += value;
                break;
            case 'W':
                waypoint.x -= value;
                break;
            case 'L':
                rotateWaypoint(waypoint, 'L', value);
                break;
            case 'R':
                rotateWaypoint(waypoint, 'R', value);
                break;
            case 'F':
                ship.x += waypoint.x * value;
                ship.y += waypoint.y * value;
                break;
            }
        }
        int manhattanDistance = std::abs(ship.x) + std::abs(ship.y);
        std::cout << "Manhattanova vzdalenost s waypointem pro soubor " << filename << ": " << manhattanDistance << std::endl;
    }

    void navigate(const std::vector<std::string>& instructions, const std::string& filename)
    {
        Position ship;
        for (const auto& instruction : instructions)
        {
            char action = instruction[0];
            int value = std::stoi(instruction.substr(1));
            ship.move(action, value);
        }
        int manhattanDistance = std::abs(ship.x) + std::abs(ship.y);
        std::cout << "Manhattanova vzdalenost bez waypointu pro soubor " << filename << ": " << manhattanDistance << std::endl;
    }

public:
    Lod(int startX, int startY, int initialDirection, int waypointX, int waypointY)
    {
            // Definuje se na zacatku
    }

    int naviguj(const std::string& cesta_soubor, bool druhe_reseni)
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
            navigateWithWaypoint(instructions, cesta_soubor);
        }
        else
        {
            navigate(instructions, cesta_soubor);
        }
        return 0;
    }
};

int main()
{
    std::vector<std::string> filenames = { "vstup_1.txt", "vstup_2.txt", "vstup_3.txt" };

    for (const auto& filename : filenames)
    {
        Lod lod(0, 0, 0, 10, 1);
        lod.naviguj(filename, false);

        Lod lod2(0, 0, 0, 10, 1);
        lod2.naviguj(filename, true);
    }
    return 0;
}
