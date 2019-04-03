#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <ctime>
#include <windows.h>
#include <fstream>

using namespace std;

template<typename typ>
void wyswietlTablice(vector<typ> tabl){
    int i=0;
    cout<<"Tablica:"<<endl;
    for(typ t : tabl){
        //setw ustawia minimalna ilosc znakow, a ktorych wyswietla sie zmienna
        cout<<setw(5)<<t<<" ";
        i++;
        //dopasowac do szerokosci ekranu (13)
        if(i%13==0)
            cout<<endl;
    }
    cout<<endl;
}

template<typename typ, int rozmiar>
vector<typ> generujTablice(){
    vector<typ> tabl;
    for(auto i=1;i<=rozmiar;++i){
        typ losowa = rand();
        tabl.push_back(losowa);
    }
    //wyswietlTablice<typ>(tabl);
    return tabl;
}

template<typename typ>
bool sprawdz(vector<typ> tabl){
    typ tmp;
    tmp=tabl[0];
    for(typ t : tabl){
        if(t<tmp){
            //cout<<"Zle posortowane!"<<endl;
            return 0;
        }
        tmp=t;
    }
    //cout<<"Dobrze posortowane!"<<endl;
    return 1;
}

/*
template<typename typ>
vector<typ> merge(vector<typ> lewa, vector<typ> prawa){

    vector<typ> result;
    for(;;){
        if(lewa[0]<=prawa[0]){
            result.push_back(lewa[0]);
            lewa.erase(lewa.begin());
            if(lewa.empty())
                break;
        }
        else{
            result.push_back(prawa[0]);
            prawa.erase(prawa.begin());
            if(prawa.empty())
                break;
        }
    }

    if(prawa.size()!=0){
        for(typ p : prawa)
            result.push_back(p);
    }
    if(lewa.size()!=0){
        for(typ l : lewa)
            result.push_back(l);
    }
    return result;
}*/
/*
template<typename typ>
void mergesort(vector<typ> &tabl){
    if(tabl.size()>1){
        unsigned int const srodek = tabl.size()/2;
        vector<typ> lewaCzesc (tabl.begin(), tabl.begin()+srodek);
        vector<typ> prawaCzesc (tabl.begin()+srodek, tabl.end());
        mergesort<typ>(lewaCzesc);
        mergesort<typ>(prawaCzesc);
        tabl=merge(lewaCzesc, prawaCzesc);
    }

}
*/

template<typename typ>
void merge(vector<typ>& tabl, int poczatek, int srodek, int koniec){
    vector<typ> tablTmp(koniec-poczatek+1);
    int k=0;
    int i=poczatek;
    int j=srodek+1;

    while(i<=srodek && j<=koniec){
        if(tabl[i]<tabl[j]){
            tablTmp[k]=tabl[i];
            i++;
        }

        else{
            tablTmp[k]=tabl[j];
            j++;
        }
        k++;
    }

    while(i<=srodek){
        tablTmp[k]=tabl[i];
        k++;
        i++;
    }
    while(j<=koniec){
        tablTmp[k]=tabl[j];
        k++;
        j++;
    }
    for(i=poczatek;i<=koniec;i++)
        tabl[i]=tablTmp[i-poczatek];
}

template<typename typ>
void mergesort(vector<typ>& tabl,int poczatek, int koniec)
{
    if(poczatek<koniec){
        unsigned int const srodek = (poczatek+koniec)/2;
        mergesort<typ>(tabl,poczatek,srodek);
        mergesort<typ>(tabl,srodek+1,koniec);
        merge(tabl, poczatek, srodek, koniec);
    }
}


