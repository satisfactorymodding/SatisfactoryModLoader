#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Jetpack_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Jetpack.Anim_Jetpack_C
// 0x040D (0x076D - 0x0360)
class UAnim_Jetpack_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_211DD88A48FD16E577A2C7B3C5BC5134;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4BE4DAB24DFBF4B7874053932CFC86FF;// 0x03A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_BB0735394DCC5B947AF456B82D2E797A;// 0x03F0(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_A552F60447EAB45773E3589038904EB9;// 0x0438(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_7FFF784647F281A096030EACA15447AC;// 0x0560(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_318D6A244F4F68778403738BF13027AE;// 0x05A0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_1EC7E4604960CDD4F0C3FF9E72393948;// 0x0640(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_5EDE350942F2CDCB9F42F78AE5FA0D06;// 0x0680(0x00E0)
	struct FVector                                     mVelocityLocalNormalized;                                 // 0x0760(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EMovementMode>                         mCharacterMovementMode;                                   // 0x076C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Jetpack.Anim_Jetpack_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Jetpack_AnimGraphNode_TransitionResult_4BE4DAB24DFBF4B7874053932CFC86FF();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Jetpack_AnimGraphNode_TransitionResult_BB0735394DCC5B947AF456B82D2E797A();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_Jetpack(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
