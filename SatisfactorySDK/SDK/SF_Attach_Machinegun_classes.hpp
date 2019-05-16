#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attach_Machinegun_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_Machinegun.Attach_Machinegun_C
// 0x0018 (0x0388 - 0x0370)
class AAttach_Machinegun_C : public AFGWeaponAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0370(0x0008) (Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Machinegun;                                               // 0x0378(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0380(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_Machinegun.Attach_Machinegun_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayFireEffect(struct FVector* flashLocation);
	void ClientPlayReloadEffect();
	void ExecuteUbergraph_Attach_Machinegun(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
