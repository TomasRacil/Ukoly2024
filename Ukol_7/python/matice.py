import random

#n je pocet radku m je pocet sloupcu
#funkce vraci hodnotu typu list[list[int]] coz je seznam seznamu
#seznam seznamu kde kazdy vnitrni seznam predstavuje jeden radek a obsahuje cela cisla
def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    matice: list[list[int]] = [] #inicializace matice jako prazdneho seznamu
    
    for radek in range(n): #cyklus se opakuje n-krat, kde n je pocet radku
    #takze promenna prvek je indexem kazdeho radku matice
    #tento for prochazi kazdy radek, a po jednotlivych pruchodech vytvori 
    # novy radek = new row neboli aktualni radek
        new_row = [] #po kazde iteraci cyklu je vytvoren prazdny seznam new row 
        #new row je novy radek ktery bude naplnen nahodnymi cisly
        for prvek in range(m): #cyklus se opakuje m-krat kde m je pocet sloupcu
            #v kazde iteraci cyklu bude promenna prvek indexem pro kazdy 
            # prvek v radku
            new_row.append(random.randint(0,9)) #generace nahodneho cisla a toto cislo je pridano
            #do seznamu new row, ktery predstavuje aktualni radek matice
        matice.append(new_row) #aktualni radek naplneny cisly pridame do
        #seznamu matice
    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    if len(matice) == 0: #pokud je matice prazdna
        return ""
    
    reprezentace = ""

    for radek in matice: #pro kazdy radek matice
        for i in range(len(radek)): #tento rozsah cisel bude pouzit pro
            #indexovani jednotlivych prvku seznamu radek
            reprezentace += str(radek[i]) #pridame aktualni prvek jako text
            if i < len(radek) - 1: #pokud to neni posledni prvek tak:
                reprezentace += " " #pridame mezeru

        reprezentace += "\n" #jdeme na dalsi radek

    return reprezentace

    #...range(n) je funkce ktera generuje sekvenci cisel od 0 do posledniho n-1
    #takze pokud range(len(radek)) ....posledni prvek je len(radek)-1



def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    
        #kontrola rozmeru
    if len(matice1) != len(matice2):
        return None
    if len(matice1) == 0:
        return[]

    if len(matice1[0]) != len(matice2[0]):
        return None

    #soucet matic
    #pokud matice maji stejny pocet sloupcu a radku
    #scitame odpovidajici stejne pozice
    matice_soucet: list[list[int]] = [] #prazdna matice ktera bude obsahovat pozdeji vysledek
    for i in range(len(matice1)): #pro kazdy radek v matici1, zaciname s matice1 protoze predpokladame ze
        #obe matice maji stejny rozmery
        radek = [] #vytvorime prazdny seznam pro aktualni radek vylsedne matice
        for j in range(len(matice1[0])): #pro kazdy sloupec v prvnim radku matice1
            #secteme odpovidajici prvky z matice1 a matice2
            #tedy matice1[i][j] je prvek z matice1 v radku i a sloupci j
            radek.append(matice1[i][j]+ matice2[i][j])
        matice_soucet.append(radek) #pridame secteny radek do vysledne matice


    return matice_soucet #vysledna matice


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    

    #kontrola nasobeni
    #pocet_sloupcu1 prvni matice musi byt roven pocet_radku2 druhe matice
    
    

    pocet_radku1 = len(matice1) #pocet radku
    if pocet_radku1 != 0: #pokud pocet radku prvni matice neni roven 0 tak:
        if len(matice1[0]) != len(matice2): #a pokud  pocet sloupcu v prvni matici neni rovno poctu radku ve druhe matici tak:
            return None

    #pokud prvni matice ma 0 radku a
    #je splnena prvni podminka druha ne
    elif len(matice2) == 0: #pokud druha matice ma 0 radku, 
        return[] #vratime prazdnou matici


    #pokud prvni matice ma 0 radku a pocet sloupcu prvni matice neni
    #rovny poctu radku druhe matice...
    #tedy neni splnena ani jedna podminka
    else:
        return None

    
    matice: list[list[int]] = []
    pocet_sloupcu1 = len(matice1[0]) #delka jejiho prvniho radku
    pocet_sloupcu2 = len(matice2[0])
    pocet_radku1 = len(matice1)
    pocet_radku2 = len(matice2)
    vysledna_matice = []

    for radek in range(pocet_radku1): #vysledna matice ma tolik radku jako matice1
        new_row = []
        for prvek in range(pocet_sloupcu2):
            new_row.append(0)
        vysledna_matice.append(new_row)


    for radek in range(len(vysledna_matice)): #pro kazdy radek vysledny matice, v prvni iteraci radek na indexu 0
        for sloupec in range(len(vysledna_matice[0])): #pro kazdy sloupec vysledny matice, .... sloupec na indexu 0
            for dvojice in range(pocet_sloupcu1): #(len(pocet_sloupcu1) nebo (len(pocet_radku2))... protoze pocet sloupcu prvni matice musi byt roven poctu radku druhe matice
                vysledna_matice[radek][sloupec] += matice1[radek][dvojice] * matice2[dvojice][sloupec]

    return vysledna_matice



def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    if len(matice) == 0: #podminka pro pocet radku, aby nebyla prazna
        return[]

    if len(matice[0]) == 0: #podminka pro radek bez sloupce,tj. bez prvku
        return[[]]


    transponovana_matice: list[list[int]] = []

    #pro kazdy sloupec puvodni matice vytvorime novy radek
    for sloupec in range(len(matice[0])):
        novy_radek = [] #novy radek v transponovane matici
        for radek in range(len(matice)): #pro kazdy radek puvodni matice
            novy_radek.append(matice[radek][sloupec]) #prida hodnotu na spravne misto v novem radku transponovane matice
        transponovana_matice.append(novy_radek)


    return transponovana_matice


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))