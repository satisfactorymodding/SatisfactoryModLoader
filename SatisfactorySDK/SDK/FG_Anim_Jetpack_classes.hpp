#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

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
// 0x0435 (0x0795 - 0x0360)
class UAnim_Jetpack_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_211DD88A48FD16E577A2C7B3C5BC5134;      // 0x0368(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4BE4DAB24DFBF4B7874053932CFC86FF;// 0x03B0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_BB0735394DCC5B947AF456B82D2E797A;// 0x03F8(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_A552F60447EAB45773E3589038904EB9;// 0x0440(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_7FFF784647F281A096030EACA15447AC;// 0x0568(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_318D6A244F4F68778403738BF13027AE;// 0x05B0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_1EC7E4604960CDD4F0C3FF9E72393948;// 0x0660(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_5EDE350942F2CDCB9F42F78AE5FA0D06;// 0x06A8(0x00E0)
	struct FVector                                     mVelocityLocalNormalized;                                 // 0x0788(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EMovementMode>                         mCharacterMovementMode;                                   // 0x0794(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Jetpack.Anim_Jetpack_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Jetpack_AnimGraphNode_TransitionResult_BB0735394DCC5B947AF456B82D2E797A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Jetpack_AnimGraphNode_BlendSpacePlayer_A552F60447EAB45773E3589038904EB9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Jetpack_AnimGraphNode_TransitionResult_4BE4DAB24DFBF4B7874053932CFC86FF();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_Jetpack(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
