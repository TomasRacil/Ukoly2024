#ifndef ORGANISMUS_H
#define ORGANISMUS_H

#include <string>
#include <cstdlib>

class Organismus {
protected:
    int x, y;       
    int energie;    
    bool alive;     

public:
    Organismus(int x, int y) : x(x), y(y), energie(100), alive(true) {}

    virtual ~Organismus() {}

    virtual void pohyb(int sirka, int vyska) {
        x = (x + rand() % 3 - 1 + sirka) % sirka; 
        y = (y + rand() % 3 - 1 + vyska) % vyska; 
    }

    virtual std::string getTyp() const = 0; 

    void zmensiZivotnost() {
        energie -= 10;
        if (energie <= 0) alive = false;
    }

    bool isAlive() const { return alive; }

    int getX() const { return x; }
    int getY() const { return y; }
};

class Rostlina : public Organismus {
public:
    Rostlina(int x, int y) : Organismus(x, y) {}

    std::string getTyp() const override { return "Rostlina"; }
};

class Zivocich : public Organismus {
public:
    Zivocich(int x, int y) : Organismus(x, y) {}

    std::string getTyp() const override { return "Zivocich"; }
};

#endif
