#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_GeneratorFuel_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_GeneratorFuel.Anim_GeneratorFuel_C
// 0x0538 (0x0EE8 - 0x09B0)
class UAnim_GeneratorFuel_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_5E84AD75461F278ED3FBE2975E6424DF;      // 0x09B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_26125A344B9DED34195BDEB37E7D23E5;// 0x0A00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F97B320E45E0C9E565BA47BFFFC7484F;// 0x0A48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_CB02B87E41305029B6C4529024011E0D;// 0x0A90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F4B3DD684A170E4A4EE4A089E52E7C30;// 0x0AD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_10A4F85D4EB0F8DAD2904D987D832A56;// 0x0B20(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_13D8E6B14D7478D0CB72599C109BBD12;// 0x0BD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_EB2D152B46A297F5491322A150C6D863;// 0x0C18(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_A5ED11AF46ED5D262EBB99A5B77DC4C4;// 0x0CC8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_ADDF8C414177EAB5E999C999C0891FC7;// 0x0D10(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_8BA49C9E4BAE6CBA5CB85E84F16970F3;// 0x0DC0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_DCDA3E0546A1561350A3C39D6C32A6AB;// 0x0E08(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_GeneratorFuel.Anim_GeneratorFuel_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorFuel_AnimGraphNode_TransitionResult_CB02B87E41305029B6C4529024011E0D();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorFuel_AnimGraphNode_TransitionResult_F4B3DD684A170E4A4EE4A089E52E7C30();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorFuel_AnimGraphNode_SequencePlayer_10A4F85D4EB0F8DAD2904D987D832A56();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorFuel_AnimGraphNode_TransitionResult_F97B320E45E0C9E565BA47BFFFC7484F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorFuel_AnimGraphNode_SequencePlayer_EB2D152B46A297F5491322A150C6D863();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorFuel_AnimGraphNode_SequencePlayer_ADDF8C414177EAB5E999C999C0891FC7();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_GeneratorFuel_AnimGraphNode_TransitionResult_26125A344B9DED34195BDEB37E7D23E5();
	void AnimNotify_FuelGenEnteredProducingState();
	void AnimNotify_FuelGenLeftProducingState();
	void ExecuteUbergraph_Anim_GeneratorFuel(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
