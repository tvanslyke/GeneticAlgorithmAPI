/*
 * MutatorDiagnostics.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#include "MutatorDiagnostics.h"




size_t MutatorDiagnostics::assignID()
{
	static bool init = false;
	if(not init)
	{
		init = true;
		count = 0;
	}
	return count++;
}

size_t MutatorDiagnostics::count = 0;
