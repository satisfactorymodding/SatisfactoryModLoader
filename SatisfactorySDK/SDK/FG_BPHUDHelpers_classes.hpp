#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BPHUDHelpers_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BPHUDHelpers.BPHUDHelpers_C
// 0x0000 (0x0028 - 0x0028)
class UBPHUDHelpers_C : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BPHUDHelpers.BPHUDHelpers_C");
		return ptr;
	}


	void ShowHideHUD(bool isMenuOpen, class APawn* OwningPawn, class AController* Controller, class UObject* __WorldContext);
	void PopStackWidget(class AController* instigatingController, class UFGInteractWidget* Stack_Widget, class UObject* __WorldContext);
	void PushStackWidget(class AController* instigatingController, class UFGInteractWidget* stackWidget, class UObject* __WorldContext);
	void GetBPHUD(class AController* Controller, class UObject* __WorldContext, class ABP_HUD_C** outHUD);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
