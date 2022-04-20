#include "rotkvica.hpp"

rotkvica::rotkvica(float x,float y,mole* krtica){
    
    m_krtica = krtica;
    poz_x=x;
    poz_z=y;
    poz_y=0.5;
    m_preostalo_koraka=3;
       
}

void rotkvica::uvuci(bool pecurka_pokrenut){
        
    if(poklapaju_se_koordinate() && !pojedena() && !m_krtica->provera_otkljucano()){
        
        //U slucaju da je pojedena pecurka krtica 
        //moze da uvuce celo povrce odjednom
        if(pecurka_pokrenut){
            
            poz_y-=0.03*m_preostalo_koraka;
            m_preostalo_koraka=0;
            
        }
        //Inace uvlaci rotkvicu korak po korak
        else{
            poz_y-=0.02;
            m_preostalo_koraka--;
        }
        
        //Ako je rotkvica pojedena uvecava se broj poena
        if(m_preostalo_koraka==0)
            m_krtica->uvecaj_poene(3);
        
    }
}

bool rotkvica::poklapaju_se_koordinate() const {
        
    return (m_krtica->x() >(poz_x-granica) && m_krtica->x() <(poz_x+granica)) &&
        (m_krtica->z() >(poz_z-granica) && m_krtica->z() <(poz_z+granica));
        
}

bool rotkvica::pojedena() const {
        
    return poz_y<=0.45;
        
}

bool rotkvica::trenutno_zakljucana() const {
        
    return poklapaju_se_koordinate() && !m_krtica->provera_otkljucano() && m_preostalo_koraka<3;
    
}

std::pair<float,float> rotkvica::get_koordinate() const {
        
    return std::make_pair(poz_x,poz_z);
        
}

int rotkvica::preostalo_koraka() const {
        return m_preostalo_koraka;
}

float rotkvica::x() const {
        return poz_x;
}

float rotkvica::y() const {
        return poz_y;
}

float rotkvica::z() const {
        return poz_z;
}