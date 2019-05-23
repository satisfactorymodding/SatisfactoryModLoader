#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ExplorerAnim_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass BP_ExplorerAnim.BP_ExplorerAnim_C
// 0x4794 (0x5104 - 0x0970)
class UBP_ExplorerAnim_C : public UVehicleAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0970(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_9D16FFC542ACACB41446D3B41131D86C;// 0x0978(0x0048)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_95CB199F42EBA61E1D50DCB63F7A6CF4;// 0x09C0(0x0050)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_DF7A6E0649DA38CDC5AEBAA271DFAE6B;// 0x0A10(0x00E0)
	struct FAnimNode_WheelHandler                      AnimGraphNode_WheelHandler_06A1607C450B688DE3C4B9B3D9729934;// 0x0AF0(0x0130)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_A0DAEA724119C1E42D184AA72251A7C6;  // 0x0C20(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_A5A2CF444B923CE796C68EA300D2BCD8;  // 0x0D70(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_036D72134DC53D40EC5EFBB1FDFDA5F6;  // 0x0EC0(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_0B69B53E4E4E84C89B8948B895BBC268;  // 0x1010(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_14AA1F9D46825B7B82B4BF83A9D81BE5;  // 0x1160(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_04A7420045AB7873D3926BA4EA271A20;  // 0x12B0(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_E61C317E4F6B5305D1E589B486601575;  // 0x1400(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_A31AE31E4D2E3ADA64EF06A3D011B86B;  // 0x1550(0x0150)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_E93252C045F42CB0B0173CA23E415699;    // 0x16A0(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_FFDE652E49A15280A21E57B0BB328BF3;    // 0x18E0(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_30C92DA748BCAEA96ED73F8F0B49895C;    // 0x1B20(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_5FC74B3142DFF53A58FB0AB238454F04;    // 0x1D60(0x0240)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_B146524D4D4BB8319B01918640C0AD35;  // 0x1FA0(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_879750BA4DEAC42643CF85909E7AFACE;  // 0x20F0(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_11764DD14E3EC588ED9C08B4B7DC4E30;  // 0x2240(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_A1B02EE042FACDAE601C44BB64DF440D;  // 0x2390(0x0150)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_9C42334243018DF1758710857AF3288E;    // 0x24E0(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_C0D41EF64CB70C68C726739C2E44B903;    // 0x2720(0x0240)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_A4AB4C314BE286894853B685A52F9E54;  // 0x2960(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_EC7A377E450BA942BB72D6850DCA4868;  // 0x2AB0(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_6C8481474888372BE888B1ABC35F5BC9;  // 0x2C00(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_891BAFB440B1A6605AEE749B846AA5DC;  // 0x2D50(0x0150)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_5AA6C0F8456D1265CEACD89C3C2D6299;    // 0x2EA0(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_FB70A99B495EA5C90BB8FA884E87A758;    // 0x30E0(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_DB8CEC874A0A15466AE45293E53648AB;    // 0x3320(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_6314DC9243535AAFCF41AD860B8A2DB3;    // 0x3560(0x0240)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_FDF3838D42178F6D76BB40A6076741FC;  // 0x37A0(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_E5721424416F722689A111B5F7BFFAB8;  // 0x38F0(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_9014D4E9498CAF45EA81D1AEBFB640B6;  // 0x3A40(0x0150)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_59C01284453EBDEA47334B96FE228089;  // 0x3B90(0x0150)
	struct FAnimNode_MeshSpaceRefPose                  AnimGraphNode_MeshRefPose_5A3F71E54788CA08AFF6B883F1ECF479;// 0x3CE0(0x0030)
	struct FAnimNode_Root                              AnimGraphNode_Root_BD8ADF2543CD3614801096AAEB591F0D;      // 0x3D10(0x0048)
	unsigned char                                      UnknownData00[0x8];                                       // 0x3D58(0x0008) MISSED OFFSET
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_367253004A34813987434C9DA5088629;    // 0x3D60(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_F23017784B86F49D5CC6D8AE2641F1CC;    // 0x3FA0(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_E50D54994D456D5EA1B9818B0A3C0523;    // 0x41E0(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_631E9B204DCAB8EFBAC521A2DDE32DC2;    // 0x4420(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_9B96CE004218AEBB0CB020BCDA249988;    // 0x4660(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_D9FE5F714E1ABAB3E0080893D8819C2C;    // 0x48A0(0x0240)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_CAE5F4CD4693937037AB489F6E27CEAD;// 0x4AE0(0x0160)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_6BCD400C4C41794BE73DCC80C70E733F;    // 0x4C40(0x0240)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_1F6F39E448BDA7BB449F7583DE271A80;    // 0x4E80(0x0240)
	struct FRotator                                    mPassengerRotation;                                       // 0x50C0(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mSteeringWheelLocationLeft;                               // 0x50CC(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mSteeringWheelRotation;                                   // 0x50D8(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float                                              mSteerAngle;                                              // 0x50E4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mSteeringWheelLocationRight;                              // 0x50E8(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mVelocity;                                                // 0x50F4(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float                                              mSpeed;                                                   // 0x5100(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass BP_ExplorerAnim.BP_ExplorerAnim_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_BP_ExplorerAnim_AnimGraphNode_ModifyBone_CAE5F4CD4693937037AB489F6E27CEAD();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_BP_ExplorerAnim(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
