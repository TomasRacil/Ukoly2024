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


    #getry
    @property
    def nazev(self) -> str:
        return self._nazev
    
    @property
    def autor(self) -> str:
        return self._autor
    
    @property
    def rok_vydani(self) -> int:
        return self._rok_vydani
    
    @property
    def isbn(self) -> str:
        return self._isbn

    def __str__(self) -> str:
        return ""

    #setry
    @nazev.setter
    def nazev(self, nazev: str):
        self._nazev = nazev
    
    @autor.setter
    def autor(self, autor: str):
        self._autor = autor

    @rok_vydani.setter
    def rok_vydani(self, rok_vydani: int):
        self._rok_vydani = rok_vydani

    @isbn.setter
    def isbn(self, isbn: str):
        if len(isbn) != 13:
            raise ValueError("ISBN musí mít 13 znaků.")
        if not isbn.isdigit():
            raise ValueError("ISBN musí obsahovat pouze číslice.")
        self._isbn = isbn

    def __str__(self) -> str:
        return f"{self._nazev} - {self._autor} ({self._rok_vydani})"