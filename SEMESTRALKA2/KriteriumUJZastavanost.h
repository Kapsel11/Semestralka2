#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJZastavanost : public KriteriumUJ<long double> 
{
public:
	KriteriumUJZastavanost() { typ = KRIT_UJ_ZASTAVANOST; };
	long double ohodnot(UzemnaJednotka *u) { return (100 * (u->getZastavPlocha() / u->getVymera())); };
};