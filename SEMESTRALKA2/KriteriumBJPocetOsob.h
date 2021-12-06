#pragma once
#include "KriteriumBJ.h"

class KriteriumBJPocetOsob : public KriteriumBJ<int> {
public:
	KriteriumBJPocetOsob() { typ = KRIT_BJ_POCET_OSOB; };
	TypKriteria getTyp() { return typ; };
	int ohodnot(BytovaJednotka* o) { return o->getPoceOsob(); };
};