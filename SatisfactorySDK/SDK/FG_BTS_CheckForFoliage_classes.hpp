#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_CheckForFoliage_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTS_CheckForFoliage.BTS_CheckForFoliage_C
// 0x0030 (0x00C8 - 0x0098)
class UBTS_CheckForFoliage_C : public UBTService_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0098(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mHasFoliageNearbyBBKey;                                   // 0x00A0(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTS_CheckForFoliage.BTS_CheckForFoliage_C");
		return ptr;
	}


	void ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds);
	void ExecuteUbergraph_BTS_CheckForFoliage(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
