#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attach_NobeliskDetonator_R_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C
// 0x0018 (0x0390 - 0x0378)
class AAttach_NobeliskDetonator_R_C : public AFGNobeliskExplosiveAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0378(0x0008) (Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      NobeliskExplosive_Skl_01;                                 // 0x0380(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0388(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnIsLoadedSet();
	void PlayFireEffect(struct FVector* flashLocation);
	void OnBeginFireEffect(struct FVector* Location);
	void ClientPlayReloadEffect();
	void OnAttach();
	void ExecuteUbergraph_Attach_NobeliskDetonator_R(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
