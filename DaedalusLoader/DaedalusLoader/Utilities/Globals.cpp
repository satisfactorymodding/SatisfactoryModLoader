#include "Globals.h"

Global* Global::glb = nullptr;

Global* Global::GetGlobals()
{
	if (!glb)
	{
		glb = new Global();
	}
	return glb;
}