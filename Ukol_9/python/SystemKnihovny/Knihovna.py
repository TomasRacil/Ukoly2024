from __future__ import annotations
from .Kniha import Kniha
from .Ctenar import Ctenar
import csv
import datetime


class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}

    def pridej_knihu(self, kniha):
        self.knihy.append(kniha)

        # Implementujte class metodu z_csv(cls, soubor: str) -> Knihovna v třídě Knihovna, která načte data o knihovně (název knihovny a seznam knih) z CSV souboru.

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        """
        Načte data knihovny ze souboru CSV.
        Args:
            soubor: Cesta k souboru CSV.
        Returns:
            Objekt Knihovna načtený ze souboru.
        """
        with open(soubor, newline='', encoding='utf-8') as csvfile:
            reader = csv.reader(csvfile)
            # Načtení názvu knihovny
            prvni_radek = next(reader)
            nazev_knihovny = prvni_radek[0].split(":")[1].strip()

            knihovna = cls(nazev_knihovny)
            reader = csv.DictReader(csvfile)
            for row in reader:
                if row['typ'] == 'kniha':
                    knihovna.pridej_knihu(
                        Kniha(row['nazev'], row['autor'], int(row['rok_vydani']), row['isbn'])
                    )
                elif row['typ'] == 'ctenar':
                    knihovna.registruj_ctenare(
                        Ctenar(row['jmeno'], row['prijmeni'])
                    )
        return knihovna

    def kniha_existuje(funkce):
        """
        Dekorátor kontrolující existenci knihy v knihovně.
        """

        def wrapper(self, isbn: str, *args, **kwargs):
            """
            Wrapper funkce kontrolující existenci knihy před voláním dané funkce.
            """
            if not any(kniha.isbn == isbn for kniha in self.knihy):
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return funkce(self, isbn, *args, **kwargs)

        return wrapper

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy or self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    def vyhledej_knihu(self, klicova_slovo: str = None, nazev: str = None, autor: str = None, isbn: str = None):
        results = []
        for kniha in self.knihy:
            if (klicova_slovo and (
                    klicova_slovo in kniha.nazev or klicova_slovo in kniha.autor or klicova_slovo in kniha.isbn)) or \
                    (nazev and nazev in kniha.nazev) or \
                    (autor and autor in kniha.autor) or \
                    (isbn and isbn == kniha.isbn):
                results.append(kniha)
        return results

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        if cislo_prukazky is not None:
            return [ctenar for ctenar in self.ctenari if ctenar.cislo_prukazky == cislo_prukazky]
        return [
            ctenar for ctenar in self.ctenari
            if klicova_slovo.lower() in ctenar.jmeno.lower() or
               klicova_slovo.lower() in ctenar.prijmeni.lower()
        ]

    def __str__(self) -> str:
        return f"{self.nazev}, Knihy: {len(self.knihy)}, Ctenari: {len(self.ctenari)}"
