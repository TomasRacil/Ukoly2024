import csv
import random
import datetime

from Ukol_9.python.SystemKnihovny import Knihovna


class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn  # Volá setter, kde je validace

    @property
    def isbn(self) -> str:
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if len(value) != 13 or not value.isdigit():
            raise ValueError("ISBN musí mít 13 číslic.")
        self._isbn = value

    @property
    def nazev(self) -> str:
        return self._nazev

    @nazev.setter
    def nazev(self, value: str):
        if not value.strip():
            raise ValueError("Název knihy nesmí být prázdný.")
        self._nazev = value

    @property
    def autor(self) -> str:
        return self._autor

    @autor.setter
    def autor(self, value: str):
        if not value.strip():
            raise ValueError("Autor nesmí být prázdný.")
        self._autor = value

    @property
    def rok_vydani(self) -> int:
        return self._rok_vydani

    @rok_vydani.setter
    def rok_vydani(self, value: int):
        if value > datetime.date.today().year:
            raise ValueError("Rok vydání nemůže být v budoucnosti.")
        self._rok_vydani = value

    def __str__(self) -> str:
        return f"{self._nazev} od {self._autor}, {self._rok_vydani}, ISBN: {self._isbn}"


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def jmeno(self) -> str:
        return self._jmeno

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    @jmeno.setter
    def jmeno(self, value: str):
        if not value:
            raise ValueError("Jméno nesmí být prázdné.")
        self._jmeno = value

    @prijmeni.setter
    def prijmeni(self, value: str):
        if not value:
            raise ValueError("Příjmení nesmí být prázdné.")
        self._prijmeni = value

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value <= 0:
            raise ValueError("Číslo průkazky musí být kladné.")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(100000, 999999)

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni}, číslo průkazky: {self.cislo_prukazky}"


class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}

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
            # Načtení názvu knihovny z prvního řádku
            prvni_radek = next(reader)
            nazev_knihovny = prvni_radek[0].split(":")[1].strip()

            knihovna = cls(nazev_knihovny)
            reader = csv.DictReader(csvfile)  # DictReader začne číst od aktuální pozice
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

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        return [
            kniha for kniha in self.knihy
            if klicova_slovo.lower() in kniha.nazev.lower() or
               klicova_slovo.lower() in kniha.autor.lower() or
               kniha.isbn == isbn
        ]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        return [
            ctenar for ctenar in self.ctenari
            if klicova_slovo.lower() in ctenar.jmeno.lower() or
               klicova_slovo.lower() in ctenar.prijmeni.lower() or
               (cislo_prukazky and ctenar.cislo_prukazky == cislo_prukazky)
        ]

    def __str__(self) -> str:
        return f"Knihovna: {self.nazev}, Knihy: {len(self.knihy)}, Čtenáři: {len(self.ctenari)}"
