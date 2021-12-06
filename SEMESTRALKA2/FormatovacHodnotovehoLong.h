#pragma once
#include "FormatovacFiltra.h"
#include "FilterPodlaHodnoty.h"
#include "UzemnaJednotka.h"

class FormatovacHodnotovehoLong : public FormatovacFiltra<FilterPodlaHodnoty<std::string, UzemnaJednotka*, long long>>
{
protected:
	void vypisFilter(FilterPodlaHodnoty<std::string, UzemnaJednotka*, long long>* filter);
	void nacitajHodnotyParametrov(FilterPodlaHodnoty<std::string, UzemnaJednotka*, long long>* filter);
};