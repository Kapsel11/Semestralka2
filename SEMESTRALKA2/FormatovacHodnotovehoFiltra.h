#pragma once
#include "FormatovacFiltra.h"
#include "FilterPodlaHodnoty.h"
#include "UzemnaJednotka.h"
#include "RegisterFormatovacov.h"
#include "FormatovacKriteria.h"

template <typename K, typename T, typename V>
class FormatovacHodnotovehoFiltra : public FormatovacFiltra<FilterPodlaHodnoty<K, T, V>>
{
private:
	TypKriteria typ;
public:
	FilterPodlaHodnoty<K, T, V>* pripravFilter(TypKriteria teep)
	{
		typ = teep;
		FilterPodlaHodnoty<K, T, V> filty;
		FilterPodlaHodnoty<K, T, V>* f = &filty;
		vypisFilter(f);
		nacitajHodnotyParametrov(f);

	};
protected:

	void vypisFilter(FilterPodlaHodnoty<K, T, V>* filter)
	{
		RegisterFormatovacov<Kriterium<std::string, UzemnaJednotka*>> ahoj;
		ahoj.dajMiFormatovacKriteria(typ)->pripravKriterium(filter->getKriterJUM());
	};

	void nacitajHodnotyParametrov(FilterPodlaHodnoty<K, T, V>* filter)
	{

	};
};