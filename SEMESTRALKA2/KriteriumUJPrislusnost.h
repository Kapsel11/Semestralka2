#pragma once
#include "KriteriumUJ.h"

class KriteriumUJPrislusnost : public KriteriumUJ<bool> {
public:
	KriteriumUJPrislusnost() { typ = KRIT_UJ_PRISLUSNOST; };
	bool ohodnot(UzemnaJednotka* o, std::string vyssiCelok) { return o->getPatriDoVyssiehoCelku(vyssiCelok); };
	bool ohodnot(UzemnaJednotka* o) { return false; };
	bool ohodnot(BytovaJednotka* b, std::string vyssiCelok) { return false; };
};