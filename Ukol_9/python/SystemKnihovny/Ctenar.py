class Ctenar:
    def __init__(self, jmeno, prijmeni):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self._cislo_prukazky = self._vygeneruj_cislo_prukazky()

    @property
    def jmeno(self):
        return self._jmeno

    @property
    def prijmeni(self):
        return self._prijmeni

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value):
        if value <= 0:
            raise ValueError("Číslo průkazky musí být kladné")
        self._cislo_prukazky = value

    def _vygeneruj_cislo_prukazky(self):
        return 1  # Příklad generování čísla průkazky
