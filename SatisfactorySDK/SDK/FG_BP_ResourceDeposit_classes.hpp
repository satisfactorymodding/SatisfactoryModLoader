#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceDeposit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ResourceDeposit.BP_ResourceDeposit_C
// 0x0008 (0x0408 - 0x0400)
class ABP_ResourceDeposit_C : public AFGResourceDeposit
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0400(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ResourceDeposit.BP_ResourceDeposit_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveBeginPlay();
	void PlayDepletedEffect(class UClass** Descriptor);
	void ExecuteUbergraph_BP_ResourceDeposit(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
