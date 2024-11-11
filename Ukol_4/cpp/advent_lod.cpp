#include <iostream>
#include <fstream>
#include <string>;

struct Waypoint {
    int posX, posY;
};

class Lod
{
private:
public:
    int currentX, currentY, targetX, targetY, countOfTiles, state, manhattan;
    char way, previous;

    Waypoint waypoint; // struktura s x / y souřadnicí

    void getCoordinates(std::string coordinate); // načtení řádku, získání souřadnice a posunu, pohyb lodi na x/y podle STATE -> určuje směr lodi kam míří

    void getCoordinatesSecondSol(std::string coordinate); // -||- pohyb waypointu, pohyb lodi a získání manhatanu, reset x/y waypointu
    
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y);

    int naviguj(std::string cesta_soubor, bool druhe_reseni);

};



Lod::Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y) {
    currentX = x, currentY = y, targetX = cilovy_bod_x, targetY = cilovy_bod_y, way = smer;
    state = 0, manhattan = 0;
    waypoint.posX = x; waypoint.posY = y;
}

void Lod::getCoordinatesSecondSol(std::string coordinate) {
    int rem = 0;
    way = coordinate[0];
    coordinate[0] = '0';
    countOfTiles = stoi(coordinate);

    if (state == 0) {
        switch (way) {
        case 'N':
            previous = 'N';
            waypoint.posX -= countOfTiles;
            break;
        case 'E':
            previous = 'E';
            waypoint.posY += countOfTiles;
            break;
        case 'S':
            previous = 'S';
            waypoint.posX += countOfTiles;
            break;
        case 'W':
            previous = 'W';
            waypoint.posY -= countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            if (previous == 'S' || previous == 'E') {
                manhattan += (waypoint.posX + waypoint.posY);
            }
            else {
                manhattan -= (waypoint.posX + waypoint.posY);
            }
            waypoint.posX = 0;
            waypoint.posY = 0;
            break;
        }
    }
    else if (state == 1) {
        switch (way) {
        case 'N':
            previous = 'N';
            waypoint.posY -= countOfTiles;
            break;
        case 'E':
            previous = 'E';
            waypoint.posX -= countOfTiles;
            break;
        case 'S':
            previous = 'S';
            waypoint.posY += countOfTiles;
            break;
        case 'W':
            previous = 'W';
            waypoint.posX += countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            if (previous == 'S' || previous == 'W') {
                manhattan += (waypoint.posX + waypoint.posY);
            }
            else {
                manhattan -= (waypoint.posX + waypoint.posY);
            }
            waypoint.posX = 0;
            waypoint.posY = 0;
            break;
        }
    }
    else if (state == 2) {
        switch (way) {
        case 'N':
            previous = 'N';
            waypoint.posX += countOfTiles;
            break;
        case 'E':
            previous = 'E';
            waypoint.posY -= countOfTiles;
            break;
        case 'S':
            previous = 'S';
            waypoint.posX -= countOfTiles;
            break;
        case 'W':
            previous = 'W';
            waypoint.posY += countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            if (previous == 'N' || previous == 'W') {
                manhattan += (waypoint.posX + waypoint.posY);
            }
            else {
                manhattan -= (waypoint.posX + waypoint.posY);
            }
            waypoint.posX = 0;
            waypoint.posY = 0;
            break;
        }
    }
    else {
        switch (way) {
        case 'N':
            previous = 'N';
            waypoint.posY += countOfTiles;
            break;
        case 'E':
            previous = 'E';
            waypoint.posX += countOfTiles;
            break;
        case 'S':
            previous = 'S';
            waypoint.posY -= countOfTiles;
            break;
        case 'W':
            previous = 'W';
            waypoint.posX -= countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            if (previous == 'N' || previous == 'E') {
                manhattan += (waypoint.posX + waypoint.posY);
            }
            else {
                manhattan -= (waypoint.posX + waypoint.posY);
            }
            waypoint.posX = 0;
            waypoint.posY = 0;
            break;
        }
    }
}


void Lod::getCoordinates(std::string coordinate) {
    int rem = 0;
    way = coordinate[0];
    coordinate[0] = '0';
    countOfTiles = stoi(coordinate);
    reset:
    if (state == 0) {
        switch (way) {
        case 'N':
            previous = 'N';
            currentX -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'E':
            previous = 'E';
            currentY += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'S':
            previous = 'S';
            currentX += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'W':
            previous = 'W';
            currentY -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            way = previous;
            goto reset;
            break;
        }
    }
    else if (state == 1) {
        switch (way) {
        case 'N':
            previous = 'N';
            currentY -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'E':
            previous = 'E';
            currentX -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'S':
            previous = 'S';
            currentY += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'W':
            previous = 'W';
            currentX += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            way = previous;
            goto reset;
            break;
        }
    }
    else if (state == 2) {
        switch (way) {
        case 'N':
            previous = 'N';
            currentX += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'E':
            previous = 'E';
            currentY -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'S':
            previous = 'S';
            currentX -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'W':
            previous = 'W';
            currentY += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            way = previous;
            goto reset;
            break;
        }
    }
    else {
        switch (way) {
        case 'N':
            previous = 'N';
            currentY += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'E':
            previous = 'E';
            currentX += countOfTiles;
            manhattan += countOfTiles;
            break;
        case 'S':
            previous = 'S';
            currentY -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'W':
            previous = 'W';
            currentX -= countOfTiles;
            manhattan -= countOfTiles;
            break;
        case 'R':
            rem = 0;
            while (countOfTiles >= 90) {
                rem++;
                countOfTiles -= 90;
            }
            state += rem;
            while (state > 4) {
                state = 0;
                rem -= 4;
                state = rem;
            }
            break;
        case 'L':
            rem = 0;
            while (countOfTiles >= 90) {
                rem--;
                countOfTiles -= 90;
            }
            state += rem;
            if (state < 0) {
                state = 4 - rem;
            }
            break;
        case 'F':
            way = previous;
            goto reset;
            break;
        }
    }

}

int Lod::naviguj(std::string filePath, bool secondSolution) {
    std::string line;
    std::fstream file(filePath);
    if (secondSolution) {
        while (!file.eof()) {
            std::getline(file, line);
            getCoordinatesSecondSol(line);
        }
    }
    else {
        while (!file.eof()) {
            std::getline(file, line);
            getCoordinates(line);
        }
    }
    manhattan = abs(manhattan);
    return manhattan;
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
