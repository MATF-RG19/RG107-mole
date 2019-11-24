#include<iostream>
#include<GL/glut.h>

static int window_height,window_width;

static void on_display(void);
static void on_keyboard(unsigned char key,int x,int y);
static void on_reshape(int width, int height);

static float cx,cz;

int main(int argc,char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(500,200);
    glutCreateWindow("Mole");
    
    cz=0;
    cx=0;
    
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
    gluLookAt(-0.1,1.3,1.3,0,0,0,0,1,0);
    
    
    glColor3f(0.41,0.29,0.18);
    glBegin(GL_POLYGON);
        glVertex3f(cx-0.1,0.5,cz-0.1);
        glVertex3f(cx-0.1,0.5,cz);
        glVertex3f(cx,0.5,cz);
        glVertex3f(cx,0.5,cz-0.1);
    glEnd();
    
    
    glTranslatef(-0.75,0,-1.15);
    glScalef(2,0.5,2);
    glColor3f(0.64,0.46,0.29);
    glutSolidCube(1);
    glColor3f(0,0,0);
    glutWireCube(1);
   
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key,int x,int y){
    
    switch(key){
        
        case 27:
            exit(0);break;
            
        case 'a':
                cx+=-0.1;break;
        case 'w':
            cz+=-0.1;break;
        case 'd':
            cx+=0.1;break;
        case 's':
            cz+=0.1;break;
    }
    
    glutPostRedisplay();
    
}
