import random
import csv
from datetime import date
from typing import List, Optional


# Dekorátor pro kontrolu existence knihy v knihovně podle ISBN
def kniha_existuje(func):
    def wrapper(self, isbn, *args, **kwargs):
        if not any(kniha.isbn == isbn for kniha in self.knihy):
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        return func(self, isbn, *args, **kwargs)
    return wrapper


class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self.isbn = isbn  # Spustí setter pro validaci

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if len(value) != 13 or not value.isdigit():
            raise ValueError(f"Neplatné ISBN: {value}")
        self._isbn = value


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value <= 0:
            raise ValueError(f"Číslo průkazky musí být kladné číslo, dostal jsem: {value}")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky():
        return random.randint(1, 1000000)


class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy: List[Kniha] = []
        self.ctenari: List[Ctenar] = []
        self.vypujcene_knihy: dict = {}

    @classmethod
    def z_csv(cls, soubor: str) -> 'Knihovna':
        with open(soubor, mode='r', newline='', encoding='utf-8') as csvfile:
            reader = csv.reader(csvfile)
            prvni_radek = next(reader)
            if prvni_radek and "Knihovna:" in prvni_radek[0]:
                nazev_knihovny = prvni_radek[0].split(":")[1].strip()
            else:
                nazev_knihovny = "Neznámá knihovna"

            knihovna = cls(nazev_knihovny)

            next(reader)  # Přeskočení záhlaví

            for row in reader:
                if row[0] == "kniha":
                    knihovna.knihy.append(Kniha(row[1], row[2], int(row[3]), row[4]))
                elif row[0] == "ctenar":
                    ctenar = Ctenar(row[5], row[6])
                    knihovna.ctenari.append(ctenar)

        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        kniha = next(k for k in self.knihy if k.isbn == isbn)
        self.knihy.remove(kniha)

    def vyhledej_knihu(self, klicova_slovo: Optional[str] = None, isbn: Optional[str] = None) -> List[Kniha]:
        if klicova_slovo:
            return [kniha for kniha in self.knihy if klicova_slovo.lower() in kniha.nazev.lower()]
        if isbn:
            return [kniha for kniha in self.knihy if kniha.isbn == isbn]
        return []

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari.remove(ctenar)

    def vyhledej_ctenare(self, klicova_slovo: Optional[str] = None, cislo_prukazky: Optional[int] = None) -> List[Ctenar]:
        if klicova_slovo:
            return [ctenar for ctenar in self.ctenari if klicova_slovo.lower() in ctenar.jmeno.lower()]
        if cislo_prukazky:
            return [ctenar for ctenar in self.ctenari if ctenar.cislo_prukazky == cislo_prukazky]
        return []

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if ctenar not in self.ctenari:
            raise ValueError("Čtenář není registrován.")
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


if __name__ == "__main__":
    knihovna = Knihovna("Městská knihovna")
    kniha1 = Kniha("Stopařův průvodce po Galaxii", "Douglas Adams", 1979, "9780345391803")
    knihovna.pridej_knihu(kniha1)

    ctenar1 = Ctenar("Jan", "Novák")
    knihovna.registruj_ctenare(ctenar1)

    knihovna.vypujc_knihu("9780345391803", ctenar1)
    print(f"Kniha {kniha1.nazev} byla vypůjčena čtenáři {ctenar1.jmeno}.")

    knihovna.vrat_knihu("9780345391803", ctenar1)
    print(f"Kniha {kniha1.nazev} byla vrácena.")
