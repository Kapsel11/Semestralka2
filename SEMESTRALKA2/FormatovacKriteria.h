#pragma once
#include "Kriterium.h"

template<typename K>
class FormatovacKriteria {
public:
	void pripravKriterium(K* kriterium);
	// tato bude volat ostatne metody
protected:
	virtual void vypisKriterium(K *kriterium)=0;
	virtual void nacitajHodnotyParametrov(K *kriterium)=0;
};