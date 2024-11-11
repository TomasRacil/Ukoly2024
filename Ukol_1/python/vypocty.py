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

    cisla = sorted(cisla)
    n = len(cisla)
    if n % 2 == 1:
        return cisla[n // 2]
    else:
        return (cisla[n // 2 - 1] + cisla[n // 2]) / 2.0


def main():

    vstup = input("Zadejte seznam cisel oddelenych carkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Soucet:", soucet(cisla))
    print("Soucin:", soucin(cisla))
    print("Prumerna hodnota:", prumer(cisla))
    print("Median:", median(cisla))


if __name__ == "__main__":
    main()
