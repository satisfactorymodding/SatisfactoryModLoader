#include <stdafx.h>

//Code provided by Brabb3l

#include "AssetLoader.h"

namespace SML {
	namespace Assets {
		SDK::UObject* AssetLoader::loadObjectSimple(SDK::UClass *Class, const wchar_t *Name) {
			return loadUObjectFunc(Class, nullptr, Name, nullptr, 0, nullptr, false);
		}

		SDK::UObject* AssetLoader::loadObject(SDK::UClass *ObjectClass, SDK::UObject *InOuter, const wchar_t *InName, const wchar_t *Filename, unsigned int LoadFlags, SDK::UPackageMap *Sandbox, bool bAllowObjectReconciliation) {
			return loadUObjectFunc(ObjectClass, InOuter, InName, Filename, LoadFlags, Sandbox, bAllowObjectReconciliation);
		}

		void AssetLoader::init() {
			loadUObjectFunc = (SDK::UObject*(*)(SDK::UClass*, SDK::UObject*, const wchar_t*, const wchar_t*, unsigned int, SDK::UPackageMap*, bool)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "StaticLoadObject");
		}

		SDK::UObject*(*AssetLoader::loadUObjectFunc)(SDK::UClass *ObjectClass, SDK::UObject *InOuter, const wchar_t *InName, const wchar_t *Filename, unsigned int LoadFlags, SDK::UPackageMap *Sandbox, bool bAllowObjectReconciliation) = NULL;
	}
}