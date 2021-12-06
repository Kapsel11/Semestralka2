#pragma once
#include "KriteriumBJ.h"			// DOROBIT 
#include <iostream>

class KriteriumBJPocetIzieb : public KriteriumBJ<int> {
public:
	KriteriumBJPocetIzieb() { typ = KRIT_BJ_POCET_IZIEB; };
	int ohodnot(BytovaJednotka* b) { return  b->getPocetIzieb(); };
};