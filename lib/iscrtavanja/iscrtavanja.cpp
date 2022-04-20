#include "iscrtavanja.hpp"

void initialize(GLuint names[])
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
    std::string s = "../img/game_over.bmp";
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

    std::string s2 = "../img/win.bmp";
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
    
    
    std::string s3 = "../img/trava.bmp";
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

void trava(GLuint names[]){
    
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

void ispis_fiksiranog_teksta(std::string s,float x,float y,int opcija,int window_height,int window_width){
    
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

void drawCircle(float r, float x, float y) {
        
        glBegin(GL_TRIANGLE_FAN);
        
        glVertex3f(x,0.502,y); 
        for(float i = 0.0f; i <= 360; i++)
                glVertex3f(r*cos(M_PI * i / 180.0) + x,0.502, r*sin(M_PI * i / 180.0) + y);
        
        glEnd();
}

void iscrtaj_sargarepu(const sargarepa& s, int pecurka_pokrenut, int pecurka_parametar){
    
    //Sargarepu iscrtavamo samo u slucaju da nije skroz uvucena u zemlju
    if(!s.pojedena()){
        
        //Ako je bar malo uvucena ispisivacemo preostali 
        //broj koraka za uvlacenje
        if(s.preostalo_koraka()<4){
            
            std::string str=std::to_string(s.preostalo_koraka());
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

void iscrtaj_rotkvicu(const rotkvica& r, int pecurka_pokrenut, int pecurka_parametar){
    
    //Rotkvicu iscrtavamo samo u slucaju da nije skroz uvucena u zemlju
    if(!r.pojedena()){
        
        //Ako je bar malo uvucena ispisivacemo preostali 
        //broj koraka za uvlacenje
        if(r.preostalo_koraka()<3){
            
            std::string str=std::to_string(r.preostalo_koraka());
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

void iscrtaj_pecurku(const pecurka& p){
        
    if(!p.pojedena()){
        
        //Izvrsava se samo u slucaju da je pecurka bar malo uvucena
        if(p.preostalo_koraka()<6){
            
            std::string str=std::to_string(p.preostalo_koraka());
            if(p.trenutno_zakljucana())
                //U slucaju da krtica trenutno uvlaci rotkvicu
                //broj preostalih uvlacenja je obojen u crveno
                ispis_teksta(p.x(),p.z(),str,1);
            else
                ispis_teksta(p.x(),p.z(),str,0);
            
        }
        
        //Crtamo i rupu kada pecurka dodje do kape
        if(p.preostalo_koraka()<3){
            glColor3f(0,0,0);
            drawCircle(0.08,p.x(),p.z());
        
            glPushMatrix();
                glTranslatef(0,-0.001,0);
                glColor3f(0.43,0.26,0.18);
                drawCircle(0.1,p.x(),p.z());
            glPopMatrix();
            
        }
        
        
        //Iscrtavanje prstenova oko kape i stope
        glPushMatrix();
            glColor3f(0.2,0.2,0.2);
            glTranslatef(p.x(),p.y()+0.1,p.z());
                glBegin(GL_LINE_LOOP);
            
                    for(int i=0;i<220;i++){
                        
                        glVertex3f(cos(2*PI/220*i)*0.0801,0.0,sin(2*PI/220*i)*0.0801);
                        
                        
                    }
            
            glEnd();
        glPopMatrix();
        
        glPushMatrix();
            glColor3f(0.2,0.2,0.2);
            glTranslatef(p.x(),p.y()+0.001,p.z());
                glBegin(GL_LINE_LOOP);
            
                    for(int i=0;i<180;i++){
                        
                        glVertex3f(cos(2*PI/180*i)*0.04,0.0,sin(2*PI/180*i)*0.04);
                        
                        
                    }
            
            glEnd();
        glPopMatrix();
        
        
        //Crtanje kape pecurke (prepolovljena sfera)
        glPushMatrix();
            
                glTranslatef(p.x(),p.y()+0.1,p.z());
            
                glColor3f(0.61,0.28,0.87);
                
                
                glEnable(GL_CLIP_PLANE0);
                double clip_plane[]={0,1,0,0};
                glClipPlane(GL_CLIP_PLANE0,clip_plane);
                
                
                glutSolidSphere(0.08,30,30);
                
                
                glDisable(GL_CLIP_PLANE0);
                
        glPopMatrix();
        
        
        //Crtanje stope (cilindra), kod preuzet sa vezbi
        glPushMatrix();
            
            glTranslatef(p.x(),p.y(),p.z());
            
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
        drawCircle(0.08,p.x(),p.z());
        
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glPushMatrix();
            glTranslatef(0,-0.001,0);
            glColor3f(0.43,0.26,0.18);
            drawCircle(0.1,p.x(),p.z());
        glPopMatrix();
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        
        
        //Kada je pojedena pecurka krtica se otkljucava
        if(p.poklapaju_se_koordinate() && !p.m_krtica->provera_otkljucano())
            p.m_krtica->otkljucaj();
    }
}

void show_game_over(GLuint names[], int window_height, int window_width){


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

void show_game_won(GLuint names[], int window_height, int window_width){


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

void zbunje_i_drvo(int pecurka_pokrenut, int pecurka_parametar){
    
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