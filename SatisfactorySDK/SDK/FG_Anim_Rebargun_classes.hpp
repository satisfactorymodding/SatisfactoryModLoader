#pragma once

// Satisfactory SDK

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
// 0x065B (0x09BB - 0x0360)
class UAnim_Rebargun_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_8D2C8AC9425BAC78CC6873AD45D65449;      // 0x0368(0x0040)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_756D4D614AF05578E7E2248C52535E0C;      // 0x03A8(0x0068)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6BD2A36D4B5EE69E25775294CF5CCD45;// 0x0410(0x00A0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_B47BC2C0483BB4FA39187EB917D97637;// 0x04B0(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_3B26FA7D4EDFCEFAB4460CA93417414C;// 0x0520(0x00D0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_530A8A3749207BE46459A6BB878334B7;// 0x05F0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_AC4CB12D45243B5B9CCC898C4E70E57B;// 0x0630(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_F0B807EA466560AF3274EA82FFD7D3DA;// 0x0710(0x00D8)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_04E9A32D44CCC62BF9EEA6BFE8952B80;// 0x07E8(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_4ECE27C2491B5622B9BEE49A1FFE5F82;// 0x08C0(0x0048)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_AEB3CAC54DC31D2DD4D8DAA19B832259;      // 0x0908(0x0068)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_570548254EC917AFABEB0D80CAF4A0A6;// 0x0970(0x0048)
	bool                                               mHasAmmunition;                                           // 0x09B8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsLoaded;                                                // 0x09B9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsReloading;                                             // 0x09BA(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

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
