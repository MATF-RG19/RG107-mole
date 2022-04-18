#include<iostream>
#include<GL/glut.h>
#include<cmath>
#include<string>
#include<time.h>
#include<vector>

#include "image.h"
#include "mole.hpp"
#include "sargarepa.hpp"
#include "rotkvica.hpp"


#define PI 3.14159265
#define EPSILON 0.01

#define TIMER_VREME 5

#define TIMER_PECURKA 2

#define TIMER_KRETANJE 0
#define TIMER_N 1

#define TIMER_KRETANJEA 3
#define TIMER_NA 4

using namespace std;


//BITNO: Parametri za sve boje koriscene u projektu su sa 
//sajta Encycolorpedia:https://encycolorpedia.com


static int window_height,window_width;
static void on_display(void);
static void on_keyboard(unsigned char key,int x,int y);
static void on_reshape(int width, int height);

static GLuint names[3];

//Indikator koji sluzi da onemoguci otkljucavanje krtice onda kada je igra gotova
static bool igra_zavrsena;

//Deo koda koji sluzi za inicijalizaciju oko tekstura
//Kod je preuzet od kolege Davida Nestorovica ciji
//projekat je Minecraft-boxing (MATF-RG19/RG86-minecraft-boxing)
//Ovim putem se jos jednom zahvaljujem kolegi Davidu :)
static void initialize(void)
{
    //instanciranje objekta tipa image
    Image * image;


    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    
    //inicijalizacija slike    
    image = image_init(0, 0);

    //koliko ima idjeva
    glGenTextures(3, names);

    //ovde je bio problem konverzije string tipa u char*
    //verovatno zbog toga sto je biblioteka image pisana u c-u
    //kako bi radilo u image.c sam promenio da drugi argument fje image_read bude
    //konstantan char*
    //a onda sam na internetu pronasao metodu c_str() nad objektima tipa string
    std::string s = "game_over.bmp";
    image_read(image, s.c_str());

    
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s2 = "win.bmp";
    image_read(image, s2.c_str());

    
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    std::string s3 = "trava.bmp";
    image_read(image, s3.c_str());

    
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    //uklanjamo dinamicki alociran objekat
    image_done(image);

}

