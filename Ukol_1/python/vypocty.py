import math

def soucet(cisla: list[int]) -> int:
  if not cisla:
    print("Seznam čísel je prázdný.")
    return 0
  return sum(cisla)

def soucin(cisla: list[int]) -> int:
  if not cisla:
    print("Seznam čísel je prázdný.")
    return 0
  return math.prod(cisla)

def prumer(cisla: list[int]) -> float:
  if not cisla:
    cisla = []
    raise ValueError("Seznam čísel je prázdný.")
  return sum(cisla) / len(cisla)

def median(cisla: list[int]) -> float:
  cisla.sort()
  if not cisla:
    cisla = []
    raise ValueError("Seznam čísel je prázdný.")

  delka = len(cisla)
  if delka % 2 == 0:
    return (cisla[delka // 2 - 1] + cisla[delka // 2]) / 2
  else:
    return cisla[delka // 2]

def main():
  vstup = input("Zadejte seznam čísel oddělených čárkou: ")
  cisla = [int(cislo) for cislo in vstup.split(",") if cislo.strip() != "" and cislo.strip().isdigit()]
  if not cisla:
    raise ValueError("Nebyla zadána žádná čísla.")  #

  print("Součet:", soucet(cisla))
  print("Součin:", soucin(cisla))
  print("Průměrná hodnota:", prumer(cisla))
  print("Medián:", median(cisla))

if __name__ == "__main__":
  main()
