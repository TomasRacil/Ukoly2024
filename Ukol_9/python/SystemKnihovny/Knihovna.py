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
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
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
        pass

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        """
        Odebere knihu z knihovny.

        Args:
            isbn: ISBN knihy, která má být odebrána.
        Raises:
            ValueError: Pokud kniha s daným ISBN neexistuje.
        """
        pass

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        """
        Vyhledá knihy podle klíčového slova nebo ISBN.

        Args:
            klicova_slovo: Klíčové slovo pro vyhledávání v názvu nebo autorovi.
            isbn: ISBN knihy.
        Returns:
            Seznam nalezených knih.
        """
        return []

    def registruj_ctenare(self, ctenar: Ctenar):
        """
        Zaregistruje čtenáře do knihovny.

        Args:
            ctenar: Objekt čtenáře, který má být zaregistrován.
        """
        pass

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """
        Zruší registraci čtenáře v knihovně.

        Args:
            ctenar: Objekt čtenáře, jehož registrace má být zrušena.
        """
        pass

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        """
        Vyhledá čtenáře podle klíčového slova nebo čísla průkazky.

        Args:
            klicova_slovo: Klíčové slovo pro vyhledávání v jméně nebo příjmení.
            cislo_prukazky: Číslo průkazky čtenáře.
        Returns:
            Seznam nalezených čtenářů.
        """
        return []

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
        pass

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
        pass

    def __str__(self) -> str:
        return ""
