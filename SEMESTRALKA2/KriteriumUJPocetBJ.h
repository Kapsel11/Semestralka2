#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJPocetBJ : public KriteriumUJ<int>
{
public:
	KriteriumUJPocetBJ() { typ = KRIT_UJ_POCET_BJ; };
	int ohodnot(UzemnaJednotka* u) { return u->getSumPocetBJ(); };
};