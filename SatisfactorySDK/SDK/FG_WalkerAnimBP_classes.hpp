#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_WalkerAnimBP_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass WalkerAnimBP.WalkerAnimBP_C
// 0x0321 (0x0681 - 0x0360)
class UWalkerAnimBP_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_413503994630E97C073489B1FEC9066B;      // 0x0368(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_266D62DD44B286D763DAC0AB630AFA52;// 0x03B0(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_09A15877440B0B2E2AF6CEA42A36DBD0;// 0x04D8(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_614EE10F49641CF197A0C8ACB4D6DC17;// 0x0520(0x00E0)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_D6056173467CA8DC949D4A93EC2478CB;      // 0x0600(0x0070)
	float                                              Speed;                                                    // 0x0670(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0674(0x0004) MISSED OFFSET
	class UAnimSequence*                               Animattack;                                               // 0x0678(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               Attacking;                                                // 0x0680(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass WalkerAnimBP.WalkerAnimBP_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_WalkerAnimBP_AnimGraphNode_BlendSpacePlayer_266D62DD44B286D763DAC0AB630AFA52();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_WalkerAnimBP(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
