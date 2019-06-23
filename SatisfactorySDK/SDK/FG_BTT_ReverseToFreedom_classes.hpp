#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_ReverseToFreedom_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_ReverseToFreedom.BTT_ReverseToFreedom_C
// 0x0009 (0x00A9 - 0x00A0)
class UBTT_ReverseToFreedom_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	bool                                               mIsStuckBBKey;                                            // 0x00A8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_ReverseToFreedom.BTT_ReverseToFreedom_C");
		return ptr;
	}


	void ReverseComplete();
	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_ReverseToFreedom(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
