#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_1PportableMiner_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_1PportableMiner.Anim_1PportableMiner_C
// 0x0979 (0x0CD9 - 0x0360)
class UAnim_1PportableMiner_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_94BF3D69485F1BDA691945AEDE6F098E;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B392C0124773DC7F9E6D158EE884C586;// 0x03A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9303EDE44A5AAF546D17639FD5DB9340;// 0x03F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2D899F194CC5AB60994BBBB3656A69C1;// 0x0438(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_DE80A22C462AAD6D4AF0FAA2C35116D6;// 0x0480(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_FEB68251477AF8323B3C37B67C6B8035;// 0x04C8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_88075AD545F4ED1673A522BFA69A3FCF;// 0x0510(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_18B9D1964A9FB7AF5749B89C511DA245;// 0x0558(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_BA6F90A8470AD1E89AB12BBEF20ABF61;// 0x05A0(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_DAF4981E4B54D8E6892513BC2C3282A0;// 0x0610(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D3F4C8F0451A784478AD31AAFAD33DCB;// 0x0650(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_8E5CD7EA4D49B23638C22F85A7B06133;// 0x06F0(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_784E3D5E4E2850538D163BA309393C4F;// 0x0730(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1009A665402C5052A95F3981BFF70542;// 0x0778(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F7BE25E84ED19F677421E4B3CD075D3D;// 0x07C0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_EC0E4B614015CECAAB55C2AC0AD2E642;// 0x0860(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6FC2C88241B960648E5260973462C8DB;// 0x08A0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_4645A75B4B717EC218EC9FAE4D66F29B;// 0x0940(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_112F9D3348C25F98EE5707AD5BD5A697;// 0x0980(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_6A94D1994C9BDBD826899797C4EAC97D;// 0x0A60(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3CCB3324488125C702F657A6B349FD99;// 0x0AA0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_6BDD87A648D8B88DD24CB0B043C389A9;// 0x0B40(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_98D1CA854E6B842D7A8F9982F6FEB5E1;// 0x0B80(0x00E0)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_6A35F4A94CA6F79C41FE53826D808744;      // 0x0C60(0x0068)
	float                                              mSpeed;                                                   // 0x0CC8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSpeedZ;                                                  // 0x0CCC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UCharacterMovementComponent*                 mCharacterMovementComponent;                              // 0x0CD0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	TEnumAsByte<EMovementMode>                         mMovementMode;                                            // 0x0CD8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_1PportableMiner.Anim_1PportableMiner_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_DE80A22C462AAD6D4AF0FAA2C35116D6();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_2D899F194CC5AB60994BBBB3656A69C1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_FEB68251477AF8323B3C37B67C6B8035();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_88075AD545F4ED1673A522BFA69A3FCF();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_18B9D1964A9FB7AF5749B89C511DA245();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_9303EDE44A5AAF546D17639FD5DB9340();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_784E3D5E4E2850538D163BA309393C4F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_1009A665402C5052A95F3981BFF70542();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1PportableMiner_AnimGraphNode_TransitionResult_B392C0124773DC7F9E6D158EE884C586();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_1PportableMiner(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
