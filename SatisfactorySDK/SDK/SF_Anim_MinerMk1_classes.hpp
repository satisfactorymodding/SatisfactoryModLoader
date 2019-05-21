#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_MinerMk1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_MinerMk1.Anim_MinerMk1_C
// 0x0A1B (0x13CB - 0x09B0)
class UAnim_MinerMk1_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_58ABB10C40A18882F1638E8CC151E46D;      // 0x09B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7041A21846343F6F20B12B87F046FACE;// 0x0A00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5586953F4FAB4C7B19E400885A50B47F;// 0x0A48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2B57AAD24131D2450C5ECBB5A708A642;// 0x0A90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_08F66A774DC7927D384EF28807B056AE;// 0x0AD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CD513362432B727911A9E8803FCAAC71;// 0x0B20(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_76E15C8B467013748B4298A539B242AD;// 0x0BD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_9367EEFD4B2726AD204A5A963FA1D0D4;// 0x0C18(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_702DB2E549606B966A7E64A1ED709808;// 0x0CC8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_309C66EC448B62CC35C683BBFDF9B3CE;// 0x0D10(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_F6D80F4F4D0DD6BCB95AF3B36177888B;// 0x0DC0(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_38D5FF5E4FBABE6A038C3596F2072BF0;// 0x0E08(0x0070)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_B24559DC4A16DED4752721B3414231C0;// 0x0E78(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_6015FC6B4562A27B99A1E3AA08A43F51;// 0x0EC0(0x00E0)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F09A4E7E4D87848227BD558A191FA9E8;// 0x0FA0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_28F3013B45B7F27F7C671C9902192B2B;// 0x0FE8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8F1DCDA842E034650112A287761EFBD3;// 0x1030(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_14E7082E43AC83DD7D0B8FB814CC7262;// 0x10E0(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_DBBB9FB441A3992584D11FA2C4136C3D;// 0x1128(0x0070)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_CB11984B4D370FFBE07A17B309EE18DA;// 0x1198(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_F58F64C1476CE7575D3BE4A3D8475BA6;// 0x11E0(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_5E5F517646F502BAC1218AA5E2E46B61;// 0x12C0(0x00E0)
	struct FTimerHandle                                mTimer;                                                   // 0x13A0(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	bool                                               mReadyForReload;                                          // 0x13A8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x13A9(0x0003) MISSED OFFSET
	float                                              mReloadTimer;                                             // 0x13AC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystemComponent*                    mDrillingVfx_01;                                          // 0x13B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mVentVfx_01;                                              // 0x13B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mVentVfx_02;                                              // 0x13C0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mAG_StartupToStartupOfflineTransition;                    // 0x13C8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_ProducingToSuspendedTransition_;                      // 0x13C9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_ToProducingTransition;                                // 0x13CA(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_MinerMk1.Anim_MinerMk1_C");
		return ptr;
	}


	void SetupReloadTimer();
	void ReloadTimer();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_MinerMk1_AnimGraphNode_SequencePlayer_9367EEFD4B2726AD204A5A963FA1D0D4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_MinerMk1_AnimGraphNode_TransitionResult_08F66A774DC7927D384EF28807B056AE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_MinerMk1_AnimGraphNode_SequencePlayer_309C66EC448B62CC35C683BBFDF9B3CE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_MinerMk1_AnimGraphNode_SequencePlayer_CD513362432B727911A9E8803FCAAC71();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_MinerMk1_AnimGraphNode_TransitionResult_28F3013B45B7F27F7C671C9902192B2B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_MinerMk1_AnimGraphNode_TransitionResult_5586953F4FAB4C7B19E400885A50B47F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_MinerMk1_AnimGraphNode_TransitionResult_7041A21846343F6F20B12B87F046FACE();
	void AnimNotify_MinerEnteredReloadState();
	void AnimNotify_StartDrillVFX();
	void BlueprintInitializeAnimation();
	void AnimNotify_OnResumeProducing();
	void AnimNotify_OnStopProducing();
	void AnimNotify_StartEngineLoop();
	void ExecuteUbergraph_Anim_MinerMk1(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
