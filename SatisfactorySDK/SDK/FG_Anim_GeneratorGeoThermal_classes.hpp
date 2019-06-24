#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_GeneratorGeoThermal_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_GeneratorGeoThermal.Anim_GeneratorGeoThermal_C
// 0x0330 (0x0690 - 0x0360)
class UAnim_GeneratorGeoThermal_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_C1ABFB86499F00687712BF9FCA9AB494;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8EEE8F6B439AC5D7ECE36EB60B3511EE;// 0x03A8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FB431E53464B360DDE4437836923CFCB;// 0x03F0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_0948BF3148C7AE9C890C5D9551833FB9;// 0x0490(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3096A41B4F67A59C0DB3C6A07204B54E;// 0x04D0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_B6D2B3A446F08F832B371A8F8EA0F46C;// 0x0570(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_85F1BD4D46ACDED06A44EBB5528E3CD8;// 0x05B0(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_GeneratorGeoThermal.Anim_GeneratorGeoThermal_C");
		return ptr;
	}


	void ExecuteUbergraph_Anim_GeneratorGeoThermal(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
