#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ConsumeableEquipmentAttachment_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C
// 0x0018 (0x0378 - 0x0360)
class ABP_ConsumeableEquipmentAttachment_C : public AFGEquipmentAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        StaticMesh;                                               // 0x0368(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0370(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C");
		return ptr;
	}


	void GetHandsItem(class UClass** Item);
	void UserConstructionScript();
	void ReceiveTick(float* DeltaSeconds);
	void PlayUseEffect(struct FVector* UseLocation);
	void OnAttach();
	void ExecuteUbergraph_BP_ConsumeableEquipmentAttachment(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
