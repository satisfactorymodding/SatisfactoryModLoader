#pragma once

// Satisfactory SDK

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
// 0x0309 (0x0669 - 0x0360)
class UWalkerAnimBP_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_413503994630E97C073489B1FEC9066B;      // 0x0368(0x0040)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_266D62DD44B286D763DAC0AB630AFA52;// 0x03A8(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_09A15877440B0B2E2AF6CEA42A36DBD0;// 0x04D0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_614EE10F49641CF197A0C8ACB4D6DC17;// 0x0510(0x00E0)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_D6056173467CA8DC949D4A93EC2478CB;      // 0x05F0(0x0068)
	float                                              Speed;                                                    // 0x0658(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x065C(0x0004) MISSED OFFSET
	class UAnimSequence*                               Animattack;                                               // 0x0660(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               Attacking;                                                // 0x0668(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass WalkerAnimBP.WalkerAnimBP_C");
		return ptr;
	}


	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_WalkerAnimBP(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
