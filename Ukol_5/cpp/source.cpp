
#include "prostredi.h"
#include "rostlina.h"
#include "zvire.h"

int main() {
    Prostredi ekosystem;


#include <iostream>
#include <vector>

using namespace std;

// Alias pro seznam organismů
using SeznamOrganismu = vector<class Organismus*>;

// Základní třída Organismus
class Organismus {
public:
    Organismus(int pocatecniEnergie) : energie(pocatecniEnergie) {} // Konstruktor
    virtual ~Organismus() {} // Virtuální destruktor
    virtual void akce(SeznamOrganismu& populace) = 0; // Hlavní chování organismu
    virtual bool jeRostlina() const = 0; // Určuje, zda je to rostlina
    bool jeMrtvy() const { return energie <= 0; } // Zjistí, jestli organismus zemřel
    void pridejEnergii(int hodnota) { energie += hodnota; } // Změna energie
    int getEnergie() const { return energie; } // Získání aktuální energie
protected:
    int energie; // Energie organismu
};

// Třída Rostlina (dědí Organismus)
class Rostlina : public Organismus {
public:
    Rostlina(int pocatecniEnergie) : Organismus(pocatecniEnergie) {} // Konstruktor
    void akce(SeznamOrganismu& populace) override {
        energie += 10; // Rostlina získává energii (fotosyntéza)
        if (energie >= 50) { // Pokud má dost energie, rozmnoží se
            populace.push_back(new Rostlina(20)); // Přidá novou rostlinu
            energie -= 20; // Mateřská rostlina ztrácí energii
            cout << "Rostlina se rozmnožila." << endl;
        }
    }
    bool jeRostlina() const override { return true; } // Je to rostlina
};

// Třída Zvire (dědí Organismus)
class Zvire : public Organismus {
public:
    Zvire(int pocatecniEnergie) : Organismus(pocatecniEnergie) {} // Konstruktor
    void akce(SeznamOrganismu& populace) override {
        energie -= 8; // Ztráta energie (metabolismus + pohyb)
        for (auto& organismus : populace) { // Hledání rostliny k jídlu
            if (organismus->jeRostlina() && !organismus->jeMrtvy()) {
                organismus->pridejEnergii(-10); // Rostlina ztratí energii
                energie += 15; // Zvíře získává energii
                cout << "Zvíře snědlo rostlinu." << endl;
                break;
            }
        }
        if (energie >= 100) { // Pokud má dost energie, rozmnoží se
            populace.push_back(new Zvire(50)); // Přidá nové zvíře
            energie -= 50; // Mateřské zvíře ztrácí energii
            cout << "Zvíře se rozmnožilo." << endl;
        }
    }
    bool jeRostlina() const override { return false; } // Není to rostlina
};

// Třída Prostredi (spravuje ekosystém)
class Prostredi {
public:
    Prostredi() {} // Konstruktor
    ~Prostredi() { // Destruktor (uvolnění paměti)
        for (auto organismus : populace) {
            delete organismus;
        }
    }
    void pridatOrganismus(Organismus* organismus) {
        populace.push_back(organismus); // Přidání organismu do ekosystému
    }
    void simulace(int kola) {
        for (int kolo = 1; kolo <= kola; ++kolo) {
            cout << "\nKolo " << kolo << ":" << endl;
            for (auto& organismus : populace) { // Každý organismus provede svou akci
                if (!organismus->jeMrtvy()) {
                    organismus->akce(populace);
                    cout << "Organismus s energií: " << organismus->getEnergie() << endl;
                }
            }
            odstranMrtve(); // Odstranění mrtvých organismů
            cout << "Počet organismů: " << populace.size() << endl;
        }
    }
private:
    SeznamOrganismu populace; // Kolekce organismů
    void odstranMrtve() {
        for (size_t i = 0; i < populace.size(); ++i) {
            if (populace[i]->jeMrtvy()) {
                delete populace[i]; // Uvolnění paměti mrtvého organismu
                populace.erase(populace.begin() + i); // Odstranění z populace
                --i; // Korekce indexu
            }
        }
    }
};

// Funkce main
int main() {
    Prostredi ekosystem; // Vytvoření ekosystému

    // Přidání organismů
    ekosystem.pridatOrganismus(new Rostlina(30));
    ekosystem.pridatOrganismus(new Zvire(60));
    ekosystem.pridatOrganismus(new Rostlina(40));
    ekosystem.pridatOrganismus(new Zvire(80));

    // Spuštění simulace na 10 kol
    ekosystem.simulace(10);

    return 0;
}
