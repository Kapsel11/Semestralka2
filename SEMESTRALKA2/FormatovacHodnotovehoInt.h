#pragma once
#include "FormatovacFiltra.h"
#include "FilterPodlaHodnoty.h"
#include "UzemnaJednotka.h"

class FormatovacHodnotovehoInt : public FormatovacFiltra<FilterPodlaHodnoty<std::string, UzemnaJednotka*, int>>
{
protected:
	void vypisFilter(FilterPodlaHodnoty<std::string, UzemnaJednotka*, int>* filter);
	void nacitajHodnotyParametrov(FilterPodlaHodnoty<std::string, UzemnaJednotka*, int>* filter);
};