#pragma once
#include "Filter.h"

template <typename F>
class FormatovacFiltra {
public:
	/*F* pripravFilter()
	{
		vypisFilter(F * fe);
		nacitajHodnotyParametrov(F * fe);
	};*/
protected:
	virtual void vypisFilter(F *filter) = 0;
	virtual void nacitajHodnotyParametrov(F *filter) = 0;
};