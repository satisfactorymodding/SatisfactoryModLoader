#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_SpaceGiraffe_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_SpaceGiraffe.Anim_SpaceGiraffe_C
// 0x2108 (0x2588 - 0x0480)
class UAnim_SpaceGiraffe_C : public UFGCharacterAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0480(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_95A130C04491B485CA38F49924CC9DFD;// 0x0488(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_120EBA2A4C99D3C03736878049EF1F10;// 0x04D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7F1B08E040F99C1589080BBA92D288F1;// 0x0518(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5BBF92D944CF08F557873D8B5513CC19;// 0x0560(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_AF899D1E48DFA2EB12A55C9539DED982;// 0x05A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_20C4CA1B4A7945931FBC37ACFE1B467C;// 0x05F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_415F86E747A721B391576B9E390AAA87;// 0x0638(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_66BAFC474B02BC263C77359E53B778BE;// 0x0680(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_BAEDB63945389A2F24D2D2A23218CB41;// 0x0720(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B2CA804B49A6CDE1308FCA9E8B9CA9B6;// 0x0760(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E4FAA9C7407475C7DB6316A1EA9252F1;// 0x07A8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_EC1592404257479A7C7D9D86FE86A385;// 0x07F0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_6666191E4D2BC26E49B4C7B75196837D;// 0x0890(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_587FD66848CF62C90AD9238C168F3A56;// 0x08D0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_F037D0BD47835E9B82F508AA43311A1A;// 0x0970(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_B171BEEB49734F3634AEBFAC28D8712E;// 0x09B0(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_4608A6CC4636F870BBB8E68A2F381C4E;// 0x0A90(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E781810648AD7688DF7B2F838DC4BC1F;// 0x0AD0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9BEB9D5A47DE28245A5623A988839514;// 0x0B18(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5487D4264DFD341FF663708950A54E18;// 0x0B60(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_2FFAD59148485FE3AA60F2AB5C1D1996;// 0x0C00(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_13AAD5BF43F6A63B7CD2379171D24B9D;// 0x0C40(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_91FAF8FA403965FB2A7A90BE67116910;// 0x0CE0(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1D43BB74420CED0C9C7F04A36F5F12A4;// 0x0D20(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_5D6B1BCF463FE2F7AD1B92BF725C0340;// 0x0DC0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_B52A2A5C4D89A873480CCBA11C285D02;// 0x0E00(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_1A006E5E4E92D5C4AEBE2FB6B8610240;// 0x0EE0(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F0453F3E4E9997886C27AABF1AB7E0EE;// 0x0F20(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8156FCD84DC7E28EF3DE2A89196836DA;// 0x0F68(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2C92026444AA4DC3C8127BA2255E1616;// 0x0FB0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_8460571440EF4D012347CA8957E9B7AE;// 0x1050(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CF9FC8C94DB87ED8C6375B90CA3D5FE9;// 0x1090(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C34E74D647DD8CB873E93B97C5FF982A;// 0x1130(0x0040)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_A91378A24B4D6D18EDB814BF3E35FD6C;// 0x1170(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_1D35F7884A8DF5DF744086A1EC0F3560;// 0x1298(0x0040)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_28B6FD35448C65570D1BA081616D38FE;// 0x12D8(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_56EE9CBB46C9C45F8C8166BA9C701C3B;// 0x1368(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_A53C7F1F4BD1D656AEB206B28F43C10A;// 0x13A8(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_9FA021084E84E6075F9F7A9ACB1DF402;// 0x1488(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_104F89C54434F2639D0D6893CE277AAA;// 0x14C8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_880F5CF04D75AC0AC663C6BE6F670A65;// 0x1568(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_865D4B48455F2F189F159086DE6DF7D5;// 0x15A8(0x00E0)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_9ECDF102435E06AED962F892F05361C1;// 0x1688(0x0040)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_C1D2893B427F79E00FA5EFB0C6531EF0;// 0x16C8(0x0138)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_22BF12CF48B7E5B4FAA98EBAB098AF4E;// 0x1800(0x0040)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_9F4419E84BAEE74B07C141A8E85D91F7;// 0x1840(0x0040)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_BBBFFCA4492ED97B98E9378822C8D667;// 0x1880(0x00D0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_01C0667A4417E58803AFE7801F56E3D4;// 0x1950(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_88D1540C41527A351236919638BC5C20;// 0x1A88(0x0138)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_2343FD324C0E92ED8B2B4F93216C445B;// 0x1BC0(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_0510412040EBEF81AA3BC3898710E0CD;// 0x1C98(0x0048)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_88930E55442DA1662D19F393C6FA8524;// 0x1CE0(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_4E55933044EF83FADA84A48CAFC339A1;// 0x1DB8(0x0048)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_58E7B5B74F64F414328130A3076CB6C5;// 0x1E00(0x0048)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_D2E9055A411911CB93EE809D2D955540;// 0x1E48(0x0040)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_4FA3438B4490EBC2301DDC9BB0243AFF;// 0x1E88(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_808DE48747B7915FDC84969FAB2A0B84;// 0x1F60(0x0048)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_5F659AFA46145A0D946371A18369190A;// 0x1FA8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E805DB174E3AB0B4550876AE7EB51DF3;// 0x1FF0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_53A5C3B1476FBB34DA1626988FA99F1C;// 0x2038(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_851E2BD04DA9E46982B347A389F38C95;// 0x2080(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_771BDDA94BAF381F86A3F79A48983723;// 0x21A8(0x0040)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_B2E169E5411D51D707027582A2B0D5DB;// 0x21E8(0x0038)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C998578F4A19918B48637B9821B4C9E3;// 0x2220(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_7BA1B61F4D5C5EBDDE3D8BBA83ABACC5;// 0x2260(0x00E0)
	struct FAnimNode_ApplyAdditive                     AnimGraphNode_ApplyAdditive_3A2E302044CF2728F5869C88E0C9A8BF;// 0x2340(0x00F0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_92688C514B57FFEC3472D987225A4B84;// 0x2430(0x00D8)
	struct FAnimNode_Root                              AnimGraphNode_Root_7864885B4A2ED77FEFAD8C84353334DA;      // 0x2508(0x0040)
	class USkeletalMeshComponent*                      mSkeletalmeshComponent;                                   // 0x2548(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mRadialDmgTaken;                                          // 0x2550(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPointDmgTaken;                                           // 0x2551(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x2552(0x0002) MISSED OFFSET
	float                                              mHitDirection;                                            // 0x2554(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRotationDirection;                                       // 0x2558(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsRotating;                                              // 0x255C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsPanic;                                                 // 0x255D(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAg_IdleToWalkTransition;                                 // 0x255E(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToIdleTransition;                                 // 0x255F(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToRunTransition;                                  // 0x2560(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x2561(0x0003) MISSED OFFSET
	struct FRotator                                    mAG_SurfaceRotation;                                      // 0x2564(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationChest;                                 // 0x2570(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationPelvis;                                // 0x257C(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_SpaceGiraffe.Anim_SpaceGiraffe_C");
		return ptr;
	}


	void CalculateAnimGraphValues();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_5BBF92D944CF08F557873D8B5513CC19();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_120EBA2A4C99D3C03736878049EF1F10();
	void OnPointDamageTaken(struct FVector* shootDIrection);
	void OnRadialDamageTaken();
	void StartRotation(const struct FRotator& Target_Rotation);
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_SpaceGiraffe(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
