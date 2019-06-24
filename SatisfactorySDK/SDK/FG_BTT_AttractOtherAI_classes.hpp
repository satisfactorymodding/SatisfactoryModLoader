#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_AttractOtherAI_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_AttractOtherAI.BTT_AttractOtherAI_C
// 0x008C (0x012C - 0x00A0)
class UBTT_AttractOtherAI_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FName                                       RequiredBoolKey;                                          // 0x00A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FName                                       SummonLocationKey;                                        // 0x00B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MinimumRange;                                             // 0x00B8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MaximumRange;                                             // 0x00BC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<float>                                      DistanceArray;                                            // 0x00C0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                MaxSummonedHogs;                                          // 0x00D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00D4(0x0004) MISSED OFFSET
	TArray<class AChar_Hog_C*>                         SortedHogs;                                               // 0x00D8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance)
	TArray<class AChar_Hog_C*>                         NearbyHogs;                                               // 0x00E8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance)
	struct FBlackboardKeySelector                      mOtherLocationOption;                                     // 0x00F8(0x0028) (Edit, BlueprintVisible)
	struct FVector                                     UsedLocation;                                             // 0x0120(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_AttractOtherAI.BTT_AttractOtherAI_C");
		return ptr;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_AttractOtherAI(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
