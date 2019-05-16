#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_OilPump_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_OilPump.Anim_OilPump_C
// 0x0538 (0x0EE8 - 0x09B0)
class UAnim_OilPump_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_CD1B59C9446CDD02F132DCA20D839CBF;      // 0x09B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2729557F406A49CCEAF030B9D88ADC02;// 0x0A00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_43F0088642F0F7CF36FDF4852D24B9BE;// 0x0A48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_78BA76784E582F7D667CAC8F22AD1BB8;// 0x0A90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_92613B6C49E875FC2F817CA2C8B5527D;// 0x0AD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_84238E4D40417405E0471B8943A4C67F;// 0x0B20(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_4B15F41A48E67B3A9CD6409CC5DF30C8;// 0x0BD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3638272D4A8FDBC4C03869B542A98FA0;// 0x0C18(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_1BAD3D6D4A0111911E5CF28E1B979DFD;// 0x0CC8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B1AA41E7409CA3CA198A27BB2CF76CC1;// 0x0D10(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_F8F1D1524F8F60565B1F099819E26664;// 0x0DC0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_274B27DB4DE33FE2EAD8F284EBA4649D;// 0x0E08(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_OilPump.Anim_OilPump_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilPump_AnimGraphNode_TransitionResult_78BA76784E582F7D667CAC8F22AD1BB8();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilPump_AnimGraphNode_TransitionResult_92613B6C49E875FC2F817CA2C8B5527D();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilPump_AnimGraphNode_SequencePlayer_84238E4D40417405E0471B8943A4C67F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilPump_AnimGraphNode_TransitionResult_43F0088642F0F7CF36FDF4852D24B9BE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilPump_AnimGraphNode_SequencePlayer_3638272D4A8FDBC4C03869B542A98FA0();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilPump_AnimGraphNode_SequencePlayer_B1AA41E7409CA3CA198A27BB2CF76CC1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_OilPump_AnimGraphNode_TransitionResult_2729557F406A49CCEAF030B9D88ADC02();
	void AnimNotify_BurnerFlareNotify();
	void AnimNotify_OilpumpEnteredProducingState();
	void AnimNotify_OilpumpLeftProducingState();
	void AnimNotify_OilpumpEnteredOfflineState();
	void AnimNotify_OilpumpLeftOfflineState();
	void ExecuteUbergraph_Anim_OilPump(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
