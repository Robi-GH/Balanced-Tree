#ifndef BALANSIRANOSTABLO_CPP
#define BALANSIRANOSTABLO_CPP
#include "BalansiranoStablo.h"
#include <iostream>
#include <vector>

using namespace std;

template <typename Tip>
pair<typename BalansiranoStablo<Tip>::Cvor*, bool> BalansiranoStablo<Tip>::Insert(const Tip vrijednost){
    bool uslov = false;
    Cvor *trenutni = korijen, *prethodni = nullptr, *pomocnitrenutni=nullptr;
    if(this->Find(vrijednost) != nullptr) return {trenutni, false};
    while(trenutni != nullptr){
        if(vrijednost < trenutni->element){
            if(!uslov  && !DaLiJeBalansirano(trenutni, 1,0) && DaLiJeVisinaMin3(trenutni, vrijednost, 0)){
                pomocnitrenutni = trenutni;
                uslov = true;
            }
        }
        else{
            if(!uslov  && !DaLiJeBalansirano(trenutni,0, 1) && DaLiJeVisinaMin3(trenutni, vrijednost, 1)){
                pomocnitrenutni = trenutni;
                uslov = true;
            }
        }
        prethodni = trenutni;
        if(vrijednost < trenutni->element){
            trenutni->broj_elemenata_l++;
            trenutni = trenutni->ld;

        }
        else{
            trenutni->broj_elemenata_d++;
            trenutni = trenutni->dd;
        }
    }
    Cvor *novi = new Cvor(vrijednost, prethodni);
    if(korijen == nullptr){
        korijen = novi;
    }
    else{
        if(prethodni ->element < novi->element){
            prethodni->dd = novi;
        }
        else{
            prethodni->ld = novi;
        }
    }
    if(uslov){
        Balansiraj(pomocnitrenutni);
    }
    n++;
    return {novi, true};
}

template <typename Tip>
typename BalansiranoStablo<Tip>::Cvor* BalansiranoStablo<Tip>::Find(const Tip vrijednost) const{
    Cvor *trenutni = korijen;
    while(trenutni != nullptr){
        if(trenutni->element == vrijednost) return trenutni;
        if(vrijednost < trenutni->element) trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }
    return nullptr;
}

template <typename Tip>
bool BalansiranoStablo<Tip>::DaLiJeVisinaMin3(Cvor *cvor,int el,int lijevoILIdesno)const{
    if(lijevoILIdesno==1){
        if(cvor->broj_elemenata_d >=3) return true;
        else if(cvor -> broj_elemenata_d <= 1) return false;
        else{
            if(cvor -> dd != nullptr && cvor -> dd -> element < el && cvor -> dd -> dd == nullptr) return false;
            else if(cvor -> dd != nullptr && cvor -> dd -> element > el && cvor -> dd -> ld == nullptr) return false;
            else return true;
        }
    }
    else if(lijevoILIdesno==0){
        if(cvor->broj_elemenata_l >=3) return true;
        else if(cvor -> broj_elemenata_l <= 1) return false;
        else{
            if(cvor -> ld !=nullptr && cvor -> ld -> element < el && cvor -> ld -> dd == nullptr) return false;
            else if(cvor -> ld != nullptr && cvor -> ld -> element > el && cvor -> ld -> ld == nullptr) return false;
            else return true;
        }
    }
    else{
        return VisinaCvora(cvor)>=3;
    }
    return false;
}

template <typename Tip>
bool BalansiranoStablo<Tip>::DaLiJeBalansirano(Cvor *cvor, int a, int b) const{
    if(2*((cvor->broj_elemenata_d)+b) <=(cvor->broj_elemenata_l)+a || 2*((cvor->broj_elemenata_l)+a) <=(cvor->broj_elemenata_d)+b) return false;
    return true;
}

template <typename Tip>
void BalansiranoStablo<Tip>::Balansiraj(Cvor *trenutni){
    vector<Tip> v;
    InOrderCvora(trenutni, v);
    for(auto element : v){
        EraseZaBalansiranje(element);
    }
    BalansirajRekurzivno(-1,v.size(), v);
}

template <typename Tip>
void BalansiranoStablo<Tip>::InOrderCvora(Cvor *cvor, vector<Tip>& v){
    if(cvor == nullptr) return;
    InOrderCvora(cvor->ld, v);
    v.push_back(cvor->element);
    InOrderCvora(cvor->dd, v);
}

