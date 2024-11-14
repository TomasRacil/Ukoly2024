import statistics


def soucet(cisla: list[int]) -> int:
   return sum(cisla)


def soucin(cisla: list[int]) -> int:
 if len(cisla) == 0:
     return 0
soucin = 1
for i in cisla:
    soucin *= i
return soucin
    

def prumer(cisla: list[int]) -> float:
   if len(cisla) == 0:
      raise ValueError

return sum(cisla) / len(cisla)

def median(cisla: list[int]) -> float:
return statistics.median(cisla)

def main():
    """Načte vstup od uživatele, zavolá funkce pro výpočet a vypíše výsledky."""
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))


if __name__ == "__main__":
    main()
