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
        """
        Načte data knihovny ze souboru CSV.
        """
        with open(soubor, "r", encoding="utf-8") as file:
            reader = csv.reader(file)

            # 1. První řádek obsahuje název knihovny
            prvni_radek = next(reader)
            nazev_knihovny = prvni_radek[0].split(":", 1)[1].strip()

            # 2. Přeskočíme záhlaví (druhý řádek)
            next(reader)

            # 3. Inicializace knihovny
            knihovna = cls(nazev_knihovny)

            # 4. Načítání dat (knihy a čtenáři)
            for radek in reader:
                if radek[0] == "kniha":
                    kniha = Kniha(
                        nazev=radek[1],
                        autor=radek[2],
                        rok_vydani=int(radek[3]),
                        isbn=radek[4],
                    )
                    knihovna.pridej_knihu(kniha)
                elif radek[0] == "ctenar":
                    ctenar = Ctenar(
                        jmeno=radek[5],
                        prijmeni=radek[6],
                    )
                    knihovna.registruj_ctenare(ctenar)

        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        """Přidá knihu do seznamu knih."""
        self.knihy.append(kniha)

    def odeber_knihu(self, isbn: str):
        """Odebere knihu ze seznamu podle ISBN."""
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        """Vyhledá knihu podle klíčového slova nebo ISBN."""
        return [
            kniha for kniha in self.knihy
            if (isbn and kniha.isbn == isbn) or
               (klicova_slovo.lower() in kniha.nazev.lower() or klicova_slovo.lower() in kniha.autor.lower())
        ]

    def registruj_ctenare(self, ctenar: Ctenar):
        """Zaregistruje čtenáře."""
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """Zruší registraci čtenáře."""
        self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

    def vyhledej_ctenare(self, klicova_slovo: str = ""):
        """Vyhledá čtenáře podle jména nebo příjmení."""
        return [
            ctenar for ctenar in self.ctenari
            if klicova_slovo.lower() in ctenar.jmeno.lower() or klicova_slovo.lower() in ctenar.prijmeni.lower()
        ]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """Vypůjčí knihu čtenáři."""
        for kniha in self.knihy:
            if kniha.isbn == isbn:
                if isbn in self.vypujcene_knihy:
                    raise ValueError("Kniha je již vypůjčena.")
                self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())
                return
        raise ValueError("Kniha nebyla nalezena.")

    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        """Vrátí vypůjčenou knihu."""
        if isbn in self.vypujcene_knihy:
            if self.vypujcene_knihy[isbn][0] == ctenar:
                del self.vypujcene_knihy[isbn]
                return
            else:
                raise ValueError("Kniha není vypůjčena tímto čtenářem.")
        raise ValueError("Kniha nebyla nalezena.")

    def __str__(self) -> str:
        knihy_str = "\n".join(str(kniha) for kniha in self.knihy)
        ctenari_str = "\n".join(str(ctenar) for ctenar in self.ctenari)
        return f"Knihovna: {self.nazev}\nKnihy:\n{knihy_str}\nČtenáři:\n{ctenari_str}"
