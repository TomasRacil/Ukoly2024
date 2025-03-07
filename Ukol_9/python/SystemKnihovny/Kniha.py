class Kniha:
    """
    Třída reprezentující knihu.
    """
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn  # použije se setter

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

    @isbn.setter
    def isbn(self, value: str):
        """
        Validuje a nastavuje ISBN. Požadujeme formát ISBN-13 (13 číslic).
        """
        if not (len(value) == 13 and value.isdigit()):
            raise ValueError(f"Neplatné ISBN '{value}'. ISBN musí mít 13 číslic.")
        self._isbn = value

    def __str__(self) -> str:
        """
        Textová reprezentace knihy.
        """
        return f"{self._nazev} ({self._autor}, {self._rok_vydani}) [{self._isbn}]"
