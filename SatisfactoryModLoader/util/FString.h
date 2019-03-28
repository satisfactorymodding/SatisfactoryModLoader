#pragma once
#include <Windows.h>
#include <cstdint>

struct FString {
	int16_t* data;
	int32_t length;
};