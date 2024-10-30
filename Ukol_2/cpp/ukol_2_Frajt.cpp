#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
// funkce pro ceasar sifru
void Ceasar(string s, char u)
{
    ifstream file;
    string line;
    string text = "";
    int klic;
    cout<<"O kolik je posun?"<<endl;
    cin>>klic;
    // pokud je potreba desifrovat tak prevratime hodnotu klice
    if (u == 'd')
    {
        klic = klic*-1;
    }
    // otevirani a cteni souboru
    file.open(s);
    while (getline(file,line))
    {
        cout<<line<<endl;
        text+= line + "\n";
        cout<<"text: " + text<<endl;
    }
    // sifrovani/desifrovani textu 
    string newtext = "";
    // sifrujeme charakter po charakteru   
        for (char c : text)
        {
            // pouzil jsem int, protoze s char se mohlo stat ze jsme po posunu byli mimo ascii tabulku.
            int newc;
            // vztahuje se pouze na velka pismena, kdyz se dostaneme na konec abecedy musime se posunout na jeji zacatek.
            if (c >= 65 && c <= 90)
            {
                newc = c + klic;
                if (newc >90){
                    newc = newc - 26;
                }
                if (newc <65){
                    newc = newc + 26;
                }
                // na konci charakter zapiseme
                newtext+=char(newc);
            }
            else if(c >= 97 && c <= 122)
            {
                // tady se resi mala pismenka stejnym zpusobem
                newc = c + klic;
                if (newc >122){
                    newc = newc - 26;
                }
                if (newc <97){
                    newc = newc + 26;
                }
                newtext+=char(newc);
            }
            else
            // kdyz to neni pismeno, tak ten charakter proste opiseme
            {
                newtext+=c;
            }
        }
    // vypsani do souboru (v xor sifre mam i vystup do noveho souboru, ale osobne bych to psal do stejneho souboru)
    ofstream out(s);
    out<<newtext<<endl;
    file.close(); 
}
// funkce pro vigener sifru
void Vigener(string s,char u)
{
    ifstream file;
    string line;
    string text = "";
    string klic;
    cout<<"Zadejte klic:"<<endl;
    cin>>klic;
    cout<<klic<<endl;
    // opet cteni souboru
    file.open(s);
    while (getline(file,line))
    {
        text+= line + "\n";
    } 
    string newtext = "";
    // u teto sifry se nam to o kolik budeme posouvat meni, takze sledujeme na ktere pozici v klici se nachazime  
    int keyPos = 0; 
        for (char c : text)
        {
            int newc;
            // preklad pro velka pismena
            if (c >= 65 && c <= 90)
            {
                // preklad probiha temer stejne, jen v tomto pripade nemuzeme pro desifrovani jen obratit klic
                if(u == 's')
                {
                    newc = c + (tolower(klic[keyPos]) - 96);
                }
                else if (u == 'd')
                {
                    newc = c - (tolower(klic[keyPos]) - 96);
                }
                if (newc >90){
                    newc = newc - 26;
                }
                if (newc <65){
                    newc = newc + 26;
                }
                newtext+=char(newc);
                
            }
            // preklad pro mala pismena
            else if(c >= 97 && c <= 122)
            {
                if(u == 's')
                {   
                    newc = c + (tolower(klic[keyPos]) - 96);
                }
                else if (u == 'd')
                {
                    newc = c - (tolower(klic[keyPos]) - 96);
                }
                if (newc >122){
                    newc = newc - 26;
                }
                if (newc <97){
                    newc = newc + 26;
                }
                newtext+=char(newc);
            }
            else
            {
                newtext+=c;
            }
            // tato cast kodu nam zajisti, ze se budeme posouvat i v klici
            // pokud jeste nejsme na pozici posledniho charakteru, tak posuneme o jedno 
            if (keyPos < klic.length()-1){
                    keyPos++;
                }
            // pokud jsme na posledni pozici, vratime se na zacatek
            else{
                    keyPos = 0;
                }
        }
    // vypis do souboru
    ofstream out(s);
    out<<newtext<<endl;
    file.close();
}
// pomocna funkce na prevod charakteru do binarniho kodu
string getbin(int c){
    string bin = "";
    // zapisujeme zbytek po deleni 2...
    while (c != 1){
        bin += to_string(c%2);
        c = c/2;
    }
    // na konec pripiseme 1...
    bin += "1";
    // pokud je cislo moc kratke pridame potrebny pocet nul...
    int dodatek = 8-bin.length();
    for (int i=0;i< dodatek;i++){
        bin += "0";
    }
    // a cele cislo prevratime
    reverse(bin.begin(),bin.end());
    return bin;
}
// funkce ktera z binarniho kodu vycte charakter
char revbin(string s){
    // prevratime cislo protoze zaciname pocitat od jednotek
    reverse(s.begin(),s.end());
    int znak = 0;
    // a kazdou cislici vynasobime mocninou dvou podle toho kde se v cisle nachazi
    for (int i = 0; i<7;i++){
        int hod = s[i]-48;
        int moc = pow(2,i);
        znak += hod*moc;
    }
    return znak;
}
// funkce pro xor sifru
void orExclusive(string s){
    ifstream file;
    string line;
    string text = "";
    string klic;
    // keyPos zajisti, ze ke znaku v textu priradime patricny znak v klici
    int keyPos = 0;
    cout<<"Zadejte klic:"<<endl;
    cin>>klic;
    cout<<klic<<endl;
    // otevirani a cteni souboru
    file.open(s);
    while (getline(file,line))
    {
        text+= line + "\n";
    }
    cout<<"text: " + text<<endl;
    // text.pop_back() zajisti, ze nebudeme prekladat mezeru, ktera se na konci textu automaticky nachazi
    text.pop_back();
    string newtext = "";
    // opet cely text rozlozime na charaktery
    for (char c : text){
        // text i klic prelozime do binarniho kodu
        string binc = getbin(c);
        string bink = getbin(klic[keyPos]);
        // binPos nam zajisti, ze budeme vzdy pracovat na stejne pozici v binarnich kodech
        int binPos = 0;
        string newbin = "";
        // vytvarime novy binarni kod z dvou predchozich kodu
        for (char b : binc){
            // coz prakticky znamena ze kdyz se cislice na stejne pozici rovnaji tak xor vyhodi 0 a kdyz ne tak 1
            if (b == bink[binPos]){
                newbin += "0";
            }
            else{
                newbin += "1";
            }
            // tady se opet posovame na novou pozici v binarnim kodu
            if (binPos < bink.length()-1){
                    binPos++;
            }
            else{
                    binPos = 0;
            }
        }
        // prekladame ziskany binarni kod na charakter
        char newc = revbin(newbin);
        // zapisujeme do vystupniho textu
        newtext += char(newc);
        // a posouvame na dalsi charakter v klici
        if (keyPos < klic.length()-1){
                    keyPos++;
            }
        else{
                    keyPos = 0;
            }
    }
    // zapisovani do noveho souboru (program odsekne .txt na konci a prida koncovku sifry + .txt)
    for (int i=0;i<4;i++){
        s.pop_back();
    }
    ofstream out(s + "_xor.txt");
    out<<newtext<<endl;
    file.close();
}
// main 
int main ()
{
    fstream file;
    // tento charakter urcuje jestli budeme sifrovat nebo desifrovat
    char ukol;
    // tento urcuje jakou sifru pouzijeme
    char sifra;
    bool existsoubor = false;
    bool existsifra = false;
    bool existukol = false;
    // tento string uklada nazev souboru
    string soubor;
    // pomoci while zajistime, aby program pokracoval az pote co uzivatel zada spravny imput
    while(existukol == false){
        cout<<"Chcete sifrovat nebo desifrovat? (s/d)"<<endl;
        cin>>ukol;
        if(ukol == 's' || ukol == 'd'){
            existukol == true;
            break;
        }
        else{
            cout<<"Zadavejte pouze pismena uvedena v zavorce!"<<endl;
        }
    }
    while(existsoubor == false){
        cout<<"Zadejte nazev souboru"<<endl;
        cin>>soubor;
        file.open(soubor);
        // to jestli soubor existuje overujeme tak ze se soubor pokusime otevrit
        if (file.fail() == false){
            existsoubor = true;
            break;
        }
        else{
            cout<<"Tento soubor neexistuje!"<<endl;
        }
    }
    file.close();
    while(existsifra == false){
        cout<<"Zadejte typ sifry (c=ceasar,v=vigener,x=XOR)"<<endl;
        cin>>sifra;
        if(sifra == 'c' || sifra == 'v'|| sifra == 'x'){
            existsifra = true;
            break;
        }
        else{
            cout<<"Zadavejte pouze pismena uvedena v zavorce!"<<endl;
        }
    }
    // rozpoznavani kterou sifru budeme pouzivat
    if (sifra == 'c')
    {
        Ceasar(soubor,ukol);
    }
    else if(sifra == 'v')
    {
        Vigener(soubor,ukol);
    }
    else if(sifra == 'x')
    {
        orExclusive(soubor);
    }
    return 0;
    
}