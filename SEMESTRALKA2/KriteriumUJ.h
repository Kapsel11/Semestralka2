#pragma once
#include "Kriterium.h"
#include "UzemnaJednotka.h"

template<typename T>
class KriteriumUJ : public Kriterium<T, UzemnaJednotka*>
{
public:
	virtual T ohodnot(UzemnaJednotka *u) = 0;
};

/*#pragma once
#include "Kriterium.h"
#include "UzemnaJednotka.h"

template <typename T>
class KriteriumUJ : public Kriterium<T, UzemnaJednotka>
{
public:
	virtual T ohodnot(UzemnaJednotka u);
};*/