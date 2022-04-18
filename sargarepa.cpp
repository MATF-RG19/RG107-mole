
#include "sargarepa.hpp"

sargarepa::sargarepa(float x,float y, mole* krtica) {
    
        m_krtica = krtica;
        poz_x=x;
        poz_z=y;
        poz_y=0.6;
        m_preostalo_koraka=4;
}

void sargarepa::uvuci(bool pecurka_pokrenut) {
        
        if(poklapaju_se_koordinate() && !pojedena() && !m_krtica->provera_otkljucano()){
                
                //U slucaju da je pojedena pecurka krtica 
                //moze da uvuce celo povrce odjednom
                if(pecurka_pokrenut){
                
                poz_y-=0.03*m_preostalo_koraka;
                m_preostalo_koraka=0;
                
                }
                //Inace uvlaci sargarepu deo po deo
                else{
                poz_y-=0.03;
                m_preostalo_koraka--;
                }
                
                //Ako je sargarepa skroz uvucena, povecava se broj poena
                if(m_preostalo_koraka==0)
                m_krtica->uvecaj_poene(4);
                
        }
}
bool sargarepa::poklapaju_se_koordinate() const {
        
        return (m_krtica->x() >(poz_x-granica) && m_krtica->x() <(poz_x+granica)) &&
            (m_krtica->z() >(poz_z-granica) && m_krtica->z() <(poz_z+granica));
    
}

bool sargarepa::pojedena() const {
        
        return poz_y<=0.5;
        
}

bool sargarepa::trenutno_zakljucana() const {
        
        return poklapaju_se_koordinate() && !m_krtica->provera_otkljucano() && m_preostalo_koraka<4;
        
}

std::pair<float,float> sargarepa::get_koordinate() const {
        
        return std::make_pair(poz_x,poz_z);
        
}

int sargarepa::preostalo_koraka() const {
        return m_preostalo_koraka;
}

float sargarepa::x() const {
        return poz_x;
}

float sargarepa::y() const {
        return poz_y;
}

float sargarepa::z() const {
        return poz_z;
}