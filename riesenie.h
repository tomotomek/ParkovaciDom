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
	bool nacitajZoSuboru(const string &nazov);
};
#endif
