#ifndef ORGANISMUS_H
#define ORGANISMUS_H

#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>

class Organismus {
protected:
    int energie;
    int x, y;
    std::string typ;
    int zivotnost;
    int id;
    static int id_counter;

public:
    Organismus(int p_energie, int p_zivotnost)
        : energie(p_energie), zivotnost(p_zivotnost), x(0), y(0), id(id_counter++) {}

    virtual void pohyb(int sirka, int vyska) = 0;
    virtual void konzumace(int hodnota) = 0;
    virtual bool rozmnozit(std::vector<Organismus*>& organismy, int sirka, int vyska) = 0;

    bool isAlive() const { return zivotnost > 0 && energie > 0; }
    int getX() const { return x; }
    int getY() const { return y; }
    std::string getTyp() const { return typ; }
    int getEnergie() const { return energie; }
    int getID() const { return id; }
    void setEnergie(int hodnota) { energie = hodnota; }
    void zmensiZivotnost() { zivotnost--; }
};

int Organismus::id_counter = 1;

class Rostlina : public Organismus {
public:
    Rostlina(int x, int y) : Organismus(10, 300) {
        this->x = x;
        this->y = y;
        typ = "kytka";
    }

    void pohyb(int sirka, int vyska) override {
        // Rostlina se nepohybuje.
    }

    void konzumace(int hodnota) override {
        energie += hodnota;
    }

    bool rozmnozit(std::vector<Organismus*>& organismy, int sirka, int vyska) override {
        if (energie > 15) {
            int newX = std::clamp(x + (rand() % 3) - 1, 0, sirka - 1);
            int newY = std::clamp(y + (rand() % 3) - 1, 0, vyska - 1);

            Rostlina* novaRostlina = new Rostlina(newX, newY);
            organismy.push_back(novaRostlina);
            energie -= 8;
            return true;
        }
        return false;
    }
};

class Zivocich : public Organismus {
protected:
    std::deque<std::pair<int, int>> predchoziPozice;

public:
    Zivocich(int x, int y, int p_energie, int p_zivotnost) 
        : Organismus(p_energie, p_zivotnost) {
        this->x = x;
        this->y = y;
    }

    void pohyb(int sirka, int vyska) override {
        if (predchoziPozice.size() == 3) {
            predchoziPozice.pop_front();
        }

        int novyX, novyY;
        do {
            novyX = x + (rand() % 3) - 1;
            novyY = y + (rand() % 3) - 1;

            novyX = std::clamp(novyX, 0, sirka - 1);
            novyY = std::clamp(novyY, 0, vyska - 1);
        } while (std::find(predchoziPozice.begin(), predchoziPozice.end(), std::make_pair(novyX, novyY)) != predchoziPozice.end());

        x = novyX;
        y = novyY;
        predchoziPozice.push_back({x, y});
    }

    void konzumace(int hodnota) override {
        energie += hodnota;
    }

    virtual bool rozmnozit(std::vector<Organismus*>& organismy, int sirka, int vyska) override = 0;
};

class Bylozravec : public Zivocich {
public:
    Bylozravec(int x, int y) : Zivocich(x, y, 20, 150) {
        typ = "bylozravec";
    }

    bool rozmnozit(std::vector<Organismus*>& organismy, int sirka, int vyska) override {
        if (energie > 40) {
            int newX = std::clamp(x + (rand() % 3) - 1, 0, sirka - 1);
            int newY = std::clamp(y + (rand() % 3) - 1, 0, vyska - 1);

            Bylozravec* novyBylozravec = new Bylozravec(newX, newY);
            organismy.push_back(novyBylozravec);
            energie -= 20;
            return true;
        }
        return false;
    }
};

class Masozravec : public Zivocich {
public:
    Masozravec(int x, int y) : Zivocich(x, y, 30, 200) {
        typ = "masozravec";
    }

    bool rozmnozit(std::vector<Organismus*>& organismy, int sirka, int vyska) override {
        if (energie > 50) {
            int newX = std::clamp(x + (rand() % 3) - 1, 0, sirka - 1);
            int newY = std::clamp(y + (rand() % 3) - 1, 0, vyska - 1);

            Masozravec* novyMasozravec = new Masozravec(newX, newY);
            organismy.push_back(novyMasozravec);
            energie -= 30;
            return true;
        }
        return false;
    }
};

#endif
