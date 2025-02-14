class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        try:
            if int(isbn) > 0:
                self.isbn = isbn
            else:
                raise ValueError
        except Exception:
            raise ValueError('Invalid ISBN.')

    #getters - must be implemented all bcs of the tests
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
    
    #setters:
    @nazev.setter
    def nazev(self, val: str):
        self._nazev = val
    @autor.setter
    def autor(self, val: str):
        self._autor = val
    @rok_vydani.setter
    def rok_vydani(self, val: str):
        self._rok_vydani = val
    @isbn.setter
    def isbn(self, val: str):
        #check if val is integer
        try:
            int(val)
        except Exception:
            raise ValueError('Invalid ISBN.')
        if len(val) != 13:
            raise ValueError('ISBN must have 13 digits!')
        self._isbn = val

    def __str__(self) -> str:
        kniha : str = "\n"
        kniha += "Title: " + self.nazev
        kniha += "\n\tAuthor:\t\t\t" + self.autor + "\n"
        kniha += "\tYear of publication\t" + str(self.rok_vydani) + "\n"
        kniha += "\tISBN:\t\t\t" + str(self.isbn)
        return kniha
