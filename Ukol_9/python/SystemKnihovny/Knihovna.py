import datetime
import csv
from .Kniha import Kniha
from .Ctenar import Ctenar


class Knihovna:
    def __init__(self, nazev):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}  # ISBN -> [ctenar, datum_vypujceni]

    def pridej_knihu(self, kniha):
        self.knihy.append(kniha)

    def odeber_knihu(self, isbn):
        kniha = next((k for k in self.knihy if k.isbn == isbn), None)
        if not kniha:
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        self.knihy.remove(kniha)

    def vypujc_knihu(self, isbn, ctenar):
        kniha = next((k for k in self.knihy if k.isbn == isbn), None)
        if not kniha:
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = [ctenar, datetime.date.today()]

    def vrat_knihu(self, isbn, ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError("Tento čtenář tuto knihu nevypůjčil.")
        del self.vypujcene_knihy[isbn]

    def registruj_ctenare(self, ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar):
        if ctenar in self.ctenari:
            self.ctenari.remove(ctenar)

    def vyhledej_knihu(self, klicova_slovo=None, isbn=None):
            if klicova_slovo:
                return [k for k in self.knihy if klicova_slovo.lower() in k.nazev.lower()]
            if isbn:
                return [k for k in self.knihy if k.isbn == isbn]
            return []

    def vyhledej_ctenare(self, klicova_slovo=None, cislo_prukazky=None):
        if klicova_slovo:
            return [c for c in self.ctenari if klicova_slovo.lower() in c.jmeno.lower()]
        if cislo_prukazky:
            return [c for c in self.ctenari if c.cislo_prukazky == cislo_prukazky]
        return []


    @classmethod
    def z_csv(cls, soubor):
        with open(soubor, newline="") as csvfile:
            reader = csv.reader(csvfile)
            nazev_knihovny = next(reader)[0].split(":")[1]
            knihovna = cls(nazev_knihovny)
            next(reader)  # Přeskočí hlavičku
            for row in reader:
                if row[0] == "kniha":
                    knihovna.knihy.append(Kniha(row[1], row[2], int(row[3]), row[4]))
                elif row[0] == "ctenar":
                    knihovna.ctenari.append(Ctenar(row[5], row[6]))
        return knihovna
