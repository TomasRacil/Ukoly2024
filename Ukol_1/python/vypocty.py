def soucet(cisla: list[int]) -> int:
    if not cisla:
        return 0
    return sum(cisla)


def soucin(cisla: list[int]) -> int:
    if not cisla:
        return 0
    produkt = 1
    for cislo in cisla:
        produkt *= cislo
    return produkt


def prumer(cisla: list[int]) -> float:
    if not cisla:
        cisla = []
        raise ValueError("Seznam cisel je prazdny!")

    return sum(cisla) / len(cisla) if cisla else 0


def median(cisla: list[int]) -> float:
    if not cisla:
        cisla = []
        raise ValueError("Seznam cisel je prazdny!")
    cisla = sorted(cisla)
    n = len(cisla)
    if n == 0:
        return 0
    stred = n // 2
    if n % 2 == 0:
        return (cisla[stred - 1] + cisla[stred]) / 2
    return cisla[stred]


def main():
    vstup = input("Zadejte seznam cisel oddelenych carkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",") if cislo.strip().isdigit()]

    print("Soucet:", soucet(cisla))
    print("Soucin:", soucin(cisla))
    print("Prumrrna hodnota:", prumer(cisla))
    print("Median:", median(cisla))


if __name__ == "__main__":
    main()
