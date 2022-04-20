#ifndef __COVECULJAK__
#define __COVECULJAK__

#include <GL/glut.h>
#include <cmath>
#include <time.h>
#include <vector>
#include <utility>

#include "mole.hpp"
#include "sargarepa.hpp"
#include "rotkvica.hpp"
#include "pecurka.hpp"

//fale makroi


class coveculjak{

private:
    //Koordinate seljaka
    float m_pox,m_poz;
    //Granicne koordinate do kojih moze da se krece
    //i na x i na z osi
    float m_granica_plus, m_granica_minus;
    //Promenljive za tajmere koji sluze
    //za kretanje seljaka i pomeranje ruku/nogu
    int m_timer_noga=0;
    int m_timer_pokrenut=1;
    double m_timer_vrednost=0;

    //Indikator koji sluzi da promeni znak
    //parametra tajmer (tajmer_vrednost)
    int m_ind1=0;
public:

    coveculjak(float a,float b,float c,float d);

    int timer_noga() const;
    void inc_timer_noga(int inc);

    int timer_pokrenut() const;

    double timer_vrednost() const;
    void inc_timer_vrednost(double inc);
    
    int ind1() const;
    
    //Iscrtavamo glavu(sfera)
    void glava(int pecurka_pokrenut, int pecurka_parametar);
    //Iscrtavamo torzo
    void torzo(int pecurka_pokrenut, int pecurka_parametar);
    
    //Iscrtavamo levu nogu
    void leva_noga(int pecurka_pokrenut, int pecurka_parametar);
    //Iscrtavamo desnu nogu
    void desna_noga(int pecurka_pokrenut, int pecurka_parametar);
    //Iscrtavamo desnu ruku
    void desna_ruka(int pecurka_pokrenut, int pecurka_parametar);
    
    //Iscrtavamo levu ruku
    void leva_ruka(int pecurka_pokrenut, int pecurka_parametar);
    
    //Ugao za koji se coveculjak rotira
    int ugao=0;
    
    //Iscrtavamo kompletnog coveculjka
    void iscrtaj(int pecurka_pokrenut, int pecurka_parametar);
    
    // Iscrtavamo kvadrat oko coveculjka u kom on
    // moze da registruje da krtica uvlaci povrce
    void oblast();
    
    
    //Vrsimo proveru da li krtica uvlaci neko povrce koje se nalazi 
    //u okviru oblasti koja se iscrtava oko coveculjka
    bool uhvatio_krticu(const std::vector<sargarepa>& sargarepice,
                        const std::vector<rotkvica>& rotkvice,
                        const pecurka& magicna_pecurka);
    
    //Iscrtavamo coveculjka na poziciji njegovih koordinata
    void iscrtaj_na_poziciji(int pecurka_pokrenut, int pecurka_parametar);
    
    //Metod koji pokrece coveculjka
    // i u svakom koraku proverava da li je
    //u oblasti krtica koja trenutno uvlaci povrce
    bool hodaj( bool smer, 
                int pecurka_pokrenut, 
                int pecurka_parametar, 
                bool igra_zavrsena,
                const std::vector<sargarepa>& sargarepice,
                const std::vector<rotkvica>& rotkvice,
                const pecurka& magicna_pecurka);
    
    //Zaustavljamo tajmere
    void stani();
    void kreni();
    
    //Indikator koji oznacava kuda se krece coveculjak
    //ako se krece gore-dole onda je true, false znaci levo-desno
    bool smer=true;

    bool kretanje(int pecurka_pokrenut, int pecurka_parametar, bool igra_zavrsena, 
                const std::vector<sargarepa>& sargarepice,
                const std::vector<rotkvica>& rotkvice,
                const pecurka& magicna_pecurka);

};

#endif