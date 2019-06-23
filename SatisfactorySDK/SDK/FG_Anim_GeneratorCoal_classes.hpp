#pragma once

// Satisfactory SDK

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
// 0x04E8 (0x0E98 - 0x09B0)
class UAnim_GeneratorCoal_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_476CE0BA4DA46DBEC92EF39AC566BE55;      // 0x09B8(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6AFFA24E4E0AD020F19140B1B01896F5;// 0x09F8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F93745A74D5AA92D10BCD68ECA33B5ED;// 0x0A40(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B47EBB67404893271FEE04B73B99898E;// 0x0A88(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C148440A4E27971146F60EB2F8E9C97A;// 0x0AD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_32B40B744F4E6F72EAF58DB33F145162;// 0x0B18(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_84CDBDD9412D1A0B8051D4A9510F14A0;// 0x0BB8(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6EAB64214218EBFF68E2F1B380D16695;// 0x0BF8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_4D9A0C554A82051C2211A78BEA234970;// 0x0C98(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_4A4D20464ADEE6ADD34C73B560C1DCE9;// 0x0CD8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_8B6BF2094E5FB53F66E277A4ECE8A0D2;// 0x0D78(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_B9E9CE664FC796B1693B4ABEA83DB86B;// 0x0DB8(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_GeneratorCoal.Anim_GeneratorCoal_C");
		return ptr;
	}


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
