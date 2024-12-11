#include "prostredi.h"
#include "organismus.h"

// Konstruktor prostředí - nastavuje výšku a šířku prostředí.
Prostredi::Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}

// Metoda pro simulaci jednoho kroku prostředí.
void Prostredi::krok() {
    // 1. Každý organismus vykoná své tři hlavní akce: pohyb, metabolismus a rozmnožování.
    for (Organismus *o : organismy) {
        o->pohyb();
        o->metabolismus();
        o->rozmnozovani();
    }

    // 2. Vyhodnocení interakcí mezi organismy (např. konzumace).
    for (Organismus *o1 : organismy) {
        for (Organismus *o2 : organismy) {
            // Pokud jsou na stejné pozici a nejsou to stejná instance.
            if (o1 != o2 && o1->x == o2->x && o1->y == o2->y) {
                o1->konzumuj(o2); // o1 se pokusí konzumovat o2.
            }
        }
    }

    organismy.remove_if([](Organismus *o)
                        { return !o->JeZivy(); });}

void Prostredi :: odeberOrganismus(Organismus *o)
{
    organismy.remove(o);
}

void Prostredi :: vypisStav()
{
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (Organismus *o : organismy)
    {
        switch (o->getType())
        {
            case 'R':
                pocetRostlin++;
                break;
            case 'B':
                pocetBylozravcu++;
                break;
            case 'M':
                pocetMasozravcu++;
                break;
        }
    }
    cout << "Rostliny: " << pocetRostlin
         << ", Bylozravci: " << pocetBylozravcu
         << ", Masozravci: " << pocetMasozravcu << endl;
}