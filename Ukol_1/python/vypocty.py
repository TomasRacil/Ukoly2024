def soucet(cisla: list[int]) -> int:
  soucet = 0
  for i in range(len(cisla)):
    soucet += cisla[i]
  
  return soucet

def soucin(cisla: list[int]) -> int:
  soucin = 1
  for i in range(len(cisla)):
    soucin *= cisla[i]
  
  return soucin


def prumer(cisla: list[int]) -> float:
  soucet = 0
  pocet = 0
  for i in range(len(cisla)):
    soucet += cisla[i]
    pocet += 1
  prum = float(soucet/pocet)
  
  return prum


def median(cisla: list[int]) -> float:
  delka = len(cisla)
  cisla.sort()
  if(delka % 2 == 0):
    return (cisla[delka//2 - 1] + cisla[delka//2]) / 2
  else:
    return cisla[delka//2]


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
