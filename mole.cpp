#include<iostream>
#include<GL/glut.h>
#include<cmath>
#include<string>


using namespace std;

static int window_height,window_width;

static void on_display(void);
static void on_keyboard(unsigned char key,int x,int y);
static void on_reshape(int width, int height);

//Koordinate krtice
static float cx,cz;

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

void ispis_teksta(float x, float y, string s)
{ 

    glColor3f(1, 1, 1); 
    glRasterPos3f(x,0.65,y);
    for(int i=0;i<s.size();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[i]);

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
                ispis_teksta(poz_x,poz_z,str);
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
        
       if(poklapaju_se_koordinate() && !pojedena()){
            poz_y-=0.03;
            preostalo_koraka--;
       }
    }
    
    float granica=0.1;
    bool poklapaju_se_koordinate(){
        return (cx >(poz_x-granica) && cx <(poz_x+granica)) &&
            (cz >(poz_z-granica) && cz <(poz_z+granica));
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
                ispis_teksta(poz_x,poz_z,str);
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
        
       if(poklapaju_se_koordinate() && !pojedena()){
            poz_y-=0.03;
            preostalo_koraka--;
       }
    }
    
    float granica=0.1;
    bool poklapaju_se_koordinate(){
        return (cx >(poz_x-granica) && cx <(poz_x+granica)) &&
            (cz >(poz_z-granica) && cz <(poz_z+granica));
    }
    
    bool pojedena(){
        return poz_y<=0.45;
    }
    
    //Geter, ne znam zasto sam ga napisao
    pair<float,float> get_koordinate(){
        return make_pair(poz_x,poz_y);
    }
    
};


//Coveculjci jos uvek ne rade nista, samo se iscrtavaju

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
            glScalef(0.25,1,0.25);
            glutSolidCube(0.21);
        glPopMatrix();
        
    }
    
    void desna_noga(){
        
        glPushMatrix();
            glColor3f(0.18,0.34,0.49);
            glTranslatef(0.03,0.62,0);
            glScalef(0.25,1,0.25);
            glutSolidCube(0.21);
        glPopMatrix();
        
    }
    
    void desna_ruka(){
        
        glPushMatrix();
            glColor3f(0.29,0.52,0.74);
            glTranslatef(0.075,0.83,0);
            glScalef(0.2,1,0.2);
            glutSolidCube(0.18);
        glPopMatrix();
        
    }
    
   void leva_ruka(){
       
        glPushMatrix();
            glColor3f(0.29,0.52,0.74);
            glTranslatef(-0.075,0.83,0);
            glScalef(0.2,1,0.2);
            glutSolidCube(0.18);
        glPopMatrix();
    
    }
    
    void iscrtaj(){
        
        glTranslatef(pox,0,poz);
        
        glava();
        torzo();
        leva_noga();
        desna_noga();
        leva_ruka();
        desna_ruka();
        
    }
    
};

//TRENUTNO NIJE POTREBNO
// class krtica{
//         
//     private:
//         float cx,cz;
//         float tx=0,tz=0;
//     public:
//         
//         krtica(){
//             cx=0,cz=0;
//         }
//         
//         void iscrtaj(){
//                 glPushMatrix();
//                 glTranslatef(tx,0,tz);
//                 glColor3f(0.41,0.29,0.18);
//                 glBegin(GL_POLYGON);
//                     glVertex3f(cx-0.1,0.501,cz-0.1);
//                     glVertex3f(cx-0.1,0.501,cz);
//                     glVertex3f(cx,0.501,cz);
//                     glVertex3f(cx,0.501,cz-0.1);
//                 glEnd();
//                 glPopMatrix();
//                 cout<< cx+tx<< " "<<cz+tz<<endl;anthony hopkins
//         }
//         
//         
//         
//         void pomeri_gore(){
// //             if(cz>-1.35)
//                 tz+=-0.05;
//         }
//         
//         
//         void pomeri_dole(){
// //             if(cz<1.5)
//                 tz+=0.05;
//         }
//         
//         
//         void pomeri_levo(){
// //             if(cx>-1.4)
//                 tx+=-0.05;
//         }
//         
//         
//         void pomeri_desno(){
// //             if(cx<1.4)
//                 tx+=0.05;
//         }
//         
//     };

