import statistics
cisla = []
print("Zadejte libovolny pocet cisel(pro ukonceni zadejte 0)")

while True:
    cislo = int(input())
    if cislo == 0:
        break
    
    cisla.append(cislo)
    
soucet = sum(cisla)
print("Soucet cisel je: ", soucet)


soucin = 1
for cislo in cisla:
    soucin *= cislo
print("Soucin cisel je: ", soucin)


prumer = soucet / len(cisla)
print("Prumer cisel je: ", prumer)


median = statistics.median(cisla)
print("Median cisel je: ", median)
