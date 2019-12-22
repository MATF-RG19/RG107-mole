#include<iostream>
#include<GL/glut.h>
#include<cmath>
#include<string>
#include<time.h>
#include<vector>

#define TIMER_KRETANJE 0
#define TIMER_N 1
using namespace std;

static int window_height,window_width;

static int timer_pokrenut=1;
static double timer_vrednost=0;


static void on_display(void);
static void on_keyboard(unsigned char key,int x,int y);
static void on_reshape(int width, int height);


int ind1=0;
static void on_timer(int id){
    
    if(id!=TIMER_KRETANJE)
        return;
    
    if(ind1==0)
        timer_vrednost+=0.02;
    else
        timer_vrednost-=0.02;
    
    glutPostRedisplay();
    
    if(timer_pokrenut)
        glutTimerFunc(50,on_timer,TIMER_KRETANJE);
    
}

static int timer_noga=0;
static int ind=0;

static void on_timer2(int id){
    
    if(id!=TIMER_N)
        return;
    if(timer_noga<=-20)
        ind=0;
    else if(timer_noga>=20)
        ind=1;
    
    if(ind==1)
        timer_noga-=1;
    else
        timer_noga+=1;
    
    glutPostRedisplay();
    
    if(timer_pokrenut)
        glutTimerFunc(10,on_timer2,TIMER_N);
    
}


//Koordinate krtice
//static float cx,cz;


void ispis_teksta(float x, float y, string s,int opcija)
{ 
    //Opcija 0 je ispis preostalog broja uvlacenja za povrce
    //Opcija 1 je za ispis broja osvojenih poena

    if(opcija==0){
    
        glColor3f(1, 1, 1); 
        glRasterPos3f(x,0.65,y);
        for(int i=0;i<s.size();i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[i]);
        
    }
    
    else if(opcija==1){
        
        glColor3f(1, 1, 1); 
        glRasterPos2f(x,y);
        for(int i=0;i<s.size();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[i]);
        
        
    }
    
}


class mole{
    
public:
    float cx,cz;
    int poeni=0;
    int otkljucano=1;
    
    mole(float x,float y){
        
        cx=x;
        cz=y;
        
    }
    
    void iscrtaj(){
        //Poeni se samo trenutno ovako ispisuju
        ispis_teksta(cx,cz,to_string(poeni),0);
        glColor3f(0.41,0.29,0.18);
        glBegin(GL_POLYGON);
            glVertex3f(cx+0.05,0.501,cz+0.05);
            glVertex3f(cx-0.05,0.501,cz+0.05);
            glVertex3f(cx-0.05,0.501,cz-0.05);
            glVertex3f(cx+0.05,0.501,cz-0.05);
        glEnd();
        
    }
    
    void pomeri_levo(){
       
        if(cx>-1.4 && otkljucano)
                cx+=-0.05;
        
    }
    
    void pomeri_desno(){
        
        if(cx<1.4 && otkljucano)
                cx+=0.05;
        
    }
    
    void pomeri_gore(){
        
        if(cz>-1.4 && otkljucano)
                cz+=-0.05;
        
    }
    
    void pomeri_dole(){
        
        if(cz<1.45 && otkljucano)
                cz+=0.05;
        
    }
    
    void pomeri_gore_levo(){
        
        pomeri_gore();
        pomeri_levo();
        
    }
    
      void pomeri_gore_desno(){
        
        pomeri_gore();
        pomeri_desno();
        
    }
    
      void pomeri_dole_levo(){
        
        pomeri_dole();
        pomeri_levo();
        
    }
    
      void pomeri_dole_desno(){
        
        pomeri_dole();
        pomeri_desno();
        
    }

    void zakljucaj(){
        otkljucano=0;
    }
    
    void otkljucaj(){
        otkljucano=1;
    }
    
    bool provera_otkljucano(){
        return otkljucano;
    }
    
};

static mole krtica=mole(0,1.45);

//Koordinate kamere
static float vx,vy,vz;

//Preuzeto sa:
//https://community.khronos.org/t/drawing-a-circle-filled-using-gl-lines/74955/2
//Uz nekoliko manjih modifikacija
static void drawCircle(float r, float x, float y) {
        
        glBegin(GL_TRIANGLE_FAN);
        
        glVertex3f(x,0.502,y); 
        for(float i = 0.0f; i <= 360; i++)
                glVertex3f(r*cos(M_PI * i / 180.0) + x,0.502, r*sin(M_PI * i / 180.0) + y);
        
        glEnd();
}


class sargarepa{
    
