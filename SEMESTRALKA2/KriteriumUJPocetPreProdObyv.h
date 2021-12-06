#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJPocetPreProdObyv : public KriteriumUJ<int> {
public:
	KriteriumUJPocetPreProdObyv() { typ = KRIT_UJ_POCET_PRE_PROD; };
	int ohodnot(UzemnaJednotka u) { return u.getPocetPreProdObyv(); };
};