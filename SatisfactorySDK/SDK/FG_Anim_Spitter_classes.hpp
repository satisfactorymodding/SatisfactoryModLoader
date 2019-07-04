#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Spitter_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Spitter.Anim_Spitter_C
// 0x3544 (0x39C4 - 0x0480)
class UAnim_Spitter_C : public UFGCharacterAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0480(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5BD90E984D6796E56563089F4ACCDDE4;// 0x0488(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9E855A614B2C00878464659B421B6957;// 0x04D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_859CB71B400A285FD10921A3622FD363;// 0x0518(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F23BD76A41466F02C635A592A9D6426E;// 0x0560(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_ECD147D7452E69903A384283814F58B6;// 0x0600(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C44C51ED4F818D71B9F86383BAB5CB94;// 0x0640(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_F7224D0447316CE0FF902088F4672CD3;// 0x06E0(0x0040)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_D757052A4F249B5C75DC7FA9A2723AFD;// 0x0720(0x0048)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_ACBAF4004867676CE8E9A6BB321D5BBE;// 0x0768(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_88A713DA4F023ECEFDDF3BB14D3A67C2;// 0x07A8(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_5180F85E4B1382ACE4619994C00603E6;// 0x0888(0x00D8)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_A37ED50840B43A10C94D27A560E5CE31;      // 0x0960(0x0068)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_5C81ED2D48ED2DDA200F30965C02B641;// 0x09C8(0x0040)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_92692D02456B919175717D870DDF4F62;// 0x0A08(0x00D8)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_0EDFA364495F59F0F3E109A067D2082F;// 0x0AE0(0x0040)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_52ED8B21439083F459931EA284050C70;// 0x0B20(0x00D0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_736E9DB641F02C1F28CE9884428D349A;// 0x0BF0(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_583465874EEDFCE1A9E7D0BE9B105BE6;// 0x0D28(0x0138)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_ADE043E940FEF0F7E6B3ADA008CC9BD6;// 0x0E60(0x0048)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_EA2CF3DD49BFD5733F2F8D9D79990EA3;// 0x0EA8(0x0040)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_3181EBF047E682449B9252BEAF245A7E;// 0x0EE8(0x0040)
	struct FAnimNode_Root                              AnimGraphNode_Root_326D0E194C81A2D2AC420F87B27FDA6F;      // 0x0F28(0x0040)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_C18BB37D4B1D825BE1CCA3891B68D428;// 0x0F68(0x00C0)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_A8CFAE9743E1FC7400894FA5E04F37C2;// 0x1028(0x01E0)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_4F085E3A4CFE735A67ECAFB6074B7826;// 0x1208(0x00C0)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_29C6E07F497EADE11A9A6CB1D3000664;// 0x12C8(0x00C0)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_BCB948424416820B1BE0DE97D7DD494A;// 0x1388(0x0040)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_40A559F94521F02CAC3583BE1E2656E8;// 0x13C8(0x0040)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_1D003B53445C53C24083AFA900A7EB8C;// 0x1408(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D9705CD24FE33AC56B24A284E00AF0AF;// 0x1450(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8E5A1D07496F259FAB1CA784A576A92C;// 0x1498(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F81A446448B97515A5625FB6A475D546;// 0x14E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4310C5404B3437ADDA794CBC5402756F;// 0x1528(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3D3C07184FDB1D2068B6578E6DA75635;// 0x1570(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_48A9498844D1C6E9B8C312BB8B146B0A;// 0x1610(0x0040)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_BC462D524C94CDC5A72A3D8CA97E5A38;// 0x1650(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C80138B944135429A735CEB92CCFBBCE;// 0x1778(0x0040)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_A615D64F4DA7478BC9CCAB8F1D8553C1;// 0x17B8(0x0038)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_D21255074ABB4E05E99C2B8AF7E0DA56;// 0x17F0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_269E76154924780C646867A7ECBA82D6;// 0x1830(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_6E8290A147274A148033C49A8B84A898;// 0x1910(0x0048)
	struct FAnimNode_ApplyAdditive                     AnimGraphNode_ApplyAdditive_63C8DC9B41A7C7A9E99695AD1B0C4526;// 0x1958(0x00F0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_984822D64B68940EB8DCB3A362C28AF4;// 0x1A48(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_2C4732F34C31F78D5E66918DC23C405E;// 0x1B20(0x0048)
	unsigned char                                      UnknownData00[0x8];                                       // 0x1B68(0x0008) MISSED OFFSET
	struct FAnimNode_RigidBody                         AnimGraphNode_RigidBody_501BA8894A0ADF068C073D9805E13285; // 0x1B70(0x0570)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C9A2C4744CC31A8CA3DA6398B7FABFD2;// 0x20E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6C95A5994FDAA7019F770ABB935AC6A6;// 0x2128(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4DD16A0C4514EEBD175A42BAF5B04F2F;// 0x2170(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4125F5E84ACF3BC77FAA7B8754C9577E;// 0x21B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F59AB4D046321D1D1D4ED6BFFA4CE266;// 0x2200(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E5A14AC943454B0D928B91923D852F46;// 0x2248(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_04C813FB491ABC2E1F0127A0FC731DE7;// 0x2290(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_75AE1D524F1EE16230E5FBBE9E8D9A6D;// 0x22D8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_622FF2EF4AF81337AF4B3C83FEF600C7;// 0x2320(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_466373D846257892BA73B098CECD65C1;// 0x23C0(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DFAADCBA42BC49E774B226A8660D8F38;// 0x2400(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_605A4E94431E7BFA0454EF93F8352C1E;// 0x24A0(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7F28B5394A0806AD9981C7B0B7A4FE14;// 0x24E0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_10118AD5436C5B816790F78F879ADB4F;// 0x2580(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D2176B2A468D5821867A938C732FB7CD;// 0x25C0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FC4F58FF46BD65D5F5192D8294A5D47D;// 0x2608(0x00A0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_DDEDB15746050ED4C6F8BFA812B2E771;// 0x26A8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E1CA89BB423D1B10A6DA1E8AD625DBD7;// 0x2778(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_FB5193AB4C5C3BA1E71DC0B80AEA5B51;// 0x2818(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_4D0C7A014324EC9F96B723B427839B75;// 0x2858(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_4847D9D04A45A28704DB849897B7EB94;// 0x28F8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_BD0749AD428C843DED5453A791329622;// 0x2938(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_EB8F4A9A4064D2BC31B99D8A1830C3FC;// 0x2A18(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_DE4BE947481096ABF302C68FE13F7527;// 0x2A58(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_08046A124CF7A5454F205888A93F2ACA;// 0x2AA0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E1CB7C6C460BAF2EDC0F7CBFF09FB978;// 0x2AE8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_147212EA425EF973F79576872D59A8E6;// 0x2B88(0x0040)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_AB0615414C7C9CD6098ACFB8EDDD2659;// 0x2BC8(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_AA9E50F74F4CD0FBF5608E8CB796B75A;// 0x2C58(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_0ABFAA5045EF3F1F36A8FBBC13D7A866;// 0x2C98(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_3243B8034D70560E04A37BA0FE2597D4;// 0x2D78(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_83C9835D40AEC7A2F83A7A8F1AF99258;// 0x2DB8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_39003B8E465E1D358ADE998B6E5F1A54;// 0x2E00(0x0048)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_57EC1F474B949436ADDEBCB135629BF9;// 0x2E48(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_474D5C764354A641D1D034934E55603C;// 0x2F18(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_ABE8AA6349E0449953E9D581284676E1;// 0x2FB8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_5D0E29E34DAFC2FC280BDF89470F2C41;// 0x3058(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_804FBFBF4898B983DA1DB097A24E16B5;// 0x3098(0x00A0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_B4E3C1E4423A37F008AD45BCE7A2B79E;// 0x3138(0x00D0)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_AD7D581D49C16A35E3B97FB09A6745C5;// 0x3208(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_1B34DF65466A68E983A9E4AFBE06FF1C;// 0x3298(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_A31F574C4670A4840F3E1E8248788A6B;// 0x32D8(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C42E9F024A3647EF491272AB96ADEBE4;// 0x33B8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_EFFBAB2C401AC4CCC0B3068AECEEB78F;// 0x33F8(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_90F7AE6344720A4F6AB8E7ADA93EE344;// 0x34D8(0x00D8)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_BE00186C484DE6269A16469D6762BC7A;// 0x35B0(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_B0E218DF449587BADCDDACA531729A9B;// 0x36E8(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_4F8C95E24C7346D297D553A96F9EC7AF;// 0x3820(0x0138)
	bool                                               mHasAggroTarget;                                          // 0x3958(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x3959(0x0007) MISSED OFFSET
	TArray<struct FEnemyFootstepStruct>                SoundMap;                                                 // 0x3960(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                ArrayIndex;                                               // 0x3970(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHitDirection;                                            // 0x3974(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPointDmgTaken;                                           // 0x3978(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mRadialDmgTaken;                                          // 0x3979(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsFalling;                                            // 0x397A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsWalking;                                            // 0x397B(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToIdleTransition;                                 // 0x397C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAg_IdleToWalkTransition;                                 // 0x397D(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToRunTransition;                                  // 0x397E(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_RunToWalkTransition;                                  // 0x397F(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAG_InvertedAimPitch;                                     // 0x3980(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_SurfaceRotation;                                      // 0x3984(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAG_InvertedAimYaw;                                       // 0x3990(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationPelvis;                                // 0x3994(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    WalkLeanRotationHead;                                     // 0x39A0(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_WalkLeanRotationSpine;                                // 0x39AC(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_WalkLeanRotationPelvis;                               // 0x39B8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Spitter.Anim_Spitter_C");
		return ptr;
	}


	void CalculateAnimGraphVariables();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Spitter_AnimGraphNode_TransitionResult_C9A2C4744CC31A8CA3DA6398B7FABFD2();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Spitter_AnimGraphNode_TransitionResult_F59AB4D046321D1D1D4ED6BFFA4CE266();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Spitter_AnimGraphNode_TransitionResult_E5A14AC943454B0D928B91923D852F46();
	void AnimNotify_SpitterWalkToRunNotify();
	void OnRadialDamageTaken();
	void OnPointDamageTaken(struct FVector* shootDIrection);
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_Spitter(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
