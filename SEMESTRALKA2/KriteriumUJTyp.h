#pragma once
#include "KriteriumUJ.h"

class KriteriumUJTyp : public KriteriumUJ<TypUzemnejJednotky> {
public:
	KriteriumUJTyp() { typ = KRIT_UJ_TYP; };
	TypUzemnejJednotky ohodnot(UzemnaJednotka* o) { return o->getTypUJ(); };
};

