#pragma once
#include "../UMLDefs.h"
#include <windows.h>
#include <cstdio>
#include <cinttypes>
bool LOADER_API Read(void* address, void* buffer, unsigned long long size);
bool LOADER_API Write(void* address, void* buffer, unsigned long long size);

template<typename T>
T Read(void* address)
{
	T buffer{};
	Read(address, &buffer, sizeof(T));
	return buffer;
}

template<typename T>
T Write(void* address, T buffer)
{
	Write(address, &buffer, sizeof(T));
	return buffer;
}

namespace MEM
{
	HWND FindWindow(DWORD pid, wchar_t const* className);

	uint8_t __declspec(noinline)* GetAddressPTR(uint8_t* ptr, uint8_t offset, uint8_t instr_size);
};