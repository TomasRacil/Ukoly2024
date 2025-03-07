from __future__ import annotations
from .Kniha import Kniha
from .Ctenar import Ctenar
import csv
import datetime

class Knihovna:
    """
    Třída reprezentující knihovnu.
    """
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy: list[Kniha] = []
        self.ctenari: list[Ctenar] = []
        # Slovník vypůjčených knih: klíč = ISBN, hodnota = (Ctenar, datum_vypujcky)
        self.vypujcene_knihy: dict[str, tuple[Ctenar, datetime.date]] = {}

    @staticmethod
    def kniha_existuje(funkce):
        """
        Dekorátor kontrolující existenci knihy v knihovně podle ISBN.
        Pokud kniha neexistuje, vyvolá ValueError s požadovanou hláškou.
        """
        def wrapper(self: Knihovna, isbn: str, *args, **kwargs):
            kniha = None
            for k in self.knihy:
                if k.isbn == isbn:
                    kniha = k
                    break
            if kniha is None:
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        """
        Načte data o knihovně (název, knihy, čtenáře) ze souboru CSV.

        Očekává se, že:
         - první řádek obsahuje např. "Knihovna:Městská knihovna"
         - druhý řádek je hlavička: "typ,nazev,autor,rok_vydani,isbn,jmeno,prijmeni"
         - další řádky obsahují vždy buď definici knihy nebo čtenáře.
        """
        import os
        with open(soubor, mode='r', encoding='utf-8') as f:
            # 1) První řádek
            prvni_radek = f.readline().strip()
            if not prvni_radek.startswith("Knihovna:"):
                knihovna = cls("Neznámá knihovna")
            else:
                nazev_knihovny = prvni_radek.split(":", 1)[1]
                knihovna = cls(nazev_knihovny.strip())

            # 2) Druhý řádek (hlavička) přeskočíme
            f.readline()

            # 3) Čtení dalších řádků
            csv_reader = csv.reader(f, delimiter=',')
            for row in csv_reader:
                if not row:
                    continue
                typ = row[0]
                if typ == "kniha":
                    # row = [ "kniha", "Název", "Autor", "Rok", "ISBN", "", "" ]
                    nazev, autor, rok_vydani, isbn = row[1], row[2], row[3], row[4]
                    try:
                        rok_vydani_int = int(rok_vydani)
                    except ValueError:
                        rok_vydani_int = 0
                    kniha = Kniha(nazev, autor, rok_vydani_int, isbn)
                    knihovna.knihy.append(kniha)
                elif typ == "ctenar":
                    # row = [ "ctenar", "", "", "", "", "Jméno", "Příjmení" ]
                    jmeno, prijmeni = row[5], row[6]
                    ctenar = Ctenar(jmeno, prijmeni)
                    knihovna.ctenari.append(ctenar)

        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        """
        Přidá knihu do knihovny, pokud již není přidána.
        """
        for k in self.knihy:
            if k.isbn == kniha.isbn:
                # Již existuje, nic neděláme
                return
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        """
        Odebere knihu z knihovny. Pokud je kniha vypůjčena, vyvolá chybu.
        """
        for idx, k in enumerate(self.knihy):
            if k.isbn == isbn:
                if isbn in self.vypujcene_knihy:
                    raise ValueError(f"Kniha s ISBN {isbn} je právě vypůjčena a nemůže být odebrána.")
                del self.knihy[idx]
                return

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = "") -> list[Kniha]:
        """
        Vyhledá knihy podle klíčového slova v názvu/autorovi, nebo podle ISBN.
        """
        nalezene = []
        if isbn:
            for k in self.knihy:
                if k.isbn == isbn:
                    nalezene.append(k)
        else:
            kl = klicova_slovo.lower()
            for k in self.knihy:
                if kl in k.nazev.lower() or kl in k.autor.lower():
                    nalezene.append(k)
        return nalezene

    def registruj_ctenare(self, ctenar: Ctenar):
        """
        Zaregistruje čtenáře, pokud již není registrován.
        """
        for c in self.ctenari:
            if c.cislo_prukazky == ctenar.cislo_prukazky:
                return
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """
        Zruší registraci čtenáře (pokud nemá vypůjčené knihy).
        """
        # Ověříme, zda čtenář nemá nějakou knihu vypůjčenou
        for isbn, (ct, _) in self.vypujcene_knihy.items():
            if ct == ctenar:
                raise ValueError("Čtenář má vypůjčené knihy, nelze zrušit registraci.")
        self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None) -> list[Ctenar]:
        """
        Vyhledá čtenáře podle jména/příjmení nebo čísla průkazky.
        """
        nalezeni = []
        if cislo_prukazky is not None:
            for c in self.ctenari:
                if c.cislo_prukazky == cislo_prukazky:
                    nalezeni.append(c)
        else:
            kl = klicova_slovo.lower()
            for c in self.ctenari:
                if kl in c.jmeno.lower() or kl in c.prijmeni.lower():
                    nalezeni.append(c)
        return nalezeni

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        """
        Vypůjčí knihu čtenáři. Vyvolá chybu pouze pokud je kniha už vypůjčena
        """
        # ! Úprava: odstranění kontroly "ctenar not in self.ctenari"
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        """
        Vrátí knihu. Vyvolá chybu, pokud kniha není vypůjčena tímto čtenářem.
        """
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        ctenar_vypujcil, _ = self.vypujcene_knihy[isbn]
        if ctenar_vypujcil != ctenar:
            raise ValueError(f"Kniha s ISBN {isbn} byla vypůjčena jiným čtenářem.")
        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        """
        Přehledný výpis knihovny (název, seznam knih, čtenářů a vypůjčení).
        """
        s = [f"Knihovna: {self.nazev}", "Seznam knih:"]
        for k in self.knihy:
            s.append(f"  - {k}")
        s.append("Seznam čtenářů:")
        for c in self.ctenari:
            s.append(f"  - {c}")
        if self.vypujcene_knihy:
            s.append("Vypůjčené knihy:")
            for isbn, (ctenar, datum) in self.vypujcene_knihy.items():
                s.append(f"  - {isbn} -> {ctenar}, od {datum}")
        else:
            s.append("Aktuálně žádné knihy nejsou vypůjčeny.")
        return "\n".join(s)
