#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJPocetProdObyv: public KriteriumUJ<int>
{
public:
	KriteriumUJPocetProdObyv() { typ = KRIT_UJ_POCET_PRODUKTIVNYCH; };
	int ohodnot(UzemnaJednotka *u) { return u->getPocetProObyv(); };
};