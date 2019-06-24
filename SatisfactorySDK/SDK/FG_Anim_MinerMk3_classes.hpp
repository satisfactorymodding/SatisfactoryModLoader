#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_MinerMk3_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_MinerMk3.Anim_MinerMk3_C
// 0x0CFB (0x105B - 0x0360)
class UAnim_MinerMk3_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_9490786F4ABD7B663FBA2AA9AEA7EF9A;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4624E7904C75388508BA90916F6BC2FB;// 0x03A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_58C5A66A4D8050EEB23D5D9D9D6D9363;// 0x03F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9A3E8465470CB691D8F3528833E34714;// 0x0438(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5383FC6245FC913C36B979AFDF90F8D1;// 0x0480(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_DB9F2D8B4EBD9E4E56D7A48BCC32F296;// 0x04C8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6F0A569A406F08FF75E608AFD729E238;// 0x0510(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E065F66443945C301036A490F260860A;// 0x0558(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_712C152D4B2B6B7C692ACBBEDF7E5376;// 0x05F8(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0F970CA6467796C23354E490C7B2A14A;// 0x0638(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_0487BBA044B744F4804AF3ACECC1264E;// 0x06D8(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E29A1E4B4E5F1BA784C34FB52004755B;// 0x0718(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_9A02610D4B59053BDA804A8CE879B376;// 0x07B8(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7CC1A0994AEA741E22D47288756CC648;// 0x07F8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_863B3A6C4C736F8A214F098A87634661;// 0x0898(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DF3B36DE48E2F3181262E0A04EEFDFE8;// 0x08D8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C092B6EC459FE957662F1492C8B21B01;// 0x0978(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_EC3A03FF4F1C7C11B10C9CB3C71E6B29;// 0x09B8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_ECAFA84240D5F417322800A53AF7A0F5;// 0x0A58(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_A3219A214AB8688CBFCF9AB97C37F989;// 0x0A98(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_078CEEDA487886164A9BCABDE7130358;// 0x0B08(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_7C284094469F10334E637BA9DDC1F28E;// 0x0B48(0x00E0)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B09E37534533D87488634D8AF48FB0A5;// 0x0C28(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3E21833947DC6F75C2A178A42402E782;// 0x0C70(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1CC21BE047CCB6C8F0F731BC0813163C;// 0x0CB8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_402A801B4AD097693C918C922D695D21;// 0x0D58(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_58FF5E144384BBB4E838A39F169E2AA7;// 0x0D98(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_FD9A72744A0CAB08FF3321B7BFB7BB48;// 0x0E08(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_7DBAECCE4240AD73643EF7B3E38AB979;// 0x0E48(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_586118144A8D3C852557F4B208C1DD93;// 0x0F28(0x00D8)
	float                                              mDeltaTime;                                               // 0x1000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsProducing;                                             // 0x1004(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasPower;                                                // 0x1005(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x1006(0x0002) MISSED OFFSET
	class UParticleSystem*                             mFirstParticle;                                           // 0x1008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAnimPlayRate;                                            // 0x1010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeNotProducing;                                        // 0x1014(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRampItUpTime;                                            // 0x1018(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRampDownTime;                                            // 0x101C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mReadyForReload;                                          // 0x1020(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x1021(0x0007) MISSED OFFSET
	class UParticleSystemComponent*                    mDrillingVfx_01;                                          // 0x1028(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mVentVfx_01;                                              // 0x1030(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mVentVfx_02;                                              // 0x1038(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mDrillingVfx_02;                                          // 0x1040(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	float                                              mReloadTimer;                                             // 0x1048(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x104C(0x0004) MISSED OFFSET
	struct FTimerHandle                                mTimer;                                                   // 0x1050(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	bool                                               mAG_StartupToStartupOfflineTransition;                    // 0x1058(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_ProducingToSuspendedTransition_;                      // 0x1059(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_ToProducingTransition;                                // 0x105A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_MinerMk3.Anim_MinerMk3_C");
		return ptr;
	}


	void CalculateAnimGraphVariables();
	void ReloadTimer();
	void SetupReloadTimer();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void AnimNotify_StartDrillVFX();
	void AnimNotify_StopDrillVfx();
	void BlueprintInitializeAnimation();
	void AnimNotify_MinerIndustrialEnteredReloadState();
	void AnimNotify_MinerIndustrialEnteredOutputFullState();
	void AnimNotify_MinerIndustrialLeftOutputFullState();
	void AnimNotify_MinerIndustrialAudioStartSpin();
	void AnimNotify_MinerIndustrialAudioDrillDown();
	void AnimNotify_MinerIndustrialAudioStopDrill();
	void AnimNotify_MinerIndustrialAudioLowpassOn();
	void AnimNotify_MinerIndustrialAudioLowpassOff();
	void HasPowerChanged(bool State);
	void ExecuteUbergraph_Anim_MinerMk3(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
