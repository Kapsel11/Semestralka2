#pragma once
#include "KriteriumBJ.h"
#include <iostream>
#include "BytovaJednotka.h"

class KriteriumBJPocet : public KriteriumBJ<int> {
public:
	KriteriumBJPocet() { typ = KRIT_BJ_POCET; };
	int ohodnot(BytovaJednotka* b) { return b->getPocet(); };
	void setUJ(int value);
};