#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_VehicleTargetPoint_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_VehicleTargetPoint.BP_VehicleTargetPoint_C
// 0x0030 (0x0380 - 0x0350)
class ABP_VehicleTargetPoint_C : public AFGTargetPoint
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0350(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        ArrowMesh;                                                // 0x0358(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UTextRenderComponent*                        TextRender;                                               // 0x0360(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FText                                       mUseText;                                                 // 0x0368(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_VehicleTargetPoint.BP_VehicleTargetPoint_C");
		return ptr;
	}


	struct FText GetLookAtDecription(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	bool IsUseable();
	void UpdateUseState(class AFGCharacterPlayer* byCharacter, const struct FVector& atLocation, class UPrimitiveComponent* componentHit, struct FUseState* out_useState);
	bool ShouldSave();
	bool NeedTransform();
	void GatherDependencies(TArray<class UObject*>* out_dependentObjects);
	void UserConstructionScript();
	void OnUseStop(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void RegisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void UnregisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void ReceiveBeginPlay();
	void OnUse(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void StartIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void StopIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void SetMeshRotation();
	void ExecuteUbergraph_BP_VehicleTargetPoint(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