template <typename Tip>
void BalansiranoStablo<Tip>::InOrder(Cvor* cvor) const{
    if(cvor == nullptr) return;
    InOrder(cvor->ld);
    cout<<cvor->element<<" ";
    InOrder(cvor->dd);
}

template <typename Tip>
void BalansiranoStablo<Tip>::EraseZaBalansiranje(const Tip vrijednost){
    Cvor* cvor = Find(vrijednost);
    if(cvor == nullptr) return;
    else{
        PromjenaBrojaElemenata(cvor);
    }
    if(cvor->ld == nullptr && cvor->dd == nullptr){   //ako je list
        if(cvor->rod == nullptr) korijen = nullptr;   //ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = nullptr;
            else cvor->rod->dd = nullptr;
        }
    }
    else if(cvor->ld == nullptr){                    //ako nema lijevo dijete
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) korijen = cvor->dd; //ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }
    else if(cvor->dd == nullptr){                   //ako nema desno dijete
        cvor->ld->rod = cvor->rod;
        if(cvor->rod == nullptr) korijen = cvor->ld;//ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = cvor->ld;
            else cvor->rod->dd = cvor->ld;
        }
    }
    else{                                           //ako ima oba djeteta
        Cvor* sljedbenik = SljedbenikZaBalansiranje(cvor);
        sljedbenik->ld = cvor->ld;
        cvor->ld->rod = sljedbenik;
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) korijen = cvor->dd;//ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }
    delete cvor;
    n--;
}

template <typename Tip>
void BalansiranoStablo<Tip>::PromjenaBrojaElemenata(Cvor *cvor){
    if(cvor == korijen)return;
    Cvor *trenutni = korijen;
    while(trenutni != cvor){
        if(cvor->element < trenutni->element){
            trenutni->broj_elemenata_l--;
            trenutni = trenutni->ld;
        }
        else{
            trenutni->broj_elemenata_d--;
            trenutni = trenutni->dd;
        }
    }
}

template <typename Tip>
void BalansiranoStablo<Tip>::BalansirajRekurzivno(int pocetak, int kraj, vector<Tip>& v){
    if (kraj-pocetak<=1) return;
    int sredina = (pocetak + kraj)/2;
    this->InsertBalansirano(v[sredina]);
    BalansirajRekurzivno(pocetak, sredina,v);
    BalansirajRekurzivno(sredina, kraj,v);
}

template <typename Tip>
void BalansiranoStablo<Tip>::InsertBalansirano(const Tip vrijednost){
    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr){
        prethodni = trenutni;
        if(vrijednost < trenutni->element){
            trenutni->broj_elemenata_l++;
            trenutni = trenutni->ld;
        }
        else{
            trenutni->broj_elemenata_d++;
            trenutni = trenutni->dd;
        }
    }
    Cvor *novi = new Cvor(vrijednost, prethodni);
    if(korijen == nullptr){
        korijen = novi;
    }
    else{
        if(prethodni ->element < novi->element){
            prethodni->dd = novi;
        }
        else{
            prethodni->ld = novi;
        }
    }
    n++;
}

template <typename Tip>
typename BalansiranoStablo<Tip>::Cvor* BalansiranoStablo<Tip>::SljedbenikZaBalansiranje(BalansiranoStablo<Tip>::Cvor* cvor) const{
    if(cvor->dd != nullptr){
        Cvor *trenutni = cvor->dd;
        while(trenutni->ld != nullptr){
            trenutni->broj_elemenata_l+=cvor->broj_elemenata_l;
            trenutni = trenutni->ld;
        }
        trenutni->broj_elemenata_l=cvor->broj_elemenata_l;
        return trenutni;
    }
    Cvor* trenutni = cvor;
    while(trenutni->rod != nullptr){
        if(trenutni->rod->ld == trenutni) return trenutni->rod;
        if(trenutni->rod->dd == trenutni) trenutni = trenutni->rod;
    }
    return nullptr;
}

template <typename Tip>
int BalansiranoStablo<Tip>::VisinaCvora(Cvor* cvor) const{
    if(cvor == nullptr) return -1;
    return max(VisinaCvora(cvor->ld), VisinaCvora(cvor->dd)) + 1;
}

