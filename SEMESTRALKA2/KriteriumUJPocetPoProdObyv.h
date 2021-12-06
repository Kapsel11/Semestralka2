#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJPocetPoProdObyv: public KriteriumUJ<int>
{
public:
	KriteriumUJPocetPoProdObyv() { typ = KRIT_UJ_POCET_PO_PROD; };
	int ohodnot(UzemnaJednotka u) { return u.getPocetPoProObyv(); };
};