static sargarepa a=sargarepa(0.5,0);
static sargarepa  b=sargarepa(-0.5,0);
static sargarepa c=sargarepa(0.3,-1.2);
static rotkvica d=rotkvica(0.5,0.5);
static rotkvica e=rotkvica(-0.5,1);

// static krtica mole=krtica();

static coveculjak cikica=coveculjak(-1,-0.3);
static coveculjak cikica2=coveculjak(2,1.2);

int main(int argc,char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(500,200);
    glutCreateWindow("Mole");
    
    //Koordinate centra krtice
    cz=1.45;
    cx=0;
    
    //Podrazumevane koordinate kamere
    vx=0;
    vy=1.9;
    vz=2.3;
    
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
        
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
    
//     mole.iscrtaj();
    
    
//     glPushMatrix();
//         glColor3f(0.2,0.2,0.2);
//         glTranslatef(0,1,0);
//         glutSolidSphere(0.05,50,50);
//     glPopMatrix();
//     glPushMatrix();
//         glColor3f(0.18,0.34,0.49);
//         glTranslatef(0,0.83,0);
//         glScalef(0.5,1,0.5);
//         glutSolidCube(0.22);
//     glPopMatrix();
//     glPushMatrix();
//         glColor3f(0.18,0.34,0.49);
//         glTranslatef(-0.03,0.62,0);
//         glScalef(0.25,1,0.25);
//         glutSolidCube(0.21);
//     glPopMatrix();
//     glPushMatrix();
//         glColor3f(0.18,0.34,0.49);
//         glTranslatef(0.03,0.62,0);
//         glScalef(0.25,1,0.25);
//         glutSolidCube(0.21);
//     glPopMatrix();
//     glPushMatrix();
//         glColor3f(0.29,0.52,0.74);
//         glTranslatef(0.075,0.83,0);
//         glScalef(0.2,1,0.2);
//         glutSolidCube(0.18);
//     glPopMatrix();
//     glPushMatrix();
//         glColor3f(0.29,0.52,0.74);
//         glTranslatef(-0.075,0.83,0);
//         glScalef(0.2,1,0.2);
//         glutSolidCube(0.18);
//     glPopMatrix();
    
    
    //Kvadrat koji predstavlja krticu
    glColor3f(0.41,0.29,0.18);
    glBegin(GL_POLYGON);
        glVertex3f(cx+0.05,0.501,cz+0.05);
        glVertex3f(cx-0.05,0.501,cz+0.05);
        glVertex3f(cx-0.05,0.501,cz-0.05);
        glVertex3f(cx+0.05,0.501,cz-0.05);
    glEnd();
    
    //Postolje(kocka)
    glPushMatrix();
        glTranslatef(0,0.25,0);
        glScalef(3,0.5,3);
        glColor3f(0.64,0.46,0.29);
        glutSolidCube(1);
        glColor3f(0,0,0);
        glutWireCube(1);
    glPopMatrix();
  
    
  //  a=sargarepa(0.5,0);
    a.iscrtaj();
   // b=sargarepa(-0.5,0);
    b.iscrtaj();
    //c=sargarepa(0.3,0.15);
    c.iscrtaj();
    
    d.iscrtaj();
    
    e.iscrtaj();
    
    cikica.iscrtaj();
    
    cikica2.iscrtaj();
    
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
            if(cx>-1.4)
                cx+=-0.05;break;
        case 'w':
            if(cz>-1.4)
                cz+=-0.05;break;
        case 'd':
            if(cx<1.4)
                cx+=0.05;break;
        case 's':
            if(cz<1.45)
                cz+=0.05;break;
            
//             
            //Za klasu krtica
//         case 'a':
//             mole.pomeri_levo();break;
//         case 'w':
//             mole.pomeri_gore();break;
//         case 'd':
//             mole.pomeri_desno();break;
//         case 's':
//             mole.pomeri_dole();break;
//             
            
            
        case  'u':
            a.uvuci();
            b.uvuci();
            c.uvuci();
            d.uvuci();
            e.uvuci();
            break;
            
        //Upravljanje kamerom
        //Uvecavanje x,y,z
        case 'x':
            vx+=0.1;break;
        case 'c':
            vy+=0.1;break;   
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
