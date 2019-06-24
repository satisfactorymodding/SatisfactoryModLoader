#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_PortableMinerDispenser_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C
// 0x0018 (0x0378 - 0x0360)
class AAttach_PortableMinerDispenser_C : public AFGEquipmentAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      _1P_PortableMiner;                                        // 0x0368(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0370(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayAttachEffects3P();
	void PlayDetachEffects3P();
	void ExecuteUbergraph_Attach_PortableMinerDispenser(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
