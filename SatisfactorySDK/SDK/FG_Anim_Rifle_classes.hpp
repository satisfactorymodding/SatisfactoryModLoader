#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Rifle_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Rifle.Anim_Rifle_C
// 0x0BA3 (0x0F03 - 0x0360)
class UAnim_Rifle_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_6EFE0FA44A00D1B521AB0C8AFDCC8010;      // 0x0368(0x0048)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_199C33404DC0B661A4DA148B6361C228;      // 0x03B0(0x0070)
	struct FAnimNode_RigidBody                         AnimGraphNode_RigidBody_F15389EB446558A513A3DF954E1D4A04; // 0x0420(0x05A0)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_CBF17BA0490823773FB7E391B575D5CB;// 0x09C0(0x0048)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_E076FF1F4E5BE845C4B155A67CE3C888;// 0x0A08(0x0048)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_570D901C4DACE4282FB82D92DFDB8CDC;// 0x0A50(0x0160)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_9810A5E74A4B67E52CD4DEA7D9E5E937;// 0x0BB0(0x00D0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_56CE3D5A4EE9E42B4BDE2CBC7FFAEF6E;// 0x0C80(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_CBC2E475463486EDE66449B31CFC4518;// 0x0D60(0x0050)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_A09E7ADE4B949F2D2CF8AD9A0BF4794B;// 0x0DB0(0x0048)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_31AF89BD4A8F77ED5660CA8A504FBF69;// 0x0DF8(0x0050)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_4868CF684FB7843E03C72683A0097209;// 0x0E48(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_A1F9DAE7470D19FB227BBA85479F60FC;// 0x0E90(0x0070)
	bool                                               mHasAmmunition;                                           // 0x0F00(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasReloadedOnce;                                         // 0x0F01(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHideAmmoBox;                                             // 0x0F02(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Rifle.Anim_Rifle_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rifle_AnimGraphNode_BlendListByBool_9810A5E74A4B67E52CD4DEA7D9E5E937();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_Rifle(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
