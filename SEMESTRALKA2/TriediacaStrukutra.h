#pragma once

template <typename T, int pocetJednotiek>
class TriediacaStruktura {
private:
	T Jednotky[pocetJednotiek];
public:
	inline void nastavIndex(int index, T uj)
	{
		Jednotky[index] = uj;
	};

	T& operator[](int index)
	{
		return Jednotky[index];
	}

	void swap(int index1, int index2)
	{
		T c = Jednotky[index1];
		Jednotky[index1] = Jednotky[index2];
		Jednotky[index2] = c;
	}

	int size() 
	{
		return pocetJednotiek;
	}
};