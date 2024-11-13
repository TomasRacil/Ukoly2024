
def soucet(cisla):
    suma= 0
    for cislo in cisla:
        suma += cislo
    return suma

def soucin(cisla):
    if len(cisla) == 0:
        return 0
    soucin= 1
    for cislo in cisla:
        soucin *= cislo
    return soucin

def prumer(cisla):
    if len(cisla) == 0:
        raise ValueError("Seznam cisel je prazdny.")
    suma= soucet(cisla)
    return suma / len(cisla)

def median(cisla):
    if len(cisla) == 0:
        raise ValueError("Seznam cisel je prazdny")
    cisla.sort()
    n = len(cisla)
    if n % 2 == 0:
        return (cisla[n // 2 -1] + cisla[n // 2]) / 2
    else:
        return cisla[n // 2]

def main():
    vstup = input("zadej cisla oddelena carkama: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("soucet:", soucet(cisla))
    print("soucin:", soucin(cisla))
    print("prumerna hodnota :", prumer(cisla))
    print("median:", median(cisla))

if __name__ == "__main__":
    main()
