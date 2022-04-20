#include "pecurka.hpp"

pecurka::pecurka(mole* krtica) {
    m_krtica = krtica;

    // Nasumicno biramo poziciju pecurke
    // Ona se uvek nalazi u centralnom delu
    // Tako da je ili u samom centru i moze se pojesti bez 
    // mogucnosti da nas seljak uhvati
    // Ili je na nekoj od ivica i postoji mogucnost da nas uhvati 
    srand(time(NULL));
    int a=5.0*(rand()/(float)RAND_MAX);
    
    if(a<=1.0){
        poz_x=0.25;
        poz_z=0;
    }
    
    else if(a<=2.0){
        poz_x=-0.25;
        poz_z=0;
    }
    
    else if(a<=3.0){
        poz_x=0;
        poz_z=0.25;
    }
    
    else if(a<=4.0){
        poz_x=0;
        poz_z=-0.25;
    }
    
    else if(a<=5.0){
        poz_x=0;
        poz_z=0;
    }
    
    poz_y=0.5;
    m_preostalo_koraka=6;
       
}

bool pecurka::uvuci(){
    
    if(poklapaju_se_koordinate() && !pojedena() && !m_krtica->provera_otkljucano()){
        
        poz_y-=0.025;
        m_preostalo_koraka--;
        
        //Ako je pecurka uvucena pokrecemo 
        //timer_pecurka koji pokrece efekat delovanja pecurke na krticu
        //Ukoliko je pecurka dobra, krtica postaje brza i povrce moze 
        //da uvuce u jednom potezu inace ne moze da se pomeri sve dok traje efekat
        if(m_preostalo_koraka==0) {
            //Povecava se broj osvojenih poena
            m_krtica->uvecaj_poene(10);
        }
        return true;
    }
    return false;
}

bool pecurka::poklapaju_se_koordinate() const {
    
    return (m_krtica->x() >(poz_x-granica) && m_krtica->x() <(poz_x+granica)) &&
        (m_krtica->z() >(poz_z-granica) && m_krtica->z() <(poz_z+granica));
        
}

bool pecurka::pojedena() const {
        
    return poz_y<=0.35;
    
}

bool pecurka::trenutno_zakljucana() const {
    
    return poklapaju_se_koordinate() && !m_krtica->provera_otkljucano() && m_preostalo_koraka<6;
    
}

int pecurka::preostalo_koraka() const {

    return m_preostalo_koraka;

}

float pecurka::x() const {
        return poz_x;
    }

float pecurka::y() const {
    return poz_y;
}

float pecurka::z() const {
    return poz_z;
}

std::pair<float,float> pecurka::get_koordinate() const {
        
    return std::make_pair(poz_x,poz_z);
        
}