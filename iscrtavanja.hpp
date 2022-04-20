#include "image.h"
#include <GL/glut.h>
#include <cmath>
#include <string>

#include "sargarepa.hpp"
#include "rotkvica.hpp"
#include "pecurka.hpp"

#define PI 3.14159265
#define EPSILON 0.01

#define TIMER_VREME 5

#define TIMER_PECURKA 2

#define TIMER_KRETANJE 0
#define TIMER_N 1

#define TIMER_KRETANJEA 3
#define TIMER_NA 4


//Deo koda koji sluzi za inicijalizaciju oko tekstura
//Kod je preuzet od kolege Davida Nestorovica ciji
//projekat je Minecraft-boxing (MATF-RG19/RG86-minecraft-boxing)
//Ovim putem se jos jednom zahvaljujem kolegi Davidu :)
void initialize(GLuint names[]);

//Iscrtavanje trave
void trava(GLuint names[]);

//Funkcija koja vrsi ispis teksta u prostoru,
//koristi se za ispis broja preostalih klikova potrebnih 
//da bi se povrce skroz uvuklo pod zemlju
void ispis_teksta(float x, float y,std::string s,int opcija);

//Ispisuje tekst koji je fiksiran u prozoru (broj osvojenih poena, preostalo vreme)
//Funkcija prima tekst, koordinate pozicije i opciju(kojim fontom ce tekst biti ispisan)
void ispis_fiksiranog_teksta(std::string s,float x,float y,int opcija,int window_height,int window_width);

//Preuzeto sa:
//https://community.khronos.org/t/drawing-a-circle-filled-using-gl-lines/74955/2
//Uz nekoliko manjih modifikacija (tad jos nisam znao da nacrtam krug)
void drawCircle(float r, float x, float y);

void iscrtaj_sargarepu(const sargarepa& s,int pecurka_pokrenut, int pecurka_parametar);
void iscrtaj_rotkvicu(const rotkvica& r,int pecurka_pokrenut, int pecurka_parametar);
void iscrtaj_pecurku(const pecurka& p);

//Kod takodje preuzet od kolege Davida
//Uz neke izmene
//Iscrtavanje slike 'Game over' u slucaju da je igrac izgubio
void show_game_over(GLuint names[], int window_height, int window_width);

//Iscrtavanje slike you win u slucaju da je igrac pobedio
void show_game_won(GLuint names[], int window_height, int window_width);

//Iscrtavamo zbunje i drvo
void zbunje_i_drvo(int pecurka_pokrenut, int pecurka_parametar);