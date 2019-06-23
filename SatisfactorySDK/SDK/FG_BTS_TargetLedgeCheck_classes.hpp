#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_TargetLedgeCheck_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTS_TargetLedgeCheck.BTS_TargetLedgeCheck_C
// 0x0084 (0x011C - 0x0098)
class UBTS_TargetLedgeCheck_C : public UBTService_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0098(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mBBKeyA;                                                  // 0x00A0(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      mBBKeyB;                                                  // 0x00C8(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      mBBKeyC;                                                  // 0x00F0(0x0028) (Edit, BlueprintVisible)
	float                                              mCanFallDistance;                                         // 0x0118(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTS_TargetLedgeCheck.BTS_TargetLedgeCheck_C");
		return ptr;
	}


	void GetKeyLocation(const struct FBlackboardKeySelector& Key, struct FVector* Location);
	void ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds);
	void ExecuteUbergraph_BTS_TargetLedgeCheck(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
