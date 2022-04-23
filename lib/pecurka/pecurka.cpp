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

auto pecurka::uvuci() -> bool{
    
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

auto pecurka::poklapaju_se_koordinate() const -> bool {
    
    return (m_krtica->x() >(poz_x-granica) && m_krtica->x() <(poz_x+granica)) &&
        (m_krtica->z() >(poz_z-granica) && m_krtica->z() <(poz_z+granica));
        
}

auto pecurka::pojedena() const -> bool {
        
    return poz_y<=0.35;
    
}

auto pecurka::trenutno_zakljucana() const -> bool {
    
    return poklapaju_se_koordinate() && !m_krtica->provera_otkljucano() && m_preostalo_koraka<6;
    
}

auto pecurka::preostalo_koraka() const -> int {

    return m_preostalo_koraka;

}

auto pecurka::x() const -> float {
        return poz_x;
    }

auto pecurka::y() const -> float {
    return poz_y;
}

auto pecurka::z() const -> float {
    return poz_z;
}

auto pecurka::get_koordinate() const -> std::pair<float,float> {
        
    return std::make_pair(poz_x,poz_z);
        
}