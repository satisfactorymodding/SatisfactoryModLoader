#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_FGWaterAudio_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass FGWaterAudio.FGWaterAudio_C
// 0x0010 (0x0048 - 0x0038)
class UFGWaterAudio_C : public UFGWaterAudio
{
public:
	class FString                                      mString;                                                  // 0x0038(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass FGWaterAudio.FGWaterAudio_C");
		return ptr;
	}


	void OnCameraExitedWater(class AFGWaterVolume** waterVolume, struct FVector* exitLocation, class AFGPlayerController** PC);
	void OnCameraEnteredWater(class AFGWaterVolume** waterVolume, struct FVector* enterLocation, class AFGPlayerController** PC);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
