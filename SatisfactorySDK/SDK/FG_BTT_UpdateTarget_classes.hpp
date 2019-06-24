#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_UpdateTarget_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_UpdateTarget.BTT_UpdateTarget_C
// 0x0058 (0x00F8 - 0x00A0)
class UBTT_UpdateTarget_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      TargetPoint;                                              // 0x00A8(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      WantsNewTargetBBKey;                                      // 0x00D0(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_UpdateTarget.BTT_UpdateTarget_C");
		return ptr;
	}


	void ReceiveExecute(class AActor** OwnerActor);
	void ExecuteUbergraph_BTT_UpdateTarget(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