template<typename typ>
void quicksort(vector<typ> &tabl, int poczatek, int koniec){
    int srodek = (poczatek+koniec)/2;
    if(tabl.size()>1){
        int p,l;
        typ pivot = tabl[srodek];
        p=koniec;
        l=poczatek;
        while(l<=p){
            while( !(tabl[p]<=pivot||p<=poczatek) ){
                p--;
            }
            while( !(tabl[l]>=pivot||l>=koniec) ){
                l++;
            }

            if(l<=p){
                typ tmp=tabl[p];
                tabl[p]=tabl[l];
                tabl[l]=tmp;
                p--;
                l++;

            }
        };

        if(poczatek<p)
            quicksort(tabl,poczatek,p);
        if(l<koniec)
            quicksort(tabl,l,koniec);
    }
}

template<typename typ>
void makeheap(vector<typ>& tabl, int poczatek, int koniec){
    typ pierwszy=tabl[poczatek];
    int j=2*poczatek;
    while( j<=koniec ){
        if(j<koniec && tabl[j+1] > tabl[j])
            j++;
        if(pierwszy>=tabl[j])
            break;
        //w domysle warunek (pierwszy<tabl[j])
        tabl[j/2]=tabl[j];
        j=2*j;
    }
    tabl[j/2]=pierwszy;
}

template<typename typ>
void heapsort(vector<typ>& tabl, int poczatek, int koniec){
    typ tmp;
    koniec++;
    for(int i=(koniec-1)/2;i>=poczatek;i--){
        makeheap(tabl,i,koniec-1);
    }
    for(int j=koniec-1;j>poczatek;j--){
        tmp=tabl[j];
        tabl[j]=tabl[poczatek];
        tabl[poczatek]=tmp;
        makeheap(tabl,poczatek,j-1);
    }
}

//Nie dziele funkcji quicksort na czesci z ktorych moglbym korzystac tutaj, zeby nie tworzyc dodatkowego vectora
template<typename typ>
void introsort(vector<typ>& tabl, int poczatek, int koniec){
    int M;
    M=2*log(koniec-poczatek+1);
    if(M>0){
        int srodek = (poczatek+koniec)/2;
        if(tabl.size()>1){
            int p,l;
            typ pivot = tabl[srodek];
            p=koniec;
            l=poczatek;
            while(l<=p){
                while( !(tabl[p]<=pivot||p<=poczatek) ){
                    p--;
                }
                while( !(tabl[l]>=pivot||l>=koniec) ){
                    l++;
                }

                if(l<=p){
                    typ tmp=tabl[p];
                    tabl[p]=tabl[l];
                    tabl[l]=tmp;
                    p--;
                    l++;

                }
            }

            if(poczatek<p)
                introsort(tabl,poczatek,p);
            if(l<koniec)
                introsort(tabl,l,koniec);
        }
    }
    else{
        heapsort(tabl,0,tabl.size()-1);
    }
}

template<typename typ>
float testujAlgorytm(vector<typ>& tabl, string typSortowania){
    float czasWykonaniaAlgorytmu=0;
    switch(typSortowania[0]){//nie ma instrukcji wejscia, wiec nie sprawdzam czy jest pusty
    case 'm':{
        DWORD start = GetTickCount();
        mergesort(tabl,0,tabl.size()-1);
        DWORD koniec = GetTickCount();
        czasWykonaniaAlgorytmu=koniec-start;
        break;}
    case 'q':{
        DWORD start = GetTickCount();
        quicksort(tabl,0,tabl.size()-1);
        DWORD koniec = GetTickCount();
        czasWykonaniaAlgorytmu=koniec-start;
        break;}
    case 'i':{
        DWORD start = GetTickCount();
        introsort(tabl,0,tabl.size()-1);
        DWORD koniec = GetTickCount();
        czasWykonaniaAlgorytmu=koniec-start;
        break;}
    case 'h':{
        DWORD start = GetTickCount();
        heapsort(tabl,0,tabl.size()-1);
        DWORD koniec = GetTickCount();
        czasWykonaniaAlgorytmu=koniec-start;
        break;}
    }
    return czasWykonaniaAlgorytmu;
}

template<typename typ>
void sortujCzeciowo(vector<typ>& tabl, float procentPosortowania){
    int koniec=(tabl.size()-1)*0.01*procentPosortowania;
    quicksort(tabl,0,koniec);
}

