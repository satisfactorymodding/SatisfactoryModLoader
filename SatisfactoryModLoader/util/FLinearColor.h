#pragma once
#include <Windows.h>

class FLinearColor {
	union {
		struct {
			float R;
			float G;
			float B;
			float A;
		};

		float Pow22OneOver255Table[256];
		float sRGBToLinearTable[256];
	};

	static const FLinearColor White;
	static const FLinearColor Gray;
	static const FLinearColor Black;
	static const FLinearColor Transparent;
	static const FLinearColor Red;
	static const FLinearColor Green;
	static const FLinearColor Blue;
	static const FLinearColor Yellow;
};