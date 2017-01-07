#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//#include "riesenie.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
class AUTO {
	char *spzAuta = nullptr;
	char *casPrijazdu = nullptr;
public:
	AUTO(const char *spzAuta, const char *casPrijazdu);
	~AUTO() {
		if (spzAuta != nullptr) {
			delete[] spzAuta;
			spzAuta = nullptr;
		}
		if (casPrijazdu != nullptr) {
			delete[] casPrijazdu;
			casPrijazdu = nullptr;
		}
	}
	void vlozSpz(const char *spz);
	void vlozCas(const char *cas);
	const char *spz() const;
	const char *cas() const;
};
class PARKOVACIE_MIESTO {
	AUTO car;
	bool obsadenost;
	//2.uloha
	enum typMiesta { Vsetci, Vozickar };
	typMiesta typ;
public:
	//1.uloha
	PARKOVACIE_MIESTO();
	~PARKOVACIE_MIESTO();
	bool getObsadeneMiesto() const { return obsadenost; };
	bool zaparkujAuto(const char *spz, const char *cas);
	bool vyparkujAuto();
	const char *spzAuta() const;
	const char *casPrijazdu() const;
	//2.uloha
	void nastavTypMiesta(const char *typ);
	const char *getTypMiesta() const;
};
//3.uloha
class PARKOVISKO {
	int pocetPoschodi;
	int pocetMiestNaPoschodi;
	PARKOVACIE_MIESTO **miesta;
public:
	PARKOVISKO(int poschodia, int sirka, int dlzka);
	~PARKOVISKO();
	int pocetVsetkychMiest() const;
	int pocetMiest(const char *typ) const;
	int pocetVolnychMiest(const char *typ) const;
	//4.uloha
	bool zparkujAuto(const char *spz, const char *cas, const char *typIzby);
	char *zoznamAut(char *spzAut) const;
	//5.uloha
	int vyparkujAuto(const char *priezviskoMeno, const char *casVyjazdu);
	int zaplat(const char *casVjazdu, const char *casVyjazdu);
	//6.uloha
	bool nacitajZoSuboru(const string &nazov);
};
#endif

const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";
const int DUMMY_INT = -1;

//pomocna fcia
string zmenZaMedzeru(string cas) {
	int lenth = cas.size();
	for (unsigned int i = 0; i < lenth; i++) {
		if (cas[i] == ':') {
			cas[i] = ' ';
		}
	}
	return cas;
}
int indexDna(const int rok, const int mesiac, const int den) {
	int posun = 0;
	int index = den;
	if (mesiac > 2) {
		if (rok % 4 == 0) { posun = -1; }
		else { posun = -2; }
	}
	index += (mesiac - 1) * 30 + (mesiac / 2) + posun;
	return index;
}
double prepocetNaHodiny(double hod, double min, double sec) {
	return (hod + min / 60 + sec / 3600);
}

//1.uloha
AUTO::AUTO(const char *spzAuta, const char *casPrijazdu) {
	vlozSpz(spzAuta);
	vlozCas(casPrijazdu);
}
void AUTO::vlozSpz(const char *spz) {
	if (spz == nullptr) {
		spzAuta = nullptr;
	}
	else {
		char *vysl = new char[strlen(spz)+1];
		for (unsigned int i = 0; i < strlen(spz); i++) {
			vysl[i] = spz[i];
			vysl[i + 1] = '\0';
		}
		spzAuta = vysl;
	}
}
void AUTO::vlozCas(const char *cas) {
	if (cas == nullptr) {
		casPrijazdu = nullptr;
	}
	else {
		char *vysl = new char[strlen(cas)+1];
		for (unsigned int i = 0; i < strlen(cas); i++) {
			vysl[i] = cas[i];
			vysl[i + 1] = '\0';
		}
		casPrijazdu = vysl;
	}
}
const char *AUTO::cas() const {
	if (casPrijazdu == nullptr) {
		return "nezadane";
	}
	return casPrijazdu;
}
const char *AUTO::spz() const {
	if (spzAuta == nullptr) {
		return "nezadane";
	}
	return spzAuta;
}


