#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_ColorGun_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_ColorGun.Anim_ColorGun_C
// 0x0A10 (0x0D70 - 0x0360)
class UAnim_ColorGun_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_29EA8947467ED618FD7415B65BEDC7F0;      // 0x0368(0x0070)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_00F6E1B64A52D18F883663B1C1A069A5;// 0x03D8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_A404DC48408EDC8FFABA07B273E61FF2;// 0x0488(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_B575227A40BD32CF1042BC8C0E27F6F9;// 0x04D0(0x0070)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_A1E6A0F9468528E213EC42AA6BDA2D43;// 0x0540(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_586EEFA64C946A07A78FC8B6A88E7EE8;// 0x0588(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_470D9FE34726B7A7DB664CB919E4BE16;// 0x0668(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_7500AAEF4A7586420BD58B854CF53E6D;// 0x0748(0x0050)
	struct FAnimNode_Root                              AnimGraphNode_Root_4B2FC81849D4A033E1F991982958B9F4;      // 0x0798(0x0048)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_7F04DFFF436DE81902964287C13D6EF7;// 0x07E0(0x00E0)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6687313246ECAA6943C95AA89D3AF8AD;// 0x08C0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4B344B1E4821A1BCC5B0A18790FC2036;// 0x0908(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_A12C331148FC48EA84995FAD20060B47;// 0x0950(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_661D43734BC356176DB5B5B47B93C0EA;// 0x0998(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DD23DDE74CA45B086D73BBA7060A2988;// 0x09E0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_D314A851446E855D8CF8E182E109E006;// 0x0A90(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C69AAC9B43E2ED3365ACAB9398FD016B;// 0x0AD8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_4A0882AA4A15D8B21FC0A6A4BEB55988;// 0x0B88(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_113C8A694519794D44F2AE8B47618B2F;// 0x0BD0(0x0070)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_198FE13249BC0C50CA0EDFA548EC44A5;// 0x0C40(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_E29F040742D537326A0FC1B964BDB4F8;// 0x0C88(0x00E0)
	bool                                               mIsEquipped;                                              // 0x0D68(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsReloading;                                             // 0x0D69(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasAmmunition;                                           // 0x0D6A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x0D6B(0x0001) MISSED OFFSET
	float                                              mSpeed;                                                   // 0x0D6C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_ColorGun.Anim_ColorGun_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ColorGun_AnimGraphNode_TransitionResult_4B344B1E4821A1BCC5B0A18790FC2036();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ColorGun_AnimGraphNode_TransitionResult_6687313246ECAA6943C95AA89D3AF8AD();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ColorGun_AnimGraphNode_TransitionResult_661D43734BC356176DB5B5B47B93C0EA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ColorGun_AnimGraphNode_TransitionResult_A12C331148FC48EA84995FAD20060B47();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_ColorGun(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
