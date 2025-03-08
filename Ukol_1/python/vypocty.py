from typing import List
import statistics

def soucet(cisla: List[int]) -> int:
    return sum(cisla)

def soucin(cisla: List[int]) -> int:
    if not cisla:
        return 0
    soucin = 1
    for cislo in cisla:
        soucin *= cislo
    return soucin

def prumer(cisla: List[int]) -> float:
    if not cisla:
        raise ValueError("Seznam čísel nesmí být prázdný.")
    return sum(cisla) / len(cisla)

def median(cisla: List[int]) -> float:
    if not cisla:
        raise ValueError("Seznam čísel nesmí být prázdný.")
    return statistics.median(cisla)

def main():
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    try:
        cisla = [int(cislo) for cislo in vstup.split(",")]
    except ValueError:
        print("Chyba: Vstup musí obsahovat pouze celá čísla oddělená čárkami.")
        return

    if not cisla:
        print("Chyba: Seznam čísel nesmí být prázdný.")
        return

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))

if __name__ == "__main__":
    main()
