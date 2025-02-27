import statistics
def soucet(cisla: list[int]) -> int:
    soucet = sum(cisla)
    return soucet


def soucin(cisla: list[int]) -> int:
    v = 1
    if cisla != []:
      for cislo in cisla:
          v = v*cislo
    else:
        v= v*0
    return v


def prumer(cisla: list[int]) -> float:
    if cisla != []:
      prumer = round(sum(cisla)/len(cisla),2)
    else:
        prumer = 0
    return prumer


def median(cisla: list[int]) -> float:
    if cisla != []:
      median = statistics.median(cisla)
    else:
      median = 0
    return median


def main():
    """Načte vstup od uživatele, zavolá funkce pro výpočet a vypíše výsledky."""
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    if vstup != "":
      cisla = [int(cislo) for cislo in vstup.split(",")]
    else:
        cisla = []

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))


if __name__ == "__main__":
    main()
