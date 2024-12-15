import re
    import re
    import random
    import csv
    from datetime import datetime, date
    from os.path import realpath, dirname, join

    class Kniha:
        def __init__(self, nazev, autor, rok_vydani, isbn):
            self.nazev = nazev
            self.autor = autor
            self.rok_vydani = rok_vydani
            self.isbn = isbn

        @property
        def isbn(self):
            return self._isbn

        @isbn.setter
        def isbn(self, value):
            if not re.match(r'^\d{13}$', value):
                raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
            self._isbn = value

        def __str__(self):
            return f"{self.nazev} od {self.autor} ({self.rok_vydani}), ISBN: {self.isbn}"


    class Ctenar:
        def __init__(self, jmeno, prijmeni):
            self.jmeno = jmeno
            self.prijmeni = prijmeni
            self.cislo_prukazky = self.vygeneruj_cislo_prukazky()

        @property
        def cislo_prukazky(self):
            return self._cislo_prukazky

        @cislo_prukazky.setter
        def cislo_prukazky(self, value):
            if value <= 0:
                raise ValueError("Číslo průkazky musí být kladné celé číslo.")
            self._cislo_prukazky = value

        @staticmethod
        def vygeneruj_cislo_prukazky():
            return random.randint(1, 10000)

        def __str__(self):
            return f"{self.jmeno} {self.prijmeni}, číslo průkazky: {self.cislo_prukazky}"


    def kniha_existuje(func):
        def wrapper(self, isbn, *args, **kwargs):
            if not any(kniha.isbn == isbn for kniha in self.knihy):
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return func(self, isbn, *args, **kwargs)
        return wrapper


    class Knihovna:
        def __init__(self, nazev):
            self.nazev = nazev
            self.knihy = []
            self.ctenari = []
            self.vypujcene_knihy = {}

        @classmethod
        def z_csv(cls, soubor):
            knihovna = cls("Moje Knihovna")
            with open(soubor, newline='', encoding='utf-8') as csvfile:
                reader = csv.DictReader(csvfile)
                for row in reader:
                    if row['typ'] == 'kniha':
                        kniha = Kniha(row['nazev'], row['autor'], int(row['rok_vydani']), row['isbn'])
                        knihovna.pridej_knihu(kniha)
                    elif row['typ'] == 'ctenar':
                        ctenar = Ctenar(row['jmeno'], row['prijmeni'])
                        knihovna.registruj_ctenare(ctenar)
            return knihovna

        def pridej_knihu(self, kniha):
            self.knihy.append(kniha)

        @kniha_existuje
        def odeber_knihu(self, isbn):
            self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

        def vyhledej_knihu(self, klicova_slovo):
            return [kniha for kniha in self.knihy if klicova_slovo.lower() in kniha.nazev.lower() or klicova_slovo.lower() in kniha.autor.lower() or klicova_slovo == kniha.isbn]

        def registruj_ctenare(self, ctenar):
            self.ctenari.append(ctenar)

        def zrus_registraci_ctenare(self, ctenar):
            self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

        def vyhledej_ctenare(self, klicova_slovo):
            return [ctenar for ctenar in self.ctenari if klicova_slovo.lower() in ctenar.jmeno.lower() or klicova_slovo.lower() in ctenar.prijmeni.lower() or klicova_slovo == str(ctenar.cislo_prukazky)]

        @kniha_existuje
        def vypujc_knihu(self, isbn, ctenar):
            if isbn in self.vypujcene_knihy:
                raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
            self.vypujcene_knihy[isbn] = (ctenar, date.today())

        @kniha_existuje
        def vrat_knihu(self, isbn, ctenar):
            if isbn not in self.vypujcene_knihy:
                raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
            if self.vypujcene_knihy[isbn][0] != ctenar:
                raise ValueError("Kniha nebyla vypůjčena tímto čtenářem.")
            del self.vypujcene_knihy[isbn]

        def __str__(self):
            return f"Knihovna {self.nazev} má {len(self.knihy)} knih a {len(self.ctenari)} čtenářů."


    if __name__ == "__main__":
        knihovna = Knihovna.z_csv(join(dirname(realpath(__file__)), "knihovna.csv"))
        print(f"Knihovna načtena z CSV: {knihovna.nazev}")

        kniha1 = Kniha("Stopařův průvodce po Galaxii", "Douglas Adams", 1979, "9780345391803")
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

        print(f"Vyhledávání knih podle klíčových slov: {[str(kniha) for kniha in knihovna.vyhledej_knihu('1984')]}")
        print(f"Vyhledávání čtenářů podle klíčových slov: {[str(ctenar) for ctenar in knihovna.vyhledej_ctenare('Petr')]}")

        knihovna.pridej_knihu(kniha1)
        knihovna.vypujc_knihu(kniha1.isbn, ctenar2)
        print(f"Vypůjčené knihy: {[(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")
        knihovna.vrat_knihu(kniha1.isbn, ctenar2)
        print(f"Vypůjčené knihy po vrácení: {[(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")

        print(knihovna)

