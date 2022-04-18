#ifndef __ROTKVICA__
#define __ROTKVICA__

#include "mole.hpp"
#include <utility>

class rotkvica{
    
   private:
       //Koordinate pozicije sargarepe
        float poz_x,poz_y,poz_z;
        //Broj koraka preostalih za potpuno uvlacenje 
        //sargarepe u zemlju
        int m_preostalo_koraka;

    public:
    mole* m_krtica = new mole(0,0);
    rotkvica(float x,float y, mole* m_krtica);
    
    //Metod za uvlacenje rotkvice, pokrece se iz
    //on_keyboard funkcije, pritiskom na taster 'u',
    //ali tek nakon sto se krtica zakaci za rotkvicu
    //pritiskom na taster 'i'
    void uvuci(bool pecurka_pokrenut);
    
    float granica=0.1;
    //Funkcija koja proverava da li je krtica ispod ili dovoljno blizu rotkvice
    //da moze da se uhvati i da je uvuce
    bool poklapaju_se_koordinate() const;
    bool pojedena() const;
    bool trenutno_zakljucana() const;
   
    int preostalo_koraka() const;
    float x() const;
    float y() const;
    float z() const;

    std::pair<float,float> get_koordinate() const;
    
};

#endif