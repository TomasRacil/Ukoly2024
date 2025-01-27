import csv
import datetime

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
        if not any(kniha.isbn == isbn for kniha in self.knihy):
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        return funkce(self, isbn, *args, **kwargs)
    return wrapper

class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}

    @classmethod
    def z_csv(cls, soubor: str):
        """
        Načte data knihovny ze souboru CSV.

        Args:
            soubor: Cesta k souboru CSV.
        Returns:
            Objekt Knihovna načtený ze souboru.
        """
        from .Kniha import Kniha
        from .Ctenar import Ctenar

        knihovna = cls("Neznámá knihovna")
        with open(soubor, newline='') as csvfile:
            reader = csv.reader(csvfile)
            # Načteme první řádek s názvem knihovny
            knihovna.nazev = next(reader)[0].split(":")[1].strip()
            # Načteme hlavičku
            headers = next(reader)
            for row in reader:
                if row[0] == 'kniha':
                    knihovna.knihy.append(Kniha(row[1], row[2], int(row[3]), row[4]))
                elif row[0] == 'ctenar':
                    knihovna.ctenari.append(Ctenar(row[5], row[6]))
        return knihovna

    def pridej_knihu(self, kniha):
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

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        """
        Vyhledá knihy podle klíčového slova nebo ISBN.

        Args:
            klicova_slovo: Klíčové slovo pro vyhledávání v názvu nebo autorovi.
            isbn: ISBN knihy.
        Returns:
            Seznam nalezených knih.
        """
        results = []
        for kniha in self.knihy:
            if (klicova_slovo and (klicova_slovo in kniha.nazev or klicova_slovo in kniha.autor)) or (isbn and kniha.isbn == isbn):
                results.append(kniha)
        return results

    def registruj_ctenare(self, ctenar):
        """
        Zaregistruje čtenáře do knihovny.

        Args:
            ctenar: Objekt čtenáře, který má být zaregistrován.
        """
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar):
        """
        Zruší registraci čtenáře v knihovně.

        Args:
            ctenar: Objekt čtenáře, jehož registrace má být zrušena.
        """
        if ctenar not in self.ctenari:
            raise ValueError(f"Čtenář {ctenar.jmeno} {ctenar.prijmeni} není registrován.")
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
        results = []
        for ctenar in self.ctenari:
            if (klicova_slovo and (klicova_slovo in ctenar.jmeno or klicova_slovo in ctenar.prijmeni)) or (cislo_prukazky and ctenar.cislo_prukazky == cislo_prukazky):
                results.append(ctenar)
        return results

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar):
        """
        Vypůjčí knihu čtenáři.

        Args:
            isbn: ISBN knihy, která má být vypůjčena.
            ctenar: Objekt čtenáře, který si knihu půjčuje.
        Raises:
            ValueError: Pokud kniha s daným ISBN neexistuje nebo je již vypůjčena.
        """
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar):
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
        del self.vypujcene_knihy[isbn]

    def __str__(self):
        return f"Knihovna: {self.nazev}, Knihy: {len(self.knihy)}, Čtenáři: {len(self.ctenari)}"