template<typename typ>
void sortujOdwrotnie(vector<typ>& tabl){
    int koniec=tabl.size()-1;
    quicksort(tabl,0,koniec);
    typ tmp;
    for(int l=0;l<koniec/2;l++){
       tmp=tabl[l];
       tabl[l]=tabl[koniec-l];
       tabl[koniec-l]=tmp;
    }
}

template<typename typ, int rozmiar>
void testujLosowaIZapiszCzasDoPliku(string algorytm,ofstream& plik){
    plik<<"Testowany algorytm: "<<algorytm<<endl;
    plik<<"Rozmiar tablicy: "<<rozmiar<<endl;
    cout<<"Testowany algorytm: "<<algorytm<<endl;
    cout<<"Rozmiar tablicy: "<<rozmiar<<endl;
    long long int suma=0;
    int dzielnik = 100;
    for(int i=1;i<=100;i++){

        vector<typ> tablica = generujTablice<typ,rozmiar>();
        float czas=testujAlgorytm(tablica,algorytm);

        if(i<10)
            cout<<i<<".   ";
        else if(i==100)
            cout<<i<<". ";
        else
            cout<<i<<".  ";

        if(sprawdz(tablica)==1){
            cout<<"Czas: "<<czas<<" ms"<<endl;
            plik<<czas<<",";
            suma+=czas;
        }
        else{
            plik<<endl<<"Blad sortowania"<<endl;
            dzielnik--;
        }
    }
    float srednia=suma/dzielnik;
    plik<<endl<<"Sredni czas: "<<srednia<<" ms"<<endl;
}

template<typename typ, int rozmiar>
void testujCzesciowoPosortowanaIZapiszCzasDoPliku(string algorytm,ofstream& plik,int procentPosortowania){
    plik<<"Testowany algorytm: "<<algorytm<<endl;
    plik<<"Rozmiar tablicy: "<<rozmiar<<endl;
    cout<<"Testowany algorytm: "<<algorytm<<endl;
    cout<<"Rozmiar tablicy: "<<rozmiar<<endl;
    long long int suma=0;
    int dzielnik = 100;
    for(int i=1;i<=100;i++){

        vector<typ> tablica = generujTablice<typ,rozmiar>();
        sortujCzeciowo(tablica,procentPosortowania);
        float czas=testujAlgorytm(tablica,algorytm);

        if(i<10)
            cout<<i<<".   ";
        else if(i==100)
            cout<<i<<". ";
        else
            cout<<i<<".  ";

        if(sprawdz(tablica)==1){
            cout<<"Czas: "<<czas<<" ms"<<endl;
            plik<<czas<<",";
            suma+=czas;
        }
        else{
            plik<<endl<<"Blad sortowania"<<endl;
            dzielnik--;
        }
    }
    float srednia=suma/dzielnik;
    plik<<endl<<"Sredni czas: "<<srednia<<" ms"<<endl;
}

template<typename typ, int rozmiar>
void testujOdwrotniePosortowanaIZapiszCzasDoPliku(string algorytm,ofstream& plik){
    plik<<"Testowany algorytm: "<<algorytm<<endl;
    plik<<"Rozmiar tablicy: "<<rozmiar<<endl;
    cout<<"Testowany algorytm: "<<algorytm<<endl;
    cout<<"Rozmiar tablicy: "<<rozmiar<<endl;
    long long int suma=0;
    int dzielnik = 100;
    for(int i=1;i<=100;i++){
        vector<typ> tablica = generujTablice<typ,rozmiar>();
        sortujOdwrotnie(tablica);
        float czas=testujAlgorytm(tablica,algorytm);

        if(i<10)
            cout<<i<<".   ";
        else if(i==100)
            cout<<i<<". ";
        else
            cout<<i<<".  ";

        if(sprawdz(tablica)==1){
            cout<<"Czas: "<<czas<<" ms"<<endl;
            plik<<czas<<",";
            suma+=czas;
        }
        else{
            plik<<endl<<"Blad sortowania"<<endl;
            dzielnik--;
        }
    }
    float srednia=suma/dzielnik;
    plik<<endl<<"Sredni czas: "<<srednia<<" ms"<<endl;
}

