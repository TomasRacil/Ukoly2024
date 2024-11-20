
//tady je jedna verze ktará mi jakš takš funguje dole jsou ty části rozdělené ale uplně nevím jak to odevzdat správně takže to dám jako komentář
#include <iostream>
#include <vector>

using namespace std;

// Abstraktní třída Organismus
class Organismus {
public:
    virtual void update() = 0; // Čistě virtuální metoda
    virtual ~Organismus() = default;
};

// Třída Zvire, dědí z Organismus
class Zvire : public Organismus {
protected:
    int energie;
    int pohybEnergie;
public:
    Zvire(int energie, int pohybEnergie) : energie(energie), pohybEnergie(pohybEnergie) {
        cout << "Constructor Zvire" << endl;
    }
    void pohyb() {
        energie -= pohybEnergie;
        cout << "Zvire se pohybuje, energie: " << energie << endl;
    }
    ~Zvire() override = default;
};

// Třída Rostlina, dědí z Organismus
class Rostlina : public Organismus {
public:
    void update() override {
        cout << "Rostlina roste." << endl;
    }
};

// Třída Bylozravec, dědí z Zvire
class Bylozravec : public Zvire {
public:
    Bylozravec(int energie) : Zvire(energie, 10) {
        cout << "Constructor Bylozravec" << endl;
    }
    void update() override {
        pohyb();
        cout << "Bylozravec hledá potravu." << endl;
    }
};

// Třída Masozravec, dědí z Zvire
class Masozravec : public Zvire {
public:
    Masozravec(int energie) : Zvire(energie, 20) {
        cout << "Constructor Masozravec" << endl;
    }
    void update() override {
        pohyb();
        cout << "Masozravec loví." << endl;
    }
};

// Třída Prostredi, která spravuje všechny organismy
class Prostredi {
private:
    vector<Organismus*> organismy;
public:
    void pridatOrganismus(Organismus* organismus) {
        organismy.push_back(organismus);
    }
    void aktualizovat() {
        for (auto organismus : organismy) {
            organismus->update();
        }
    }
    ~Prostredi() {
        for (auto organismus : organismy) {
            delete organismus;
        }
    }
};

int main() {
    Prostredi prostredi;

    prostredi.pridatOrganismus(new Rostlina());
    prostredi.pridatOrganismus(new Bylozravec(100));
    prostredi.pridatOrganismus(new Masozravec(150));

    cout << "První aktualizace prostředí:" << endl;
    prostredi.aktualizovat();

    cout << "Druhá aktualizace prostředí:" << endl;
    prostredi.aktualizovat();

    return 0;
}

//tady je ten kod podle zadaní rozdělený na více menších ale jak jsem říkal uplně nevím jak to mám odevzdat správně a pořád mi to nechce fungovat tak jak bych chtěl

/*
// ========================== organismus.h ==========================
#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Organismus {
public:
    virtual void update() = 0; // Abstraktní metoda
    virtual ~Organismus() = default;
};

#endif // ORGANISMUS_H

// ========================== zvire.h ==========================
#ifndef ZVIRE_H
#define ZVIRE_H

#include "organismus.h"

class Zvire : public Organismus {
protected:
    int energie;
public:
    Zvire(int energie);
    virtual void pohyb();
    virtual ~Zvire() = default;
};

#endif // ZVIRE_H

// ========================== rostlina.h ==========================
#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.h"

class Rostlina : public Organismus {
public:
    void update() override;
};

#endif // ROSTLINA_H

// ========================== bylozravec.h ==========================
#ifndef BYLOZRAVEC_H
#define BYLOZRAVEC_H

#include "zvire.h"

class Bylozravec : public Zvire {
public:
    Bylozravec(int energie);
    void update() override;
};

#endif // BYLOZRAVEC_H

// ========================== masozravec.h ==========================
#ifndef MASOZRAVEC_H
#define MASOZRAVEC_H

#include "zvire.h"

class Masozravec : public Zvire {
public:
    Masozravec(int energie);
    void update() override;
};

#endif // MASOZRAVEC_H

// ========================== prostredi.h ==========================
#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <vector>
#include "organismus.h"

class Prostredi {
private:
    std::vector<Organismus*> organismy;
public:
    ~Prostredi();
    void pridatOrganismus(Organismus* organismus);
    void aktualizovat();
};

#endif // PROSTREDI_H

// ========================== organismus.cpp ==========================
#include "organismus.h"
// Zde není potřeba implementace, protože jde o abstraktní třídu.

// ========================== zvire.cpp ==========================
#include "zvire.h"
#include <iostream>

Zvire::Zvire(int energie) : energie(energie) {}

void Zvire::pohyb() {
    energie -= 10;
    std::cout << "Zvire se pohybuje, energie: " << energie << "\n";
}

// ========================== rostlina.cpp ==========================
#include "rostlina.h"
#include <iostream>

void Rostlina::update() {
    std::cout << "Rostlina roste.\n";
}

// ========================== bylozravec.cpp ==========================
#include "bylozravec.h"
#include <iostream>

Bylozravec::Bylozravec(int energie) : Zvire(energie) {}

void Bylozravec::update() {
    pohyb();
    std::cout << "Bylozravec hledá potravu.\n";
}

// ========================== masozravec.cpp ==========================
#include "masozravec.h"
#include <iostream>

Masozravec::Masozravec(int energie) : Zvire(energie) {}

void Masozravec::update() {
    pohyb();
    std::cout << "Masozravec loví.\n";
}

// ========================== prostredi.cpp ==========================
#include "prostredi.h"

Prostredi::~Prostredi() {
    for (auto organismus : organismy) {
        delete organismus;
    }
}

void Prostredi::pridatOrganismus(Organismus* organismus) {
    organismy.push_back(organismus);
}

void Prostredi::aktualizovat() {
    for (auto organismus : organismy) {
        organismus->update();
    }
}

// ========================== source.cpp ==========================
#include "prostredi.h"
#include "bylozravec.h"
#include "masozravec.h"
#include "rostlina.h"

int main() {
    Prostredi prostredi;

    prostredi.pridatOrganismus(new Rostlina());
    prostredi.pridatOrganismus(new Bylozravec(100));
    prostredi.pridatOrganismus(new Masozravec(150));

    prostredi.aktualizovat();

    return 0;
}

*/