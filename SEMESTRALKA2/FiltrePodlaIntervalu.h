#pragma once
#include "Filter.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"


template <typename K, typename T, typename V>
class FilterPodlaIntervalu : public Filter<K, T, V>
{
private:
	KriteriumUJPrislusnost* kriterium_pris = nullptr;
	std::string vyssiCelok;
	bool aplikovat;
	V min;			// NaSTAVIT ESTE
	V max;
public:
	bool splnaFilter(T o, bool prislusnost = false)
	{
		if (aplikovat)
		{
			if (prislusnost == false)
			{
				V hodnota = this->kriterium->ohodnot(o);
				return hodnota >= min && hodnota <= max;
			}
			else
			{
				this->kriterium_pris->ohodnot(o, vyssiCelok);
			}
		}
		else
		{
			return true;
		}
		//return this->kriterium->ohodnot(o) >= min && this->kriterium->ohodnot(o) <= max;
	};
	void vyfiltrujTabulku(SortedSequenceTable<K, T>* t, UnsortedSequenceTable<K, T>* cistaTab, bool prislusnost = false)
	{
		for (auto ti : *t)
		{
			if (prislusnost == true)
			{
				if (splnaFilter(ti->accessData(), true))
				{
					cistaTab->insert(ti->getKey(), ti->accessData());
				}
			}
			else
			{
				if (splnaFilter(ti->accessData()))
				{
					cistaTab->insert(ti->getKey(), ti->accessData());
				}
			}
		}
	};
	FilterPodlaIntervalu(Kriterium<V, T>* krit, V min, V max, bool aplikovat);
	FilterPodlaIntervalu(KriteriumUJPrislusnost* kriterium, V min, V max, bool aplikovat, std::string vyssiCelok);
};

template <typename K, typename T, typename V>
FilterPodlaIntervalu<K, T, V>::FilterPodlaIntervalu(Kriterium<V, T>* krit, V min, V max, bool aplikovat)
{
	this->kriterium = krit;
	this->min = min;
	this->max = max;
	this->prislusnost = false;
	this->aplikovat = aplikovat;
}

template <typename K, typename T, typename V>
FilterPodlaIntervalu<K, T, V>::FilterPodlaIntervalu(KriteriumUJPrislusnost* krit, V min, V max, bool aplikovat, std::string vyssiCelok)
{
	this->kriterium = krit;
	this->min = min;
	this->max = max;
	this->prislusnost = true;
	this->aplikovat = aplikovat;
}


