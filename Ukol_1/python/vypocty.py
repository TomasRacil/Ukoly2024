from typing import List
import statistics

def soucet(cisla: List[int]) -> int:
    return sum(cisla)

def soucin(cisla: List[int]) -> int:
    soucin = 1
    for cislo in cisla:
        soucin *= cislo
    return soucin

def prumer(cisla: List[int]) -> float:
    return sum(cisla) / len(cisla) if cisla else 0

def median(cisla: List[int]) -> float:
    return statistics.median(cisla)

def main():
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))

if __name__ == "__main__":
    main()
