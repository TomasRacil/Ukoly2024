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
            kniha = next((kniha for kniha in self.knihy if kniha.isbn == isbn), None)

            if not kniha:
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")

            if funkce.__name__ == 'vypujc_knihu' and isbn in self.vypujcene_knihy:
                raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")

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
        knihovna = Knihovna("Neznámá knihovna")
        with open(soubor, mode='r', encoding='utf-8') as file:
            reader = csv.reader(file)
            knihovna.nazev = next(reader)[0].replace("Knihovna:", "").strip()
            next(reader)

            for row in reader:
                if len(row) >= 5 and row[0] == "kniha":
                    kniha = Kniha(row[1], row[2], int(row[3]), row[4])
                    knihovna.pridej_knihu(kniha)
                elif len(row) >= 7 and row[0] == "ctenar":
                    ctenar = Ctenar(row[5], row[6])
                    knihovna.registruj_ctenare(ctenar)

        return knihovna

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
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

        if isbn in self.vypujcene_knihy:
            del self.vypujcene_knihy[isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        """
        Vyhledá knihy podle klíčového slova nebo ISBN.

        Args:
            klicova_slovo: Klíčové slovo pro vyhledávání v názvu nebo autorovi.
            isbn: ISBN knihy.
        Returns:
            Seznam nalezených knih.
        """
        if isbn:
            return [kniha for kniha in self.knihy if kniha.isbn == isbn]
        return [kniha for kniha in self.knihy if klicova_slovo.lower() in kniha.nazev.lower() or klicova_slovo.lower() in kniha.autor.lower()]

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
        self.ctenari = [c for c in self.ctenari if c != ctenar]


    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        """
        Vyhledá čtenáře podle klíčového slova nebo čísla průkazky.

        Args:
            klicova_slovo: Klíčové slovo pro vyhledávání v jméně nebo příjmení.
            cislo_prukazky: Číslo průkazky čtenáře.
        Returns:
            Seznam nalezených čtenářů.
        """
        if cislo_prukazky:
            return [ctenar for ctenar in self.ctenari if ctenar.cislo_prukazky == cislo_prukazky]
        return [ctenar for ctenar in self.ctenari if klicova_slovo.lower() in ctenar.jmeno.lower() or klicova_slovo.lower() in ctenar.prijmeni.lower()]


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
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

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
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")

        vypujceny_ctenar, _ = self.vypujcene_knihy[isbn]
        if vypujceny_ctenar != ctenar:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena tímto čtenářem.")

        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        return f"Knihovna: {self.nazev}, Počet knih: {len(self.knihy)}, Počet čtenářů: {len(self.ctenari)}"
