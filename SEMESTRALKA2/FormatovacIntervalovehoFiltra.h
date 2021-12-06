#pragma once
#include "FormatovacFiltra.h"
#include "FiltrePodlaIntervalu.h"


class FormatovacIntervalovehoFiltra : public FormatovacFiltra<FilterPodlaIntervalu>
{
protected:
	 void vypisFilter(FilterPodlaIntervalu filter);
	 void nacitajHodnotyParametrov(FilterPodlaIntervalu filter);
};