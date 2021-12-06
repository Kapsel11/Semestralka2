#pragma once
#include "Kriterium.h"
#include <iostream>


template <typename T>
class KriteriumBJ : public Kriterium<T, BytovaJednotka*>
{
	virtual T ohodnot(BytovaJednotka* b) = 0;
};