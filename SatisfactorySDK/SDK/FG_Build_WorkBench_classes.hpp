#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_WorkBench_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_WorkBench.Build_WorkBench_C
// 0x0048 (0x05B0 - 0x0568)
class ABuild_WorkBench_C : public AFGBuildable
{
public:
	class UFGFactoryLegsComponent*                     FGFactoryLegs;                                            // 0x0568(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        Glass;                                                    // 0x0570(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGColoredInstanceMeshProxy*                 FGColoredInstanceMeshProxy;                               // 0x0578(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_BuildingSpotLight_C*                     BP_BuildingSpotLight;                                     // 0x0580(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_WorkBenchComponent_C*                    BP_WorkBenchComponent;                                    // 0x0588(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               Clearance;                                                // 0x0590(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FText                                       mOccupiedText;                                            // 0x0598(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_WorkBench.Build_WorkBench_C");
		return ptr;
	}


	struct FText GetLookAtDecription(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	bool IsUseable();
	void UpdateUseState(class AFGCharacterPlayer** byCharacter, struct FVector* atLocation, class UPrimitiveComponent** componentHit, struct FUseState* out_useState);
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
