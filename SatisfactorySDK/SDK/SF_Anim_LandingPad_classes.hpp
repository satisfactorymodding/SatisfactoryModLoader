#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_LandingPad_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_LandingPad.Anim_LandingPad_C
// 0x0660 (0x09C0 - 0x0360)
class UAnim_LandingPad_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_9A8789434B768F1C5ADF8B8D231C57DA;      // 0x0368(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E4A0A1484FD618C09AC43E9C16D4A37B;// 0x03B0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_FC0C6E7D43EE683F25EFAABABC9E0759;// 0x03F8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C2876A294300AB58F38D12BD82860D4A;// 0x0440(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1EB610874256993492C21CB7314D49F1;// 0x0488(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5FE59C4D4958213A2D0083B3058EEE2D;// 0x04D0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_4BF461E44B6F7A4F2301908D4627176E;// 0x0518(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_2FA6F9FE4D6CD97D3239F6BBC1A8627A;// 0x05C8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D3AF394046102DDB0B9782B6A1B62E37;// 0x0610(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_122549E54CD70E36BF637FA52252C436;// 0x06C0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FA362D6C4A7FF5BC712C27B8EF56E8C3;// 0x0708(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_1E5A604249424B5E8188D9AAD0614A52;// 0x07B8(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_A9BC56114E90BD8D4A22098EBB5ADAC2;// 0x0800(0x0070)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_9158BB3E4AF09A3CAC28A39F9ED7ED98;// 0x0870(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_B85EB4F34432941C37832095720BB0D8;// 0x08B8(0x00E0)
	bool                                               mHasPower;                                                // 0x0998(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0999(0x0007) MISSED OFFSET
	class UParticleSystemComponent*                    mBiogenVfx_01;                                            // 0x09A0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mBiogenVfx_02;                                            // 0x09A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	float                                              mDeltaTime;                                               // 0x09B0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x09B4(0x0004) MISSED OFFSET
	class UParticleSystemComponent*                    mFunnelVfx;                                               // 0x09B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_LandingPad.Anim_LandingPad_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_LandingPad_AnimGraphNode_TransitionResult_C2876A294300AB58F38D12BD82860D4A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_LandingPad_AnimGraphNode_TransitionResult_1EB610874256993492C21CB7314D49F1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_LandingPad_AnimGraphNode_TransitionResult_5FE59C4D4958213A2D0083B3058EEE2D();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_LandingPad_AnimGraphNode_TransitionResult_FC0C6E7D43EE683F25EFAABABC9E0759();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_LandingPad_AnimGraphNode_TransitionResult_E4A0A1484FD618C09AC43E9C16D4A37B();
	void HasPowerChanged(bool State);
	void BlueprintInitializeAnimation();
	void ExecuteUbergraph_Anim_LandingPad(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
