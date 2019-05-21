#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_SeaSlugAnim_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass BP_SeaSlugAnim.BP_SeaSlugAnim_C
// 0x05B1 (0x0A31 - 0x0480)
class UBP_SeaSlugAnim_C : public UFGCharacterAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0480(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_62569A55495B2BF69FA237AF948B684A;      // 0x0488(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4942E5B04BC541E81411BFBAE14430EE;// 0x04D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_42FDDF7C47EE5CB5A20F0481B99344F3;// 0x0518(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6646F8BC4A5594CC335E8C93F8BF3EB2;// 0x0560(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C6C92D5B47863D503BE143916BD58CF3;// 0x05A8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_44E248844DE1C4479BCAC3B42C20EEE6;// 0x0658(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5614B94742E645BAA8F26EA4D112B254;// 0x06A0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_A977037842E6363D8AB836A885F34CAD;// 0x0750(0x0048)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_5E9739AC4C0282F2CA7DA48FAB7A9204;// 0x0798(0x0090)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_B69D94624F2BB22CFFEB5EB55C9F049A;// 0x0828(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_7A3033A749993EB96E9F309BFCB780AD;// 0x0870(0x00E0)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_4A985A5D49AFBBA102C113B297037FBF;// 0x0950(0x00E0)
	bool                                               mIsDiving;                                                // 0x0A30(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass BP_SeaSlugAnim.BP_SeaSlugAnim_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_BP_SeaSlugAnim_AnimGraphNode_TransitionResult_42FDDF7C47EE5CB5A20F0481B99344F3();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_BP_SeaSlugAnim_AnimGraphNode_TransitionResult_6646F8BC4A5594CC335E8C93F8BF3EB2();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void AnimNotify_PlayRippleVfX_notify();
	void AnimNotify_PlayRippleVfx_02_notify();
	void AnimNotify_PlayRippleVfx_03_notify();
	void ExecuteUbergraph_BP_SeaSlugAnim(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
