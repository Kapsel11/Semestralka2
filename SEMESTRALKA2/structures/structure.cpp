#include "structure.h"
#include <tchar.h>
#include "heap_monitor.h"

namespace structures {

	Structure::Structure()
	{
	}

	Structure::~Structure()
	{
	}

	bool Structure::isEmpty() const
	{
		return size() == 0;
	}

}