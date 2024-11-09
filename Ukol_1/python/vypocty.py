def soucet(cisla: list[int]) -> int:
    
    return sum(cisla)


def soucin(cisla: list[int]) -> int:
   
    soucin = 1
    for cislo in cisla:
        soucin *= cislo
    return soucin


def prumer(cisla: list[int]) -> float:
   
    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
   
    cisla.sort()
    n = len(cisla)
    mid = n // 2
    if n % 2 == 0:
        return (cisla[mid - 1] + cisla[mid]) / 2
    else:
        return cisla[mid]


def main():
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))


if __name__ == "__main__":
    main()
