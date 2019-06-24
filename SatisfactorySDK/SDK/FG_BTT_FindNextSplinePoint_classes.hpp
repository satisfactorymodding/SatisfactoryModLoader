#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FindNextSplinePoint_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_FindNextSplinePoint.BTT_FindNextSplinePoint_C
// 0x0088 (0x0128 - 0x00A0)
class UBTT_FindNextSplinePoint_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      SplineKey;                                                // 0x00A8(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      MoveToKey;                                                // 0x00D0(0x0028) (Edit, BlueprintVisible)
	bool                                               ForceSucess;                                              // 0x00F8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00F9(0x0007) MISSED OFFSET
	struct FBlackboardKeySelector                      SplineIndexKey;                                           // 0x0100(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_FindNextSplinePoint.BTT_FindNextSplinePoint_C");
		return ptr;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_FindNextSplinePoint(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
