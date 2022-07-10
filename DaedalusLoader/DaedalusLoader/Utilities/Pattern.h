#pragma once
#include <Windows.h>
#include <Psapi.h>

namespace Pattern
{
#define INRANGE(x,a,b)      (x >= a && x <= b) 
#define getBits(x)          (INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte(x)          (getBits(x[0]) << 4 | getBits(x[1]))

	static PBYTE BaseAddress = NULL;
	static MODULEINFO ModuleInfo;

	static PBYTE Find(const char* pattern, PBYTE rangeStart = NULL, PBYTE rangeEnd = NULL)
	{
		if (BaseAddress == NULL)
		{
			BaseAddress = (PBYTE)GetModuleHandle(NULL);
			GetModuleInformation(GetCurrentProcess(), (HMODULE)BaseAddress, &ModuleInfo, sizeof(ModuleInfo));
		}

		if (rangeStart == NULL) rangeStart = BaseAddress;
		if (rangeEnd == NULL) rangeEnd = rangeStart + ModuleInfo.SizeOfImage;

		const unsigned char* pat = reinterpret_cast<const unsigned char*>(pattern);
		PBYTE firstMatch = 0;
		for (PBYTE pCur = rangeStart; pCur < rangeEnd; ++pCur)
		{
			if (*(PBYTE)pat == (BYTE)'\?' || *pCur == getByte(pat))
			{
				if (!firstMatch) firstMatch = pCur;
				pat += (*(PWORD)pat == (WORD)'\?\?' || *(PBYTE)pat != (BYTE)'\?') ? 2 : 1;
				if (!*pat) return firstMatch;
				pat++;
				if (!*pat) return firstMatch;
			}
			else if (firstMatch)
			{
				pCur = firstMatch;
				pat = reinterpret_cast<const unsigned char*>(pattern);
				firstMatch = 0;
			}
		}
		return NULL;
	}
}