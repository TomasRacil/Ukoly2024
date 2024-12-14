from __future__ import annotations
from .Kniha import Kniha
from .Ctenar import Ctenar
import csv
import datetime
import re

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
            existuje = False
            for kniha in self.knihy:
                if kniha.isbn == isbn:
                    existuje = True
                    break
            if existuje:
                return funkce(self, isbn, *args, **kwargs)
            else:
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:

        with open(soubor, "r") as file:
            file = file.readlines()
            knihovna = Knihovna((re.findall(r"Knihovna:(.*)",file[0]))[0])
            for i in range(2,len(file)):
                row = [str for str in file[i].split(',')]
                if row[0] == "kniha":
                    #pridej knihu
                    #typ,nazev,autor,rok_vydani,isbn,jmeno,prijmeni
                    knihovna.pridej_knihu(Kniha(row[1],row[2],row[3],row[4]))
                    pass
                if row[0] == "ctenar":
                    #pridej ctenare
                    knihovna.registruj_ctenare(Ctenar(row[-2],row[-1]))
                i += 1
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)
        pass

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        for kniha in self.knihy:
            if kniha.isbn == isbn:
                self.knihy.remove(kniha)

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        nalezene_knihy : list = []
        for kniha in self.knihy:
            if isbn != "" and isbn == kniha.isbn:
                nalezene_knihy.append(kniha)
            elif klicova_slovo != "" and kniha._autor.find(klicova_slovo) != -1 or kniha._nazev.find(klicova_slovo) != -1:
                nalezene_knihy.append(kniha)
        return nalezene_knihy

    def registruj_ctenare(self, ctenar: Ctenar):
        """
        Zaregistruje čtenáře do knihovny.

        Args:
            ctenar: Objekt čtenáře, který má být zaregistrován.
        """
        self.ctenari.append(ctenar)
        pass

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        """
        Zruší registraci čtenáře v knihovně.

        Args:
            ctenar: Objekt čtenáře, jehož registrace má být zrušena.
        """
        for person in self.ctenari:
            if person == ctenar:
                self.ctenari.remove(person)
                break

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):

        ctenari : list = []
        for person in self.ctenari:
            tmp : str = person._jmeno + person._prijmeni
            if cislo_prukazky == person.cislo_prukazky or (klicova_slovo != "" and tmp.find(klicova_slovo) != -1):
                ctenari.append(person)
        return ctenari
    

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
        #dictionary isbn : (ctenar, datum)
        if self.vypujcene_knihy.get(isbn) != None:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.") #kniha uz je vypujcena
        
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
        #dictionary isbn : (ctenar, datum)
        if self.vypujcene_knihy.get(isbn) == None or self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError("kniha s daným ISBN není vypůjčena tímto čtenářem")
        
        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        out : str = ""
        out += self.nazev + "\n"
        out += "Knihy:"
        for kniha in self.knihy:
             out += str(kniha)
        out += "\nCtenari:"
        for ctenar in self.ctenari:
            out += str(ctenar)
        return out
