#pragma once

#include "FormatovacKriteria.h"
#include "TypKriteria.h"

#include "KriteriumUJNazov.h"
#include "KriteriumUJPocetPreProdObyv.h"
#include "KriteriumUJPocetBJ.h"
#include "KriteriumUJCelkovaVymera.h"
#include "KriteriumUJPocetPoProdObyv.h"
#include "KriteriumUJPocetProdObyv.h"
#include "KriteriumUJPrislusnost.h"
#include "KriteriumUJZastavanost.h"
#include "KriteriumUJZastavanaPlocha.h"
#include "KriteriumUJTyp.h"
#include "KriteriumUJPocetObyv.h"

#include "KriteriumBJPocet.h"
#include "KriteriumBJPocetIzieb.h"
#include "KriteriumBJPocetOsob.h"
#include "KriteriumBJTyp.h"

#include "FormatovacKriteriaUJNazov.h"
#include "FormatovacKriteriaUJTyp.h"
#include "FormatovacKriteriaUJPocetBJ.h"
#include "FormatovacKriteriaUJPocetObyv.h"
#include "FormatovacKriteriaUJPocetPoProdObyv.h"
#include "FormatovacKriteriaUJPocetPreProdObyv.h"
#include "FormatovacKriteriaUJPocetProdObyv.h"
#include "FormatovacKriteriaUJPrislusnost.h"
#include "FormatovacKriteriaUJZastavanaPlocha.h"
#include "FormatovacKriteriaUJZastavanost.h"
#include "FormatovacKriteriaUJCelkovaVymera.h"

template<typename K>	// Mozno netreba alebo ?
class RegisterFormatovacov {
public:
	 FormatovacKriteria<K>* dajMiFormatovacKriteria(TypKriteria id)
	{
		switch (id)
		{
		case		KRIT_UJ_NAZOV:
			return FormatovacKriteriaUJNazov();
		case		KRIT_UJ_TYP:
			return FormatovacKriteriaUJTyp();
		case		KRIT_UJ_PRISLUSNOST:
			return FormatovacKriteriaUJPrislusnost();
		case		KRIT_UJ_POCET_PRE_PROD:
			return FormatovacKriteriaUJPocetPreProdObyv(); 
		case		KRIT_UJ_POCET_PRODUKTIVNYCH:
			return FormatovacKriteriaUJPocetProdObyv();
		case		KRIT_UJ_POCET_PO_PROD:
			return FormatovacKriteriaUJPocetPoProdObyv();
		case		KRIT_UJ_POCET_OBYVATELOV:
			return FormatovacKriteriaUJPocetObyv();
		case		KRIT_UJ_CELKOVA_VYMERA:
			return FormatovacKriteriaUJCelkovaVymera();
		case		KRIT_UJ_ZASTAVANA_PLOCHA:
			return FormatovacKriteriaUJZastavanaPlocha();
		case		KRIT_UJ_ZASTAVANOST:
			return  FormatovacKriteriaUJZastavanost();
			/*	case		KRIT_BJ_TYP:
					return FormatovacKriteria<KriteriumBJTyp>();
				case		KRIT_BJ_POCET_OSOB:
					return FormatovacKriteria<KriteriumBJPocetOsob>();
				case		KRIT_BJ_POCET_IZIEB:
					return FormatovacKriteria<KriteriumBJPocetIzieb>();
				case		KRIT_BJ_POCET:
					return FormatovacKriteria<KriteriumBJPocet>();
				case		KRIT_UJ_POCET_BJ:
					return FormatovacKriteria<KriteriumUJPocetBJ>();
					*/
		}
	}
};