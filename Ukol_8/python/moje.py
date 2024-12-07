from __future__ import annotations
import random
from typing import Union

class Matice:
    def __init__(self, n: int, m: int, data=None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        
        if data:
            if len(data) == n and all((len(row) == m for row in data)):
                self.data = data
            else:
                raise ValueError("Velikost poskytnutých dat neodpovídá rozměrům matice.")
        else:
            matice = []
            for i in range(n):
                novy_radek = []
                for j in range(m):
                    novy_radek.append(random.randint(0,9))
                matice.append(novy_radek)
                
            self.data = matice


    def __str__(self) -> str:
        radky_jako_retezce = []
        for radek in self.data:
            radek_retezec = " ".join(map(str, radek))
            radky_jako_retezce.append(radek_retezec)
        stringova_reprezentace = "\n".join(radky_jako_retezce)

        return stringova_reprezentace

    def __add__(self, other: "Matice") -> "Matice":
        """Sečte aktuální matici s maticí other."""
        # Implementace součtu matic
        vysledek = []
        for i in range(len(self.data)):
            novy_radek = []
            for j in range(len(self.data[0])):
                soucet = self.data[i][j] + other.data[i][j]
                novy_radek.append(soucet)
            vysledek.append(novy_radek)

        return Matice(self.n, self.m, vysledek)
        
    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        # Implementace násobení matic
        if isinstance(other, Matice):
            if self.m != other.n:
                raise ValueError("Pro maticové násobení musí počet sloupců první matice odpovídat počtu řádků druhé matice.")
            
            nasobeni = []
            for i in range(self.n):
                novy_radek = []
                for j in range(other.m):
                    soucin = 0
                    for k in range(other.n):
                        soucin += self.data[i][k] * other.data[k][j]
                    novy_radek.append(soucin)
                nasobeni.append(novy_radek)
            return Matice(self.n, other.m, nasobeni)
        
        elif isinstance(other, int):
            skalarem = []
            cislo = other
            for i in range(self.n):
                novy_radek = []
                for j in range(self.m):
                    novy_radek.append(self.data[i][j] * cislo)
                skalarem.append(novy_radek)
            return Matice(self.n, self.m, skalarem)
        
        else:
           raise TypeError("Lze násobit pouze jinou maticí nebo skalárem (int).") 

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        # Implementace transpozice matice
        transponovana = []
        for i in range(self.m):
            novy_radek = []
            for j in range(self.n):
                novy_radek.append(self.data[j][i])
            transponovana.append(novy_radek)
        
        return Matice(self.m, self.n, transponovana)

if __name__ == "__main__":

# Příklad použití
    matice1 = Matice(2, 3, [[1, 2, 3], [4, 5, 6]])

    # Maticové násobení
    vysledek = matice1.transpozice()
    print(vysledek)