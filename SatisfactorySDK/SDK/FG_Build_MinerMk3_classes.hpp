#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_MinerMk3_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_MinerMk3.Build_MinerMk3_C
// 0x0028 (0x0738 - 0x0710)
class ABuild_MinerMk3_C : public ABuild_MinerMk2_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0710(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UBP_LadderComponent_C*                       BP_LadderComponent;                                       // 0x0718(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	TEnumAsByte<EMinerState>                           mInternalMiningState_1;                                   // 0x0720(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0721(0x0007) MISSED OFFSET
	struct FTimerHandle                                mToggleMiningStateHandle_1;                               // 0x0728(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	float                                              mMinimumDrillTime_1;                                      // 0x0730(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaximumDrillTime_1;                                      // 0x0734(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_MinerMk3.Build_MinerMk3_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveDestroyed();
	void ReceiveBeginPlay();
	void ExecuteUbergraph_Build_MinerMk3(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
