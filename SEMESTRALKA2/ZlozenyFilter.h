#pragma once
#include "Filter.h"
#include "structures/list/array_list.h"

using namespace structures;

template <typename K, typename T>
class ZlozenyFilter {
private:
	ArrayList<UniverzalnyFilter<T>*> *filtre; 
public:
	bool splnaFilter(T o)		
	{
		for (auto f : *filtre)
		{
			if (f->Prislusnost())
			{
				if (!f->splnaFilter(o, true))	
				{
					return false;
				}
			}
			else
			{
				if (!f->splnaFilter(o))	
				{
					return false;
				}
			}
		}
		return true;
	}

	ZlozenyFilter()
	{
		filtre = new ArrayList<UniverzalnyFilter<T>*>();
	};

	~ZlozenyFilter()
	{
		filtre->clear();
		delete filtre;
		filtre = nullptr;
	}
	void pridajFilter(UniverzalnyFilter<T>* novy)
	{
		filtre->add(novy);
	}

	void vyfiltrujTabulku(SortedSequenceTable<K, T>* t, UnsortedSequenceTable<K, T>* cistaTab)
	{
		for (auto ti : *t)
		{
			if (splnaFilter(ti->accessData()))
			{
				cistaTab->insert(ti->getKey(), ti->accessData());
			}
		}
	}

	void vyfiltrujTabulku(BytovaJednotka* t, ArrayList<T>* cistaTab)
	{
		for (int i = 0; i < constants::POCET_BJ; i++)
		{
			if (splnaFilter(&(t[i])))
			{
				cistaTab->add(&(t[i]));
			}
		}
	}

	void vyfiltrujTabulku(BytovaJednotka* t, BytovaJednotka b [], int & pocet)
	{
		for (int i = 0; i < constants::POCET_BJ; i++)
		{
			if (splnaFilter(&t[i]))
			{
				b[pocet] = t[i];
				pocet++;
			}
		}
	}

};