#pragma once
#include "KriteriumUJ.h"
#include <iostream>
#include "UzemnaJednotka.h"

class KriteriumUJCelkovaVymera : public KriteriumUJ<long long>
{
public:
	KriteriumUJCelkovaVymera() { typ = KRIT_UJ_CELKOVA_VYMERA; };
	long long ohodnot(UzemnaJednotka *u) { return u->getVymera(); };
};