#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_WaitAtStop_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_WaitAtStop.BTT_WaitAtStop_C
// 0x0008 (0x00A8 - 0x00A0)
class UBTT_WaitAtStop_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_WaitAtStop.BTT_WaitAtStop_C");
		return ptr;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void Done();
	void ExecuteUbergraph_BTT_WaitAtStop(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
