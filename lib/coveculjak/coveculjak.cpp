#include "coveculjak.hpp"

coveculjak::coveculjak(float a,float b,float c,float d){
        
    m_pox=a;
    m_poz=b;
    
    m_granica_minus=c;
    m_granica_plus=d;
    
}

int coveculjak::timer_noga() const {
    return m_timer_noga;
}

void coveculjak::inc_timer_noga(int inc) {
    m_timer_noga += inc;
}

int coveculjak::timer_pokrenut() const {
    return m_timer_pokrenut;
}

double coveculjak::timer_vrednost() const {
    return m_timer_vrednost;
}

void coveculjak::inc_timer_vrednost(double inc) {
    m_timer_vrednost += inc;
}

int coveculjak::ind1() const {
    return m_ind1;
}

void coveculjak::glava(int pecurka_pokrenut, int pecurka_parametar){
        
    glPushMatrix();
        glColor3f(0.2,0.2,0.2);
        
        //Funkcija koja se javlja na vise mesta
        //Sluzi da menja boju objektu ukoliko
        //je aktivan efekat pecurke na krticu
        srand((pecurka_parametar+15)/30);
        if(pecurka_pokrenut)
                glColor3f(rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
        
        glTranslatef(0,1,0);
        glutSolidSphere(0.05,50,50);
    glPopMatrix();
    
}

void coveculjak::torzo(int pecurka_pokrenut, int pecurka_parametar){
        
    glPushMatrix();
        glColor3f(0.18,0.34,0.49);
        
        //Objasnjeno u metodi "glava"
        srand((pecurka_parametar+22)/30);
        if(pecurka_pokrenut)
                glColor3f(1.0-rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
        
        
        glTranslatef(0,0.83,0);
        glScalef(0.5,1,0.5);
        glutSolidCube(0.22);
    glPopMatrix();
    
}

void coveculjak::leva_noga(int pecurka_pokrenut, int pecurka_parametar){
        
    glPushMatrix();
        glColor3f(0.18,0.34,0.49);
        //Objasnjeno u metodi "glava"
        srand((pecurka_parametar+11)/30);
        if(pecurka_pokrenut)
                glColor3f(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
        
        glTranslatef(-0.03,0.62,0);
        glTranslatef(0,0.1,0);
        glRotatef(0+m_timer_noga,1,0,0);
        glTranslatef(0,-0.1,0);
        glScalef(0.25,1,0.25);
        
        glutSolidCube(0.21);
    glPopMatrix();

}

void coveculjak::desna_noga(int pecurka_pokrenut, int pecurka_parametar){
        
    glPushMatrix();
        glColor3f(0.18,0.34,0.49);
        //Objasnjeno u metodi "glava"
        srand((pecurka_parametar+11)/30);
        if(pecurka_pokrenut)
                glColor3f(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
        
        glTranslatef(0.03,0.62,0);
        glTranslatef(0,0.1,0);
        glRotatef(0-m_timer_noga,1,0,0);
        glTranslatef(0,-0.1,0);
        glScalef(0.25,1,0.25);
        glutSolidCube(0.21);
    glPopMatrix();
    
}

void coveculjak::desna_ruka(int pecurka_pokrenut, int pecurka_parametar){
        
    glPushMatrix();
        //Originalna boja je samo trenutno zakomentarisana
        // glColor3f(0.29,0.52,0.74);
        glColor3f(1,0,0);
        //Objasnjeno u metodi "glava"
        srand((pecurka_parametar+10)/30);
            if(pecurka_pokrenut)
                glColor3f(rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
        
        glTranslatef(0.075,0.83,0);
        glTranslatef(0,0.085,0);
        glRotatef(0+m_timer_noga,1,0,0);
        glTranslatef(0,-0.085,0);
        glScalef(0.2,1,0.2);
        glutSolidCube(0.18);
    glPopMatrix();
    
}

void coveculjak::leva_ruka(int pecurka_pokrenut, int pecurka_parametar){
       
    glPushMatrix();
        glColor3f(0.29,0.52,0.74);
        //Objasnjeno u metodi "glava"
        srand((pecurka_parametar+5)/30);
            if(pecurka_pokrenut)
                glColor3f(rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
        
        glTranslatef(-0.075,0.83,0);
        glTranslatef(0,0.085,0);
        glRotatef(0-m_timer_noga,1,0,0);
        glTranslatef(0,-0.085,0);
        glScalef(0.2,1,0.2);
        glutSolidCube(0.18);
    glPopMatrix();

}

void coveculjak::iscrtaj(int pecurka_pokrenut, int pecurka_parametar){
        
    glPushMatrix();
        glRotatef(ugao,0,1,0);
        glava(pecurka_pokrenut, pecurka_parametar);
        torzo(pecurka_pokrenut, pecurka_parametar);
        leva_noga(pecurka_pokrenut, pecurka_parametar);
        desna_noga(pecurka_pokrenut, pecurka_parametar);
        leva_ruka(pecurka_pokrenut, pecurka_parametar);
        desna_ruka(pecurka_pokrenut, pecurka_parametar);
        oblast();
    glPopMatrix();

}

void coveculjak::oblast(){
        
    //Ne zelimo da bude osvetljen
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4f(0.29,0.52,0.74,0.5);
    glBegin(GL_QUADS);
        glVertex3f(0.3,0.51,0.3);
        glVertex3f(-0.3,0.51,0.3);
        glVertex3f(-0.3,0.51,-0.3);
        glVertex3f(0.3,0.51,-0.3);
    glEnd();
    
    glDisable(GL_BLEND);
    
    //Ivica oko kvadrata
    glColor3f(0.18,0.34,0.49);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0.3,0.51,0.3);
        glVertex3f(-0.3,0.51,0.3);
        glVertex3f(-0.3,0.51,-0.3);
        glVertex3f(0.3,0.51,-0.3);
    glEnd();
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

bool coveculjak::uhvatio_krticu(const std::vector<sargarepa>& sargarepice,
                        const std::vector<rotkvica>& rotkvice,
                        const pecurka& magicna_pecurka
                        ){
        
    float x_trenutno;
    float y_trenutno;
    
    float stranica_x;
    float stranica_y;
    
    //U slucaju da se krtica krece duz x ili z ose, ta 
    //koordinata se ne menja,dok drugu moramo azurirati
    //jer se coveculjak za vreme kretanja translira iz 
    //coska u kom je poslednjem bio
    
    if(smer){
        
        x_trenutno=m_pox;
        y_trenutno=m_poz+m_timer_vrednost;
        
    }
    
    else{
        
        x_trenutno=m_pox+m_timer_vrednost;
        y_trenutno=m_poz;
        
    }
    
    float znak1=1.0;
    float znak2=1.0;
    
    if(x_trenutno>=0)
        stranica_x=0.3;
    else {
        stranica_x=-0.3;
        znak1*=-1.0;
    }
    
    if(y_trenutno>=0)
        stranica_y=0.3;
    else {
        stranica_y=-0.3;
        znak2*=-1.0;
    }
    
    //Racunamo koordinatu za svaku od ivica oblasti
    //Dovoljne su nam cetiri koordinate da utvrdimo da li
    //se neka tacka (centar povrca) nalazi u okviru kvadrata
    //Ovakvim izracunavanjem obezbedjujemo da je npr.
    //stranica1 uvek x koordinata stranice koja se nalazi ispred seljaka
    float stranica1=znak1*(fabs(x_trenutno)+stranica_x);
    float stranica2=znak1*(fabs(x_trenutno)-stranica_x);
    float stranica3=znak2*(fabs(y_trenutno)+stranica_y);
    float stranica4=znak2*(fabs(y_trenutno)-stranica_y);
    
    //Za svako povrce proveravamo da li je u oblasti
    
    //Moramo proveriti da li se u vektorima nalazi bar jedno povrce
    if(sargarepice.size()>0){
    
        for (unsigned i=0;i<sargarepice.size();i++){
            std::pair<float,float>k=sargarepice[i].get_koordinate();
            
            if(stranica1>=k.first && stranica2<=k.first && 
                stranica3>=k.second && stranica4<=k.second && sargarepice[i].trenutno_zakljucana())
                                return true;
            
        }
    }
    

    if(rotkvice.size()>0){
    
        for (unsigned i=0;i<rotkvice.size();i++){
            std::pair<float,float>k=rotkvice[i].get_koordinate();
            
            if(stranica1>=k.first && stranica2<=k.first && 
                stranica3>=k.second && stranica4<=k.second && rotkvice[i].trenutno_zakljucana())
                                return true;
            
        }
    }
    
    
    std::pair<float,float>k=magicna_pecurka.get_koordinate();
            
            if(stranica1>=k.first && stranica2<=k.first && 
                stranica3>=k.second && stranica4<=k.second && magicna_pecurka.trenutno_zakljucana())
                                return true;
    
    
    
    //Nismo nasli u oblasti nijedno povrce koje krtica trenutno uvlaci
    return false;
}

void coveculjak::iscrtaj_na_poziciji(int pecurka_pokrenut, int pecurka_parametar){
        
    glPushMatrix();
        glTranslatef(m_pox,0,m_poz);
        iscrtaj(pecurka_pokrenut, pecurka_parametar);
    glPopMatrix();
    
}

bool coveculjak::hodaj( bool smer, 
                int pecurka_pokrenut, 
                int pecurka_parametar, 
                bool igra_zavrsena,
                const std::vector<sargarepa>& sargarepice,
                const std::vector<rotkvica>& rotkvice,
                const pecurka& magicna_pecurka) {
        
    if(!igra_zavrsena){
        glPushMatrix();
            if(smer)
                glTranslatef(m_pox,0,m_poz+m_timer_vrednost);
            else
                glTranslatef(m_pox+m_timer_vrednost,0,m_poz);
            
            iscrtaj(pecurka_pokrenut, pecurka_parametar);
            
        glPopMatrix();
    }
    
    return uhvatio_krticu(sargarepice, rotkvice, magicna_pecurka);
}

void coveculjak::stani(){
        
    m_timer_noga=0;
    m_timer_pokrenut=0;
    
}

void coveculjak::kreni(){
        
    m_timer_noga=1;
    m_timer_pokrenut=1;
    
}

bool coveculjak::kretanje(int pecurka_pokrenut, int pecurka_parametar, bool igra_zavrsena, 
                const std::vector<sargarepa>& sargarepice,
                const std::vector<rotkvica>& rotkvice,
                const pecurka& magicna_pecurka) {
    
    //Coveculjak hoda ukoliko se nalazi izmedju granica
    //Provera kada se krece paralelno sa z osom
    if(smer && m_poz+m_timer_vrednost<=m_granica_plus && m_poz+m_timer_vrednost>=m_granica_minus){
            if(hodaj(smer, pecurka_pokrenut, pecurka_parametar, igra_zavrsena, sargarepice, rotkvice, magicna_pecurka))
                return false;
        
    }
    //Provera kada se krece paralelno sa x osom
    else if(!smer && m_pox+m_timer_vrednost<=m_granica_plus && m_pox+m_timer_vrednost>=m_granica_minus){
            if(hodaj(smer, pecurka_pokrenut, pecurka_parametar, igra_zavrsena,sargarepice, rotkvice, magicna_pecurka))
                return false;
        
    }
    
    //Ako je dosao do granice
    else{
        
        //Zaustavljamo coveculjka
        //Samo za zaustavljanje kretanja ruku i nogu
        stani();
        
        //Apdejtujemo koordinate coveculjka na
        //koordinate coska u kom je trenutno
        if(smer){
                if(m_ind1)m_poz+=m_timer_vrednost+0.02;
            else m_poz+=m_timer_vrednost-0.02;
        }
        else{
            if(m_ind1)m_pox+=m_timer_vrednost+0.02;
            else m_pox+=m_timer_vrednost-0.02;
        }
        
        //Resetujemo vrednost tajmera
        m_timer_vrednost=0;

        //Iscrtavanje coveculjka kada stoji(inace treperi kada stigne u cosak)
        iscrtaj_na_poziciji(pecurka_pokrenut, pecurka_parametar);

        //Odlucujemo da li ce iz trenutno pozicije ici gore/dole ili levo/desno
        //Ukoliko odabere levo/desno kretace se levo ili desno u zavisnosti od toga
        //do koje je ivice stigao, ne moze preci preko granice kvadrata koji mu je zadat
        srand(time(NULL));
        smer=(2*(rand()/(float)RAND_MAX)>=1.0 ? true:false);
        
        //F-ovi sluze da bi poredjenje uopste bilo moguce, inace ne radi kako treba
        if(m_pox==(m_granica_minus+0.01f)&& m_poz==(m_granica_minus+0.01f)){
            
            if(smer)
                ugao=0;
            else ugao=90;
            
            m_ind1=0;
            m_timer_vrednost=0.02;
            
        }
        
        else if(m_pox==(m_granica_minus+0.01f) && m_poz==(m_granica_plus-0.01f)){
            
            if(smer){
                m_ind1=1;
                m_timer_vrednost=-0.02;
                ugao=180;
            }
            else{
                m_ind1=0;
                m_timer_vrednost=0.02;
                ugao=90;
            }
        }
        
        else if(m_pox==(m_granica_plus-0.01f) && m_poz==(m_granica_plus-0.01f)){
            
            if(smer)
                ugao=180;
            else ugao=-90;
            m_ind1=1;
            m_timer_vrednost=-0.02;
            
            
        }
        else if(m_pox==(m_granica_plus-0.01f) && m_poz==(m_granica_minus+0.01f)){
            
            if(smer){
                ugao=0;
                m_ind1=0;
                m_timer_vrednost=0.02;
            }
            else {
                ugao=-90;
                m_ind1=1;
                m_timer_vrednost=-0.02;
            }
        }
        
        //Za ponovno pokretanje ruku i nogu        
        kreni();
    
    }
    return true;
}