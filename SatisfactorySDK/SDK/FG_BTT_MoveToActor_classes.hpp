#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveToActor_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_MoveToActor.BTT_MoveToActor_C
// 0x0060 (0x0100 - 0x00A0)
class UBTT_MoveToActor_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mTargetActorBBKey;                                        // 0x00A8(0x0028) (Edit, BlueprintVisible)
	float                                              mAcceptanceRadius;                                        // 0x00D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00D4(0x0004) MISSED OFFSET
	struct FBlackboardKeySelector                      mAcceptanceRadiusBBkey;                                   // 0x00D8(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_MoveToActor.BTT_MoveToActor_C");
		return ptr;
	}


	void OnFail_A86C15A64D326131272CCA93E74F5421(TEnumAsByte<EPathFollowingResult> MovementResult);
	void OnSuccess_A86C15A64D326131272CCA93E74F5421(TEnumAsByte<EPathFollowingResult> MovementResult);
	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_MoveToActor(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
