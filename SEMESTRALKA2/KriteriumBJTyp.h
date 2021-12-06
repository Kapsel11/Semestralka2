#pragma once
#include "KriteriumBJ.h"

class KriteriumBJTyp : public KriteriumBJ<std::string> {
public:
	KriteriumBJTyp() { typ = KRIT_BJ_TYP; };
	TypKriteria getTyp() { return typ; };
	std::string ohodnot(BytovaJednotka* o) { return o->getTyp(); };
};