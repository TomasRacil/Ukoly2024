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


    def kniha_existuje(func):
        def wrapper(self, isbn: str, *args, **kwargs):
            isbn_exists = False
            for book in self.knihy:
                if book.isbn == isbn:
                    isbn_exists = True
                    break
            if isbn_exists:
                return func(self, isbn, *args, **kwargs)
            else:
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        with open(soubor, "r") as file:
            file = file.readlines()
            knihovna = Knihovna((re.findall(r"Knihovna:(.*)",file[0]))[0]) #using regexp to find library name in first row of the file
            for i in range(2,len(file)):
                #for each row, starting with third (skipping name and description)
                row = [str for str in file[i].split(',')]
                if row[0] == "kniha":
                    #row represents a book
                    knihovna.pridej_knihu(Kniha(row[1],row[2],row[3],row[4]))
                    pass
                if row[0] == "ctenar":
                    #row represents a reader
                    knihovna.registruj_ctenare(Ctenar(row[-2],row[-1][:-1])) #remove additional \n character from surname
        return knihovna

    def pridej_knihu(self, kniha: Kniha):
        #add book to library
        self.knihy.append(kniha)
        pass

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        #make a new list without all occurences of the book(s) with passed isbn
        self.knihy = [book for book in self.knihy if book.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        found_books : list = []
        for book in self.knihy:
            if isbn == book.isbn:
                #isbn matches 
                found_books.append(book)
            elif klicova_slovo != "" and book.autor.find(klicova_slovo) != -1 or book.nazev.find(klicova_slovo) != -1:
                #keyword isn't empty and is substring of book's name or author
                found_books.append(book)
        return found_books

    def registruj_ctenare(self, ctenar: Ctenar):
        #adds new reader
        self.ctenari.append(ctenar)
        pass

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        #make a new list without all occurences of the reader
        self.ctenari = [reader for reader in self.ctenari if reader != ctenar]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        readers : list = []
        for reader in self.ctenari:
            #tmp is concatenated first name and surname in which the keyword is searched if it's not empty
            tmp : str = reader.jmeno + reader.prijmeni
            if cislo_prukazky == reader.cislo_prukazky or (klicova_slovo != "" and tmp.find(klicova_slovo) != -1):
                readers.append(reader)
        return readers
    

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        #dictionary key=isbn : value=(reader, date)
        if self.vypujcene_knihy.get(isbn) != None:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if self.vypujcene_knihy.get(isbn) == None or self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError("kniha s daným ISBN není vypůjčena tímto čtenářem")
        
        #delete key and val
        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        #string representation of a book
        out : str = ""
        out += self.nazev + "\n"
        out += "Books:"
        for kniha in self.knihy:
             out += str(kniha)
        out += "\nRegistered readers:"
        for ctenar in self.ctenari:
            out += str(ctenar)
        return out
