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

    @staticmethod
    def kniha_existuje(funkce):
        """
        Dekorátor kontrolující existenci knihy v knihovně.
        """
        def wrapper(self, isbn: str, *args, **kwargs):
            if isbn not in [kniha.isbn for kniha in self.knihy]:
                raise ValueError(f"Kniha s ISBN {isbn} v knihovně neexistuje.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        """
        Načte data knihovny ze souboru CSV.
        """
        with open(soubor, mode="r", encoding="utf-8") as f:
            reader = csv.reader(f)
            nazev = next(reader)[0]
            knihovna = cls(nazev)
            knihovna.knihy = [Kniha(*radek) for radek in reader]
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        """
        Přidá knihu do knihovny.
        """
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        """
        Odebere knihu z knihovny.
        """
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        """
        Vyhledá knihy podle klíčového slova nebo ISBN.
        """
        return [
            kniha for kniha in self.knihy
            if klicova_slovo.lower() in kniha.nazev.lower() or kniha.isbn == isbn
        ]

    def registruj_ctenare(self, ctenar: Ctenar):
        """
        Zaregistruje čtenáře do knihovny.
        """
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """
        Zruší registraci čtenáře v knihovně.
        """
        self.ctenari = [
            c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky
        ]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        """
        Vyhledá čtenáře podle klíčového slova nebo čísla průkazky.
        """
        return [
            ctenar for ctenar in self.ctenari
            if klicova_slovo.lower() in f"{ctenar.jmeno} {ctenar.prijmeni}".lower()
            or (cislo_prukazky and ctenar.cislo_prukazky == cislo_prukazky)
        ]

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """
        Vypůjčí knihu čtenáři.
        """
        if isbn in self.vypujcene_knihy:
            raise ValueError("Tato kniha je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.datetime.now())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        """
        Vrátí knihu.
        """
        if (
            isbn not in self.vypujcene_knihy
            or self.vypujcene_knihy[isbn][0] != ctenar
        ):
            raise ValueError("Kniha není vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        return f"Knihovna {self.nazev} obsahuje {len(self.knihy)} knih a {len(self.ctenari)} čtenářů."
