#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Beacon_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Beacon.Anim_Beacon_C
// 0x00E8 (0x0448 - 0x0360)
class UAnim_Beacon_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_DE6AE9EF4B223BA4744B01B8C1BFFCE2;      // 0x0368(0x0040)
	struct FAnimNode_RefPose                           AnimGraphNode_LocalRefPose_37EF49644A8D9662DB458F8BC9F0174E;// 0x03A8(0x0038)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_9D6B724149F3026767E821A35A55EAB0;      // 0x03E0(0x0068)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Beacon.Anim_Beacon_C");
		return ptr;
	}


	void ExecuteUbergraph_Anim_Beacon(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
