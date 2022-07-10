#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "Utilities/EngineDefFinder.h"
#include "Basic.hpp"
#include "Utilities/Pattern.h"
#include "CoreUObject_classes.hpp"
namespace UE4
{
	static void InitSDK()
	{
		DWORD64   Names_offset = NULL;
		if (!FName::IsUsingNamePool())
		{
			Names_offset = (*(DWORD64*)(GameProfile::SelectedGameProfile.GName));
			FName::GNames = (DWORD*)Names_offset;
		}
		else
		{
			Names_offset = (DWORD64)(GameProfile::SelectedGameProfile.GName);
			FName::GNames = (DWORD*)Names_offset;
		}

		DWORD64   GObjObjects_offset = NULL;
		GObjObjects_offset = (DWORD64)(GameProfile::SelectedGameProfile.GObject);
		UObject::GObjects = (FUObjectArray*)GObjObjects_offset;

		DWORD64   GWorldObjects = NULL;
		GWorldObjects = (DWORD64)(GameProfile::SelectedGameProfile.GWorld);
		UWorld::GWorld = (UWorld**)GWorldObjects;

		#ifdef UNREALENGINEMODLOADER_EXPORTS //Stops dumb errors from the ExampleMod shit
		if (GameProfile::SelectedGameProfile.IsUObjectMissing)
		{
			Log::Warn("UObject Not Defined. Scanning for def.");
			UE4::UObject* CoreUobjectObject;
			UE4::UObject* UEObject;

			if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
			{
				CoreUobjectObject = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(1).Object;
				UEObject = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(2).Object;
			}
			else
			{
				CoreUobjectObject = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(1).Object;
				UEObject = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(2).Object;
			}
			ClassDefFinder::FindUObjectDefs(CoreUobjectObject, UEObject);
			GameProfile::SelectedGameProfile.IsUObjectMissing = false;
		}

		if (GameProfile::SelectedGameProfile.IsUFieldMissing)
		{
			Log::Warn("UField Not Defined. Scanning for def.");
			ClassDefFinder::FindUFieldDefs();
			GameProfile::SelectedGameProfile.IsUFieldMissing = false;
		}
		if (GameProfile::SelectedGameProfile.IsUStructMissing)
		{
			Log::Warn("UStruct Not Defined. Scanning for def.");
			ClassDefFinder::FindUStructDefs();
			GameProfile::SelectedGameProfile.IsUStructMissing = false;
		}
		if (GameProfile::SelectedGameProfile.IsUFunctionMissing)
		{
			Log::Warn("UFunction Not Defined. Scanning for def.");
			ClassDefFinder::FindUFunctionDefs();
			GameProfile::SelectedGameProfile.IsUFunctionMissing = false;
		}

		if (GameProfile::SelectedGameProfile.IsPropertyMissing)
		{
			ClassDefFinder::FindUEProperty();
		}
		Log::Info("All Engine Classes Found");
		#endif

	}
}