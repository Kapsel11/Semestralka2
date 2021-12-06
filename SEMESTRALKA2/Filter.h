#pragma once
#include "Kriterium.h"
#include "UniverzalnyFilter.h"

using namespace structures;

template<typename K, typename T, typename V>
class Filter : public UniverzalnyFilter<T> {
protected:
	Kriterium<V, T> *kriterium; // T V ?? V T
public:
	//Filter(Kriterium<T, V> kriterium);
	virtual bool splnaFilter(T o, bool prislusnost = false) = 0;
	/*void vyfiltrujTabulku(SortedSequenceTable<K, T> *t, UnsortedSequenceTable<K, T> *cistaTab)
	{ 
		for (auto ti : *t)
		{
			if (splnaFilter(ti->accessData()))
			{
				cistaTab->insert(ti->getKey(), ti->accessData());
			}
		}
	};*/
	Kriterium<V, T>* getKriterJUM() { return kriterium; };
};