PARKOVACIE_MIESTO::PARKOVACIE_MIESTO() : car(nullptr, nullptr) {
	obsadenost = false;
	typ = Vsetci;
}
PARKOVACIE_MIESTO::~PARKOVACIE_MIESTO() {
}
bool PARKOVACIE_MIESTO::zaparkujAuto(const char *spz, const char *cas) {
	car.vlozSpz(spz);
	car.vlozCas(cas);
	auto m = car.spz();
	if (!obsadenost && m != "nezadane") {
		obsadenost = true;
		return true;
	}
	return false;
}
const char *PARKOVACIE_MIESTO::spzAuta() const {
	if (car.spz() != "nezadane") {
		return car.spz();
	}
	return "";
}
const char *PARKOVACIE_MIESTO::casPrijazdu() const {
	if (car.cas() != "nezadane") {
		return car.cas();
	}
	return "";
}
bool PARKOVACIE_MIESTO::vyparkujAuto() {
	if (obsadenost) {
		car.vlozSpz(nullptr);
		car.vlozCas(nullptr);
		obsadenost = false;
		return true;
	}
	return false;
}
//2.uloha
const char *PARKOVACIE_MIESTO::getTypMiesta() const {
	if (typ == Vozickar) {
		return "Vozickar";
	}
	return "Vsetci";
}
void PARKOVACIE_MIESTO::nastavTypMiesta(const char *typMiesta) {
	if (typMiesta == "Vozickar") {
		typ = Vozickar;
	}
	else {
		typ = Vsetci;
	}
}
//3.uloha
PARKOVISKO::PARKOVISKO(int poschodia, int sirka, int dlzka) {
	if (poschodia < 1 || sirka < 1 || dlzka < 1) {
		pocetPoschodi = 0;
		pocetMiestNaPoschodi = 0;
	}
	else {
		pocetPoschodi = poschodia;
		pocetMiestNaPoschodi = sirka*dlzka;
		miesta = new PARKOVACIE_MIESTO*[poschodia];
		for (unsigned int i = 0; i < poschodia; i++) {
			miesta[i] = new PARKOVACIE_MIESTO[pocetMiestNaPoschodi];
		}
		for (unsigned int i = 0; i < poschodia; i++) {
			for (unsigned int j = 0; j < pocetMiestNaPoschodi; j++) {
				if (j < sirka) {
					miesta[i][j].nastavTypMiesta("Vozickar");
				}
			}
		}
	}
}
PARKOVISKO::~PARKOVISKO() {
	if (miesta == nullptr) {
		for (unsigned int i = 0; i < pocetPoschodi; i++) {
			delete[] miesta[i];
		}
		delete[] miesta;
	}
}
int PARKOVISKO::pocetVsetkychMiest() const {
	return pocetPoschodi * pocetMiestNaPoschodi;
}
int PARKOVISKO::pocetMiest(const char *typ) const {
	int pocet = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetMiestNaPoschodi; j++) {
			if (miesta[i][j].getTypMiesta() == typ) {
				pocet++;
			}
		}
	}
	return pocet;
}
int PARKOVISKO::pocetVolnychMiest(const char *typ) const {
	int pocet = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetMiestNaPoschodi; j++) {
			if (miesta[i][j].getTypMiesta() == typ && !miesta[i][j].getObsadeneMiesto()) {
				pocet++;
			}
		}
	}
	return pocet;
}
//4.uloha

bool PARKOVISKO::zparkujAuto(const char *spz, const char *cas, const char *typ) {
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetMiestNaPoschodi; j++) {
			string tmp = { typ };
			if (miesta[i][j].getTypMiesta() == tmp && !miesta[i][j].getObsadeneMiesto()) {
				miesta[i][j].zaparkujAuto(spz, cas);
				return true;
			}
		}
	}
	
	return false;
}
char *PARKOVISKO::zoznamAut(char *spz) const {
	if (spz == nullptr) {
		return "";
	}
	spz[0] = '\0';
	int pocetObsadenych = 0, zaznacene = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetMiestNaPoschodi; j++) {
			if (miesta[i][j].getObsadeneMiesto()) {
				pocetObsadenych++;
			}
		}
	}
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetMiestNaPoschodi; j++) {
			if (miesta[i][j].getObsadeneMiesto()) {
				if (zaznacene == pocetObsadenych-1) {
					strcat(spz, miesta[i][j].spzAuta());
				}
				else {
					strcat(spz, miesta[i][j].spzAuta());
					strcat(spz, ", ");
					zaznacene++;
				}
			}
		}
	}
	return spz;
}

//5.uloha
int PARKOVISKO::zaplat(const char *casVjazdu, const char *casVyjazdu){
	string in = zmenZaMedzeru(casVjazdu);
	string out = zmenZaMedzeru(casVyjazdu);
	stringstream vjazd(in);
	stringstream vyjazd(out);
	int rok, mesiac, den, hodina, minuta, sekunda;
	int r, m, d, h, min, s;
	int hodinyNavyse = 0;
	if (vjazd >> rok >> mesiac >> den >> hodina >> minuta >> sekunda && vyjazd >> r >> m >> d >> h >> min >> s) {
		int indexDnaVjazdu = indexDna(rok, mesiac, den);
		double casVjazduVHodinach = prepocetNaHodiny(hodina, minuta, sekunda);
		int indexDnaVyjazdu = indexDna(r, m, d);
		double casVyjazduVHodinach = prepocetNaHodiny(h, min, s);
		double casDoKoncaDna = 24 - casVjazduVHodinach;
		int rozdielPoctuDni = (indexDnaVyjazdu + ((r - rok) * indexDna(rok, 12, 31)) - indexDnaVjazdu);
		if (rozdielPoctuDni > 0) {
			hodinyNavyse = (rozdielPoctuDni - 1) * 24 + casVyjazduVHodinach + casDoKoncaDna - 2;
		}
		else if ((casVyjazduVHodinach - casVjazduVHodinach) >= 3){
			hodinyNavyse = rozdielPoctuDni * 24 + (casVyjazduVHodinach - casVjazduVHodinach) - 2;
		}
		return hodinyNavyse*3;
	}
	
	return 0;
}
int PARKOVISKO::vyparkujAuto(const char *spz, const char *cas) {
	int doplat = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetMiestNaPoschodi; j++) {
			string tmp = { miesta[i][j].spzAuta() };
			if (tmp == spz) {
				doplat = zaplat(miesta[i][j].casPrijazdu(), cas);
				miesta[i][j].vyparkujAuto();
				return doplat;
			}
		}
	}
	return DUMMY_INT;
}
//6.uloha
bool PARKOVISKO::nacitajZoSuboru(const string &nazov) {
	ifstream inFile;
	string line;
	string spz, cas, typ;
	inFile.open(nazov);
	if (!inFile) {
		cout << "Nenasiel File" << endl;
		return false;
	}
	while (getline(inFile, line)) {
		if (line != "") {
			stringstream car(line);
			if (car >> spz >> cas >> typ) {
				zparkujAuto(spz.c_str(), cas.c_str(), typ.c_str());
			}
		}
	}
	inFile.close();
	return true;
}
