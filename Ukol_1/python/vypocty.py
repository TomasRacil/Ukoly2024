
def soucet(cisla: list[int]) -> int:
    soucet = 0
    for k in range(len(cisla)):
        soucet += cisla[k]

    return soucet

def soucin(cisla: list[int]) -> int:
    nasobeni = 1
    for k in range(len(cisla)):
        nasobeni *= cisla[k]

    return nasobeni

def prumer(cisla: list[int]) -> float:
    soucet = 1
    pocet = len(cisla)
    for k in range(pocet):
        soucet += cisla[k]
    prum = float(soucet/pocet)

    return prum


def median(cisla: list[int]) -> float:
   delka = len(cisla)
   cisla.sort()
   if(delka % 2 == 0):
       return (cisla[delka//2 - 1] + cisla[delka//2]) / 2
   else:
       return cisla[delka//2]


def main():
    """Na�te vstup od u�ivatele, zavol� funkce pro v�po�et a vyp�e v�sledky."""
    vstup = input("Zadejte seznam ��sel odd�len�ch ��rkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Sou�et:", soucet(cisla))
    print("Sou�in:", soucin(cisla))
    print("Pr�m�rn� hodnota:", prumer(cisla))
    print("Medi�n:", median(cisla))


if __name__ == "__main__":
    main()
