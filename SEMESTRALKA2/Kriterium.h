#pragma once
#include "TypKriteria.h"

template<typename T, typename O>
class Kriterium {
protected:
	TypKriteria typ;
public:
	TypKriteria getKriterium() { return typ; };
	virtual T ohodnot(O o) = 0;
};