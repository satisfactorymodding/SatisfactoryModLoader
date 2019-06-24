#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_Workshop_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_Workshop.Build_Workshop_C
// 0x0038 (0x05A0 - 0x0568)
class ABuild_Workshop_C : public AFGBuildable
{
public:
	class UFGFactoryLegsComponent*                     FGFactoryLegs;                                            // 0x0568(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGColoredInstanceMeshProxy*                 FGColoredInstanceMeshProxy;                               // 0x0570(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_WorkshopComponent_C*                     WorkshopComponent;                                        // 0x0578(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               Clearance;                                                // 0x0580(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FText                                       mOccupiedText;                                            // 0x0588(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_Workshop.Build_Workshop_C");
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
