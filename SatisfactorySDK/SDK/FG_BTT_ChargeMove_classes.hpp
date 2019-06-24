#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_ChargeMove_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_ChargeMove.BTT_ChargeMove_C
// 0x0010 (0x00B0 - 0x00A0)
class UBTT_ChargeMove_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	bool                                               CircleCharge;                                             // 0x00A8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x00A9(0x0003) MISSED OFFSET
	float                                              MaxChargeTime;                                            // 0x00AC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_ChargeMove.BTT_ChargeMove_C");
		return ptr;
	}


	void ReceiveExecute(class AActor** OwnerActor);
	void ChargeComplete();
	void ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_ChargeMove(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
