from typing import List

def soucet(cisla: List[int]) -> int:
    return sum(cisla)


def soucin(cisla: List[int]) -> int:
    result = 1
    for num in cisla:
        result *= num
    return result


def prumer(cisla: List[int]) -> float:
    return sum(cisla) / len(cisla) if cisla else 0.0


def median(cisla: List[int]) -> float:
    if not cisla:
        return 0.0
    sorted_cisla = sorted(cisla)
    n = len(sorted_cisla)
    mid = n // 2
    if n % 2 == 0:
        return (sorted_cisla[mid - 1] + sorted_cisla[mid]) / 2.0
    else:
        return sorted_cisla[mid]


def main():
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))


if __name__ == "__main__":
    main()
