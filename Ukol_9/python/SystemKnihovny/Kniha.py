# trida knihy v knihovne
class Kniha:

    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev         # nazev (string)
        self._autor = autor         # autor (string)
        self._rok_vydani = rok_vydani  # rok vydani (int)
        self._isbn = isbn         # (string)

        # validace ISBN
        self.validuj_isbn()

    @property
    def nazev(self) -> str:
        return self._nazev

    @nazev.setter
    def nazev(self, value: str):
        if not value.strip():
            raise ValueError("nazev nemuze byt prazdny")
        self._nazev = value

    @property
    def autor(self) -> str:
        return self._autor

    @autor.setter
    def autor(self, value: str):
        if not value.strip():
            raise ValueError("autor knihy nemuze byt prazdny")
        self._autor = value

    @property
    def rok_vydani(self) -> int:
        return self._rok_vydani

    @rok_vydani.setter
    def rok_vydani(self, value: int):
        if value < 0: # musi byt kladne cislo jinak eror
            raise ValueError("rok vydani musi byt kladny")
        self._rok_vydani = value

    @property
    def isbn(self) -> str:
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        self._isbn = value
        self.validuj_isbn()

    def validuj_isbn(self): # validace ISBN
     
        if len(self._isbn) != 13 or not self._isbn.isdigit(): # pokud ISBN nema 13 cislic, neni validni
            raise ValueError("ISBN musi mit 13 cislic")

    def __str__(self) -> str:
     
        # vrati knihu a udaje o ni
        return f"Kniha: '{self.nazev}' od {self.autor} (ISBN: {self.isbn}, Rok: {self.rok_vydani})"
