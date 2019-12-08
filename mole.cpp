#include<iostream>
#include<GL/glut.h>

using namespace std;

static int window_height,window_width;

static void on_display(void);
static void on_keyboard(unsigned char key,int x,int y);
static void on_reshape(int width, int height);

static float cx,cz;
static float vx,vy,vz;

class sargarepa{
    
   private: float poz_x,poz_y,poz_z;
   
    public:
    sargarepa(float x,float y){
    
       poz_x=x;
       poz_z=y;
       poz_y=0.6;
       
    }
    
    void iscrtaj(){
        glPushMatrix();
            glColor3f(0.93,0.57,0.13);
            glTranslatef(poz_x,poz_y,poz_z);
            glRotatef(90,1,0,0);
            glutSolidCone(0.05,0.2,10,10);
        glPopMatrix();
    }
    
    void uvuci(){
        
        if(poklapaju_se_koordinate())
        poz_y-=1;
        
    }
    
    bool poklapaju_se_koordinate(){
        return cx==poz_x  && cz==poz_z;
    }
    
    pair<float,float> get_koordinate(){
        return make_pair(poz_x,poz_y);
    }
    
};

static sargarepa a=sargarepa(0.5,0);
static sargarepa  b=sargarepa(-0.5,0);
static sargarepa c=sargarepa(0.3,0.15);
int main(int argc,char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(500,200);
    glutCreateWindow("Mole");
    
    //Koordinate centra krtice
    cz=1.5;
    cx=0.05;
    
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
    //OSE KOORDINATNOG SISTEMA
    //Y OSA
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex3f(0,1,0);
        glVertex3f(0,-1,0);
    glEnd();
    //X OSA
    glColor3f(1,1,0);
    glBegin(GL_LINES);
        glVertex3f(0.5,0,0);
        glVertex3f(-0.5,0,0);
    glEnd();
    
    //Kvadrat koji predstavlja krticu
    glColor3f(0.41,0.29,0.18);
    glBegin(GL_POLYGON);
        glVertex3f(cx-0.1,0.501,cz-0.1);
        glVertex3f(cx-0.1,0.501,cz);
        glVertex3f(cx,0.501,cz);
        glVertex3f(cx,0.501,cz-0.1);
    glEnd();
    
    //Postolje(kocka)
    glPushMatrix();
        glTranslatef(-0.05,0.25,0);
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
            if(cz>-1.35)
                cz+=-0.05;break;
        case 'd':
            if(cx<1.4)
                cx+=0.05;break;
        case 's':
            if(cz<1.5)
                cz+=0.05;break;
            
            
        //NE RADI
        case 'u':
            a.uvuci();
            b.uvuci();
            c.uvuci();
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
