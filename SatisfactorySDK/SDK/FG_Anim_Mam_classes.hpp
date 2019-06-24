#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Mam_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Mam.Anim_Mam_C
// 0x0759 (0x0AB9 - 0x0360)
class UAnim_Mam_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_01D867574B187EF6DEB2C884A64C96F0;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7B42FA4D4C5AE3B0E0A785B67992E8C9;// 0x03A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8A2BB1DC482B62F6D6BFDB8864303B73;// 0x03F0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_167D778F4E8F21A00AAF45A719F92437;// 0x0438(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_B186F3E242B672FCC46342B524F0DF41;// 0x04D8(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_08C75E904FD72C5338B2D9A40EBC4C92;// 0x0518(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_A36A15E44C81288DA35D04AA5E2B81AA;// 0x0588(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_37E767884A0B649D62AAC5985CFEA9F2;// 0x05C8(0x00E0)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8CA4CF194793432BEFBFA48EC6C1D6B4;// 0x06A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_09AFEC37414DF06BB3F61FA584003AF6;// 0x06F0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F0E0C19C4D9A0EECDC4E11A6A9EDB1AD;// 0x0738(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_66D3DC3A4CAECE2158FEAE9039683B3C;// 0x07D8(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_69E7373D4620DAA71B73E2939CDC337F;// 0x0818(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C876265F4AB1A30ABA865CBE8E3EFF24;// 0x0888(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_596EFA404E08C6DDBA8F42899D351DBA;// 0x08C8(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_F1F7800C4280C08FA300758394019E81;// 0x09A8(0x00D8)
	float                                              mDeltaTime;                                               // 0x0A80(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasPower;                                                // 0x0A84(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsProducing;                                             // 0x0A85(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0A86(0x0002) MISSED OFFSET
	int                                                mRandomAnim;                                              // 0x0A88(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0A8C(0x0004) MISSED OFFSET
	class UAnimSequence*                               mAnimSequence;                                            // 0x0A90(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystemComponent*                    mBeamVfx_01;                                              // 0x0A98(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mBeamVfx_02;                                              // 0x0AA0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mBeamVfx_03;                                              // 0x0AA8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mBeamVfx_04;                                              // 0x0AB0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mResetAnim;                                               // 0x0AB8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Mam.Anim_Mam_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Mam_AnimGraphNode_TransitionResult_7B42FA4D4C5AE3B0E0A785B67992E8C9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Mam_AnimGraphNode_TransitionResult_8CA4CF194793432BEFBFA48EC6C1D6B4();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void BlueprintInitializeAnimation();
	void HasPowerChanged(bool State);
	void AnimNotify_MamEnteredProducing();
	void AnimNotify_MamLeftProducing();
	void BlueprintBeginPlay();
	void ExecuteUbergraph_Anim_Mam(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
