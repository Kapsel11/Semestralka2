#pragma once

#include "Constants.h"
#include "UzemnaJednotka.h"
#include "BytovaJednotka.h"
#include "TriediacaStrukutra.h"
#include "structures/table/sorted_sequence_table.h"
//#include "Obce.h"
#include "csv.h"


class Loader {
public:
	void LoadData(UzemnaJednotka *jednotky, TriediacaStruktura<UzemnaJednotka*, constants::POCET_UJ>* t, structures::SortedSequenceTable<std::string, UzemnaJednotka*>* s);
};

void Loader::LoadData(UzemnaJednotka* jednotky, TriediacaStruktura<UzemnaJednotka*, constants::POCET_UJ >* t, structures::SortedSequenceTable<std::string, UzemnaJednotka*>* s)
{
	io::CSVReader < 6, io::trim_chars<>, io::no_quote_escape <';'>> in("1_Obce_SR.csv");
	io::CSVReader < 3, io::trim_chars<>, io::no_quote_escape <';'>> an("2_Územné_èlenenie_SR.csv");
	in.read_header(io::ignore_extra_column, "Obec", "a", "b", "c", "d", "e");
	an.read_header(io::ignore_extra_column, "a", "b", "c");
	std::string okres, kraj;
	std::string nazov;
	int preProObyv;
	int proObyv;
	int poProObyv;
	long long vymera;
	long long zastavPlocha;
	UzemnaJednotka pom;
	int i = 0;
	while (in.read_row(nazov, preProObyv, proObyv, poProObyv, vymera, zastavPlocha))
	{
		an.read_row(nazov, okres, kraj);
		jednotky->nazov = nazov;
		jednotky->preProObyv = preProObyv;
		jednotky->proObyv = proObyv;
		jednotky->poProObyv = poProObyv;
		jednotky->vymera = vymera;
		jednotky->zastavPlocha = zastavPlocha;
		jednotky->okres = okres;
		jednotky->kraj = kraj;
		jednotky->stat = &constants::slovensko;
		jednotky->typUJ = OBEC;
		s->insert(nazov, jednotky);
		t->nastavIndex(i, jednotky);
		i++;
		jednotky++;
	}

	io::CSVReader < 2, io::trim_chars<>, io::no_quote_escape <';'>> okres_kraj("2_Územné_èlenenie_SR_Okresy.csv");
	okres_kraj.read_header(io::ignore_extra_column, "a", "b");
	int pocet_okresov = 0, pocet_krajov = 0;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*> okre;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*> kra;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* okresy = &okre;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* kraje = &kra;

	while (okres_kraj.read_row(okres, kraj))
	{
		bool vloz_okres = false;
		bool vloz_kraj = false;

		if (okresy->containsKey(okres))
		{
			vloz_okres = false;
		}
		else {
			jednotky->okres = okres;
			jednotky->kraj = kraj;
			jednotky->stat = &constants::slovensko;
			okresy->insert(okres, jednotky);
			s->insert(okres, jednotky);
			t->nastavIndex(i, jednotky);
			i++;
			jednotky++;
		}

		if (kraje->containsKey(kraj))
		{
			vloz_kraj = false;
		}
		else {
			jednotky->okres = kraj;
			jednotky->kraj = kraj;
			jednotky->stat = &constants::slovensko;
			kraje->insert(kraj, jednotky);
			s->insert(kraj, jednotky);
			t->nastavIndex(i, jednotky);
			i++;
			jednotky++;
		}

	}
	// Okresy
	for (auto i : *okresy)
	{
		i->accessData()->typUJ = OKRES;
		i->accessData()->nazov = i->getKey();
		for (auto* ti : *s)
		{
			if (ti->accessData()->okres == i->getKey() && ti->accessData() != i->accessData())
			{
				i->accessData()->poProObyv += ti->accessData()->poProObyv;
				i->accessData()->preProObyv += ti->accessData()->preProObyv;
				i->accessData()->proObyv += ti->accessData()->proObyv;
				i->accessData()->vymera += ti->accessData()->vymera;
				i->accessData()->zastavPlocha += ti->accessData()->zastavPlocha;
			}
		}
	}

	// Kraje
	for (auto i : *kraje)
	{
		i->accessData()->typUJ = KRAJ;
		i->accessData()->nazov = i->getKey();
		for (auto* ti : *okresy)
		{
			if (ti->accessData()->kraj == i->getKey() && ti->accessData() != i->accessData())
			{
				i->accessData()->poProObyv += ti->accessData()->poProObyv;
				i->accessData()->preProObyv += ti->accessData()->preProObyv;
				i->accessData()->proObyv += ti->accessData()->proObyv;
				i->accessData()->vymera += ti->accessData()->vymera;
				i->accessData()->zastavPlocha += ti->accessData()->zastavPlocha;
			}
		}
	}

	jednotky->kraj = constants::slovensko;
	jednotky->okres = constants::slovensko;
	jednotky->nazov = constants::slovensko;
	jednotky->stat = &constants::slovensko;
	jednotky->typUJ = SLOVENSKO;
	// SLovensko
	for (auto i : *kraje)
	{
		jednotky->kraj = constants::slovensko;
		jednotky->okres = constants::slovensko;
		jednotky->nazov = constants::slovensko;
		jednotky->stat = &constants::slovensko;
		jednotky->proObyv += i->accessData()->proObyv;
		jednotky->poProObyv += i->accessData()->poProObyv;
		jednotky->preProObyv += i->accessData()->preProObyv;
		jednotky->zastavPlocha += i->accessData()->zastavPlocha;
		jednotky->vymera += i->accessData()->vymera;
	}
	s->insert(jednotky->nazov, jednotky);
	t->nastavIndex(i, jednotky);

	jednotky++;

	std::string machara, drevo;
	int pole[constants::POCET_BJ];
	int riadok = 0;
	int stlpec = 0;
	int pep = 0;
	io::CSVReader <13, io::trim_chars<>, io::no_quote_escape <';'>> fen("4_Bytové_jednotky_SR3.csv");
	fen.read_header(io::ignore_extra_column, "z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l");
	while (fen.read_row(nazov, machara, drevo, pole[stlpec++], pole[stlpec++], pole[stlpec++], pole[stlpec++], pole[stlpec++], pole[stlpec++],
		pole[stlpec++], pole[stlpec++], pole[stlpec++], pole[stlpec++]))
	{
		if (stlpec == constants::POCET_BJ )
		{
			s->operator[](nazov)->nastavBJ(pole);
			stlpec = 0;
		}
	}

		// Okresy

	for (auto i : *okresy)
	{
		for (auto* ti : *s)
		{
			if (ti->accessData()->okres == i->getKey() && ti->accessData() != i->accessData())
			{
				for (int j = 0; j < constants::POCET_BJ; j++)
				{
					i->accessData()->BJ[j].pocet += ti->accessData()->BJ[j].pocet;
				}
			}
		}
		i->accessData()->nastavBJ(nullptr, false);
	}
	// Kraje
	for (auto i : *kraje)
	{
		for (auto* ti : *okresy)
		{
			if (ti->accessData()->kraj == i->getKey() && ti->accessData() != i->accessData())
			{
				for (int j = 0; j < constants::POCET_BJ; j++)
				{
					i->accessData()->BJ[j].pocet += ti->accessData()->BJ[j].pocet;
				}
			}
		}
		i->accessData()->nastavBJ(nullptr, false);
	}

	jednotky--;
	// SLovensko
	for (auto i : *kraje)
	{
		for (int j = 0; j < constants::POCET_BJ; j++)
		{
			jednotky->BJ[j].pocet += i->accessData()->BJ[j].pocet;

		}

		jednotky->nastavBJ(nullptr, false);
	}
	jednotky++;

}