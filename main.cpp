#include<iostream>
#include<GL/glut.h>
#include<cmath>
#include<string>
#include<time.h>
#include<vector>

#include "mole.hpp"
#include "sargarepa.hpp"
#include "rotkvica.hpp"
#include "pecurka.hpp"
#include "coveculjak.hpp"
#include "iscrtavanja.hpp"
#include "igra.hpp"

#define PI 3.14159265
#define EPSILON 0.01

#define TIMER_VREME 5

#define TIMER_PECURKA 2

#define TIMER_KRETANJE 0
#define TIMER_N 1

#define TIMER_KRETANJEA 3
#define TIMER_NA 4

using namespace std;


static int window_height,window_width;

static GLuint names[3];

//Indikator koji sluzi da onemoguci otkljucavanje krtice onda kada je igra gotova
static bool igra_zavrsena;

//Promenljiva  kojoj cuvamo informaciju da li je pecurka doba ili losa
//Odnosno kakav efekat na krticu ima kada je pojede
static bool je_dobra;

//Promenljive vezane za tajmer pecurka
static int pecurka_vreme=10;
static int pecurka_pokrenut=0;
static int pecurka_parametar=0;


//Promenljive vezane za tajmer koji odbrojava vreme
static int vreme_pokrenut;
static int vreme;
//Tajmer koji odbrojava vreme do kraja igre
static void timer_vreme(int id){
    
    if(id!=TIMER_VREME)
        return;
    
    if(vreme>0){
        vreme--;
        
        //U slucaju da je pojedena pecurka
        //tajmer ce odbrojavati i vreme trajanja efekta koji 
        //pecurka ima na krticu
        if(pecurka_pokrenut && pecurka_vreme>0){
            pecurka_vreme--;
        }
        
        //U slucaju da je vreme trajanja efekta isteklo
        //zaustavljamo tajmer vezan za pecurku
        else
            pecurka_pokrenut=0;
    }
    
    if(vreme_pokrenut!=0)
        glutTimerFunc(1000,timer_vreme,TIMER_VREME);
    
}

//Tajmer koji se aktivira kada je pojedena pecurka
static void timer_pecurka(int id){
    
    if(id!=TIMER_PECURKA)
        return;
    
    pecurka_parametar++;
    
    glutPostRedisplay();
    
    if(pecurka_pokrenut!=0)
        glutTimerFunc(50,timer_pecurka,TIMER_PECURKA);
    
}


//Koordinate kamere
static float vx,vy,vz;

static mole krtica=mole(0,1.45);
static pecurka magicna_pecurka=pecurka(&krtica);
static vector<sargarepa>sargarepice;
static vector<rotkvica>rotkvice;


//Random za svaku poziciju biramo da li ce se 
//povrce tu uopste pojaviti i koja ce vrsta biti ako se pojavljuje
static void povrce(vector<sargarepa>& sargarepice, vector<rotkvica>&rotkvice){
    
   srand(time(NULL));
    float x=1.25;
    for(int i=0;i<6;i++){
        float z=-1.25;
        for (int j=0;j<6;j++){
            
            //Da li ce se povrce iscrtati u na toj poziciji
            if(2*(rand()/(float)RAND_MAX)>1.0){
                
                //Da li ce povrce biti sargarepa ili rotkvica u slucaju da se iscrtava
                if(2*(rand()/(float)RAND_MAX)>1.0){
                    
                    sargarepa a=sargarepa(x,z,&krtica);
                    sargarepice.push_back(a);
                    
                }
                
                else{
                    
                    rotkvica b=rotkvica(x,z,&krtica);
                    rotkvice.push_back(b);
                    
                }
                
            }
            
            z+=0.5;
            
        }
        x-=0.5;
    }
    
}



