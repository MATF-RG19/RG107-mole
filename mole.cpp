#include<iostream>
#include<GL/glut.h>

static void on_display(void);
static void on_keyboard(unsigned char key,int x,int y);
static void on_reshape(int width, int height);

static int window_height,window_width;

int main(int argc,char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(500,200);
    glutCreateWindow("Mole");
    
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
        
    glClearColor(0,0.5,1,0);
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
    
    glScalef(1.2,1.2,1.2);
    glRotatef(65,1,0,1);
    glTranslatef(0,0,0.5);
    glColor3f(0.5,0.3,0.12);
    glBegin(GL_POLYGON);
        glVertex3f( -0.5, -0.5, -0.5);
        glVertex3f( -0.5,  0.5, -0.5); 
        glVertex3f(  0.5,  0.5, -0.5);
        glVertex3f(  0.5, -0.5, -0.5);
    glEnd();
    
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key,int x,int y){
    
    switch(key){
        
        case 27:
            exit(0);break;
    }
}
