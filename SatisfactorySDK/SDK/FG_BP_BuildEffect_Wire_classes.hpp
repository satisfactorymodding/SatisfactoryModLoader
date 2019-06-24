#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildEffect_Wire_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildEffect_Wire.BP_BuildEffect_Wire_C
// 0x0028 (0x0350 - 0x0328)
class ABP_BuildEffect_Wire_C : public AActor
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0328(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0330(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     Timeline_0_NewTrack_0_C21AB6204CE0D2E20CFA12B09E73FB8B;   // 0x0338(0x000C) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ETimelineDirection>                    Timeline_0__Direction_C21AB6204CE0D2E20CFA12B09E73FB8B;   // 0x0344(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0345(0x0003) MISSED OFFSET
	class UTimelineComponent*                          Timeline_1;                                               // 0x0348(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildEffect_Wire.BP_BuildEffect_Wire_C");
		return ptr;
	}


	void UserConstructionScript();
	void Timeline_0__FinishedFunc();
	void Timeline_0__UpdateFunc();
	void ReceiveBeginPlay();
	void ExecuteUbergraph_BP_BuildEffect_Wire(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