   private: 
        float poz_x,poz_y,poz_z;
        int preostalo_koraka;
    public:
    sargarepa(float x,float y){
    
       poz_x=x;
       poz_z=y;
       poz_y=0.6;
       preostalo_koraka=4;
    }
    
    void iscrtaj(){
        
        if(!pojedena()){
            
            if(preostalo_koraka<4){
                string str=to_string(preostalo_koraka);
                ispis_teksta(poz_x,poz_z,str,0);
            }
            
            glPushMatrix();
                glColor3f(0.93,0.57,0.13);
                glTranslatef(poz_x,poz_y,poz_z);
                glRotatef(90,1,0,0);
                glutSolidCone(0.05,0.2,10,10);
            glPopMatrix();
        }
        //U slucaju da je sargarepa pojedena
        //crta se krug koji predstavlja rupu u zemlji
        else {
            glColor3f(0,0,0);
            drawCircle(0.05,poz_x,poz_z);
        }
    }
    
    void uvuci(){
        
       if(poklapaju_se_koordinate() && !pojedena() && !krtica.provera_otkljucano()){
            poz_y-=0.03;
            preostalo_koraka--;
            if(preostalo_koraka==0)
                krtica.poeni+=4;
       }
    }
    
    float granica=0.1;
    bool poklapaju_se_koordinate(){
        return (krtica.cx >(poz_x-granica) && krtica.cx <(poz_x+granica)) &&
            (krtica.cz >(poz_z-granica) && krtica.cz <(poz_z+granica));
    }
    
    bool pojedena(){
        return poz_y<=0.5;
    }
    
    //Geter, ne znam zasto sam ga napisao
    pair<float,float> get_koordinate(){
        return make_pair(poz_x,poz_y);
    }
    
};

class rotkvica{
    
   private:
        float poz_x,poz_y,poz_z;
        int preostalo_koraka;
    public:
    rotkvica(float x,float y){
    
       poz_x=x;
       poz_z=y;
       poz_y=0.5;
       preostalo_koraka=2;
    }
    
    void iscrtaj(){
        
        if(!pojedena()){
            
            if(preostalo_koraka<2){
                string str=to_string(preostalo_koraka);
                ispis_teksta(poz_x,poz_z,str,0);
            }
            
            glPushMatrix();
                glColor3f(0.73,0.12,0.26);
                glTranslatef(poz_x,poz_y,poz_z);
                glRotatef(90,1,0,0);
                glutSolidSphere(0.05,10,10);
            glPopMatrix();
        }
        //U slucaju da je rotkvica pojedena
        //crta se krug koji predstavlja rupu u zemlji
        else {
            glColor3f(0,0,0);
            drawCircle(0.05,poz_x,poz_z);
        }
    }
    
    void uvuci(){
        
       if(poklapaju_se_koordinate() && !pojedena() && !krtica.provera_otkljucano()){
            poz_y-=0.03;
            preostalo_koraka--;
            if(preostalo_koraka==0)
                krtica.poeni+=2;
       }
    }
    
    float granica=0.1;
    bool poklapaju_se_koordinate(){
        return (krtica.cx >(poz_x-granica) && krtica.cx <(poz_x+granica)) &&
            (krtica.cz >(poz_z-granica) && krtica.cz <(poz_z+granica));
    }
    
    bool pojedena(){
        return poz_y<=0.45;
    }
    
    //Geter, ne znam zasto sam ga napisao
    pair<float,float> get_koordinate(){
        return make_pair(poz_x,poz_y);
    }
    
};

//Vektori koji sadrze povrce

static vector<sargarepa>sargarepice;
static vector<rotkvica>rotkvice;

//Random odabir povrca

static void povrce(){
    
   srand(time(NULL));
    float x=1.25;
    for(int i=0;i<6;i++){
        float z=-1.25;
        for (int j=0;j<6;j++){
            
            //Da li ce se povrce iscrtati u tom redu i koloni
            if(2*(rand()/(float)RAND_MAX)>1.0){
                
                //Da li ce povrce biti sargarepa ili rotkvica
                if(2*(rand()/(float)RAND_MAX)>1.0){
                    
                    sargarepa a=sargarepa(x,z);
                    sargarepice.push_back(a);
                    
                }
                
                else{
                    
                    rotkvica b=rotkvica(x,z);
                    rotkvice.push_back(b);
                    
                }
                
            }
            
            z+=0.5;
            
        }
        x-=0.5;
    }
    
}


//Coveculjci se sada i krecu, jos uvek kontrolisano tastaturom

