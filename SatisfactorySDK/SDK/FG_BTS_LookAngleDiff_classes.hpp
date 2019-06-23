#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_LookAngleDiff_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTS_LookAngleDiff.BTS_LookAngleDiff_C
// 0x0080 (0x0118 - 0x0098)
class UBTS_LookAngleDiff_C : public UBTService_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0098(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mThreatBBKey;                                             // 0x00A0(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      mSneakLimitBBKey;                                         // 0x00C8(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      mIsInViewBBKey;                                           // 0x00F0(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTS_LookAngleDiff.BTS_LookAngleDiff_C");
		return ptr;
	}


	void ReceiveTick(class AActor** OwnerActor, float* DeltaSeconds);
	void ExecuteUbergraph_BTS_LookAngleDiff(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
