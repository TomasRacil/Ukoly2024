import csv
from .Kniha import Kniha
from .Ctenar import Ctenar
import datetime


class Knihovna:
    def __init__(self, nazev: str = "Neznámá knihovna"):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}

    @classmethod
    def z_csv(cls, soubor: str):
        with open(soubor, "r", encoding="utf-8") as file:
            reader = csv.reader(file)
            prvni_radek = next(reader)
            nazev_knihovny = prvni_radek[0].split(":", 1)[1].strip()
            knihovna = cls(nazev_knihovny)

            next(reader)  # přeskočení záhlaví
            for radek in reader:
                if radek[0] == "kniha":
                    knihovna.knihy.append(Kniha(radek[1], radek[2], int(radek[3]), radek[4]))
                elif radek[0] == "ctenar":
                    knihovna.ctenari.append(Ctenar(radek[5], radek[6]))
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    def kniha_existuje(funkce):
        def wrapper(self, isbn: str, *args, **kwargs):
            if not any(kniha.isbn == isbn for kniha in self.knihy):
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        return [k for k in self.knihy if isbn in k.isbn or klicova_slovo.lower() in k.nazev.lower()]

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        del self.vypujcene_knihy[isbn]
