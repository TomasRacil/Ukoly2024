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

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        with open(soubor, "r", encoding="utf-8") as file:
            reader = csv.reader(file)

            # Načítání názvu knihovny z prvního řádku
            prvni_radek = next(reader)
            nazev_knihovny = prvni_radek[0].split(":", 1)[1].strip()

            # Přeskočení druhého řádku (záhlaví)
            next(reader)

            # Vytvoření instance knihovny
            knihovna = cls(nazev_knihovny)

            for radek in reader:
                if radek[0] == "kniha":
                    kniha = Kniha(radek[1], radek[2], int(radek[3]), radek[4])
                    knihovna.pridej_knihu(kniha)
                elif radek[0] == "ctenar":
                    ctenar = Ctenar(radek[5], radek[6])
                    knihovna.registruj_ctenare(ctenar)

            return knihovna

    def pridej_knihu(self, kniha: Kniha):
        """Přidá knihu do seznamu knih."""
        self.knihy.append(kniha)

    def vyhledej_knihu(self, klicova_slovo: str = ""):
        """Vyhledá knihu podle klíčového slova."""
        return [
            kniha for kniha in self.knihy
            if klicova_slovo.lower() in kniha.nazev.lower() or klicova_slovo.lower() in kniha.autor.lower()
        ]

    def registruj_ctenare(self, ctenar: Ctenar):
        """Zaregistruje nového čtenáře."""
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """Zruší registraci čtenáře."""
        self.ctenari = [c for c in self.ctenari if c != ctenar]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """Vypůjčí knihu čtenáři."""
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        """Vrátí knihu do knihovny."""
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError("Kniha nebyla vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]

    def odeber_knihu(self, isbn: str):
        """Odebere knihu podle ISBN."""
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_ctenare(self, klicova_slovo: str = ""):
        """Vyhledá čtenáře podle klíčového slova."""
        return [
            ctenar for ctenar in self.ctenari
            if klicova_slovo.lower() in ctenar.jmeno.lower() or klicova_slovo.lower() in ctenar.prijmeni.lower()
        ]
