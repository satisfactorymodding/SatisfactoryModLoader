#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Chainsaw_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Chainsaw.Anim_Chainsaw_C
// 0x0E95 (0x11F5 - 0x0360)
class UAnim_Chainsaw_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_C2C5740A4952632C0C5B7780112B635F;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F9A492804273E08EF63B95978512DE6A;// 0x03A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_EF38A83345031AA5B90DD29377325799;// 0x03F0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_645CACA447A16826A6CBD6AA69C52390;// 0x0438(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_D92C6E56420A0E1F801358B183967DC4;// 0x04D8(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_1727E0BB4A18DA61FCAF4A9F94CEEB75;// 0x0518(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_9007B9E84DDD1F1ECE97E0AE8115C5EE;// 0x0588(0x00D0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_DDE36D904892A860342201AC72D75FB8;// 0x0658(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_C38122B74370F3AA6202B5B035DBE849;// 0x06C8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7D59850840C953202B7FF1A7E60FE808;// 0x0798(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C1B1D0E14977E2CA5AAC7C9450F4E779;// 0x0838(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_AD418394470247B2D8B9BD919781C4D0;// 0x0878(0x00E0)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_635C51664192D16D6ADE3DBF711A9E0D;      // 0x0958(0x0068)
	struct FAnimNode_RigidBody                         AnimGraphNode_RigidBody_0B59DAE945A11D83CF7103B7DAA6DC72; // 0x09C0(0x0570)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_A542F3C74DFDB817A56CA883FE28FAC1;// 0x0F30(0x0040)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_A011C58C4DD2C7CBAFC9029BFB272DFF;// 0x0F70(0x0040)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_FC242C4B4CCD700BAA4329AB59C7A6D3;// 0x0FB0(0x00D8)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_2D5F027F4B5E6B1CCE1877911CCE77A4;// 0x1088(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_4FCF7B814F5929A44F32A7988B42EAD9;// 0x1160(0x0048)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_3A722F914677C78D08A950AF2DD714FA;// 0x11A8(0x0048)
	bool                                               mIsEquipped;                                              // 0x11F0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsSawing;                                                // 0x11F1(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsAttached;                                              // 0x11F2(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsSawingAttached;                                        // 0x11F3(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasFuel;                                                 // 0x11F4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Chainsaw.Anim_Chainsaw_C");
		return ptr;
	}


	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Chainsaw_AnimGraphNode_BlendListByBool_C38122B74370F3AA6202B5B035DBE849();
	void AnimNotify_ChainSawTransition_IdleToSawing();
	void AnimNotify_ChainSawTransition_SawingToIdle();
	void ExecuteUbergraph_Anim_Chainsaw(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
