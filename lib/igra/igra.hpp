#ifndef __IGRA__
#define __IGRA__

#include "coveculjak.hpp"
#include "iscrtavanja.hpp"

#include <GL/glut.h>

// Funkcija zakljucava krticu i zaustavlja sve tajmere
void kraj_igre(mole &krtica,
			   coveculjak &cikica1,
			   coveculjak &cikica2,
			   int &vreme_pokrenut,
			   int &pecurka_pokrenut,
			   bool &igra_zavrsena);

// Funkcija koja zaustavlja igru u slucaju da je seljak uhvatio krticu
// Pokrece je coveculjak kada je uhvati
void izgubio_si(mole &krtica,
				coveculjak &cikica1,
				coveculjak &cikica2,
				int &vreme_pokrenut,
				int &pecurka_pokrenut,
				bool &igra_zavrsena,
				GLuint names[],
				int window_height,
				int window_width);

// Funkcija koja proverava da li je sve povrce pojedeno
// ukoliko jeste, igrac je pobedio
// VAZNO:Pecurka ne mora biti pojedena!!!
void pobedio_si(mole &krtica,
				coveculjak &cikica1,
				coveculjak &cikica2,
				int &vreme_pokrenut,
				int &pecurka_pokrenut,
				bool &igra_zavrsena,
				GLuint names[],
				int window_height,
				int window_width,
				const std::vector<sargarepa> &sargarepice,
				const std::vector<rotkvica> &rotkvice,
				int vreme);

#endif