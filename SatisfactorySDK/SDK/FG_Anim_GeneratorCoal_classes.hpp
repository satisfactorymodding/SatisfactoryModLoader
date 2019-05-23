#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_GeneratorCoal_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_GeneratorCoal.Anim_GeneratorCoal_C
// 0x0538 (0x0EE8 - 0x09B0)
class UAnim_GeneratorCoal_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_476CE0BA4DA46DBEC92EF39AC566BE55;      // 0x09B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6AFFA24E4E0AD020F19140B1B01896F5;// 0x0A00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F93745A74D5AA92D10BCD68ECA33B5ED;// 0x0A48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B47EBB67404893271FEE04B73B99898E;// 0x0A90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C148440A4E27971146F60EB2F8E9C97A;// 0x0AD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_32B40B744F4E6F72EAF58DB33F145162;// 0x0B20(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_84CDBDD9412D1A0B8051D4A9510F14A0;// 0x0BD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6EAB64214218EBFF68E2F1B380D16695;// 0x0C18(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_4D9A0C554A82051C2211A78BEA234970;// 0x0CC8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_4A4D20464ADEE6ADD34C73B560C1DCE9;// 0x0D10(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_8B6BF2094E5FB53F66E277A4ECE8A0D2;// 0x0DC0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_B9E9CE664FC796B1693B4ABEA83DB86B;// 0x0E08(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_GeneratorCoal.Anim_GeneratorCoal_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorCoal_AnimGraphNode_TransitionResult_B47EBB67404893271FEE04B73B99898E();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorCoal_AnimGraphNode_TransitionResult_C148440A4E27971146F60EB2F8E9C97A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorCoal_AnimGraphNode_SequencePlayer_32B40B744F4E6F72EAF58DB33F145162();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorCoal_AnimGraphNode_TransitionResult_F93745A74D5AA92D10BCD68ECA33B5ED();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorCoal_AnimGraphNode_SequencePlayer_6EAB64214218EBFF68E2F1B380D16695();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorCoal_AnimGraphNode_SequencePlayer_4A4D20464ADEE6ADD34C73B560C1DCE9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorCoal_AnimGraphNode_TransitionResult_6AFFA24E4E0AD020F19140B1B01896F5();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void AnimNotify_steamVfxNotify();
	void AnimNotify_CoalGenEnteredProducingState();
	void AnimNotify_CoalGenLeftProducingState();
	void AnimNotify_CoalGenEnteredOfflineState();
	void AnimNotify_CoalGenLeftOfflineState();
	void ExecuteUbergraph_Anim_GeneratorCoal(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