//Iscrtavanje trave
static void trava(){
    
    glBindTexture(GL_TEXTURE_2D, names[2]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(1.5,0.5,7);

                glTexCoord2f(1,0);
                 glVertex3f(7,0.5,7);

                glTexCoord2f(1,1);
                 glVertex3f(7,0.5,-7);

                glTexCoord2f(0,1);
                glVertex3f(1.5,0.5,-7);
            
            glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
     glBindTexture(GL_TEXTURE_2D, names[2]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(-10,0.5,10);

                glTexCoord2f(1,0);
                 glVertex3f(10,0.5,10);

                glTexCoord2f(1,1);
                 glVertex3f(10,0.5,1.5);

                glTexCoord2f(0,1);
                glVertex3f(-10,0.5,1.5);
            
            glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture(GL_TEXTURE_2D, names[2]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(-10,0.5,1.5);

                glTexCoord2f(1,0);
                 glVertex3f(-1.5,0.5,1.5);

                glTexCoord2f(1,1);
                 glVertex3f(-1.5,0.5,-10);

                glTexCoord2f(0,1);
                glVertex3f(-10,0.5,10);
            
            glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture(GL_TEXTURE_2D, names[2]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(-1.5,0.5,-1.5);

                glTexCoord2f(1,0);
                 glVertex3f(1.5,0.5,-1.5);

                glTexCoord2f(1,1);
                 glVertex3f(1.5,0.5,-10);

                glTexCoord2f(0,1);
                glVertex3f(-1.5,0.5,-10);
            
            glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
}




//Promenljiva  kojoj cuvamo informaciju da li je pecurka doba ili losa
//Odnosno kakav efekat na krticu ima kada je pojede
static bool je_dobra;

//Funkcije koje se izvrsavaju kada je igra zavrsena,
//detaljniji opis je iznad implementacija
static void kraj_igre();
static void izgubio_si();
static void pobedio_si();

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


//Funkcija koja vrsi ispis teksta u prostoru,
//koristi se za ispis broja preostalih klikova potrebnih 
//da bi se povrce skroz uvuklo pod zemlju
void ispis_teksta(float x, float y,std::string s,int opcija)
{ 
    //Opcija 0 je ispis teksta belom bojom, odnosno kada je 
    //krtica delom uvukla povrce, ali trenutno nije zakacena za njega
    //Opcija 1 je za ispis u slucaju da krtica uvlaci trenutno, tekst se ispisuje crveno
    
    //Ne zelimo da se tekst osvetljava
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
        
    if(opcija==0)
        glColor3f(1, 1, 1);
    else
        glColor3d(1,0,0);
    
    glRasterPos3f(x,0.65,y);
    for(int i=0;i<s.size();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[i]);
        
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
}


//Instanciramo krticu
static mole krtica=mole(0,1.45);


//Ispisuje tekst koji je fiksiran u prozoru (broj osvojenih poena, preostalo vreme)
//Funkcija prima tekst, koordinate pozicije i opciju(kojim fontom ce tekst biti ispisan)
void ispis_fiksiranog_teksta(std::string s,float x,float y,int opcija){
    
    //Ne zelimo da tekst bude osvetljen
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
     glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();
            
            gluOrtho2D(0,window_width,0,window_height);
            glRasterPos2i(x, y);
            
            glColor3f(1, 1, 1);
            
            if(opcija==0){
                
                for(int i=0;i<s.length();i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
                
            }
            
            else if(opcija==1){
                
                for(int i=0;i<s.length();i++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
                
            }
            
           
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}



//Koordinate kamere
static float vx,vy,vz;

//Preuzeto sa:
//https://community.khronos.org/t/drawing-a-circle-filled-using-gl-lines/74955/2
//Uz nekoliko manjih modifikacija (tad jos nisam znao da nacrtam krug)
static void drawCircle(float r, float x, float y) {
        
        glBegin(GL_TRIANGLE_FAN);
        
        glVertex3f(x,0.502,y); 
        for(float i = 0.0f; i <= 360; i++)
                glVertex3f(r*cos(M_PI * i / 180.0) + x,0.502, r*sin(M_PI * i / 180.0) + y);
        
        glEnd();
}


void iscrtaj_sargarepu(const sargarepa& s){
    
    //Sargarepu iscrtavamo samo u slucaju da nije skroz uvucena u zemlju
    if(!s.pojedena()){
        
        //Ako je bar malo uvucena ispisivacemo preostali 
        //broj koraka za uvlacenje
        if(s.preostalo_koraka()<4){
            
            string str=to_string(s.preostalo_koraka());
            //Ako krtica trenutno uvlaci sargarepu, tekst bojimo u crveno
            if(s.trenutno_zakljucana())
                ispis_teksta(s.x(),s.z(),str,1);
            else
                ispis_teksta(s.x(),s.z(),str,0);
            
        }
        
        //Iscrtavanje torusa oko sargarepe koji simulira gomilicu zemlje
        glColor3f(0.43,0.26,0.18);
        glPushMatrix();
            glTranslatef(s.x(),0.5,s.z());
            glRotatef(90,1,0,0);
            glutSolidTorus(0.05,0.01,40,40);
        glPopMatrix();
        
        //Iscrtavanje sargarepe
        glPushMatrix();
            
            glTranslatef(s.x(),s.y(),s.z());
            
            //Crtanje crnih prstenova na sargarepi
            glColor3f(0.1,0.1,0.1);
            glBegin(GL_LINE_LOOP);
            
                    for(int i=0;i<180;i++){
                        
                        glVertex3f(cos(2*PI/180*i)*0.049,0,sin(2*PI/180*i)*0.049);
                        
                        
                    }
            
            glEnd();
            
            glBegin(GL_LINE_LOOP);
            
                    for(int i=0;i<180;i++){
                        
                        glVertex3f(cos(2*PI/180*i)*0.04,-0.04,sin(2*PI/180*i)*0.04);
                        
                        
            }
            
            glEnd();
            
            glBegin(GL_LINE_LOOP);
            
                    for(int i=0;i<180;i++){
                        
                        glVertex3f(cos(2*PI/180*i)*0.032,-0.07,sin(2*PI/180*i)*0.032);
                        
                        
                    }
            
            glEnd();
            
            
            //Crtanje zelenog dela sargarepe
            glColor3f(0.1,0.45,0.1);
            glBegin(GL_LINES);
            
                    for(int i=0;i<10;i++){
                        
                        glVertex3f(cos(2*PI/10*i)*0.03,0.1,sin(2*PI/10*i)*0.03);
                        glVertex3f(0,-0.05,0);
                        
                    }
            
            glEnd();
            
            glRotatef(90,1,0,0);
            glColor3f(0.93,0.57,0.13);
            //U slucaju da je pecurka pojedena
            //Sargarepu bojimo razlicitim bojama sve dok traje 
            //Efekat pecurke na krticu
            srand((pecurka_parametar+15)/30);
            if(pecurka_pokrenut)
                glColor3f(1.0-rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
            
            glutSolidCone(0.05,0.2,10,10);
            
        glPopMatrix();
    }
    
    
    //U slucaju da je sargarepa pojedena
    //crta se krug koji predstavlja rupu u zemlji
    else {
        
        glColor3f(0,0,0);
        drawCircle(0.05,s.x(),s.z());
        
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glPushMatrix();
            glTranslatef(0,-0.001,0);
            glColor3f(0.43,0.26,0.18);
            drawCircle(0.07,s.x(),s.z());
        glPopMatrix();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        
        //Ako je sargarepa uvucena, krtica se automatski oslobadja,
        //jer vise nema za sta da se drzi
        if(s.poklapaju_se_koordinate() && !s.m_krtica->provera_otkljucano())
            s.m_krtica->otkljucaj();
        
    }
}

  void iscrtaj_rotkvicu(const rotkvica& r){
        
        //Rotkvicu iscrtavamo samo u slucaju da nije skroz uvucena u zemlju
        if(!r.pojedena()){
            
            //Ako je bar malo uvucena ispisivacemo preostali 
            //broj koraka za uvlacenje
            if(r.preostalo_koraka()<3){
                
                string str=to_string(r.preostalo_koraka());
                //Ako krtica trenutno uvlaci rotkvicu, tekst bojimo u crveno
                if(r.trenutno_zakljucana())
                    ispis_teksta(r.x(),r.z(),str,1);
                else
                    ispis_teksta(r.x(),r.z(),str,0);
                
            }
            
            
             //Iscrtavanje torusa oko rotkvice koji simulira gomilicu zemlje
            glColor3f(0.43,0.26,0.18);
            glPushMatrix();
                glTranslatef(r.x(),0.5,r.z());
                glRotatef(90,1,0,0);
                glutSolidTorus(0.03,0.03,40,40);
            glPopMatrix();
            
            
            glPushMatrix();
                
                glTranslatef(r.x(),r.y(),r.z());
                
                //Iscrtavanje zelenog dela rotkvice
                //Iscrtavanje spoljasnjih listova
                glColor3f(0.30,0.57,0.10);
                glBegin(GL_TRIANGLES);
                
                        for(int i=0;i<8;i+=2){
                            
                            glVertex3f(cos(2*PI/8*i)*0.05,0.13,sin(2*PI/8*i)*0.05);
                            glVertex3f(cos(2*PI/8*(i+1))*0.05,0.13,sin(2*PI/8*(i+1))*0.05);
                            glVertex3f(0,0.02,0);
                            
                        }
                
                glEnd();
                
                //Iscrtavanje unutrasnjih listova
                glColor3f(0.38,0.71,0.12);
                glBegin(GL_TRIANGLES);
                
                        for(int i=0;i<8;i+=2){
                            
                            glVertex3f(cos(2*PI/8*(i+1))*0.03,0.13,sin(2*PI/8*(i+1))*0.03);
                            glVertex3f(cos(2*PI/8*(i+2))*0.03,0.13,sin(2*PI/8*(i+2))*0.03);
                            glVertex3f(0,0.02,0);
                            
                        }
                
                glEnd();
                
                glColor3f(0.73,0.12,0.26);
                //U slucaju da je pecurka pojedena
                //rotkvicu bojimo razlicitim bojama sve dok traje 
                //efekat pecurke na krticu
                srand(pecurka_parametar/30);
                if(pecurka_pokrenut)
                    glColor3f(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
                
                glRotatef(90,1,0,0);
                glutSolidSphere(0.05,10,10);
            glPopMatrix();
            
        }
        
        //U slucaju da je rotkvica pojedena
        //crta se krug koji predstavlja rupu u zemlji
        else {
            
            glColor3f(0,0,0);
            drawCircle(0.05,r.x(),r.z());
            
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            glPushMatrix();
                glTranslatef(0,-0.001,0);
                glColor3f(0.43,0.26,0.18);
                drawCircle(0.07,r.x(),r.z());
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
          
            //Kada je pojedena rotkvica krtica se otkljucava
            if(r.poklapaju_se_koordinate() && !r.m_krtica->provera_otkljucano())
                r.m_krtica->otkljucaj();
        }
    }


//Vektori koji sadrze povrce
static vector<sargarepa>sargarepice;
static vector<rotkvica>rotkvice;


//Random za svaku poziciju biramo da li ce se 
//povrce tu uopste pojaviti i koja ce vrsta biti ako se pojavljuje
static void povrce(){
    
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


class pecurka{
    
   private:
       //Koordinate pecurke
        float poz_x,poz_y,poz_z;
        //Broj preostalih koraka potrebnih da se pecurka uvuce
        int preostalo_koraka;
    public:
        
    
    pecurka(){
        
//       Nasumicno biramo poziciju pecurke
//       Ona se uvek nalazi u centralnom delu
//       Tako da je ili u samom centru i moze se pojesti bez 
//       mogucnosti da nas seljak uhvati
//       Ili je na nekoj od ivica i postoji mogucnost da nas uhvati 
        
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
        preostalo_koraka=6;
       
    }
    
    void iscrtaj(){
        
        if(!pojedena()){
            
            //Izvrsava se samo u slucaju da je pecurka bar malo uvucena
            if(preostalo_koraka<6){
                
                string str=to_string(preostalo_koraka);
                if(trenutno_zakljucana())
                    //U slucaju da krtica trenutno uvlaci rotkvicu
                    //broj preostalih uvlacenja je obojen u crveno
                    ispis_teksta(poz_x,poz_z,str,1);
                else
                    ispis_teksta(poz_x,poz_z,str,0);
                
            }
            
            //Crtamo i rupu kada pecurka dodje do kape
            if(preostalo_koraka<3){
                glColor3f(0,0,0);
                drawCircle(0.08,poz_x,poz_z);
            
                glPushMatrix();
                    glTranslatef(0,-0.001,0);
                    glColor3f(0.43,0.26,0.18);
                    drawCircle(0.1,poz_x,poz_z);
                glPopMatrix();
                
            }
            
            
            //Iscrtavanje prstenova oko kape i stope
            glPushMatrix();
                glColor3f(0.2,0.2,0.2);
                glTranslatef(poz_x,poz_y+0.1,poz_z);
                 glBegin(GL_LINE_LOOP);
                
                        for(int i=0;i<220;i++){
                            
                            glVertex3f(cos(2*PI/220*i)*0.0801,0.0,sin(2*PI/220*i)*0.0801);
                            
                            
                        }
                
                glEnd();
            glPopMatrix();
            
            glPushMatrix();
                glColor3f(0.2,0.2,0.2);
                glTranslatef(poz_x,poz_y+0.001,poz_z);
                 glBegin(GL_LINE_LOOP);
                
                        for(int i=0;i<180;i++){
                            
                            glVertex3f(cos(2*PI/180*i)*0.04,0.0,sin(2*PI/180*i)*0.04);
                            
                            
                        }
                
                glEnd();
            glPopMatrix();
            
            
            //Crtanje kape pecurke (prepolovljena sfera)
            glPushMatrix();
                
                   glTranslatef(poz_x,poz_y+0.1,poz_z);
                
                    glColor3f(0.61,0.28,0.87);
                    
                    
                    glEnable(GL_CLIP_PLANE0);
                    double clip_plane[]={0,1,0,0};
                    glClipPlane(GL_CLIP_PLANE0,clip_plane);
                    
                    
                    glutSolidSphere(0.08,30,30);
                    
                    
                    glDisable(GL_CLIP_PLANE0);
                    
            glPopMatrix();
            
            
            //Crtanje stope (cilindra), kod preuzet sa vezbi
            glPushMatrix();
                
                glTranslatef(poz_x,poz_y,poz_z);
                
                glScalef(0.04,0.04,0.04);
                
                glColor3f(1,1,1);
                float u,v;
                glPushMatrix();
        
                for(u=0;u<PI;u+=PI/20){
                    glBegin(GL_TRIANGLE_STRIP);
                    
                        for(v=0;v<=2*PI+EPSILON;v+=PI/20){
                            glNormal3f(sin(v),0,cos(v));
                            glVertex3f(sin(v),u,cos(v));
                            
                            glNormal3f(sin(v),0,cos(v));
                            glVertex3f(sin(v),u+PI/20,cos(v));
                        }
                        
                    glEnd();
                }
                
                glPopMatrix();
                
            glPopMatrix();
            
        }
        
        //U slucaju da je pecurka pojedena
        //crta se krug koji predstavlja rupu u zemlji
        else {
            
            glColor3f(0,0,0);
            drawCircle(0.08,poz_x,poz_z);
            
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            glPushMatrix();
                glTranslatef(0,-0.001,0);
                glColor3f(0.43,0.26,0.18);
                drawCircle(0.1,poz_x,poz_z);
            glPopMatrix();
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
            
            
            //Kada je pojedena pecurka krtica se otkljucava
            if(poklapaju_se_koordinate() && !krtica.provera_otkljucano())
                krtica.otkljucaj();
        }
    }
    
    //Metod za uvlacenje pecurke, pokrece se iz
    //on_keyboard funkcije, pritiskom na taster 'u',
    //ali tek nakon sto se krtica zakaci za pecurku
    //pritiskom na taster 'i'
    void uvuci(){
        
       if(poklapaju_se_koordinate() && !pojedena() && !krtica.provera_otkljucano()){
         
           poz_y-=0.025;
            preostalo_koraka--;
            
            //Ako je pecurka uvucena pokrecemo 
            //timer_pecurka koji pokrece efekat delovanja pecurke na krticu
            //Ukoliko je pecurka dobra, krtica postaje brza i povrce moze 
            //da uvuce u jednom potezu inace ne moze da se pomeri sve dok traje efekat
            if(preostalo_koraka==0){
                glutTimerFunc(300,timer_pecurka,TIMER_PECURKA);
                pecurka_pokrenut=1;
                //Povecava se broj osvojenih poena
                krtica.uvecaj_poene(10);
            }
       }
    }
    
    
    float granica=0.1;
    //Provera da li je krtica dovoljno blizu pecurki da moze da se
    //uhvati za nju i da je uvuce
    bool poklapaju_se_koordinate() const {
        
        return (krtica.x() >(poz_x-granica) && krtica.x() <(poz_x+granica)) &&
            (krtica.z() >(poz_z-granica) && krtica.z() <(poz_z+granica));
            
    }
    
    bool pojedena() const {
        
        return poz_y<=0.35;
        
    }
    
    //Provera da li je krtica trenutno zakacena na pecurku
    bool trenutno_zakljucana(){
        
        return poklapaju_se_koordinate() && !krtica.provera_otkljucano() && preostalo_koraka<6;
        
    }
   
   
    pair<float,float> get_koordinate(){
        
        return make_pair(poz_x,poz_z);
        
    }
    
    
};

//Instanciramo pecurku
static pecurka magicna_pecurka=pecurka();


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


//Klasa za seljaka
class coveculjak{

public:
    //Koordinate seljaka
    float pox,poz;
    //Granicne koordinate do kojih moze da se krece
    //i na x i na z osi
    float granica_plus,granica_minus;
    //Promenljive za tajmere koji sluze
    //za kretanje seljaka i pomeranje ruku/nogu
    int timer_noga=0;
    int timer_pokrenut=1;
    double timer_vrednost=0;

    //Indikator koji sluzi da promeni znak
    //parametra tajmer (tajmer_vrednost)
    int ind1=0;
    
    coveculjak(float a,float b,float c,float d){
        
        pox=a;
        poz=b;
        
        granica_minus=c;
        granica_plus=d;
        
    }
    
    //Iscrtavamo glavu(sfera)
    void glava(){
        
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
    //Iscrtavamo torzo
    void torzo(){
        
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
    
    //Iscrtavamo levu nogu
    void leva_noga(){
        
        glPushMatrix();
            glColor3f(0.18,0.34,0.49);
            //Objasnjeno u metodi "glava"
            srand((pecurka_parametar+11)/30);
            if(pecurka_pokrenut)
                    glColor3f(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
            
            glTranslatef(-0.03,0.62,0);
            glTranslatef(0,0.1,0);
            glRotatef(0+timer_noga,1,0,0);
            glTranslatef(0,-0.1,0);
            glScalef(0.25,1,0.25);
            
            glutSolidCube(0.21);
        glPopMatrix();
        
    }
    //Iscrtavamo desnu nogu
    void desna_noga(){
        
        glPushMatrix();
            glColor3f(0.18,0.34,0.49);
            //Objasnjeno u metodi "glava"
            srand((pecurka_parametar+11)/30);
            if(pecurka_pokrenut)
                    glColor3f(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
            
            glTranslatef(0.03,0.62,0);
            glTranslatef(0,0.1,0);
            glRotatef(0-timer_noga,1,0,0);
            glTranslatef(0,-0.1,0);
            glScalef(0.25,1,0.25);
            glutSolidCube(0.21);
        glPopMatrix();
        
    }
    //Iscrtavamo desnu ruku
    void desna_ruka(){
        
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
            glRotatef(0+timer_noga,1,0,0);
            glTranslatef(0,-0.085,0);
            glScalef(0.2,1,0.2);
            glutSolidCube(0.18);
        glPopMatrix();
        
    }
    
    //Iscrtavamo levu ruku
   void leva_ruka(){
       
        glPushMatrix();
            glColor3f(0.29,0.52,0.74);
            //Objasnjeno u metodi "glava"
            srand((pecurka_parametar+5)/30);
                if(pecurka_pokrenut)
                    glColor3f(rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
            
            glTranslatef(-0.075,0.83,0);
            glTranslatef(0,0.085,0);
            glRotatef(0-timer_noga,1,0,0);
            glTranslatef(0,-0.085,0);
            glScalef(0.2,1,0.2);
            glutSolidCube(0.18);
        glPopMatrix();
    
    }
    
    //Ugao za koji se coveculjak rotira
    int ugao=0;
    
    //Iscrtavamo kompletnog coveculjka
    void iscrtaj(){
        
        glPushMatrix();
            glRotatef(ugao,0,1,0);
            glava();
            torzo();
            leva_noga();
            desna_noga();
            leva_ruka();
            desna_ruka();
            oblast();
        glPopMatrix();
    }
    
//     Iscrtavamo kvadrat oko coveculjka u kom on
//     moze da registruje da krtica uvlaci povrce
    void oblast(){
        
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
    
    
    //Vrsimo proveru da li krtica uvlaci neko povrce koje se nalazi 
    //u okviru oblasti koja se iscrtava oko coveculjka
    bool uhvatio_krticu(){
        
        float x_trenutno;
        float y_trenutno;
        
        float stranica_x;
        float stranica_y;
        
        //U slucaju da se krtica krece duz x ili z ose, ta 
        //koordinata se ne menja,dok drugu moramo azurirati
        //jer se coveculjak za vreme kretanja translira iz 
        //coska u kom je poslednjem bio
        
        if(smer){
            
            x_trenutno=pox;
            y_trenutno=poz+timer_vrednost;
            
        }
        
        else{
            
            x_trenutno=pox+timer_vrednost;
            y_trenutno=poz;
            
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
        
            for (int i=0;i<sargarepice.size();i++){
               pair<float,float>k=sargarepice[i].get_koordinate();
              
               if(stranica1>=k.first && stranica2<=k.first && 
                   stranica3>=k.second && stranica4<=k.second && sargarepice[i].trenutno_zakljucana())
                                    return true;
              
            }
        }
        
    
        if(rotkvice.size()>0){
        
            for (int i=0;i<rotkvice.size();i++){
                pair<float,float>k=rotkvice[i].get_koordinate();
              
                if(stranica1>=k.first && stranica2<=k.first && 
                   stranica3>=k.second && stranica4<=k.second && rotkvice[i].trenutno_zakljucana())
                                    return true;
                
            }
        }
        
        
        pair<float,float>k=magicna_pecurka.get_koordinate();
              
                if(stranica1>=k.first && stranica2<=k.first && 
                   stranica3>=k.second && stranica4<=k.second && magicna_pecurka.trenutno_zakljucana())
                                    return true;
        
        
        
        //Nismo nasli u oblasti nijedno povrce koje krtica trenutno uvlaci
        return false;
    }
    
    //Iscrtavamo coveculjka na poziciji njegovih koordinata
    void iscrtaj_na_poziciji(){
        
        glPushMatrix();
            glTranslatef(pox,0,poz);
            iscrtaj();
        glPopMatrix();
        
    }
    
    //Metod koji pokrece coveculjka
    // i u svakom koraku proverava da li je
    //u oblasti krtica koja trenutno uvlaci povrce
    void hodaj(bool a){
        
        if(!igra_zavrsena){
        glPushMatrix();
            if(a)
                glTranslatef(pox,0,poz+timer_vrednost);
            else
                glTranslatef(pox+timer_vrednost,0,poz);
            
            iscrtaj();
            
        glPopMatrix();
        }
        
         if(uhvatio_krticu())
            izgubio_si();
        
    }
    
    //Zaustavljamo tajmere
    void stani(){
        
        timer_noga=0;
        timer_pokrenut=0;
        
    }

    
    void kreni(){
        
        timer_noga=1;
        timer_pokrenut=1;
        
    }
    
    //Indikator koji oznacava kuda se krece coveculjak
    //ako se krece gore-dole onda je true, false znaci levo-desno
    bool smer=true;

    void kretanje(){
        
            //Coveculjak hoda ukoliko se nalazi izmedju granica
            //Provera kada se krece paralelno sa z osom
            if(smer && poz+timer_vrednost<=granica_plus && poz+timer_vrednost>=granica_minus){
                    hodaj(smer);
                
            }
            //Provera kada se krece paralelno sa x osom
            else if(!smer && pox+timer_vrednost<=granica_plus && pox+timer_vrednost>=granica_minus){
                    hodaj(smer);
                
            }
            
            //Ako je dosao do granice
            else{
                
                //Zaustavljamo coveculjka
                //Samo za zaustavljanje kretanja ruku i nogu
               stani();
                
                //Apdejtujemo koordinate coveculjka na
               //koordinate coska u kom je trenutno
                if(smer){
                     if(ind1)poz+=timer_vrednost+0.02;
                    else poz+=timer_vrednost-0.02;
                }
                else{
                    if(ind1)pox+=timer_vrednost+0.02;
                    else pox+=timer_vrednost-0.02;
                }
                
                //Resetujemo vrednost tajmera
                timer_vrednost=0;

                //Iscrtavanje coveculjka kada stoji(inace treperi kada stigne u cosak)
                iscrtaj_na_poziciji();

                //Odlucujemo da li ce iz trenutno pozicije ici gore/dole ili levo/desno
                //Ukoliko odabere levo/desno kretace se levo ili desno u zavisnosti od toga
                //do koje je ivice stigao, ne moze preci preko granice kvadrata koji mu je zadat
                srand(time(NULL));
                smer=(2*(rand()/(float)RAND_MAX)>=1.0 ? true:false);
                
                //F-ovi sluze da bi poredjenje uopste bilo moguce, inace ne radi kako treba
                if(pox==(granica_minus+0.01f)&& poz==(granica_minus+0.01f)){
                    
                    if(smer)
                        ugao=0;
                    else ugao=90;
                    
                    ind1=0;
                    timer_vrednost=0.02;
                    
                }
                
                else if(pox==(granica_minus+0.01f) && poz==(granica_plus-0.01f)){
                    
                    if(smer){
                        ind1=1;
                        timer_vrednost=-0.02;
                        ugao=180;
                    }
                    else{
                        ind1=0;
                        timer_vrednost=0.02;
                        ugao=90;
                    }
                }
                
                else if(pox==(granica_plus-0.01f) && poz==(granica_plus-0.01f)){
                    
                    if(smer)
                        ugao=180;
                    else ugao=-90;
                    ind1=1;
                    timer_vrednost=-0.02;
                    
                    
                }
                else if(pox==(granica_plus-0.01f) && poz==(granica_minus+0.01f)){
                    
                    if(smer){
                        ugao=0;
                        ind1=0;
                        timer_vrednost=0.02;
                    }
                    else {
                        ugao=-90;
                        ind1=1;
                        timer_vrednost=-0.02;
                    }
                }
                
                
             //Za ponovno pokretanje ruku i nogu        
               kreni();
            
           
            }
            
        
    }

};

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
    
    if(cikica1.ind1==0)
        cikica1.timer_vrednost+=0.02;
    else if(cikica1.ind1==1)
        cikica1.timer_vrednost-=0.02;
    
    glutPostRedisplay();
    
    if(cikica1.timer_pokrenut)
        glutTimerFunc(50,on_timer,TIMER_KRETANJE);
    
}

//Tajmer za pomeranje ruku i nogu prvog coveculjka
static int ind=0;
static void on_timer2(int id){
    
    if(id!=TIMER_N)
        return;
    if(cikica1.timer_noga<=-20)
        ind=0;
    else if(cikica1.timer_noga>=20)
        ind=1;
    
    if(ind==1)
        cikica1.timer_noga-=1;
    else
        cikica1.timer_noga+=1;
    
    glutPostRedisplay();
    
    if(cikica1.timer_pokrenut)
        glutTimerFunc(10,on_timer2,TIMER_N);
    
}


//Tajmeri za drugog coveculjka

//Tajmer za kretanje drugog coveculjka
static void on_timer3(int id){
    
    if(id!=TIMER_KRETANJEA)
        return;
    
    if(cikica2.ind1==0)
        cikica2.timer_vrednost+=0.02;
    else if(cikica2.ind1==1)
        cikica2.timer_vrednost-=0.02;
    
    glutPostRedisplay();
    
    if(cikica2.timer_pokrenut)
        glutTimerFunc(50,on_timer3,TIMER_KRETANJEA);
    
}

//Tajmer za pomeranje ruku i nogu drugog coveculjka
static int ind4=0;
static void on_timer4(int id){
    
    if(id!=TIMER_NA)
        return;
    if(cikica2.timer_noga<=-20)
        ind4=0;
    else if(cikica2.timer_noga>=20)
        ind4=1;
    
    if(ind4==1)
        cikica2.timer_noga-=1;
    else
        cikica2.timer_noga+=1;
    
    glutPostRedisplay();
    
    if(cikica2.timer_pokrenut)
        glutTimerFunc(10,on_timer4,TIMER_NA);
    
}



//Kod takodje preuzet od kolege Davida
//Uz neke izmene
//Iscrtavanje slike 'Game over' u slucaju da je igrac izgubio
void show_game_over(){


        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();
            
            gluOrtho2D(0,window_width,0,window_height);
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHTING);
    
            glBindTexture(GL_TEXTURE_2D, names[0]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0.1,0);
                glVertex2f(0,0);

                glTexCoord2f(1,0);
                glVertex2f(window_width,0);

                glTexCoord2f(1,0.9);
                glVertex2f(window_width, window_height);

                glTexCoord2f(0.1,0.9);
                glVertex2f(0, window_height);
            
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glEnable(GL_DEPTH_TEST);
   
}

//Iscrtavanje slike you win u slucaju da je igrac pobedio
void show_game_won(){


        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();
            
            gluOrtho2D(0,window_width,0,window_height);
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHTING);
    
            glBindTexture(GL_TEXTURE_2D, names[1]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0.1,0);
                glVertex2f(0,0);

                glTexCoord2f(1,0);
                glVertex2f(window_width,0);

                glTexCoord2f(1,0.9);
                glVertex2f(window_width, window_height);

                glTexCoord2f(0.1,0.9);
                glVertex2f(0, window_height);
            
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glEnable(GL_DEPTH_TEST);
   
}


//Funkcija zakljucava krticu i zaustavlja sve tajmere
static void kraj_igre(){
    
    krtica.zakljucaj();
    cikica1.stani();
    cikica2.stani();
    vreme_pokrenut=0;
    pecurka_pokrenut=0;
    
    igra_zavrsena=true;
    
}


//Funkcija koja zaustavlja igru u slucaju da je seljak uhvatio krticu
//Pokrece je coveculjak kada je uhvati
static void izgubio_si(){
    
    kraj_igre();
    glColor3f(1.0,1.0,1.0);
    //ispis_fiksiranog_teksta("KRAJ IGRE",350,350,1);
    show_game_over();
}

//Funkcija koja proverava da li je sve povrce pojedeno
//ukoliko jeste, igrac je pobedio
//VAZNO:Pecurka ne mora biti pojedena!!!
static void pobedio_si(){
    
    float a=true;
    
      if(sargarepice.size()>1){
        
        for (int i=0;i<sargarepice.size();i++)
            if(!sargarepice[i].pojedena())
                a=false;
        
    }
        
    if(rotkvice.size()>1){
        
        for (int i=0;i<rotkvice.size();i++)
            if(!rotkvice[i].pojedena())
                a=false;
            
    }
    
    if(a && vreme>0){
    kraj_igre();
    
    show_game_won();
    glColor3f(1,1,1);
    std::string p="Osvojeno poena:";
    ispis_fiksiranog_teksta(p,300,300,0);
    ispis_fiksiranog_teksta(to_string(krtica.poeni()),440,300,0);
    }
}


//Iscrtavamo zbunje i drvo
static void zbunje_i_drvo(){
    
    //Iscrtavamo prvi zbun(dve sfere, manja i veca)
    glPushMatrix();
        glTranslatef(-1.2,0.6,1.9);
        glColor3f(0.1,0.45,0.1);
        
        //U slucaju da krtica pojede pecurku
        //I zbunje ce menjati boju
        srand((pecurka_parametar+8)/30);
                if(pecurka_pokrenut)
                    glColor3f(1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
        glutSolidSphere(0.25,40,40);
        glTranslatef(0.25,-0.1,0);
        glutSolidSphere(0.15,40,40);
    glPopMatrix();
    
    //Identican zbun, samo sa drugim koordinatama
    glPushMatrix();
        glTranslatef(2.2,0.6,-1);
        glColor3f(0.1,0.45,0.1);
        srand((pecurka_parametar)/30);
                if(pecurka_pokrenut)
                    glColor3f(rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
        glutSolidSphere(0.25,40,40);
            glTranslatef(0.25,-0.1,0);
        glutSolidSphere(0.15,40,40);
    glPopMatrix();
    
    
    //Sfera koja predstavlja krosnju drveta
    glPushMatrix();
        glTranslatef(-2,1.3,-1.8);
        glColor3f(0.1,0.45,0.1);
        
        //Takodje menja boju kada se pojede pecurka
        srand((pecurka_parametar+17)/30);
                if(pecurka_pokrenut)
                    glColor3f(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX);
        glutSolidSphere(0.25,40,40);
    glPopMatrix();
    
    
    //Iscrtavamo cilindar koji predstavlja
    //stablo drveta, ne zelim da bude osvetljen
    //Kod je vec koriscen prilikom crtanja stope pecurke
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glPushMatrix();
                
            glTranslatef(-2.0,0.5,-1.8);
                
            glScalef(0.04,0.25,0.04);
                
            glColor3f(0.41,0.29,0.18);
            //Objasnjeno iznad
            srand((pecurka_parametar+13)/30);
                if(pecurka_pokrenut)
                    glColor3f(1.0-rand()/(float)RAND_MAX,1.0-rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
            float u,v;
            glPushMatrix();
        
                for(u=0;u<PI;u+=PI/20){
                    glBegin(GL_TRIANGLE_STRIP);
                    
                        for(v=0;v<=2*PI+EPSILON;v+=PI/20){
                            glNormal3f(sin(v),0,cos(v));
                            glVertex3f(sin(v),u,cos(v));
                            
                            glNormal3f(sin(v),0,cos(v));
                            glVertex3f(sin(v),u+PI/20,cos(v));
                        }
                        
                    glEnd();
                }
                
            glPopMatrix();
                
        glPopMatrix();
            
    //Ponovo ukljucujemo osvetljenje
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
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
    povrce();
    
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
    initialize();
    
    glutMainLoop();

    return 0;
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
    trava();

    zbunje_i_drvo();
    
    
    //Iscrtavanje svih sargarepa
    if(sargarepice.size()>0){
        
        for (int i=0;i<sargarepice.size();i++)
            iscrtaj_sargarepu(sargarepice[i]);
        
    }
        
    
        
    //Iscrtavanje svih rotkvica
    if(rotkvice.size()>0){
        
        for (int i=0;i<rotkvice.size();i++)
            iscrtaj_rotkvicu(rotkvice[i]);
        
    }
    
    //Iscrtavamo pecurku
    magicna_pecurka.iscrtaj();

    //Kretacnje seljaka
    cikica1.kretanje();
    cikica2.kretanje();
    
    //Ispis broja poena na ekranu
    if(!igra_zavrsena){
        glColor3f(0.41,0.29,0.18);
        std::string s="Poeni:";
        ispis_fiksiranog_teksta(s,10,580,0);
        glColor3f(1,1,1);
        ispis_fiksiranog_teksta(to_string(krtica.poeni()),70,579,0);
        
        //Ispis vremena na ekranu
        glColor3f(0.41,0.29,0.18);
        s="Vreme:";
        ispis_fiksiranog_teksta(s,10,560,0);
        glColor3f(1,1,1);
        ispis_fiksiranog_teksta(to_string(vreme),70,560,0);
    }
 
    
    //U zavisnosti od toga da li je dobra(zeleno) ili ne(crveno)
    //vreme trajanja efekta pecurke bojimo razlicitom bojom
    if(!je_dobra)
        glColor3f(1,0,0);
    else 
        glColor3f(0,1,0);
    if(pecurka_pokrenut)
        ispis_fiksiranog_teksta(to_string(pecurka_vreme),100,560,0);
    
    
    //Ako je pecurka pojedena i nije dobra,
    //krtica ne moze da se pomeri
    if(pecurka_pokrenut && !je_dobra)
        krtica.zakljucaj();
        
   
    //Provera da li je sve povrce pojedeno, u tom slucaju je
    //Igrac pobedio
    //VAZNO:Pecurka ne mora biti pojedena!!!
    pobedio_si();
    
    
     //Ako je vreme isteklo igrac je izgubio
    if(vreme==0)
        izgubio_si();
    
    
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
            
            magicna_pecurka.uvuci();
            }
            break;
            
    }


    glutPostRedisplay();
}
