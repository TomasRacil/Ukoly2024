import random

def vytvor_matici(n: int, m: int) -> list[list[int]]:
  
    #vytvoření prázdné matice
    matice: list[list[int]] = []
    
    #naplnění matice náhodnými čísly od 0 do 9
    for _ in range(n):
        radek = [random.randint(0, 9) for _ in range(m)]  # Vytvoří náhodný řádek
        matice.append(radek)  # Přidá řádek do matice
    
    return matice

def reprezentace_matice(matice: list[list[int]]) -> str: #vrátí matici ve stringovém tvaru
   
    #pro každý řádek matice vytvoříme string, kde jsou hodnoty odděleny mezerami
    return '\n'.join(' '.join(str(x) for x in radek) for radek in matice)

def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
  #sečtení matic a kntrola rozměrů
    #zkontrolujeme, zda mají matice stejné rozměry
    if len(matice1) != len(matice2) or len(matice1[0]) != len(matice2[0]):
        print("Chyba: Matice mají různé rozměry, součet není možný.")
        return None

    #sečteme odpovídající prvky matic
    matice: list[list[int]] = []
    for i in range(len(matice1)):
        radek = [matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))]
        matice.append(radek)
    
    return matice

def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    #vynásobí dvě matice, pokud je násobení proveditelné. Pokud ne, vrátí None.
    :return: Výsledek násobení matic nebo None, pokud není násobení proveditelné
    
    #zkontrolujeme, zda je násobení proveditelné
    if len(matice1[0]) != len(matice2):
        print("Chyba: Násobení matic není možné, počet sloupců první matice se neshoduje s počtem řádků druhé matice.")
        return None

    #inicializujeme výslednou matici, která bude mít stejné rozměry jako počet řádků první matice a počet sloupců druhé matice
    matice: list[list[int]] = [[0] * len(matice2[0]) for _ in range(len(matice1))]

    # vynásobíme matice podle pravidel násobení matic
    for i in range(len(matice1)):  # pro každý řádek první matice
        for j in range(len(matice2[0])):  # pro každý sloupec druhé matice
            for k in range(len(matice2)):  # pro každý prvek v řádku druhé matice
                matice[i][j] += matice1[i][k] * matice2[k][j]
    
    return matice

def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
   
    #transpozice matice - řádky se vymění se sloupci
    matice: list[list[int]] = [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]
    return matice

if __name__ == "__main__":
    #vytvoříme dvě matice s náhodnými čísly
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    #vytiskneme matice
    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    #sečteme matice a zobrazíme výsledek
    soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(reprezentace_matice(soucet))

    #vynásobíme matice a zobrazíme výsledek
    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek))

    #transponujeme první matici a zobrazíme výsledek
    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
