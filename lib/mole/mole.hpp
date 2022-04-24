#ifndef __MOLE__
#define __MOLE__

#include <GL/glut.h>

class mole {
  public:
	mole(float x, float y);

	// Iscrtavanje kvadrata koji predstavlja krticu
	void iscrtaj();

	// Naredni metodi sluze za pomeranje krtice po postolju
	// Pokrecu se iz on_keyboard funkcije tasterima w,s,a,d,
	// kao i q,e,z,c, za pomeranje ukoso

	float x() const;
	float z() const;

	void pomeri_levo();
	void pomeri_desno();
	void pomeri_gore();
	void pomeri_dole();

	void pomeri_gore_levo();
	void pomeri_gore_desno();
	void pomeri_dole_levo();
	void pomeri_dole_desno();

	void zakljucaj();
	void otkljucaj();
	bool provera_otkljucano();

	void uvecaj_poene(int broj_poena);
	int poeni() const;

  private:
	// Koordinate centra kvadrata koji predstavlja krticu
	float cx, cz;
	// Broj osvojenih poena
	int m_poeni = 0;
	// Indikator da li je krtica trenutno "zakljucana",
	// odnosno da li se uhvatila za neko povrce
	bool otkljucano = true;
};

#endif