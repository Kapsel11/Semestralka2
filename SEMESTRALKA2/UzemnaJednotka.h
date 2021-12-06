#pragma once
#include "TypUzemnejJednotky.h"
#include <iostream>
#include "structures/list/array_list.h"
#include "BytovaJednotka.h"

//using namespace structures;

class UzemnaJednotka
{
protected:
	TypUzemnejJednotky typUJ;
	BytovaJednotka BJ[constants::POCET_BJ];
	std::string okres;
	std::string kraj;
	std::string* stat;
	std::string nazov;
	int preProObyv;
	int proObyv;
	int poProObyv;
	long long vymera;
	long long zastavPlocha;
	int riadok;
	int stlpec;
	int pocetBJ;
	int pocet;
	int sumPocetBJ;
public:
	UzemnaJednotka() 
{
		sumPocetBJ = 0;
		typUJ = OBEC;
		pocet = 0;
		 pocetBJ = 0;
		 stlpec = 0;
		 riadok = 0;
		 preProObyv = 0;
		 proObyv = 0;
		 poProObyv = 0;
		 vymera = 0;
		 zastavPlocha = 0;
	};
	UzemnaJednotka(std::string nazov, int preProObyv, int proObyv, int poProObyv, long vymera, long zastavPlocha)
	{
		riadok = 0;
		stlpec = 0;
		this->nazov = nazov;
		this->preProObyv = preProObyv;
		this->proObyv = proObyv;
		this->poProObyv = poProObyv;
		this->vymera = vymera;
		this->zastavPlocha = zastavPlocha;
	}
	BytovaJednotka* getBJ() { return BJ; };
	std::string getNazov() { return nazov; };
	TypUzemnejJednotky getTypUJ() { return typUJ; };
	int getPocetPreProdObyv() { return preProObyv; };
	int getPocetProObyv() { return proObyv; };
	int getPocetPoProObyv() { return poProObyv; };
	long long getVymera() { return vymera; };
	long long getZastavPlocha() { return zastavPlocha; };
	friend std::ostream& operator<<(std::ostream& os, const UzemnaJednotka& o);
	//void VypisUJaBJ();
	bool getPatriDoVyssiehoCelku(std::string vyssiCelok)
	{
		return (vyssiCelok == okres || vyssiCelok == kraj || vyssiCelok == *stat);
	};
	friend class Loader;

	void nastavBJ(int arr [constants::POCET_BJ], bool spec = true)
	{
		int i = 1;
		for (int j = 0; j < 550; j++)
		{
			BJ[j].nazovUJ = &nazov;
			if(spec)
			BJ[j].pocet = arr[j];
			BJ[j].pocetIzieb = (j % 10) + 1;
		}

		BJ[0].pocetOsob = 1;

		 i = 0;
		 int f = 0;
		for (int j = 0; j < 5; j++)
		{
			for (; f < 10; i++,f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 1;
			}
			for (; f < 20; i++,f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 2;
			}
			for (; f < 30;  i++,f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 3;
			}
			for (; f < 40; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 4;
			}
			for (; f < 50; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 5;
			}
			for (; f < 60; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 6;
			}
			for (; f < 70; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 7;
			}
			for (; f < 80; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 8;
			}
			for (; f < 90; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 9;
			}
			for (; f < 100; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 10;
			}
			for (; f < 110; i++, f++)
			{
				BJ[i].typ = &constants::stringy_BJ[j];
				BJ[i].pocetOsob = 11;
			}
			f = f - 110;
		}
	};

	void scitajBJ(double arr[constants::POCET_BJ])
	{
		for (int j = 0; j < constants::POCET_BJ; j++)
		{
			BJ[j].pocet += arr[j];
		}
	}
	void setSumPocetBJ(int f)
	{
		sumPocetBJ = f;
	}
	int getSumPocetBJ()
	{
		return sumPocetBJ;
	}

	std::string getTypUJnaString()
	{
		if (typUJ == OBEC)
		{
			return "Obec";
		}
		else if (typUJ == OKRES)
		{
			return "Okres";
		}
		else if (typUJ == KRAJ)
		{
			return "Kraj";
		}
		else
		{
			return "Slovensko";
		}
	}
};

std::ostream& operator<<(std::ostream& os, const UzemnaJednotka& o) {
	os << o.nazov << "---> pocet preproduktivnych obyvatelov: " << o.preProObyv << " pocet produktivnych obyvatelov: " 
		<< o.proObyv << " pocet poproduktivnych obyvatelov: " << o.poProObyv << " vymera: " << o.vymera
		<< " zastavana plocha: " << o.zastavPlocha << std::endl;
	return os;
}



