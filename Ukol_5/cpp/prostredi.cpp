//includes in cpp file to avoid cyclic reference
#include "organismus.hpp"
#include "prostredi.hpp"

Prostredi::Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}



void Prostredi::krok() {
    //using iterator so the deletion can happen safely
    for (auto it = organismy.begin(); it != organismy.end();) {
        (*it)->pohyb();
        (*it)->metabolismus();
        (*it)->rozmnozovani();

        //consume other organism if it's on the same position
        for (auto it2 = organismy.begin(); it2 != organismy.end(); ++it2) {
            if (it != it2 && (*it)->x == (*it2)->x && (*it)->y == (*it2)->y) {
                (*it)->konzumuj(*it2);
            }
        }

        if (!(*it)->jeZivy()) {
            //fixed memory leak in v1.0 - object was dynamically allocated and must be deleted before erasing from the list
            delete (*it);
            it = organismy.erase(it);
        }
        else {
            ++it;
        }
    }
}


void Prostredi::odeberOrganismus(Organismus *o) {
    //delete all occurences of o and free dynamically allocated memory
    //calling remove() and then deleting can result in undefined behaviour, so iterator should be used like this:
    for (auto it = organismy.begin(); it != organismy.end(); ++it) {
        if (*it == o) {
            delete *it;
            organismy.erase(it);
        }
    }
}

void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (Organismus *o : organismy) {
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
    std::cout << "Rostliny: "       << pocetRostlin
              << ", Bylozravci: "   << pocetBylozravcu
              << ", Masozravci: "   << pocetMasozravcu << "\n"; //Using std::endl is a bad practice because it unnecessarily flushes the buffer and slows down the program."
}

Prostredi::~Prostredi() {
    //Free all organisms by their destruction in the most brutal possible way - by using delete operator
    for (auto it = organismy.begin(); it != organismy.end(); ++it) {
        delete *it;
    }
}