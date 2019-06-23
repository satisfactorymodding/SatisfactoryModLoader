#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_OilPump_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_OilPump.Anim_OilPump_C
// 0x04E8 (0x0E98 - 0x09B0)
class UAnim_OilPump_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_CD1B59C9446CDD02F132DCA20D839CBF;      // 0x09B8(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2729557F406A49CCEAF030B9D88ADC02;// 0x09F8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_43F0088642F0F7CF36FDF4852D24B9BE;// 0x0A40(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_78BA76784E582F7D667CAC8F22AD1BB8;// 0x0A88(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_92613B6C49E875FC2F817CA2C8B5527D;// 0x0AD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_84238E4D40417405E0471B8943A4C67F;// 0x0B18(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_4B15F41A48E67B3A9CD6409CC5DF30C8;// 0x0BB8(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3638272D4A8FDBC4C03869B542A98FA0;// 0x0BF8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_1BAD3D6D4A0111911E5CF28E1B979DFD;// 0x0C98(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B1AA41E7409CA3CA198A27BB2CF76CC1;// 0x0CD8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_F8F1D1524F8F60565B1F099819E26664;// 0x0D78(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_274B27DB4DE33FE2EAD8F284EBA4649D;// 0x0DB8(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_OilPump.Anim_OilPump_C");
		return ptr;
	}


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
