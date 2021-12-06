#pragma once
#include "FormatovacFiltra.h"
#include "FilterPodlaHodnoty.h"
#include "UzemnaJednotka.h"

class FormatovacHodnotovehoBool : public FormatovacFiltra<FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool>>
{
protected:
	void vypisFilter(FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool>* filter);
	void nacitajHodnotyParametrov(FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool>* filter);
};