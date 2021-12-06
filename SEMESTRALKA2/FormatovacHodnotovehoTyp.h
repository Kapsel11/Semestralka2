#pragma once
#include "FormatovacFiltra.h"
#include "FilterPodlaHodnoty.h"
#include "UzemnaJednotka.h"

class FormatovacHodnotovehoTyp : public FormatovacFiltra<FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky>>
{
protected:
	void vypisFilter(FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky>* filter);
	void nacitajHodnotyParametrov(FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky>* filter);
};