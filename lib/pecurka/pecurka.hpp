#ifndef __PECURKA__
#define __PECURKA__

#include "mole.hpp"

#include <time.h>
#include <utility>

class pecurka {
  private:
	// Koordinate pecurke
	float poz_x, poz_y, poz_z;
	// Broj preostalih koraka potrebnih da se pecurka uvuce
	int m_preostalo_koraka;

  public:
	mole *m_krtica = new mole(0, 0);
	explicit pecurka(mole *krtica);

	bool uvuci();

	float granica = 0.1;
	// Provera da li je krtica dovoljno blizu pecurki da moze da se
	// uhvati za nju i da je uvuce
	bool poklapaju_se_koordinate() const;
	bool pojedena() const;

	// Provera da li je krtica trenutno zakacena na pecurku
	bool trenutno_zakljucana() const;

	int preostalo_koraka() const;
	float x() const;
	float y() const;
	float z() const;

	std::pair<float, float> get_koordinate() const;
};

#endif