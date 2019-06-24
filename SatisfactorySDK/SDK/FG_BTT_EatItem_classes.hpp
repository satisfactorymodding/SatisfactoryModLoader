#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_EatItem_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_EatItem.BTT_EatItem_C
// 0x0048 (0x00E8 - 0x00A0)
class UBTT_EatItem_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mTargetItemBBKey;                                         // 0x00A8(0x0028) (Edit, BlueprintVisible)
	class UClass*                                      mDesiredItemClass;                                        // 0x00D0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                mAmountToPickup;                                          // 0x00D8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00DC(0x0004) MISSED OFFSET
	class AFGCreature*                                 mCreature;                                                // 0x00E0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_EatItem.BTT_EatItem_C");
		return ptr;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_EatItem(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
