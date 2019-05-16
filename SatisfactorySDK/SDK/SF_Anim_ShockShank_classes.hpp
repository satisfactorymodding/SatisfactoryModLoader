#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_ShockShank_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_ShockShank.Anim_ShockShank_C
// 0x0130 (0x0490 - 0x0360)
class UAnim_ShockShank_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_1EDC61494EA421D23288EA8843728A1E;      // 0x0368(0x0048)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_0C3946424C8F87A1D23B44860DFC1C55;      // 0x03B0(0x0070)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_42674141471884B6E6E5AEB7CB79E673;// 0x0420(0x0070)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_ShockShank.Anim_ShockShank_C");
		return ptr;
	}


	void AnimNotify_Notify_ShockShankAttack();
	void ExecuteUbergraph_Anim_ShockShank(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
