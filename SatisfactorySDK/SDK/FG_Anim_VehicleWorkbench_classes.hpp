#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_VehicleWorkbench_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_VehicleWorkbench.Anim_VehicleWorkbench_C
// 0x00E8 (0x0448 - 0x0360)
class UAnim_VehicleWorkbench_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_189DAB524CCACEAF870DE7A7DE5F1719;      // 0x0368(0x0040)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_BFEAAA224EFB9618FC532584C580B23F;      // 0x03A8(0x0068)
	struct FAnimNode_RefPose                           AnimGraphNode_LocalRefPose_FAA777984764E404855AB4AA9E7B9DA6;// 0x0410(0x0038)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_VehicleWorkbench.Anim_VehicleWorkbench_C");
		return ptr;
	}


	void ExecuteUbergraph_Anim_VehicleWorkbench(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