//Funkcija koja proverava da li je krtica u blizini nekog
//povrca i da u tom slucaju moze da se zakljuca
static bool provera_zakljucavanja(const mole& krtica, const vector<sargarepa>& sargarepice, 
                                                        const vector<rotkvica>& rotkvice, const pecurka& magicna_pecurka){
        
        bool a=false;
        
          
        if(sargarepice.size()>1){
        
            for (int i=0;i<sargarepice.size();i++)
            if(sargarepice[i].poklapaju_se_koordinate() && !sargarepice[i].pojedena())
                a=true;
        
        }
        
    
        if(rotkvice.size()>1){
        
            for (int i=0;i<rotkvice.size();i++)
                if(rotkvice[i].poklapaju_se_koordinate() && !rotkvice[i].pojedena())
                    a=true;
        
        }
        
        if(magicna_pecurka.poklapaju_se_koordinate() && !magicna_pecurka.pojedena())
            a=true;
        
        return a;
}

//Instanciramo dva coveculjka, zadajemo im pocetne pozicije 
//i koordinate koje predstavljaju pozitivnu i negativnu (tj. levu,desnu,godrnju,donju
//posto je kvadrat u pitanju ne trebaju nam sve cetiri) stranicu kvadrata po kom treba da se krecu
static coveculjak cikica1=coveculjak(-1,-01,-1.01,1.01);
static coveculjak cikica2=coveculjak(-0.50,-0.50,-0.51,0.51f);


//Tajmeri za prvog coveculjka

//Tajmer za pomeranje prvog coveculjka
static void on_timer(int id){
    
    if(id!=TIMER_KRETANJE)
        return;
    
    if(cikica1.ind1()==0)
        cikica1.inc_timer_vrednost(0.02);
    else if(cikica1.ind1()==1)
        cikica1.inc_timer_vrednost(-0.02);
    
    glutPostRedisplay();
    
    if(cikica1.timer_pokrenut())
        glutTimerFunc(50,on_timer,TIMER_KRETANJE);
    
}

//Tajmer za pomeranje ruku i nogu prvog coveculjka
static int ind=0;
static void on_timer2(int id){
    
    if(id!=TIMER_N)
        return;
    if(cikica1.timer_noga()<=-20)
        ind=0;
    else if(cikica1.timer_noga()>=20)
        ind=1;
    
    if(ind==1)
        cikica1.inc_timer_noga(-1);
    else
        cikica1.inc_timer_noga(1);
    
    glutPostRedisplay();
    
    if(cikica1.timer_pokrenut())
        glutTimerFunc(10,on_timer2,TIMER_N);
    
}


//Tajmeri za drugog coveculjka

//Tajmer za kretanje drugog coveculjka
static void on_timer3(int id){
    
    if(id!=TIMER_KRETANJEA)
        return;
    
    if(cikica2.ind1()==0)
        cikica2.inc_timer_vrednost(0.02);
    else if(cikica2.ind1()==1)
        cikica2.inc_timer_vrednost(-0.02);
    
    glutPostRedisplay();
    
    if(cikica2.timer_pokrenut())
        glutTimerFunc(50,on_timer3,TIMER_KRETANJEA);
    
}

//Tajmer za pomeranje ruku i nogu drugog coveculjka
static int ind4=0;
static void on_timer4(int id){
    
    if(id!=TIMER_NA)
        return;
    if(cikica2.timer_noga()<=-20)
        ind4=0;
    else if(cikica2.timer_noga()>=20)
        ind4=1;
    
    if(ind4==1)
        cikica2.inc_timer_noga(-1);
    else
        cikica2.inc_timer_noga(1);
    
    glutPostRedisplay();
    
    if(cikica2.timer_pokrenut())
        glutTimerFunc(10,on_timer4,TIMER_NA);
    
}

static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;
}

