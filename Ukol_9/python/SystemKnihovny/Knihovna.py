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
        """Načte data knihovny ze souboru CSV."""
        with open(soubor, "r", encoding="utf-8") as file:
            reader = csv.reader(file)

            # Načtení názvu knihovny z prvního řádku
            prvni_radek = next(reader)
            nazev_knihovny = prvni_radek[0].split(":", 1)[1].strip()

            # Přeskočení záhlaví
            next(reader)

            knihovna = cls(nazev_knihovny)

            # Načítání dat knih a čtenářů
            for radek in reader:
                if radek[0] == "kniha":
                    kniha = Kniha(
                        nazev=radek[1],
                        autor=radek[2],
                        rok_vydani=int(radek[3]),
                        isbn=radek[4],
                    )
                    knihovna.knihy.append(kniha)
                elif radek[0] == "ctenar":
                    ctenar = Ctenar(
                        jmeno=radek[5],
                        prijmeni=radek[6],
                    )
                    knihovna.ctenari.append(ctenar)
        return knihovna

    def odeber_knihu(self, isbn: str):
        """Odebere knihu z knihovny."""
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "") -> list[Kniha]:
        """Vyhledá knihu podle klíčového slova."""
        return [kniha for kniha in self.knihy if klicova_slovo.lower() in kniha.nazev.lower()]

    def registruj_ctenare(self, ctenar: Ctenar):
        """Zaregistruje čtenáře."""
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """Zruší registraci čtenáře."""
        self.ctenari = [c for c in self.ctenari if c != ctenar]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """Vypůjčí knihu čtenáři."""
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    def vrat_knihu(self, isbn: str):
        """Vrátí vypůjčenou knihu."""
        if isbn in self.vypujcene_knihy:
            del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        knihy_info = "\n".join(str(kniha) for kniha in self.knihy)
        ctenari_info = "\n".join(str(ctenar) for ctenar in self.ctenari)
        return f"Knihovna: {self.nazev}\nKnihy:\n{knihy_info}\nČtenáři:\n{ctenari_info}"
