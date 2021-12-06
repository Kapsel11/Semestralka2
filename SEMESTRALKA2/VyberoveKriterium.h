#pragma once
#include "Filter.h"
#include "structures/table/unsorted_sequence_table.h"

template <typename K, typename T, typename V>
class VyberoveKriterium : public Filter<K, T, V>
{
private:
	bool aplikovat;
public:
	bool splnaFilter(T o, bool prisluslusnost = false)
	{
		if (aplikovat)
		{
			return true;
		}
	};
	VyberoveKriterium(bool aplikovat)
	{
		this->aplikovat = aplikovat;
	}

	K* najdiMax(K * jednotky, int pocet, Kriterium<V, T>* kriterium)
	{
		if (pocet != 0)
		{
			if (pocet == 1)
				return jednotky;

			K* max = jednotky;

			for (int i = 1; i < pocet; i++)
			{
				jednotky++;
				if (kriterium->ohodnot(max) < kriterium->ohodnot(jednotky))
				{
					max = jednotky;
				}
			}
			return max;
		}
		else
			return 0;
	};

	K* najdiMin(K* jednotky, int pocet, Kriterium<V, T>* kriterium)
	{
		if (pocet != 0)
		{
			if (pocet == 1)
				return jednotky;

			K* min = jednotky;

			for (int i = 1; i < pocet; i++)
			{
				jednotky++;
				if (kriterium->ohodnot(min) > kriterium->ohodnot(jednotky))
				{
					min = jednotky;
				}
			}
			return min;
		}
		else
			return 0;
	};
};