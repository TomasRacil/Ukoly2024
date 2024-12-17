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

    def pridej_knihu(self, kniha: Kniha):
        """Přidá knihu do knihovny."""
        self.knihy.append(kniha)

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = "") -> list[Kniha]:
        """Vyhledá knihu podle klíčového slova nebo ISBN."""
        return [k for k in self.knihy if (isbn and k.isbn == isbn) or
                (klicova_slovo.lower() in k.nazev.lower() or klicova_slovo.lower() in k.autor.lower())]

    def registruj_ctenare(self, ctenar: Ctenar):
        """Zaregistruje čtenáře."""
        self.ctenari.append(ctenar)

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None) -> list[Ctenar]:
        """Vyhledá čtenáře podle klíčového slova nebo čísla průkazky."""
        return [c for c in self.ctenari if (cislo_prukazky and c.cislo_prukazky == cislo_prukazky) or
                (klicova_slovo.lower() in c.jmeno.lower() or klicova_slovo.lower() in c.prijmeni.lower())]

    def odeber_knihu(self, isbn: str):
        """Odebere knihu z knihovny."""
        if not any(k.isbn == isbn for k in self.knihy):
            raise ValueError("Kniha s tímto ISBN neexistuje.")
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """Vypůjčí knihu čtenáři."""
        if any(k.isbn == isbn for k in self.vypujcene_knihy):
            raise ValueError("Kniha je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        """Vrátí vypůjčenou knihu."""
        if isbn not in self.vypujcene_knihy:
            raise ValueError("Tato kniha nebyla vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError("Knihu nevypůjčil tento čtenář.")
        del self.vypujcene_knihy[isbn]

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        """Načte data knihovny ze souboru CSV."""
        with open(soubor, "r", encoding="utf-8") as file:
            reader = csv.reader(file)
            nazev_knihovny = next(reader)[0].split(":")[1].strip()
            next(reader)  # Přeskočení záhlaví
            knihovna = cls(nazev_knihovny)

            for radek in reader:
                if radek[0] == "kniha":
                    knihovna.pridej_knihu(Kniha(radek[1], radek[2], int(radek[3]), radek[4]))
                elif radek[0] == "ctenar":
                    knihovna.registruj_ctenare(Ctenar(radek[5], radek[6]))
        return knihovna
