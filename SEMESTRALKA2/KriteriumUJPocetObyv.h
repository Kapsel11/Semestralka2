#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJPocetObyv : public KriteriumUJ<int>
{
public:
	KriteriumUJPocetObyv() { typ = KRIT_UJ_POCET_OBYVATELOV; };
	int ohodnot(UzemnaJednotka* u) { return u->getPocetPoProObyv() + u->getPocetPreProdObyv() + u->getPocetProObyv(); };
};