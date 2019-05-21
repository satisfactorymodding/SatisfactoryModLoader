#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_BuildingPointLight_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildingPointLight.BP_BuildingPointLight_C
// 0x0008 (0x03A8 - 0x03A0)
class UBP_BuildingPointLight_C : public UPointLightComponent
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03A0(0x0008) (Transient, DuplicateTransient)

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
