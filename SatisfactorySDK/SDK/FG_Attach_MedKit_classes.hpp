#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_MedKit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_MedKit.Attach_MedKit_C
// 0x0018 (0x0378 - 0x0360)
class AAttach_MedKit_C : public AFGEquipmentAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Medkit_skl;                                               // 0x0368(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0370(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_MedKit.Attach_MedKit_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayUseEffect(struct FVector* UseLocation);
	void PlayAttachEffects3P();
	void ExecuteUbergraph_Attach_MedKit(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
