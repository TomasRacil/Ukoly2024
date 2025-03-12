import csv
from datetime import date
from .Kniha import Kniha
from .Ctenar import Ctenar

class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}

    def kniha_existuje(funkce):
        def wrapper(self, isbn, *args, **kwargs):
            if not any(kniha.isbn == isbn for kniha in self.knihy):
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> "Knihovna":
        with open(soubor, mode="r", encoding="utf-8") as csvfile:
            reader = csv.reader(csvfile)
            prvni_radek = next(reader)
            nazev_knihovny = prvni_radek[0].split(":")[1].strip() if "Knihovna:" in prvni_radek[0] else "Neznámá knihovna"
            knihovna = cls(nazev_knihovny)

            next(reader)  # Přeskočení záhlaví

            for row in reader:
                if row[0] == "kniha":
                    knihovna.knihy.append(Kniha(row[1], row[2], int(row[3]), row[4]))
                elif row[0] == "ctenar":
                    knihovna.ctenari.append(Ctenar(row[5], row[6]))

        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        if isbn:
            return [kniha for kniha in self.knihy if kniha.isbn == isbn]
        return [kniha for kniha in self.knihy if klicova_slovo.lower() in kniha.nazev.lower()]

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari.remove(ctenar)

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        if cislo_prukazky:
            return [ctenar for ctenar in self.ctenari if ctenar.cislo_prukazky == cislo_prukazky]
        return [ctenar for ctenar in self.ctenari if klicova_slovo.lower() in ctenar.jmeno.lower()]

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        # Pokud čtenář není registrován, automaticky ho přidáme
        if ctenar not in self.ctenari:
            self.registruj_ctenare(ctenar)

        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")

        self.vypujcene_knihy[isbn] = (ctenar, date.today())


    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        vypujceni = self.vypujcene_knihy[isbn]
        if vypujceni[0].cislo_prukazky != ctenar.cislo_prukazky:
            raise ValueError(f"Tuto knihu si nevypůjčil čtenář {ctenar.jmeno} {ctenar.prijmeni}.")
        del self.vypujcene_knihy[isbn]

    def __str__(self):
        return f"Knihovna: {self.nazev}\nKnihy: {len(self.knihy)}\nČtenáři: {len(self.ctenari)}"