class coveculjak{

private:
    float pox,poz;
    
public:
    coveculjak(float a,float b){
        
        pox=a;
        poz=b;
        
    }
    
    void glava(){
        
        glPushMatrix();
            glColor3f(0.2,0.2,0.2);
            glTranslatef(0,1,0);
            glutSolidSphere(0.05,50,50);
        glPopMatrix();
        
    }
    void torzo(){
        
        glPushMatrix();
            glColor3f(0.18,0.34,0.49);
            glTranslatef(0,0.83,0);
            glScalef(0.5,1,0.5);
            glutSolidCube(0.22);
        glPopMatrix();
        
    }
    
    void leva_noga(){
        
        glPushMatrix();
            glColor3f(0.18,0.34,0.49);
            glTranslatef(-0.03,0.62,0);
            glTranslatef(0,0.1,0);
            glRotatef(0+timer_noga,1,0,0);
            glTranslatef(0,-0.1,0);
            glScalef(0.25,1,0.25);
            
            glutSolidCube(0.21);
        glPopMatrix();
        
    }
    
    void desna_noga(){
        
        glPushMatrix();
            glColor3f(0.18,0.34,0.49);
            glTranslatef(0.03,0.62,0);
            glTranslatef(0,0.1,0);
            glRotatef(0-timer_noga,1,0,0);
            glTranslatef(0,-0.1,0);
            glScalef(0.25,1,0.25);
            glutSolidCube(0.21);
        glPopMatrix();
        
    }
    
    void desna_ruka(){
        
        glPushMatrix();
            glColor3f(0.29,0.52,0.74);
            glTranslatef(0.075,0.83,0);
            glTranslatef(0,0.085,0);
            glRotatef(0+timer_noga,1,0,0);
            glTranslatef(0,-0.085,0);
            glScalef(0.2,1,0.2);
            glutSolidCube(0.18);
        glPopMatrix();
        
    }
    
   void leva_ruka(){
       
        glPushMatrix();
            glColor3f(0.29,0.52,0.74);
            glTranslatef(-0.075,0.83,0);
            glTranslatef(0,0.085,0);
            glRotatef(0-timer_noga,1,0,0);
            glTranslatef(0,-0.085,0);
            glScalef(0.2,1,0.2);
            glutSolidCube(0.18);
        glPopMatrix();
    
    }
    
    void iscrtaj(){
        
        glPushMatrix();
        glTranslatef(pox,0,poz+timer_vrednost);
        
        glava();
        torzo();
        leva_noga();
        desna_noga();
        leva_ruka();
        desna_ruka();
        oblast();
        glPopMatrix();
    }
    
    
    void oblast(){
        
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
        
        glColor3f(0.18,0.34,0.49);
        glBegin(GL_LINE_LOOP);
            glVertex3f(0.3,0.51,0.3);
            glVertex3f(-0.3,0.51,0.3);
            glVertex3f(-0.3,0.51,-0.3);
            glVertex3f(0.3,0.51,-0.3);
        glEnd();
        
    }
    
    
    void hodaj(){
        
        //poz+=timer_vrednost;
        
    }
    
    
    
    void stani(){
        
        timer_noga=0;
        timer_pokrenut=0;
        
    }
    
    void kreni(){
        
        timer_noga=1;
        timer_pokrenut=1;
        
    }
    void kretanje(){
        
       if(poz+timer_vrednost<=1.3 && poz+timer_vrednost>=-1.3)
            hodaj();
        
        else{
            stani();
            promeni_pravac();
            kreni();
        }
        
        iscrtaj();
        
    }
    
    void promeni_pravac(){
        
        if(ind1==0)
            ind1=1;
        else ind1=0;
        
    }
    
    
};


static coveculjak cikica=coveculjak(-1,-1.3);
static coveculjak cikica2=coveculjak(-0.7,1.3);

