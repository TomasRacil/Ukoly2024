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
            nazev_knihovny = next(reader)[0].split(":", 1)[1].strip()
            next(reader)  # Přeskočení záhlaví

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
        """Přidá knihu do knihovny."""
        self.knihy.append(kniha)

    def odeber_knihu(self, isbn: str):
        """Odebere knihu z knihovny."""
        if not any(kniha.isbn == isbn for kniha in self.knihy):
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = "") -> list[Kniha]:
        """Vyhledá knihu podle klíčového slova nebo ISBN."""
        vysledky = []
        for kniha in self.knihy:
            if isbn and kniha.isbn == isbn:
                vysledky.append(kniha)
            elif klicova_slovo and klicova_slovo.lower() in kniha.nazev.lower():
                vysledky.append(kniha)
        return vysledky

    def registruj_ctenare(self, ctenar: Ctenar):
        """Zaregistruje čtenáře."""
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """Zruší registraci čtenáře."""
        self.ctenari = [c for c in self.ctenari if c != ctenar]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None) -> list[Ctenar]:
        """Vyhledá čtenáře podle klíčového slova nebo čísla průkazky."""
        vysledky = []
        for ctenar in self.ctenari:
            if cislo_prukazky and ctenar.cislo_prukazky == cislo_prukazky:
                vysledky.append(ctenar)
            elif klicova_slovo and klicova_slovo.lower() in ctenar.jmeno.lower():
                vysledky.append(ctenar)
        return vysledky

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """Vypůjčí knihu čtenáři."""
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        if not any(k.isbn == isbn for k in self.knihy):
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        """Vrátí vypůjčenou knihu."""
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        knihy_info = "\n".join(str(kniha) for kniha in self.knihy)
        ctenari_info = "\n".join(str(ctenar) for ctenar in self.ctenari)
        return f"Knihovna: {self.nazev}\nKnihy:\n{knihy_info}\nČtenáři:\n{ctenari_info}"
