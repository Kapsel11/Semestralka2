#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJZastavanaPlocha : public KriteriumUJ<long long>
{
public:
	KriteriumUJZastavanaPlocha() { typ = KRIT_UJ_ZASTAVANA_PLOCHA; };
	long long ohodnot(UzemnaJednotka *u) { return u->getZastavPlocha(); };
};