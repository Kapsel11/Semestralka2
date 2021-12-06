#pragma once
#include "structures/heap_monitor.h"
#include "Kriterium.h" 
#include "structures/table/unsorted_sequence_table.h"
#include "TriediacaStrukutra.h"

using namespace structures;

template<typename K, typename T, typename V>
class Triedenie {
private:
	void quick(int min, int max, UnsortedSequenceTable<K, T>* table, Kriterium<V, T>* krit, bool vzostupne);
public:
	void utried(TriediacaStruktura<T, constants::POCET_UJ>* t, Kriterium<V, T> * krit, bool vzostupne);
	void utried(UnsortedSequenceTable<std::string, UzemnaJednotka*>* t, Kriterium<V, T>* krit, bool vzostupne);
};



template<typename K, typename T, typename V>
void Triedenie<K, T, V>::utried(UnsortedSequenceTable<std::string, UzemnaJednotka*> *t, Kriterium<V, T>* krit, bool vzostupne)
{
	quick(0, t->size() - 1, t, krit, vzostupne);
}

template<typename K, typename T, typename V>
void Triedenie<K, T, V>::quick(int min, int max, UnsortedSequenceTable<K, T>* table, Kriterium<V, T>* krit, bool vzostupne)
{
	auto pivot = krit->ohodnot(table->getItemAtIndex((min + max) / 2).accessData());
	int left = min;
	int right = max;

	if (vzostupne)
	{
		do
		{
			while (krit->ohodnot(table->getItemAtIndex(left).accessData()) < pivot)
			{
				left++;
			}
			while (krit->ohodnot(table->getItemAtIndex(right).accessData()) > pivot)
			{
				right--;
			}
			if (left <= right)
			{
				table->swap(table->getItemAtIndex(left), table->getItemAtIndex(right));
				left++;
				right--;
			}
		} while (left <= right);
		if (min < right)
		{
			quick(min, right, table, krit, true);
		}
		if (left < max)
		{
			quick(left, max, table, krit, true);
		}
	}	
	else
	{
		do
		{
			while (krit->ohodnot(table->getItemAtIndex(left).accessData()) > pivot)
			{
				left++;
			}
			while (krit->ohodnot(table->getItemAtIndex(right).accessData()) < pivot)
			{
				right--;
			}
			if (left <= right)
			{
				table->swap(table->getItemAtIndex(left), table->getItemAtIndex(right));
				left++;
				right--;
			}
		} while (left <= right);
		if (min < right)
		{
			quick(min, right, table, krit, false);
		}
		if (left < max)
		{
			quick(left, max, table, krit, false);
		}
	}
}
