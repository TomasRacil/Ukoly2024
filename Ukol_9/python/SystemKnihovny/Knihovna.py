from __future__ import annotations
from .Kniha import Kniha
from .Ctenar import Ctenar
import csv
import datetime


class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy: list[Kniha] = []
        self.ctenari: list[Ctenar] = []
        self.vypujcene_knihy = {}

    def kniha_existuje(funkce):
        def wrapper(self, isbn: str, *args, **kwargs):
            if not any(kniha.isbn == isbn for kniha in self.knihy):
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        knihovna = None
        with open(soubor, newline='', encoding='utf-8') as csvfile:
            reader = csv.reader(csvfile)
            prvni_radek = next(reader)
            knihovna_nazev = prvni_radek[0].split(':')[1].strip()
            knihovna = cls(knihovna_nazev)
            next(reader) 
            for row in reader:
                if row[0] == 'kniha':
                    knihovna.pridej_knihu(Kniha(row[1], row[2], int(row[3]), row[4]))
                elif row[0] == 'ctenar':
                    knihovna.registruj_ctenare(Ctenar(row[5], row[6]))
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        return [kniha for kniha in self.knihy if klicova_slovo in kniha._nazev or klicova_slovo in kniha._autor or kniha.isbn == isbn]

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c != ctenar]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        return [ctenar for ctenar in self.ctenari if klicova_slovo in ctenar._jmeno or klicova_slovo in ctenar._prijmeni or ctenar.cislo_prukazky == cislo_prukazky]

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"kniha {isbn} není vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena tímto čtenřem.")
        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        knihy_str = "\n".join(str(kniha) for kniha in self.knihy)
        ctenari_str = "\n".join(str(ctenar) for ctenar in self.ctenari)
        return f"Knihovna: {self.nazev}\nKnihy:\n{knihy_str}\nČtenáři:\n{ctenari_str}"
