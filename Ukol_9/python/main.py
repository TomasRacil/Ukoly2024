from SystemKnihovny import Knihovna, Kniha, Ctenar
from os.path import realpath, dirname, join
from typing import List, Dict, Tuple
import datetime
import random
import csv



class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self._isbn = isbn

    @property
    def isbn(self):
        return self._isbn
        
    @isbn.setter
    def isbn(self, nove_isbn):
        if nove_isbn.isdigit() and len(nove_isbn) == 13:
           self._isbn = nove_isbn
        else:
            raise ValueError("spatne ISBN")
    
    def __str__(self):
        return f"Kniha: {self.nazev}, Autor: {self.autor}, Rok vydání: {self.rok_vydani}, ISBN: {self.isbn}"
        
        

class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str, cislo_prukazky=0):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self._cislo_prukazky = cislo_prukazky

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky
        
    @cislo_prukazky.setter
    def cislo_prukazky(self, nove_cislo_prukazky):
        if nove_cislo_prukazky > 0:
            self._cislo_prukazky = nove_cislo_prukazky
        else:
            raise ValueError("spatne cislo prukazky")

    @staticmethod
    def vygeneruj_cislo_prukazky():
        return random.randint(1000, 9999)

    def __str__(self):
        return f"Čtenář: {self.jmeno} {self.prijmeni}, Číslo průkazky: {self.cislo_prukazky}"
    
#Dekorátor kontroluje, zda kniha s daným ISBN existuje v knihovně.
def kniha_existuje(func):
    def obal(self, *args, **kwargs):
        if len(args) == 0:
            raise ValueError("Neplatné ISBN: není žádné ISBN zadané.")

        isbn = args[0]
        kniha = next((k for k in self.knihy if k.isbn == isbn), None)
        
        if kniha is None:
            raise ValueError("Kniha s tímto ISBN neexistuje v knihovně.")

        return func(self, *args, **kwargs)
    
    return obal


class Knihovna:
    def __init__(self, nazev: str, knihy: List[Kniha]):
        self.nazev = nazev
        self.knihy = knihy
        self.ctenari = []
        self.vypujcene_knihy: Dict[str, Tuple[Ctenar, datetime.date]] = {}

    @staticmethod
    def z_csv(soubor: str) -> 'Knihovna':
        knihy = []
        ctenari = []
        try:
            with open(soubor, mode='r', encoding='utf-8') as file:
                csv_reader = csv.reader(file, delimiter=';')
                next(csv_reader)  # Přeskočí záhlaví
                for radek in csv_reader:
                    if radek[0] == 'Kniha':  # Kniha
                        nazev, autor, rok_vydani, isbn = radek[1:]
                        try:
                            kniha = Kniha(nazev, autor, int(rok_vydani), isbn)
                            knihy.append(kniha)
                        except ValueError as e:
                            print(f"Chyba při zpracování knihy z CSV: {e}")
                    elif radek[0] == 'Čtenář':  # Čtenář
                        jmeno, prijmeni, cislo_prukazky = radek[1:]
                        try:
                            ctenar = Ctenar(jmeno, prijmeni)
                            ctenar.cislo_prukazky = int(cislo_prukazky)
                            ctenari.append(ctenar)
                        except ValueError as e:
                            print(f"Chyba při zpracování čtenáře z CSV: {e}")

        except FileNotFoundError:
            print(f"Soubor {soubor} nebyl nalezen.")
        except Exception as e:
            print(f"Nepředvídaná chyba při čtení souboru: {e}")

        return Knihovna(f"Knihovna z {soubor}", knihy)
    
    


    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [k for k in self.knihy if k.isbn != isbn]
        print(f"Kniha s ISBN {isbn} byla odebrána.")
    
    @kniha_existuje
    def vyhledej_knihu(self, klicove_slovo: str):
        return [kniha for kniha in self.knihy if klicove_slovo in kniha.nazev or klicove_slovo in kniha.autor or klicove_slovo == kniha.isbn]
    
    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        kniha = None
        for k in self.knihy:
            if k.isbn == isbn:
                kniha = k
        
        if kniha:
            self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())
        else:
            raise ValueError("Kniha neni k dispozici pro vypujceni")
        
    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy and self.vypujcene_knihy[isbn][0] == ctenar:
            del self.vypujcene_knihy[isbn]
        else:
            raise ValueError("Kniha nebyla vypujcena timto ctenarem")

    def __str__(self, isbn):
        vypujcene_knihy_info = [(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in self.vypujcene_knihy.items()]
        return (f"Knihovna '{self.nazev}' obsahuje {len(self.knihy)} knih a {len(self.ctenari)} čtenářů. "
                f"Vypůjčené knihy: {vypujcene_knihy_info}")

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def vyhledej_ctenare(self, cislo_prukazky: int):
        return [ctenar for ctenar in self.ctenari if ctenar.cislo_prukazky == cislo_prukazky]
    
    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c != ctenar]


if __name__ == "__main__":

    knihovna = Knihovna.z_csv(
        join(dirname(realpath(__file__)), "knihovna.csv"))
    print(f"Knihovna načtena z CSV: {knihovna.nazev}")

    kniha1 = Kniha("Stopařův průvodce po Galaxii",
                   "Douglas Adams", 1979, "9780345391803")
    print(f"Kniha 1: {kniha1}")

    try:
        kniha2 = Kniha("Název knihy 2", "Autor 2", 2024, "invalidISBN")
    except ValueError as e:
        print(f"Chyba při vytváření knihy 2: {e}")

    knihovna.pridej_knihu(kniha1)
    print(f"Knihy v knihovně: {[str(k) for k in knihovna.knihy]}")

    knihovna.odeber_knihu("9780345391803")
    print(f"Knihy v knihovně po odebrání: {[str(k) for k in knihovna.knihy]}")

    ctenar1 = Ctenar("Jan", "Novák")
    print(f"Čtenář 1: {ctenar1}")
    try:
        ctenar1.cislo_prukazky = -100  # Invalid
    except ValueError as e:
        print(f"Chyba nastavení čísla průkazky: {e}")
    print(f"Čtenář 1: {ctenar1}")

    ctenar2 = Ctenar("Petr", "Svoboda")
    knihovna.registruj_ctenare(ctenar1)
    knihovna.registruj_ctenare(ctenar2)
    print(f"Seznam čtenářů: {[str(c) for c in knihovna.ctenari]}")

    knihovna.zrus_registraci_ctenare(ctenar1)
    print(f"Seznam čtenářů po odebrání: {[str(c) for c in knihovna.ctenari]}")

    print(f"Vyhledávání knih podle klíčových slov: {
          [str(kniha) for kniha in knihovna.vyhledej_knihu(klicove_slovo='1984')]}")
    print(f"Vyhledávání čtenářů podle klíčových slov: {
          [str(ctenar) for ctenar in knihovna.vyhledej_ctenare(klicove_slovo='Petr')]}")

    knihovna.pridej_knihu(kniha1)
    knihovna.vypujc_knihu(kniha1.isbn, ctenar2)
    print(f"Vypůjčené knihy: {[(isbn, str(ctenar), str(datum))
          for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")
    knihovna.vrat_knihu(kniha1.isbn, ctenar2)
    print(f"Vypůjčené knihy po vrácení: {[(isbn, str(ctenar), str(datum))
          for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")

    print(knihovna)
