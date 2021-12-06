#pragma once
#include "KriteriumUJ.h"

class KriteriumUJNazov : public KriteriumUJ<std::string> {
public:
	KriteriumUJNazov() { typ = KRIT_UJ_NAZOV; };
	TypKriteria getTyp() { return typ; };
	std::string ohodnot(UzemnaJednotka *o) { return o->getNazov();};
};