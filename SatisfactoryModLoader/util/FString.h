#pragma once
#include <cstdint>
#include <Windows.h>

struct FString {
	int16_t* data;
	int32_t length;
};