int main(int argc,char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(500,200);
    glutCreateWindow("Mole");
    
    //Koordinate centra krtice
    //cz=1.45;
   // cx=0;
    
    //Podrazumevane koordinate kamere
    vx=0;
    vy=1.9;
    vz=2.3;
    
    povrce();
    
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    
     glutTimerFunc(50,on_timer,TIMER_KRETANJE);
     glutTimerFunc(10,on_timer2,TIMER_N);
    
    glClearColor(0.52,0.8,0.92,0);
    glEnable(GL_DEPTH_TEST);
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
//      Za testiranje
//     gluLookAt(0,1.9,2.3,0,0,0,0,1,0);

    // glLineWidth(6);
    
    //OSE KOORDINATNOG SISTEMA(samo kao olaksica u radu)
    //Y OSA
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex3f(0,1,0);
        glVertex3f(0,-1,0);
    glEnd();
//     X OSA
    glColor3f(1,1,0);
    glBegin(GL_LINES);
        glVertex3f(0.5,0,0);
        glVertex3f(-0.5,0,0);
    glEnd();
    
    
    //Kvadrat koji predstavlja krticu
//     glColor3f(0.41,0.29,0.18);
//     glBegin(GL_POLYGON);
//         glVertex3f(cx+0.05,0.501,cz+0.05);
//         glVertex3f(cx-0.05,0.501,cz+0.05);
//         glVertex3f(cx-0.05,0.501,cz-0.05);
//         glVertex3f(cx+0.05,0.501,cz-0.05);
//     glEnd();
    
    krtica.iscrtaj();
    
    //Postolje(kocka)
    glPushMatrix();
        glTranslatef(0,0.25,0);
        glScalef(3,0.5,3);
        glColor3f(0.64,0.46,0.29);
        glutSolidCube(1);
        glColor3f(0,0,0);
        glutWireCube(1);
    glPopMatrix();
  
    
//   //  a=sargarepa(0.5,0);
//     a.iscrtaj();
//    // b=sargarepa(-0.5,0);
//     b.iscrtaj();
//     //c=sargarepa(0.3,0.15);
//     c.iscrtaj();
//     
//     d.iscrtaj();
//     
//     e.iscrtaj();
    
    
    
    if(sargarepice.size()>1){
        
        for (int i=0;i<sargarepice.size();i++)
            sargarepice[i].iscrtaj();
        
    }
        
    if(rotkvice.size()>1){
        
        for (int i=0;i<rotkvice.size();i++)
            rotkvice[i].iscrtaj();
        
    }
    
    //TODO popraviti ispis teksta
    //ispis_teksta(0.5,1.5,to_string(krtica.poeni),1);
    
    

    cikica.kretanje();
    
    
    

    
            
    //Stampanje koordinata radi testiranja
//     cout << cx <<" "<< cz <<endl;
//     cout << a.get_koordinate().first << a.get_koordinate().second<<endl;
    
    
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key,int x,int y){
    
    switch(key){
        
        case 27:
            exit(0);break;
          
        //Upravljanje krticom:
        case 'a':
            krtica.pomeri_levo();break;
        case 'w':
           krtica.pomeri_gore();break;
        case 'd':
            krtica.pomeri_desno();break;
        case 's':
            krtica.pomeri_dole();break;
        case 'q':
            krtica.pomeri_gore_levo();break;
        case 'e':
            krtica.pomeri_gore_desno();break;
        case 'z':
            krtica.pomeri_dole_levo();break;
            case 'c':
            krtica.pomeri_dole_desno();break;
            
            
        case 'i':
            if(krtica.provera_otkljucano())
                krtica.zakljucaj();
            else
                krtica.otkljucaj();
            break;
            
//         case 'a':
//             if(cx>-1.4)
//                 cx+=-0.05;break;
//         case 'w':
//             if(cz>-1.4)
//                 cz+=-0.05;break;
//         case 'd':
//             if(cx<1.4)
//                 cx+=0.05;break;
//         case 's':
//             if(cz<1.45)
//                 cz+=0.05;break;
            
        case 't':
            if(!timer_pokrenut){
                timer_pokrenut=1;
                glutTimerFunc(50,on_timer,TIMER_KRETANJE);
                 glutTimerFunc(5,on_timer2,TIMER_N);
            }
                break;
        case 'y':
            cikica.stani();
            break;
            
        case  'u':
            
            if(sargarepice.size()>1){
               
                for (int i=0;i<sargarepice.size();i++)
                    sargarepice[i].uvuci();
               
            }
            if(rotkvice.size()>1){
        
                for (int i=0;i<rotkvice.size();i++)
                    rotkvice[i].uvuci();
        
            }
            break;
            
        //Upravljanje kamerom
        //Uvecavanje x,y,z
        case 'x':
            vx+=0.1;break;
      //  case 'c':
     //       vy+=0.1;break;   
        case 'v':
            vz+=0.1;break;
        //Umanjivanje x,y,z
        case 'b':
            vx-=0.1;break;
        case 'n':
            vy-=0.1;break;   
        case 'm':
            vz-=0.1;break;
            
        //Resetovanje kamere na podrazumevane koordinate
        case 'r':
             vx=0;vy=1.9;vz=2.3;
             break;
    }
    
//     Stampanje koordinata kamere
//     cout << vx << " " << vy << " " << vz <<endl;

    glutPostRedisplay();
}
