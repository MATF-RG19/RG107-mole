#include "igra.hpp"

void kraj_igre(mole &krtica,
			   coveculjak &cikica1,
			   coveculjak &cikica2,
			   int &vreme_pokrenut,
			   int &pecurka_pokrenut,
			   bool &igra_zavrsena) {
	krtica.zakljucaj();
	cikica1.stani();
	cikica2.stani();
	vreme_pokrenut = 0;
	pecurka_pokrenut = 0;

	igra_zavrsena = true;
}

void izgubio_si(mole &krtica,
				coveculjak &cikica1,
				coveculjak &cikica2,
				int &vreme_pokrenut,
				int &pecurka_pokrenut,
				bool &igra_zavrsena,
				GLuint names[],
				int window_height,
				int window_width) {
	kraj_igre(krtica, cikica1, cikica2, vreme_pokrenut, pecurka_pokrenut,
			  igra_zavrsena);
	glColor3f(1.0, 1.0, 1.0);
	// ispis_fiksiranog_teksta("KRAJ IGRE",350,350,1);
	show_game_over(names, window_height, window_width);
}

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
				int vreme) {
	bool a = true;

	if (sargarepice.size() > 1) {
		for (unsigned i = 0; i < sargarepice.size(); i++)
			if (!sargarepice[i].pojedena())
				a = false;
	}

	if (rotkvice.size() > 1) {
		for (unsigned i = 0; i < rotkvice.size(); i++)
			if (!rotkvice[i].pojedena())
				a = false;
	}

	if (a && vreme > 0) {
		kraj_igre(krtica, cikica1, cikica2, vreme_pokrenut, pecurka_pokrenut,
				  igra_zavrsena);

		show_game_won(names, window_height, window_width);
		glColor3f(1, 1, 1);
		std::string p = "Osvojeno poena:";
		ispis_fiksiranog_teksta(p, 300, 300, 0, window_height, window_width);
		ispis_fiksiranog_teksta(std::to_string(krtica.poeni()), 440, 300, 0,
								window_height, window_width);
	}
}
