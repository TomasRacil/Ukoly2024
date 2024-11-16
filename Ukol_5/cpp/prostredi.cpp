#include "organismus.hpp"
#include "prostredi.hpp"
#include "rostlina.hpp"
#include "bylozravec.hpp"
#include "masozravec.hpp"

Prostredi::Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}

void Prostredi::krok() {

    for (Organismus *o1 : organismy)
    {
        //check if organism is dead
        organismy.remove_if([](Organismus *o1) {return !o1->jeZivy();});
        if (!o1->jeZivy()) {
            organismy.remove(o1);
            delete o1;
            continue;
        }


        o1->pohyb();
        o1->metabolismus();
        o1->rozmnozovani();
        
        for (Organismus *o2 : organismy)
        {
            if (o1 != o2 && o1->x == o2->x && o1->y == o2->y)
            {
                o1->konzumuj(o2);
            }
        }

    }

}

void Prostredi::odeberOrganismus(Organismus *o) {
    organismy.remove(o);
    
    //TODO: resolve memory leak
    delete o;

}

void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (Organismus *o : organismy)
    {
        switch(o->getTyp()) {
            case 'R':
                pocetRostlin++;
                break;
            case 'M':
                pocetMasozravcu++;
                break;
            case 'B':
                pocetBylozravcu++;
                break;
        }
    }
    std::cout << "Rostliny: " << pocetRostlin
                << ", Bylozravci: " << pocetBylozravcu
                << ", Masozravci: " << pocetMasozravcu << std::endl;
}
