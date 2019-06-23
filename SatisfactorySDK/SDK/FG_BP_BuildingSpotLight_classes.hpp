#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingSpotLight_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildingSpotLight.BP_BuildingSpotLight_C
// 0x0008 (0x03A8 - 0x03A0)
class UBP_BuildingSpotLight_C : public USpotLightComponent
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildingSpotLight.BP_BuildingSpotLight_C");
		return ptr;
	}


	void ReceiveBeginPlay();
	void HasPowerChanged(bool State);
	void ExecuteUbergraph_BP_BuildingSpotLight(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