template<typename typ>
void przeprowadzEksperyment(ofstream& plik){

    plik<<"Start eksperymentu: "<<endl;

    plik<<endl<<"Sortowanie losowych tablic"<<endl<<endl;

    testujLosowaIZapiszCzasDoPliku<typ,10000>("mergesort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,10000>("quicksort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,10000>("introsort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,50000>("mergesort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,50000>("quicksort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,50000>("introsort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,100000>("mergesort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,100000>("quicksort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,100000>("introsort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,500000>("mergesort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,500000>("quicksort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,500000>("introsort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik);
    testujLosowaIZapiszCzasDoPliku<typ,1000000>("introsort",plik);

    plik<<endl<<"Sortowanie odwrotnie posortowanych tablic"<<endl<<endl;

    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,10000>("mergesort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,10000>("quicksort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,10000>("introsort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,50000>("mergesort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,50000>("quicksort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,50000>("introsort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,100000>("mergesort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,100000>("quicksort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,100000>("introsort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,500000>("mergesort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,500000>("quicksort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,500000>("introsort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik);
    testujOdwrotniePosortowanaIZapiszCzasDoPliku<typ,1000000>("introsort",plik);

    plik<<endl<<"Sortowanie tablicy, gdzie 25 procent elementow jest juz posortowane"<<endl<<endl;

    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("mergesort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("quicksort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("introsort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("mergesort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("quicksort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("introsort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("mergesort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("quicksort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("introsort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("mergesort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("quicksort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("introsort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik,25);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("introsort",plik,25);

    plik<<endl<<"Sortowanie tablicy, gdzie 50 procent elementow jest juz posortowane"<<endl<<endl;

    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("mergesort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("quicksort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("introsort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("mergesort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("quicksort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("introsort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("mergesort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("quicksort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("introsort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("mergesort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("quicksort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("introsort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik,50);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("introsort",plik,50);

    plik<<endl<<"Sortowanie tablicy, gdzie 75 procent elementow jest juz posortowane"<<endl<<endl;

    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("mergesort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("quicksort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("introsort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("mergesort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("quicksort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("introsort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("mergesort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("quicksort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("introsort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("mergesort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("quicksort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("introsort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik,75);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("introsort",plik,75);

    plik<<endl<<"Sortowanie tablicy, gdzie 95 procent elementow jest juz posortowane"<<endl<<endl;

    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("mergesort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("quicksort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("introsort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("mergesort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("quicksort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("introsort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("mergesort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("quicksort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("introsort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("mergesort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("quicksort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("introsort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik,95);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("introsort",plik,95);

    plik<<endl<<"Sortowanie tablicy, gdzie 99 procent elementow jest juz posortowane"<<endl<<endl;

    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("mergesort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("quicksort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("introsort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("mergesort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("quicksort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("introsort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("mergesort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("quicksort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("introsort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("mergesort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("quicksort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("introsort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik,99);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("introsort",plik,99);

    plik<<endl<<"Sortowanie tablicy, gdzie 99.7 procent elementow jest juz posortowane"<<endl<<endl;

    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("mergesort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("quicksort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,10000>("introsort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("mergesort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("quicksort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,50000>("introsort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("mergesort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("quicksort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,100000>("introsort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("mergesort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("quicksort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,500000>("introsort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("mergesort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("quicksort",plik,99.7);
    testujCzesciowoPosortowanaIZapiszCzasDoPliku<typ,1000000>("introsort",plik,99.7);

}

int main()
{
    srand(time(NULL));
    ofstream plik;
    plik.open("WynikEksperymetu.txt");
    przeprowadzEksperyment<int>(plik);
    plik.close();
}
