#include <iostream>
#include <string>

struct Uzel {
    int data;
    Uzel* dalsi;
};

// Funkce pro vytvoření nového uzlu
Uzel* vytvorUzel(int data) {
    Uzel* novyUzel = new Uzel();
    novyUzel->data = data;
    novyUzel->dalsi = nullptr;
    return novyUzel;
}

// Funkce pro vložení uzlu na začátek seznamu
void vlozNaZacatek(Uzel** hlava, int data) {
    Uzel* novyUzel = vytvorUzel(data);
    novyUzel->dalsi = *hlava;
    *hlava = novyUzel;
}

// Funkce pro vložení uzlu na konec seznamu
void vlozNaKonec(Uzel** hlava, const int data) {
    Uzel* novyUzel = vytvorUzel(data);
    if (*hlava == nullptr) {
        *hlava = novyUzel;
    } else {
        Uzel* temp = *hlava;
        while (temp->dalsi != nullptr) {
            temp = temp->dalsi;
        }
        temp->dalsi = novyUzel;
    }
}

// Funkce pro vložení na index
void vlozNaIndex(Uzel** hlava, int data, int index) {
    if (index == 0) {
        vlozNaZacatek(hlava, data);
        return;
    }
    Uzel* novyUzel = vytvorUzel(data);
    Uzel* temp = *hlava;
    for (int i = 0; i < index - 1 && temp != nullptr; i++) {
        temp = temp->dalsi;
    }
    if (temp == nullptr) {
        std::cout << "Index mimo rozsah" << std::endl;
        delete novyUzel;
    } else {
        novyUzel->dalsi = temp->dalsi;
        temp->dalsi = novyUzel;
    }
}

// Funkce pro smazání uzlu ze začátku seznamu
void smazNaZacatku(Uzel** hlava) {
    if (*hlava == nullptr) {
        std::cout << "Seznam je prázdný" << std::endl;
        return;
    }
    Uzel* temp = *hlava;
    *hlava = (*hlava)->dalsi;
    delete temp;
}

// Funkce pro smazání uzlu z konce seznamu
void smazNaKonci(Uzel** hlava) {
    if (*hlava == nullptr) {
        std::cout << "Seznam je prázdný" << std::endl;
        return;
    }
    if ((*hlava)->dalsi == nullptr) {
        delete *hlava;
        *hlava = nullptr;
        return;
    }
    Uzel* temp = *hlava;
    while (temp->dalsi->dalsi != nullptr) {
        temp = temp->dalsi;
    }
    delete temp->dalsi;
    temp->dalsi = nullptr;
}

// Funkce pro smazání uzlu na indexu
void smazNaIndexu(Uzel* hlava, int index) {
    if (index == 0) {
        smazNaZacatku(&hlava);
        return;
    }
    Uzel* temp = hlava;
    for (int i = 0; i < index - 1 && temp != nullptr; i++) {
        temp = temp->dalsi;
    }
    if (temp == nullptr || temp->dalsi == nullptr) {
        std::cout << "Index mimo rozsah" << std::endl;
    } else {
        Uzel* uzelKeSmazani = temp->dalsi;
        temp->dalsi = temp->dalsi->dalsi;
        delete uzelKeSmazani;
    }
}

// Funkce pro nalezení prvního výskytu
int najdiPrvniVyskyt(Uzel* hlava, int hodnota) {
    Uzel* temp = hlava;
    int index = 0;
    while (temp != nullptr) {
        if (temp->data == hodnota) {
            return index;
        }
        temp = temp->dalsi;
        index++;
    }
    return -1; // Hodnota nenalezena
}

// Funkce pro třídění seznamu
void seradSeznam(Uzel** hlava) {
    if (*hlava == nullptr || (*hlava)->dalsi == nullptr) {
        return;
    }
    Uzel* serazeny = nullptr;
    Uzel* aktualni = *hlava;
    while (aktualni != nullptr) {
        Uzel* dalsi = aktualni->dalsi;
        if (serazeny == nullptr || serazeny->data >= aktualni->data) {
            aktualni->dalsi = serazeny;
            serazeny = aktualni;
        } else {
            Uzel* temp = serazeny;
            while (temp->dalsi != nullptr && temp->dalsi->data < aktualni->data) {
                temp = temp->dalsi;
            }
            aktualni->dalsi = temp->dalsi;
            temp->dalsi = aktualni;
        }
        aktualni = dalsi;
    }
    *hlava = serazeny;
}

// Funkce pro smazání (dealokaci) seznamu
void smazSeznam(Uzel** hlava) {
    Uzel* aktualni = *hlava;
    Uzel* dalsi;
    while (aktualni != nullptr) {
        dalsi = aktualni->dalsi;
        delete aktualni;
        aktualni = dalsi;
    }
    *hlava = nullptr;
}

// Operátor pro tisk dat
std::ostream& operator<<(std::ostream& os, Uzel* hlava) {
    Uzel* temp = hlava;
    while (temp != nullptr) {
        os << temp->data << " -> ";
        temp = temp->dalsi;
    }
    os << "nullptr";
    return os;
}

#ifndef __TEST__ 
int main() {
    // Vytvoření seznamu
    Uzel* hlava = nullptr;
    vlozNaZacatek(&hlava, 1);
    vlozNaZacatek(&hlava, 2);
    vlozNaKonec(&hlava, 3);
    vlozNaKonec(&hlava, 4);
    vlozNaIndex(&hlava, 5, 2);
    std::cout << "Seznam po vložení prvků: " << hlava << std::endl;
    std::cout << "První výskyt hodnoty 3 je na indexu: " << najdiPrvniVyskyt(hlava, 3) << std::endl;
    std::cout << "Seznam před tříděním: " << hlava << std::endl;
    seradSeznam(&hlava);
    std::cout << "Seznam po třídění: " << hlava << std::endl;
    smazNaZacatku(&hlava);
    smazNaKonci(&hlava);
    std::cout << "Seznam po smazání prvků: " << hlava << std::endl;
    smazNaIndexu(hlava, 1);
    std::cout << "Seznam po smazání prvků: " << hlava << std::endl;
    smazSeznam(&hlava);

    return 0;
}
#endif 
