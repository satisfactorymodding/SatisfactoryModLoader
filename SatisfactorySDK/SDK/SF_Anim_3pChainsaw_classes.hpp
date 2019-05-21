#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_3pChainsaw_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_3pChainsaw.Anim_3pChainsaw_C
// 0x0564 (0x08C4 - 0x0360)
class UAnim_3pChainsaw_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_C0B6EFA4455EB71334FA669C04623ABF;      // 0x0368(0x0070)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_20C85B554421CEEBABB57BA91BD5DE2C;// 0x03D8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_120678AF44707B76E294ABA1A2D963B9;// 0x0420(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3DAFC12A474129464341108FB3141E39;// 0x0468(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_FA05044B4261E0DE8B66D6BD2D3EC944;// 0x0518(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_7644957446EBBF866C88C08EC109F69C;// 0x0560(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_A47CB03A4872455F90E03F8B7700894C;// 0x05D0(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2CF818B14EE2BFED73E9BAA2FF6DEBF8;// 0x06A0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_ADC654C6411CD6C6F407CBAA655DBEA1;// 0x0750(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_62EDA5E14D70E445AB52D8B5CC1253C8;// 0x0798(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_Root_CB7274804EBE83EA405623B0D4B77274;      // 0x0878(0x0048)
	bool                                               mIsEquipped;                                              // 0x08C0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsSawing;                                                // 0x08C1(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsAttached;                                              // 0x08C2(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsSawingAttached;                                        // 0x08C3(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_3pChainsaw.Anim_3pChainsaw_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_3pChainsaw_AnimGraphNode_BlendListByBool_A47CB03A4872455F90E03F8B7700894C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_3pChainsaw_AnimGraphNode_TransitionResult_120678AF44707B76E294ABA1A2D963B9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_3pChainsaw_AnimGraphNode_TransitionResult_20C85B554421CEEBABB57BA91BD5DE2C();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_3pChainsaw(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
