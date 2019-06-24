#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_3pChainsaw_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_3pChainsaw.Anim_3pChainsaw_C
// 0x0524 (0x0884 - 0x0360)
class UAnim_3pChainsaw_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_C0B6EFA4455EB71334FA669C04623ABF;      // 0x0368(0x0068)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_20C85B554421CEEBABB57BA91BD5DE2C;// 0x03D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_120678AF44707B76E294ABA1A2D963B9;// 0x0418(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3DAFC12A474129464341108FB3141E39;// 0x0460(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_FA05044B4261E0DE8B66D6BD2D3EC944;// 0x0500(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_7644957446EBBF866C88C08EC109F69C;// 0x0540(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_A47CB03A4872455F90E03F8B7700894C;// 0x05B0(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2CF818B14EE2BFED73E9BAA2FF6DEBF8;// 0x0680(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_ADC654C6411CD6C6F407CBAA655DBEA1;// 0x0720(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_62EDA5E14D70E445AB52D8B5CC1253C8;// 0x0760(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_Root_CB7274804EBE83EA405623B0D4B77274;      // 0x0840(0x0040)
	bool                                               mIsEquipped;                                              // 0x0880(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsSawing;                                                // 0x0881(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsAttached;                                              // 0x0882(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsSawingAttached;                                        // 0x0883(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_3pChainsaw.Anim_3pChainsaw_C");
		return ptr;
	}


	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_3pChainsaw(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
