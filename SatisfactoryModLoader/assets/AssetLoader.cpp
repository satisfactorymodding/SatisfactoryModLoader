#include <stdafx.h>

//Code provided by Brabb3l

#include "AssetLoader.h"

namespace SML {
	namespace Assets {
		SDK::UObject* AssetLoader::LoadObjectSimple(SDK::UClass *Class, const wchar_t *Name) {
			return LoadUObject(Class, nullptr, Name, nullptr, 0, nullptr, false);
		}

		SDK::UObject* AssetLoader::LoadObject(SDK::UClass *ObjectClass, SDK::UObject *InOuter, const wchar_t *InName, const wchar_t *Filename, unsigned int LoadFlags, SDK::UPackageMap *Sandbox, bool bAllowObjectReconciliation) {
			return LoadUObject(ObjectClass, InOuter, InName, Filename, LoadFlags, Sandbox, bAllowObjectReconciliation);
		}

		void AssetLoader::Init() {
			LoadUObject = (SDK::UObject*(*)(SDK::UClass*, SDK::UObject*, const wchar_t*, const wchar_t*, unsigned int, SDK::UPackageMap*, bool)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "StaticLoadObject");
		}

		SDK::UObject*(*AssetLoader::LoadUObject)(SDK::UClass *ObjectClass, SDK::UObject *InOuter, const wchar_t *InName, const wchar_t *Filename, unsigned int LoadFlags, SDK::UPackageMap *Sandbox, bool bAllowObjectReconciliation) = NULL;
	}
}