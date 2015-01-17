// EnModAul.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "EnModAul.h"


// This is an example of an exported variable
ENMODAUL_API int nEnModAul=0;

// This is an example of an exported function.
ENMODAUL_API int fnEnModAul(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see EnModAul.h for the class definition
CEnModAul::CEnModAul()
{
	return;
}
