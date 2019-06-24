#pragma once

//Code provided by Brabb3l

#include <../SatisfactorySDK/SDK.hpp>
#include <Windows.h>
#include <detours.h>

namespace SML {
	namespace Assets {
	class AssetLoader {
	public:
		static SDK::UObject* loadObjectSimple(SDK::UClass *ObjectClass, const wchar_t *InName);

		static SDK::UObject* loadObject(SDK::UClass *ObjectClass, SDK::UObject *InOuter = nullptr, const wchar_t *InName = nullptr, const wchar_t *Filename = nullptr, unsigned int LoadFlags = 0, SDK::UPackageMap *Sandbox = nullptr, bool bAllowObjectReconciliation = false);

		static void init();

	private:
		static SDK::UObject*(*loadUObjectFunc)(SDK::UClass *ObjectClass, SDK::UObject *InOuter, const wchar_t *InName, const wchar_t *Filename, unsigned int LoadFlags, SDK::UPackageMap *Sandbox, bool bAllowObjectReconciliation);
	};
	}
}