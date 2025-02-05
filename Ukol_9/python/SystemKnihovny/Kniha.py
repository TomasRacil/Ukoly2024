class Kniha:
    def __init__(self, nazev, autor, rok_vydani, isbn):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def nazev(self):
        return self._nazev

    @property
    def autor(self):
        return self._autor

    @property
    def rok_vydani(self):
        return self._rok_vydani

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, value):
        if not self._validuj_isbn(value):
            raise ValueError("Neplatné ISBN")
        self._isbn = value

    def _validuj_isbn(self, isbn):
        return len(isbn) in (10, 13) and isbn.isdigit()
