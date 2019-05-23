#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_PowerPoleMk1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_PowerPoleMk1.Build_PowerPoleMk1_C
// 0x0018 (0x05A0 - 0x0588)
class ABuild_PowerPoleMk1_C : public AFGBuildablePowerPole
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0588(0x0008) (Transient, DuplicateTransient)
	class UBP_BuildingPointLight_C*                    BP_BuildingPointLight;                                    // 0x0590(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               Clearance;                                                // 0x0598(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_PowerPoleMk1.Build_PowerPoleMk1_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnHasPowerChanged_2(bool newHasPower);
	void PlayConstructSound();
	void ReceiveBeginPlay();
	void ExecuteUbergraph_Build_PowerPoleMk1(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
