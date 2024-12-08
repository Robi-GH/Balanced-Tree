#ifndef BALANSIRANOSTABLO_H
#define BALANSIRANOSTABLO_H
#include <utility>
#include <vector>
using namespace std;

template <typename Tip>
class BalansiranoStablo {
public:
    struct Cvor {
        Tip element;
        int broj_elemenata_l, broj_elemenata_d;
        Cvor *ld, *dd, *rod;
        Cvor(Tip el, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr):element(el), rod(rod), ld(ld), dd(dd) {
            broj_elemenata_d=0;
            broj_elemenata_l=0;
        }
    };
private:
    int n;
    Cvor *korijen;
    int VisinaCvora(Cvor*) const;
    int Visina(Cvor*) const;
    void Ispis(Cvor*) const;
    void InOrder(Cvor*) const;
    Cvor* SljedbenikZaBalansiranje(Cvor*) const;
    void EraseZaBalansiranje(const Tip);
    void InsertBalansirano(const Tip);
    bool DaLiJeBalansirano(Cvor*, int=0, int=0)const;
    bool DaLiJeVisinaMin3(Cvor*,int, int=-1)const;
    void PromjenaBrojaElemenata(Cvor*);
    void Balansiraj(Cvor*);
    void BalansirajRekurzivno(int, int, vector<Tip>&);
    void InOrderCvora(Cvor*, vector<Tip>&);
    void ProvjeraZaBalansiranjeKodBrisanja(const Tip);
    void BrisanjeStabla(Cvor* cvor) {
        if (cvor == nullptr) return;
            BrisanjeStabla(cvor->ld);
            delete cvor;
            BrisanjeStabla(cvor->dd);
    }
    Cvor* KopiranjeStabla(Cvor *, Cvor* roditelj);
public:
    BalansiranoStablo():n(0),korijen(nullptr) {}
    int Size() {return n;}
    bool Empty() { return n == 0; }
    pair<Cvor*, bool> Insert(const Tip);
    Cvor* Find(const Tip)const;
    void Erase(const Tip);
    Cvor* Sljedbenik(Cvor*) const;
    void Ispis() const { Ispis(korijen); }
    void InOrder() const { InOrder(korijen); }
    int Visina() const { return Visina(korijen); }
    Cvor* Pocetak() const;
    BalansiranoStablo(const BalansiranoStablo& kopija){korijen = KopiranjeStabla(kopija.korijen, nullptr);}
    BalansiranoStablo(BalansiranoStablo &&kopija){
        korijen = kopija.korijen;
        kopija.korijen = nullptr;
    }
    ~BalansiranoStablo(){BrisanjeStabla(korijen);}
    BalansiranoStablo& operator=(const BalansiranoStablo& stablo){
        if(this != &stablo){
            BrisanjeStabla(korijen);
            korijen = KopiranjeStabla(stablo.korijen,nullptr);
        }
        return *this;
    }
    BalansiranoStablo& operator=(BalansiranoStablo &&stablo){
        if(this != &stablo){
            BrisanjeStabla(korijen);
            korijen = stablo.korijen;
            stablo.korijen = nullptr;
        }
        return *this;
    }
};

#include "BalansiranoStablo.cpp"

#endif // BALANSIRANOSTABLO_H