static void on_display(void){
     
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0,0,window_width,window_height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,0.9,7);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(vx,vy,vz,0,0,0,0,1,0);
    
    //Iscrtavamo krticu
    krtica.iscrtaj();

    //Postolje(kocka)
    glPushMatrix();
        glTranslatef(0,0.25,0);
        glScalef(3,0.5,3);
        glColor3f(0.64,0.46,0.29);
        srand((pecurka_parametar+20)/30);
        //U slucaju da je pecurka pojedena i postolje menja boju
        if(pecurka_pokrenut && pecurka_parametar>10)
            glColor3f(1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
        glutSolidCube(1);
        glColor3f(0,0,0);
        glutWireCube(1);
    glPopMatrix();
  
    
    //Pozivamo funkciju koja iscrtava travu oko kocke
    trava(names);
    zbunje_i_drvo(pecurka_pokrenut, pecurka_parametar);
    

    //Iscrtavanje svih sargarepa
    if(sargarepice.size()>0){
        
        for (int i=0;i<sargarepice.size();i++)
            iscrtaj_sargarepu(sargarepice[i],pecurka_pokrenut, pecurka_parametar);
        
    }
        
    //Iscrtavanje svih rotkvica
    if(rotkvice.size()>0){
        
        for (int i=0;i<rotkvice.size();i++)
            iscrtaj_rotkvicu(rotkvice[i],pecurka_pokrenut, pecurka_parametar);
        
    }
    
    //Iscrtavamo pecurku
    iscrtaj_pecurku(magicna_pecurka);

    //Kretacnje seljaka
    bool krece_se1 = cikica1.kretanje(pecurka_pokrenut, pecurka_parametar,igra_zavrsena,sargarepice,rotkvice,magicna_pecurka);
    bool krece_se2 = cikica2.kretanje(pecurka_pokrenut, pecurka_parametar,igra_zavrsena,sargarepice,rotkvice,magicna_pecurka);
    
    if (!krece_se1 || !krece_se2)
        izgubio_si(krtica, cikica1, cikica2, vreme_pokrenut, pecurka_pokrenut, igra_zavrsena, names, window_height, window_width);

    //Ispis broja poena na ekranu
    if(!igra_zavrsena){
        glColor3f(0.41,0.29,0.18);
        std::string s="Poeni:";
        ispis_fiksiranog_teksta(s,10,580,0,window_height,window_width);
        glColor3f(1,1,1);
        ispis_fiksiranog_teksta(to_string(krtica.poeni()),70,579,0,window_height,window_width);
        
        //Ispis vremena na ekranu
        glColor3f(0.41,0.29,0.18);
        s="Vreme:";
        ispis_fiksiranog_teksta(s,10,560,0,window_height,window_width);
        glColor3f(1,1,1);
        ispis_fiksiranog_teksta(to_string(vreme),70,560,0,window_height,window_width);
    }
 
    
    //U zavisnosti od toga da li je dobra(zeleno) ili ne(crveno)
    //vreme trajanja efekta pecurke bojimo razlicitom bojom
    if(!je_dobra)
        glColor3f(1,0,0);
    else 
        glColor3f(0,1,0);
    if(pecurka_pokrenut)
        ispis_fiksiranog_teksta(to_string(pecurka_vreme),100,560,0,window_height,window_width);
    
    
    //Ako je pecurka pojedena i nije dobra,
    //krtica ne moze da se pomeri
    if(pecurka_pokrenut && !je_dobra)
        krtica.zakljucaj();
        
   
    //Provera da li je sve povrce pojedeno, u tom slucaju je
    //Igrac pobedio
    //VAZNO:Pecurka ne mora biti pojedena!!!
    pobedio_si(krtica, cikica1, cikica2, vreme_pokrenut, pecurka_pokrenut, igra_zavrsena, names, window_height, window_width, sargarepice, rotkvice, vreme);
    
    
     //Ako je vreme isteklo igrac je izgubio
    if(vreme==0)
        izgubio_si(krtica, cikica1, cikica2, vreme_pokrenut, pecurka_pokrenut, igra_zavrsena, names, window_height, window_width);
    
    
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key,int x,int y){
    
    switch(key){
        
        case 27:
            exit(0);break;
          
        //Upravljanje krticom:
        //Pod uslovom da je pecurka pojedena
        //za svaki klik krtica pravi dupli pomeraj
        //kako bi mogla duplo brze da se krece
        //naravno, ovo vazi samo pod uslovom da je
        //pecurka dobra, inace je krtica zakljucana i ne moze da se pomera
        case 'a':
            krtica.pomeri_levo();
            if(pecurka_pokrenut)
                krtica.pomeri_levo();
            break;
        case 'w':
           krtica.pomeri_gore();
           if(pecurka_pokrenut)
                krtica.pomeri_gore();
           break;
        case 'd':
            krtica.pomeri_desno();
             if(pecurka_pokrenut)
                krtica.pomeri_desno();
             break;
        case 's':
            krtica.pomeri_dole();
             if(pecurka_pokrenut)
                krtica.pomeri_dole();
             break;
        case 'q':
            krtica.pomeri_gore_levo();
             if(pecurka_pokrenut)
                krtica.pomeri_gore_levo();
             break;
        case 'e':
            krtica.pomeri_gore_desno();
             if(pecurka_pokrenut)
                krtica.pomeri_gore_desno();
             break;
        case 'z':
            krtica.pomeri_dole_levo();
             if(pecurka_pokrenut)
                krtica.pomeri_dole_levo();
             break;
        case 'c':
            krtica.pomeri_dole_desno();
             if(pecurka_pokrenut)
                krtica.pomeri_dole_desno();
             break;
            
        //Zakljucavanje krtice onosno krtica se hvata
        //za neko povrce, ovo je moguce samo uslucaju
        //da se nalazi dovoljno blizu nekog povrca, inace
        //ne bi imala za sta da se uhvati
        case 'i':
            if(krtica.provera_otkljucano() && provera_zakljucavanja(krtica, sargarepice, rotkvice, magicna_pecurka))
                krtica.zakljucaj();
            else if(!igra_zavrsena)
                krtica.otkljucaj();
 
            break;
            
        //Uvlacenje povrca
        case  'u':
            if(!igra_zavrsena){
                if(sargarepice.size()>1){
                
                    for (int i=0;i<sargarepice.size();i++)
                        sargarepice[i].uvuci(pecurka_pokrenut);
                
                }
                if(rotkvice.size()>1){
            
                    for (int i=0;i<rotkvice.size();i++)
                        rotkvice[i].uvuci(pecurka_pokrenut);
            
                }
                
                if(magicna_pecurka.uvuci() && magicna_pecurka.preostalo_koraka()==0) {
                    glutTimerFunc(300,timer_pecurka,TIMER_PECURKA);
                    pecurka_pokrenut=1;   
                }
            }
            break;
            
    }

    glutPostRedisplay();
}