template <typename Tip>
typename BalansiranoStablo<Tip>::Cvor* BalansiranoStablo<Tip>::Sljedbenik(BalansiranoStablo<Tip>::Cvor* cvor) const{
    if(cvor->dd != nullptr){
        Cvor *trenutni = cvor->dd;
        while(trenutni->ld != nullptr){
            trenutni = trenutni->ld;
        }
        return trenutni;
    }
    Cvor* trenutni = cvor;
    while(trenutni->rod != nullptr){
        if(trenutni->rod->ld == trenutni) return trenutni->rod;
        if(trenutni->rod->dd == trenutni) trenutni = trenutni->rod;
    }
    return nullptr;
}

template <typename Tip>
void BalansiranoStablo<Tip>::Erase(const Tip vrijednost){
    Cvor* cvor = Find(vrijednost);
    if(cvor == nullptr) return;
    else{
        PromjenaBrojaElemenata(cvor);
    }
    if(cvor->ld == nullptr && cvor->dd == nullptr){   //ako je list
        if(cvor->rod == nullptr) korijen = nullptr;   //ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = nullptr;
            else cvor->rod->dd = nullptr;
        }
    }
    else if(cvor->ld == nullptr){                    //ako nema lijevo dijete
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) korijen = cvor->dd; //ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }
    else if(cvor->dd == nullptr){                   //ako nema desno dijete
        cvor->ld->rod = cvor->rod;
        if(cvor->rod == nullptr) korijen = cvor->ld;//ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = cvor->ld;
            else cvor->rod->dd = cvor->ld;
        }
    }
    else{                                           //ako ima oba djeteta
        Cvor* sljedbenik = SljedbenikZaBalansiranje(cvor);
        sljedbenik->ld = cvor->ld;
        cvor->ld->rod = sljedbenik;
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) korijen = cvor->dd;//ako je korijen
        else{
            if(cvor->rod->ld == cvor) cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }
    int el = cvor ->element;
    delete cvor;
    n--;
    ProvjeraZaBalansiranjeKodBrisanja(el);
}

template <typename Tip>
void BalansiranoStablo<Tip>::ProvjeraZaBalansiranjeKodBrisanja(const Tip el){
    Cvor *trenutni = korijen;
    while (trenutni != nullptr){
       if( DaLiJeVisinaMin3(trenutni, el) && !DaLiJeBalansirano(trenutni)){
            Balansiraj(trenutni);
            break;
        }
        if(trenutni->element < el) trenutni = trenutni->dd;
        else trenutni = trenutni->ld;
    }
}

template <typename Tip>
void BalansiranoStablo<Tip>::Ispis(Cvor* cvor) const{
    if(cvor==nullptr){
        cout << "Prazno stablo!" << endl;
        return;
    }
    cout<<"Vrijednost: " << cvor->element << ", broj lijevih elemenata: " << cvor->broj_elemenata_l << ", broj desnih elemenata: " <<  cvor->broj_elemenata_d;
    if(cvor->ld != nullptr) cout<<", Lijevo dijete: " << cvor->ld->element;
    if(cvor->dd != nullptr) cout<<", Desno dijete: " << cvor->dd->element;
    cout<<endl;
    if(cvor->ld != nullptr) Ispis(cvor->ld);
    if(cvor->dd != nullptr) Ispis(cvor->dd);
}

template <typename Tip>
int BalansiranoStablo<Tip>::Visina(Cvor* cvor) const{
    if(cvor == nullptr) return -1;
    return max(Visina(cvor->ld), Visina(cvor->dd)) + 1;

}

template <typename Tip>
typename BalansiranoStablo<Tip>::Cvor* BalansiranoStablo<Tip>::Pocetak() const{
    if(korijen == nullptr) return korijen;
    Cvor *trenutni = korijen;
    while(trenutni->ld != nullptr) trenutni = trenutni->ld;
    return trenutni;
}

template <typename Tip>
typename BalansiranoStablo<Tip>::Cvor* BalansiranoStablo<Tip>::KopiranjeStabla(Cvor* cvor, Cvor* roditelj){
    if(cvor == nullptr) return nullptr;
    Cvor* novi = new Cvor(cvor->element);
    novi->rod=roditelj;
    novi -> ld= KopiranjeStabla(cvor->ld, novi);
    novi->broj_elemenata_d=cvor->broj_elemenata_d;
    novi->broj_elemenata_l=cvor->broj_elemenata_l;
    novi -> dd= KopiranjeStabla(cvor->dd, novi);
    return novi;
}



#endif // BALANSIRANOBSTABLO_CPP
