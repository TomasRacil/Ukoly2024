#ifndef ORGANISMUS_H
#define ORGANISMUS_H

#include <vector>
#include <iostream>

class Organismus {
public:
    Organismus(int pocatecniEnergie);
    virtual ~Organismus();
    virtual void akce(std::vector<Organismus*>& populace) = 0;
    virtual bool jeRostlina() const = 0;
    bool jeMrtvy() const;
    void pridejEnergii(int hodnota);
    int getEnergie() const;

protected:
    int energie; // Energie organismu
};

#endif // ORGANISMUS_H