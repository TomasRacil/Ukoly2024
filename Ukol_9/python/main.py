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
    def __init__(self, jmeno: str, prijmeni: str, cislo_prukazky=None):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self._cislo_prukazky = cislo_prukazky or self.vygeneruj_cislo_prukazky()

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


# Dekorátor kontroluje, zda kniha s daným ISBN existuje v knihovně.
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
        try:
            with open(soubor, mode='r', encoding='utf-8') as file:
                csv_reader = csv.reader(file, delimiter=';')
                next(csv_reader)  # Přeskočí záhlaví
                for radek in csv_reader:
                    nazev, autor, rok_vydani, isbn = radek
                    knihy.append(Kniha(nazev, autor, int(rok_vydani), isbn))
        except FileNotFoundError:
            print(f"Soubor {soubor} nebyl nalezen.")
        return Knihovna("Testovaci knihovna", knihy)

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())
        else:
            raise ValueError("Kniha je již vypůjčená.")

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy and self.vypujcene_knihy[isbn][0] == ctenar:
            del self.vypujcene_knihy[isbn]
        else:
            raise ValueError("Kniha nebyla vypůjčena tímto čtenářem.")

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def vyhledej_knihu(self, klicove_slovo: str):
        return [kniha for kniha in self.knihy if klicove_slovo in kniha.nazev or klicove_slovo in kniha.autor]

    def vyhledej_ctenare(self, cislo_prukazky: int):
        return next((ctenar for ctenar in self.ctenari if ctenar.cislo_prukazky == cislo_prukazky), None)

    def __str__(self):
        vypujcene_knihy_info = [(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in self.vypujcene_knihy.items()]
        return (f"Knihovna '{self.nazev}' obsahuje {len(self.knihy)} knih a {len(self.ctenari)} čtenářů. "
                f"Vypůjčené knihy: {vypujcene_knihy_info}")


if __name__ == "__main__":
    knihovna = Knihovna.z_csv("knihovna.csv")
    print(f"Knihovna načtena z CSV: {knihovna.nazev}")

    kniha1 = Kniha("Stopařův průvodce po Galaxii", "Douglas Adams", 1979, "9780345391803")
    knihovna.pridej_knihu(kniha1)

    ctenar1 = Ctenar("Jan", "Novák")
    knihovna.registruj_ctenare(ctenar1)

    knihovna.vypujc_knihu("9780345391803", ctenar1)
    print(knihovna)

    knihovna.vrat_knihu("9780345391803", ctenar1)
    print(knihovna)
