#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_OilRefinery_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_OilRefinery.Anim_OilRefinery_C
// 0x0538 (0x0EE8 - 0x09B0)
class UAnim_OilRefinery_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_CBCE913148CE8388847B899C045DA7EF;      // 0x09B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_00E703984606D1BEF63D9A807E113CCD;// 0x0A00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_ADC926934470782C4CC4E4AA0FAF9BD1;// 0x0A48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_771BDC794315C97B9114B58B67D53B9B;// 0x0A90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_915C10B24BBBA51A6DF22CA3D0A78740;// 0x0AD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F1EFB75748441598AB354FA6C373C89A;// 0x0B20(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_799652C04926A7D14C3B9B9464EBA382;// 0x0BD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_13C879DC4AE2357A23B328B1442B4914;// 0x0C18(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_20005D57406917AB275022AF289D1ABD;// 0x0CC8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_049CFCF849B615B553EE89B9F2D39FC7;// 0x0D10(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_E3C458DB4736AB304731AF87288BA4A0;// 0x0DC0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_27BD71104A268AB51298FD84C7E61F6C;// 0x0E08(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_OilRefinery.Anim_OilRefinery_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilRefinery_AnimGraphNode_TransitionResult_771BDC794315C97B9114B58B67D53B9B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilRefinery_AnimGraphNode_TransitionResult_915C10B24BBBA51A6DF22CA3D0A78740();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilRefinery_AnimGraphNode_SequencePlayer_F1EFB75748441598AB354FA6C373C89A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilRefinery_AnimGraphNode_TransitionResult_ADC926934470782C4CC4E4AA0FAF9BD1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilRefinery_AnimGraphNode_SequencePlayer_13C879DC4AE2357A23B328B1442B4914();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilRefinery_AnimGraphNode_SequencePlayer_049CFCF849B615B553EE89B9F2D39FC7();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilRefinery_AnimGraphNode_TransitionResult_00E703984606D1BEF63D9A807E113CCD();
	void AnimNotify_OilRefineryEnteredOffline();
	void AnimNotify_OilRefineryEnteredProducing();
	void AnimNotify_OilRefineryLeftOffline();
	void AnimNotify_OilRefineryLeftProducing();
	void ExecuteUbergraph_Anim_OilRefinery(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
