#ifndef ORGANISMUS_H
#define ORGANISMUS_H

#include <string>

class Organismy {
protected:
    int energie;
    int x, y;
    std::string type;
public:
    Organismy(int p_x, int p_y, int p_energie);
    virtual void pohyb() = 0;
    int getX() const;
    int getY() const;
    int getEnergie() const;
    std::string getType() const;
    void setEnergie(int en);
};

#endif // ORGANISMUS_H
