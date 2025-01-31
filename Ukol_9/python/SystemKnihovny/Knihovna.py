from __future__ import annotations
from .Kniha import Kniha
from .Ctenar import Ctenar
import csv
import datetime


class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}

    @staticmethod
    def z_csv(soubor: str):
        with open(soubor, "r") as f:
            nazev = f.readline().split(":")[1].strip()
            knihovna = Knihovna(nazev)

            f.readline() # skip layout
            for line in f:
                typ = line.strip().split(",")[0]
                if typ == "kniha":
                    rozdelena = line.strip().split(",")
                    rozdelena.remove("kniha") # skip type
                    rozdelena = [x for x in rozdelena if x]
                    nazev, autor, rok_vydani, isbn = rozdelena
                    kniha = Kniha(nazev, autor, int(rok_vydani), isbn)
                    knihovna.pridej_knihu(kniha)
                elif typ == "ctenar":
                    rozdelena = line.strip().split(",")
                    jmeno, prijmeni = rozdelena[-2], rozdelena[-1]
                    ctenar = Ctenar(jmeno, prijmeni)
                    knihovna.registruj_ctenare(ctenar)
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def odeber_knihu(self, isbn: str):
        if isbn not in [k.isbn for k in self.knihy]:
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c != ctenar]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in [k.isbn for k in self.knihy]:
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.datetime.now().date())

    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        self.vypujcene_knihy.pop(isbn)

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        if isbn:
            return [k for k in self.knihy if k.isbn == isbn]
        elif klicova_slovo:
            return [k for k in self.knihy if klicova_slovo in k.nazev or klicova_slovo in k.autor]
        else:
            raise ValueError("Musíte zadat klíčové slovo nebo ISBN")

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        return [c for c in self.ctenari if klicova_slovo in c.jmeno or klicova_slovo in c.prijmeni]

    def __str__(self):
        return f"Knihovna: {self.nazev}, knihy: {len(self.knihy)}, čtenáři: {len(self.ctenari)}"
