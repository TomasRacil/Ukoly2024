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

    def kniha_existuje(funkce):
        """
        Dekorátor kontrolující existenci knihy v knihovně.

        Args:
            funkce: Funkce, která má být volána po kontrole existence knihy.
        """


        def wrapper(self, isbn: str, *args, **kwargs):
            """
            Wrapper funkce kontrolující existenci knihy před voláním dané funkce.
            """
               # zkontroluj, zda kniha s daným ISBN existuje v knihovně
            kniha = self.vyhledej_knihu(isbn=isbn)
            if not kniha:
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje v knihovně.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        knihovna = Knihovna("Načtená knihovna")
        with open(soubor, mode='r', newline='', encoding='utf-8') as f:
            reader = csv.reader(f)
            for row in reader:
                if row:
                    nazev, autor, rok_vydani, isbn = row
                    kniha = Kniha(nazev, autor, int(rok_vydani), isbn)
                    knihovna.pridej_knihu(kniha)
        """
        Načte data knihovny ze souboru CSV.

        Args:
            soubor: Cesta k souboru CSV.
        Returns:
            Objekt Knihovna načtený ze souboru.
        """
        return Knihovna("Neznámá knihovna")

    def pridej_knihu(self, kniha: Kniha):
        """
        Přidá knihu do knihovny.

        Args:
            kniha: Objekt knihy, který má být přidán.
        """
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        """
        Odebere knihu z knihovny.

        Args:
            isbn: ISBN knihy, která má být odebrána.
        Raises:
            ValueError: Pokud kniha s daným ISBN neexistuje.
        """
        kniha = self.vyhledej_knihu(isbn=isbn)[0]  # první výskyt knihy
        self.knihy.remove(kniha)

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        """
        Vyhledá knihy podle klíčového slova nebo ISBN.

        Args:
            klicova_slovo: Klíčové slovo pro vyhledávání v názvu nebo autorovi.
            isbn: ISBN knihy.
        Returns:
            Seznam nalezených knih.
        """
        nalezene_knihy = []
        for kniha in self.knihy:
            if klicova_slovo.lower() in kniha.nazev.lower() or klicova_slovo.lower() in kniha.autor.lower():
                nalezene_knihy.append(kniha)
            elif isbn and kniha.isbn == isbn:
                nalezene_knihy.append(kniha)
        return nalezene_knihy

    def registruj_ctenare(self, ctenar: Ctenar):
        """
        Zaregistruje čtenáře do knihovny.

        Args:
            ctenar: Objekt čtenáře, který má být zaregistrován.
        """
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """
        Zruší registraci čtenáře v knihovně.

        Args:
            ctenar: Objekt čtenáře, jehož registrace má být zrušena.
        """
        if ctenar in self.ctenari:
            self.ctenari.remove(ctenar)

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        """
        Vyhledá čtenáře podle klíčového slova nebo čísla průkazky.

        Args:
            klicova_slovo: Klíčové slovo pro vyhledávání v jméně nebo příjmení.
            cislo_prukazky: Číslo průkazky čtenáře.
        Returns:
            Seznam nalezených čtenářů.
        """
        nalezeni_ctenari = []
        for ctenar in self.ctenari:
            if klicova_slovo.lower() in ctenar.jmeno.lower() or klicova_slovo.lower() in ctenar.prijmeni.lower():
                nalezeni_ctenari.append(ctenar)           
            elif cislo_prukazky and ctenar.cislo_prukazky == cislo_prukazky:
                 nalezeni_ctenari.append(ctenar)
        return nalezeni_ctenari

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """
        Vypůjčí knihu čtenáři.

        Args:
            isbn: ISBN knihy, která má být vypůjčena.
            ctenar: Objekt čtenáře, který si knihu půjčuje.
        Raises:
            ValueError: Pokud kniha s daným ISBN neexistuje nebo je již vypůjčena.
        """
        kniha = self.vyhledej_knihu(isbn=isbn)[0]  # Získáme první výskyt knihy
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = ctenar

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        """
        Vrátí knihu.

        Args:
            isbn: ISBN knihy, která má být vrácena.
            ctenar: Objekt čtenáře, který knihu vrací.
        Raises:
            ValueError: Pokud kniha s daným ISBN není vypůjčena tímto čtenářem.
        """
        if self.vypujcene_knihy.get(isbn) != ctenar:
            raise ValueError(f"Tato kniha není vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]


    def __str__(self) -> str:
        return f"Knihovna: {self.nazev}, Počet knih: {len(self.knihy)}, Počet čtenářů: {len(self.ctenari)}"
