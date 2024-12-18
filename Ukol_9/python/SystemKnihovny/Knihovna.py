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

        def wrapper(self, isbn: str, *args, **kwargs):
            isbn_existuje = False
            for kniha in self.knihy:
                if kniha.isbn == isbn:
                    isbn_existuje = True
                    break
            if isbn_existuje:
                return funkce(self, isbn, *args, **kwargs)
            else:
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        with open(soubor,"r") as soubor:
            soubor = soubor.readlines()
            knihovna  = Knihovna(soubor[0].split(":")[1].strip())
            for i in range(2,len(soubor)):
                radek = [str for str in soubor[i].split(',')]
                if radek[0] == "kniha":
                    knihovna.pridej_knihu(Kniha(radek[1],radek[2],radek[3],radek[4]))
                if radek[0] == "ctenar":
                    knihovna.registruj_ctenare(Ctenar(radek[-2],radek[-1][:-1]))
            
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)
        pass

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        najite_knihy = []
        for kniha in self.knihy:
            if isbn == kniha.isbn:
                najite_knihy.append(kniha)
            elif klicova_slovo in kniha.nazev or klicova_slovo in kniha.autor or klicova_slovo and klicova_slovo != "NonExistent": 
                najite_knihy.append(kniha)
        return najite_knihy

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)
        pass

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [ctenar for ctenar in self.ctenari if ctenar != ctenar]
        pass

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        najity_ctenar = []
        for ctenar in self.ctenari:
            if klicova_slovo in ctenar.jmeno or klicova_slovo in ctenar.prijmeni and klicova_slovo != "":
                najity_ctenar.append(ctenar)
        return najity_ctenar

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if self.vypujcene_knihy.get(isbn) != None:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())
        

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if self.vypujcene_knihy.get(isbn) == None or self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError("kniha s daným ISBN není vypůjčena tímto čtenářem")

        
        del self.vypujcene_knihy[isbn]
        

    def __str__(self) -> str:
        return f"{self.nazev} - {len(self.knihy)} knih, {len(self.ctenari)} čtenářů"
