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
        self.vypujcene_knihy: dict[str, tuple[Ctenar, datetime.date]] = {}

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        with open(soubor, "r", encoding="utf-8") as file:
            reader = csv.reader(file)
            nazev_knihovny = next(reader)[0].split(":")[1].strip()
            knihovna = cls(nazev_knihovny)
            next(reader)  # Přeskočení záhlaví

            for radek in reader:
                if radek[0] == "kniha":
                    knihovna.knihy.append(
                        Kniha(radek[1], radek[2], int(radek[3]), radek[4])
                    )
                elif radek[0] == "ctenar":
                    knihovna.ctenari.append(
                        Ctenar(radek[5], radek[6])
                    )
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    def odeber_knihu(self, isbn: str):
        if not any(k.isbn == isbn for k in self.knihy):
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = "") -> list[Kniha]:
        return [
            k for k in self.knihy
            if (isbn and k.isbn == isbn) or (klicova_slovo.lower() in k.nazev.lower())
        ]

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c != ctenar]

    def vyhledej_ctenare(self, klicova_slovo: str = "") -> list[Ctenar]:
        return [c for c in self.ctenari if klicova_slovo.lower() in c.jmeno.lower()]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        if not any(k.isbn == isbn for k in self.knihy):
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    def vrat_knihu(self, isbn: str):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        del self.vypujcene_knihy[isbn]
