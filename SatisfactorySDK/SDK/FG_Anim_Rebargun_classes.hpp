#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Rebargun_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Rebargun.Anim_Rebargun_C
// 0x06AB (0x0A0B - 0x0360)
class UAnim_Rebargun_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_8D2C8AC9425BAC78CC6873AD45D65449;      // 0x0368(0x0048)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_756D4D614AF05578E7E2248C52535E0C;      // 0x03B0(0x0070)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6BD2A36D4B5EE69E25775294CF5CCD45;// 0x0420(0x00B0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_B47BC2C0483BB4FA39187EB917D97637;// 0x04D0(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_3B26FA7D4EDFCEFAB4460CA93417414C;// 0x0540(0x00D0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_530A8A3749207BE46459A6BB878334B7;// 0x0610(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_AC4CB12D45243B5B9CCC898C4E70E57B;// 0x0658(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_F0B807EA466560AF3274EA82FFD7D3DA;// 0x0738(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_04E9A32D44CCC62BF9EEA6BFE8952B80;// 0x0818(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_4ECE27C2491B5622B9BEE49A1FFE5F82;// 0x08F8(0x0050)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_AEB3CAC54DC31D2DD4D8DAA19B832259;      // 0x0948(0x0070)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_570548254EC917AFABEB0D80CAF4A0A6;// 0x09B8(0x0050)
	bool                                               mHasAmmunition;                                           // 0x0A08(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsLoaded;                                                // 0x0A09(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsReloading;                                             // 0x0A0A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Rebargun.Anim_Rebargun_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rebargun_AnimGraphNode_BlendListByBool_3B26FA7D4EDFCEFAB4460CA93417414C();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void AnimNotify_RebargunIsLoaded_Notify();
	void ExecuteUbergraph_Anim_Rebargun(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
