class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self._isbn = None  # Inicializace atributu
        self.isbn = isbn   # Volání validace

    @property
    def nazev(self):
        return self._nazev

    @nazev.setter
    def nazev(self, novy_nazev):
        if not novy_nazev.strip():
            raise ValueError("Název knihy nesmí být prázdný.")
        self._nazev = novy_nazev.strip()

    @property
    def autor(self):
        return self._autor

    @autor.setter
    def autor(self, novy_autor):
        if not novy_autor.strip():
            raise ValueError("Autor knihy nesmí být prázdný.")
        self._autor = novy_autor.strip()

    @property
    def rok_vydani(self):
        return self._rok_vydani

    @rok_vydani.setter
    def rok_vydani(self, novy_rok):
        if not isinstance(novy_rok, int) or novy_rok < 0:
            raise ValueError("Rok vydání musí být kladné celé číslo.")
        self._rok_vydani = novy_rok

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, nove_isbn):
        if nove_isbn.isdigit() and len(nove_isbn) == 13:
            self._isbn = nove_isbn
        else:
            raise ValueError("Špatně zadané ISBN, musí obsahovat 13 číslic.")

    def __str__(self) -> str:
        return f"{self.nazev} od {self.autor}, rok vydání: {self.rok_vydani}, ISBN: {self.isbn}"
