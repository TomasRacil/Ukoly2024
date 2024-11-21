#include <iostream>
#include <vector>

// ========================== organismus.h ==========================
class Organismus {
public:
    virtual void update() = 0; // Abstraktní metoda
    virtual ~Organismus() = default;
};

// ========================== zvire.h ==========================
class Zvire : public Organismus {
protected:
    int energie;
public:
    Zvire(int energie);
    virtual void pohyb();
    virtual ~Zvire() = default;
};

// ========================== rostlina.h ==========================
class Rostlina : public Organismus {
public:
    void update() override;
};

// ========================== bylozravec.h ==========================
class Bylozravec : public Zvire {
public:
    Bylozravec(int energie);
    void update() override;
};

// ========================== masozravec.h ==========================
class Masozravec : public Zvire {
public:
    Masozravec(int energie);
    void update() override;
};

// ========================== prostredi.h ==========================
class Prostredi {
private:
    std::vector<Organismus*> organismy;
public:
    ~Prostredi();
    void pridatOrganismus(Organismus* organismus);
    void aktualizovat();
};

// ========================== zvire.cpp ==========================
Zvire::Zvire(int energie) : energie(energie) {}

void Zvire::pohyb() {
    energie -= 10;
    std::cout << "Zvire se pohybuje, energie: " << energie << "\n";
}

// ========================== rostlina.cpp ==========================
void Rostlina::update() {
    std::cout << "Rostlina roste.\n";
}

// ========================== bylozravec.cpp ==========================
Bylozravec::Bylozravec(int energie) : Zvire(energie) {}

void Bylozravec::update() {
    pohyb();
    std::cout << "Bylozravec hledá potravu.\n";
}

// ========================== masozravec.cpp ==========================
Masozravec::Masozravec(int energie) : Zvire(energie) {}

void Masozravec::update() {
    pohyb();
    std::cout << "Masozravec loví.\n";
}

// ========================== prostredi.cpp ==========================
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
int main() {
    Prostredi prostredi;

    prostredi.pridatOrganismus(new Rostlina());
    prostredi.pridatOrganismus(new Bylozravec(100));
    prostredi.pridatOrganismus(new Masozravec(150));

    prostredi.aktualizovat();

    return 0;
}