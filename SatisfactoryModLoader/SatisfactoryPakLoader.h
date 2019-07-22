#pragma once

#include "../SatisfactorySDK/SDK.hpp"

namespace SPL {
	class AMod : public SDK::AActor {};

	struct InitMod_PreInit_Params {};

	struct InitMod_Init_Params {
		class SDK::FString Mods;
	};

	struct InitMod_PostInit_Params {
		class SDK::FString Mods;
	};

	void Init();

	template <typename T>
	void CallModFunction(AMod* mod, SDK::UFunction* fn, T params);

	/*
	(Work In Progress)

	template <typename T>
	inline void ResizeArray(SDK::TArray<T> &Array, int NewMax) {
		T* NewArray = new T[NewMax];

		if (Array.Data)
			memcpy(NewArray, Array.Data, Array.Max * sizeof(T));

		Array.Max = NewMax;
		delete[] Array.Data;
		Array.Data = NewArray;
	}

	template <typename T>
	inline void AddToArray(SDK::TArray<T> &Array, T Item) {
		if (Array.Count == Array.Max)
			ResizeArray(Array, Array.Max + 10);

		Array[Array.Count++] = Item;
	}
	*/
}
