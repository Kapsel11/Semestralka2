#pragma once

class BytovaJednotka 
{
private:
	std::string *typ;
	std::string* nazovUJ;
	int pocetOsob;
	int pocetIzieb;
	int pocet;
public:
	std::string getTyp() { return *typ; };
	int getPoceOsob() { return pocetOsob; };
	int getPocetIzieb() { return pocetIzieb; }
	int getPocet() { return pocet; };
	std::string getNazovUJ() { return *nazovUJ; };
	friend class Loader;
	friend class UzemnaJednotka;
};