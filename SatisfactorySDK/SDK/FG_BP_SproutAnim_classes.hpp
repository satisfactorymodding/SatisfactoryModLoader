#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SproutAnim_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass BP_SproutAnim.BP_SproutAnim_C
// 0x0854 (0x0BB4 - 0x0360)
class UBP_SproutAnim_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_03EB627F4C31D0339B5B888DF0CB3513;// 0x0368(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_218218A546BB90266FEFC8ADE06E967A;// 0x03B0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_80C2EEF1489AA6A9F6B3BF8EC59A0D6F;// 0x03F8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_BEDE9B5B4A32AEFD9C4943B1E8F5E4C7;// 0x0440(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_7AAD6B3945CDF183EA121FB02C3D6D86;// 0x04F0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D2FD93EA43CCF859040213A3D13F6E05;// 0x0538(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_92D1DD214BA1145F5111E5BE6E5D5DBB;// 0x05E8(0x0048)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_6DDD733B422063ADD11757AD4735B8B8;// 0x0630(0x0090)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_619F085A4A2D2A73D3D23F95D4C6E716;// 0x06C0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_791D6171414E77B05E71FEA5206F5FB2;// 0x0708(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_Root_6979F738456F1B1029D419A5C69C1F2E;      // 0x07E8(0x0048)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_79860B6A4014053CA98D26889CDB7607;// 0x0830(0x0048)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_3CDFEACF4CE1A2ACDADC58A050AC2E8B;// 0x0878(0x0048)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_101513C6454F1E16B1E9508BCBEADDB8;// 0x08C0(0x0160)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_9118B9334A32307C5806778687F0E621;// 0x0A20(0x0160)
	struct FVector                                     mScaleMesh_01;                                            // 0x0B80(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	bool                                               mSubmerge;                                                // 0x0B8C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0B8D(0x0003) MISSED OFFSET
	struct FRotator                                    mSproutRotator_01;                                        // 0x0B90(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mSproutRotator_02;                                        // 0x0B9C(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mScaleMesh_02;                                            // 0x0BA8(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass BP_SproutAnim.BP_SproutAnim_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_BP_SproutAnim_AnimGraphNode_ModifyBone_101513C6454F1E16B1E9508BCBEADDB8();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_BP_SproutAnim_AnimGraphNode_ModifyBone_9118B9334A32307C5806778687F0E621();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_BP_SproutAnim_AnimGraphNode_TransitionResult_218218A546BB90266FEFC8ADE06E967A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_BP_SproutAnim_AnimGraphNode_TransitionResult_80C2EEF1489AA6A9F6B3BF8EC59A0D6F();
	void BlueprintInitializeAnimation();
	void ExecuteUbergraph_BP_SproutAnim(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
