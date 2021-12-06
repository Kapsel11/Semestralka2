#pragma once
#include "Filter.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"

template <typename K, typename T, typename V>
class FilterPodlaHodnoty : public Filter<K, T, V>
{
private:
	V hodnota;
	KriteriumUJPrislusnost* kriterium_pris = nullptr;
	std::string vyssiCelok;
	bool aplikovat;
public:
	bool splnaFilter(T o, bool prislusnost = false) 
	{ 
		if (aplikovat)
		{
			if (prislusnost == false)
				return  this->kriterium->ohodnot(o) == hodnota;
			else
			{
				return this->kriterium_pris->ohodnot(o, vyssiCelok);
			}
		}
		else
		{
			return true;
		}
		
	};

	FilterPodlaHodnoty(Kriterium<V, T> *kriterium, V h, bool aplikovat)
	{
		this->kriterium = kriterium;
		hodnota = h;
		this->prislusnost = false;
		this->aplikovat = aplikovat;
	};

	FilterPodlaHodnoty(KriteriumUJPrislusnost* kriterium, V h, bool aplikovat, std::string vyssiCelok)
	{
		//this->kriterium = kriterium;
		kriterium_pris = kriterium;
		hodnota = h;
		this->vyssiCelok = vyssiCelok;
		this->prislusnost = true;
		this->aplikovat = aplikovat;
	}

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

};