def soucet(cisla: list[int]) -> int:

    return sum(cisla)


def soucin(cisla: list[int]) -> int:

    if not cisla:  # Handle the empty list case
        return 0
    soucin = 1
    for cislo in cisla:
        soucin *= cislo
    return soucin


def prumer(cisla: list[int]) -> float:
    if not cisla:  # Handle the empty list case
        raise ValueError("Cannot calculate the average of an empty list")
    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
    if not cisla:  # Handle the empty list case
        raise ValueError("Cannot calculate the average of an empty list")
    cisla = sorted(cisla)
    n = len(cisla)
    if n % 2 == 1:
        return cisla[n // 2]
    else:
        return (cisla[n // 2 - 1] + cisla[n // 2]) / 2.0


def main():

    try:
        vstup = input("Zadejte seznam cisel oddelenych carkou: ")
        cisla = [int(cislo) for cislo in vstup.split(",")]

        print("Soucet:", soucet(cisla))
        print("Soucin:", soucin(cisla))

        try:
            print("Prumerna hodnota:", prumer(cisla))
        except ValueError as e:
            print(e)

        try:
            print("Median:", median(cisla))
        except ValueError as e:
            print(e)

    except ValueError:
        print("Zadali jste neplatny vstup. Zkuste to znovu.")

if __name__ == "__main__":
    main()
