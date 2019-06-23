#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingPointLight_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildingPointLight.BP_BuildingPointLight_C
// 0x0008 (0x0398 - 0x0390)
class UBP_BuildingPointLight_C : public UPointLightComponent
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0390(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildingPointLight.BP_BuildingPointLight_C");
		return ptr;
	}


	void ReceiveBeginPlay();
	void HasPowerChanged(bool State);
	void ExecuteUbergraph_BP_BuildingPointLight(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
