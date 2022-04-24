#include "mole.hpp"

mole::mole(float x, float y) {
	cx = x;
	cz = y;
}

void mole::iscrtaj() {
	// Ne zelimo da bude osvetljen,zbog boljeg kontrasta
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glColor3f(0.41, 0.29, 0.18);

	glBegin(GL_POLYGON);
	glVertex3f(cx + 0.05, 0.501, cz + 0.05);
	glVertex3f(cx - 0.05, 0.501, cz + 0.05);
	glVertex3f(cx - 0.05, 0.501, cz - 0.05);
	glVertex3f(cx + 0.05, 0.501, cz - 0.05);
	glEnd();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

auto mole::x() const -> float {
	return cx;
}

auto mole::z() const -> float {
	return cz;
}

void mole::pomeri_levo() {
	if (cx > -1.4 && otkljucano)
		cx += -0.05;
}

void mole::pomeri_desno() {
	if (cx < 1.4 && otkljucano)
		cx += 0.05;
}

void mole::pomeri_gore() {
	if (cz > -1.4 && otkljucano)
		cz += -0.05;
}

void mole::pomeri_dole() {
	if (cz < 1.45 && otkljucano)
		cz += 0.05;
}

void mole::pomeri_gore_levo() {
	pomeri_gore();
	pomeri_levo();
}

void mole::pomeri_gore_desno() {
	pomeri_gore();
	pomeri_desno();
}

void mole::pomeri_dole_levo() {
	pomeri_dole();
	pomeri_levo();
}

void mole::pomeri_dole_desno() {
	pomeri_dole();
	pomeri_desno();
}

void mole::zakljucaj() {
	otkljucano = false;
}

void mole::otkljucaj() {
	otkljucano = true;
}

auto mole::provera_otkljucano() -> bool {
	return otkljucano;
}

void mole::uvecaj_poene(int broj_poena) {
	m_poeni += broj_poena;
}

auto mole::poeni() const -> int {
	return m_poeni;
}