import random
import csv
from datetime import datetime
from os.path import realpath, dirname, join

class Kniha:
    def __init__(self, nazev, autor, rok_vydani, isbn):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, value):
        if not re.match(r'^\d{13}$', value):
            raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
        self._isbn = value

    def __str__(self):
        return f"{self.nazev} od {self.autor} ({self.rok_vydani}), ISBN: {self.isbn}"


class Ctenar:
    def __init__(self, jmeno, prijmeni):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value):
        if value <= 0:
            raise ValueError("Číslo průkazky musí být kladné celé číslo.")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky():
        return random.randint(1, 10000)

    def __str__(self):
        return f"{self.jmeno} {self.prijmeni}, číslo průkazky: {self.cislo_prukazky}"


def kniha_existuje(func):
    def wrapper(self, isbn, *args, **kwargs):
        if not any(kniha.isbn == isbn for kniha in self.knihy):
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje v knihovně.")
        return func(self, isbn, *args, **kwargs)
    return wrapper


class Knihovna:
    def __init__(self, nazev):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}

    @classmethod
    def z_csv(cls, soubor):
        knihovna = cls("Moje Knihovna")
        with open(soubor, newline='', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                kniha = Kniha(row['nazev'], row['autor'], int(row['rok_vydani']), row['isbn'])
                knihovna.pridej_knihu(kniha)
        return knihovna

    def pridej_knihu(self, kniha):
        self.knihy.append(kniha)

    def odeber_knihu(self, isbn):
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo):
        return [kniha for kniha in self.knihy if klicova_slovo.lower() in kniha.nazev.lower() or klicova_slovo.lower() in kniha.autor.lower() or klicova_slovo == kniha.isbn]

    def registruj_ctenare(self, ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar):
        self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

    def vyhledej_ctenare(self, klicova_slovo):
        return [ctenar for ctenar in self.ctenari if klicova_slovo.lower() in ctenar.jmeno.lower() or klicova_slovo.lower() in ctenar.prijmeni.lower() or klicova_slovo == str(ctenar.cislo_prukazky)]

    @kniha_existuje
    def vypujc_knihu(self, isbn, ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError("Kniha je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.now())

    @kniha_existuje
    def vrat_knihu(self, isbn, ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError("Kniha není vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError("Kniha nebyla vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]

    def __str__(self):
        return f"Knihovna {self.nazev} má {len(self.knihy)} knih a {len(self.ctenari)} čtenářů."


if __name__ == "__main__":
    knihovna = Knihovna.z_csv(join(dirname(realpath(__file__)), "knihovna.csv"))
    print(f"Knihovna načtena z CSV: {knihovna.nazev}")

    kniha1 = Kniha("Stopařův průvodce po Galaxii", "Douglas Adams", 1979, "9780345391803")
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

    print(f"Vyhledávání knih podle klíčových slov: {[str(kniha) for kniha in knihovna.vyhledej_knihu('1984')]}")
    print(f"Vyhledávání čtenářů podle klíčových slov: {[str(ctenar) for ctenar in knihovna.vyhledej_ctenare('Petr')]}")

    knihovna.pridej_knihu(kniha1)
    knihovna.vypujc_knihu(kniha1.isbn, ctenar2)
    print(f"Vypůjčené knihy: {[(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")
    knihovna.vrat_knihu(kniha1.isbn, ctenar2)
    print(f"Vypůjčené knihy po vrácení: {[(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")

    print(knihovna)
