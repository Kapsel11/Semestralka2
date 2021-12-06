#pragma once
#include "FormatovacFiltra.h"
#include "FilterPodlaHodnoty.h"
#include "UzemnaJednotka.h"
#include "FormatovacHodnotovehoFiltra.h"

class FormatovacHodnotovehoString : public FormatovacHodnotovehoFiltra<std::string, UzemnaJednotka*, std::string>
{
protected:
	void vypisFilter(FilterPodlaHodnoty<std::string, UzemnaJednotka*, std::string>* filter)
	{
		std::cout << "Chcete pouzit filter ? [A/N]";
		std::string vstup;
		std::cin >> vstup;
	};
	void nacitajHodnotyParametrov(FilterPodlaHodnoty<std::string, UzemnaJednotka*, std::string>* filter)
	{
		
	}
};