int main(int argc,char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(500,200);
    glutCreateWindow("Mole");
    
    
    //Podrazumevane koordinate kamere
    vx=0;
    vy=1.9;
    vz=2.3;
    
    //Indikator koji sluzi da ne dozvoli da se krtica otkljuca nakon zavrsene igre
    igra_zavrsena=false;
    
    //Postavljamo indikator da je tajmer za odbrojavanje vremena pokrenut
    vreme_pokrenut=1;
    
    //Pokretanje funkcije koja povrce smesta u vektore
    povrce(sargarepice, rotkvice);
    
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    
    //Postavljamo vreme trajanja igre
    vreme=59;
    
    //Random biramo da li je pecurka dobra ili losa
    //tj. kakav ce efekat imati na krticu ako je pojede
    srand(time(NULL));
    je_dobra= rand()/(float)RAND_MAX >0.5 ? true:false;
    
    //POKRETANJE SVIH TAJMERA
    
    glutTimerFunc(50,on_timer,TIMER_KRETANJE);
    glutTimerFunc(10,on_timer2,TIMER_N);
    glutTimerFunc(50,on_timer3,TIMER_KRETANJEA);
    glutTimerFunc(10,on_timer4,TIMER_NA);
    
    //Glavni tajmer
    glutTimerFunc(1000,timer_vreme,TIMER_VREME);
    
    glClearColor(0.52,0.8,0.92,0);
    glEnable(GL_DEPTH_TEST);
    
    //Ukljucivanje osvetljenja
    GLfloat light_position[] = { 30, 150, -120, 0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat light_specular[] = { 0.5, 0.8, 0.5, 1 };

    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };

    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    
    //pozivanje funkcije za inicijalizaciju
    initialize(names);

    glutMainLoop();

    return 0;
}
