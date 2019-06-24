#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Hog_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Hog.Anim_Hog_C
// 0x23F0 (0x2870 - 0x0480)
class UAnim_Hog_C : public UFGCharacterAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0480(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_9A5AFC004F802B4F3B6DFD9706332609;      // 0x0488(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8A55238E4D9262B3565C7591F821321F;// 0x04C8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D95893AC4E99D476EEFACC95409C8966;// 0x0510(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_A10DE9884F1D407B490F7F96B3DF7FF7;// 0x0558(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_470B0A744453F3FBEA329AB718F74D90;// 0x05A0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2AA06A7B4F77A6D3B7332585B8F0B836;// 0x05E8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F8F84F4D447420D8A2302D8B911EA497;// 0x0630(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8D00D37646159CE2EB96D6929E7FF217;// 0x0678(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_413FF2D94FAF191B1260DCA93CE55705;// 0x06C0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B9B7E4464A574463C417E69D626B92DF;// 0x0708(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6AD601874EA08CDB7157B5B158617DBE;// 0x0750(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_4BE53F4444D151BEA9E4CEB4F9689451;// 0x0798(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_058DEBF54ED0F821AF6C7AB67E532C06;// 0x07E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_54444EBA4C9FD986ADA1B88076E187F7;// 0x0828(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3D54FEC046F4BA278B96A180E53506EE;// 0x0870(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C4E682B14C1BB421FD69FC950C0942FA;// 0x08B8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_02A578F44D31E9ACB9AC7989E2EF2565;// 0x0958(0x0040)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_1FC136064121A157E31AF6A036986883;// 0x0998(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_D874A8FA4B93094B4804AF9A1F27AA44;// 0x0A28(0x0040)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_7775467F40E8D28C7D12908411841EB3;// 0x0A68(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_7C63213B49100BDE4411A49B8C2204A4;// 0x0AF8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_983008C34EFC2D2CB21AFCB9F4395616;// 0x0B38(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_DD4A63ED4E74D0E0600FB2A7D15D2D8E;// 0x0C18(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C63F7287466CF10C4738079CF8D18585;// 0x0C58(0x00A0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_6E6E2FF5499B2FB90C30A29216CA48FF;// 0x0CF8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_4F2394FB4C7192D3F064C7B466309BDB;// 0x0DC8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_49957F0F4CF57A2538E09EA09CF8F1FA;// 0x0E68(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_4DD405064CA901FD9944AF93DE85ADFD;// 0x0EA8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_B64B578D4627FE5E041FDFA05270ADE2;// 0x0F48(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_0A1A8EAF4DCE14C3383713B0AB4FB27B;// 0x0F88(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_3CF569AB4AB4AE69029D9DB95C317137;// 0x1068(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E5BEC8CB4F781FDD5498998B2DCB0E7F;// 0x10A8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_55D4E4C0431FD3CA460C7895D1A3A116;// 0x1148(0x0040)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_25444E3C401B35A4EF170993261376BF;// 0x1188(0x0090)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_DBAC197C48989C094792ABB3CE48C4FC;// 0x1218(0x00D0)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_B82800414702A5B1D113C18BF62494A1;// 0x12E8(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_DA3D4B79426278A21005489109B4D3A7;// 0x1378(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_E3D91C454AA59556D4B7A680DF36B16C;// 0x13B8(0x00E0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_0A975A65444CAF23BCE4B79B5A8B67D2;// 0x1498(0x0138)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_970E814842CE58E358BCDD854B65E511;      // 0x15D0(0x0068)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_D0DC988C43D4CB91E9ECD6812EE13746;// 0x1638(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_E64DDBDB4C6E0E5BF0515089D66456C7;// 0x1770(0x0138)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_73422ED64CC7BC169EAAE2B24F10EE25;// 0x18A8(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_99D206404957D8F8725EC4AB925FD560;// 0x1980(0x0048)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_DE4A71CC47F7C568CDA1D0B3D50440CA;// 0x19C8(0x0040)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_3687E6844DBFBD1D6BBB248FBB906E04;// 0x1A08(0x00D0)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_5271F77140EB69797ADF42A19609A83E;// 0x1AD8(0x0040)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_B6AC20334F2955BFFB725DACEF1643E7;// 0x1B18(0x0040)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_6A745050433EA115A6A5ADB4DF97EF5A;// 0x1B58(0x00D8)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_4BE9777C43E27172990E9397EB625200;// 0x1C30(0x0040)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_B25F36404BAF77101FA60A87A2476B04;// 0x1C70(0x0048)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_E49F0BAC4594399D00582B8E63903555;// 0x1CB8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_390C8B2943147F01C747D291061E0834;// 0x1D00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6CC2DC48426F2EC66CB919A4708369EE;// 0x1D48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3AF39C8145C99ED74C87AF8EB5509624;// 0x1D90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1C729C7141701D6C784926BC64273560;// 0x1DD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0C8C6E9C4C0951F290D357836EDADAD9;// 0x1E20(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_7BCD6FF74D4F6F913B343B9276917AD4;// 0x1EC0(0x0040)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_D901F83F41249A87AEA22A9928829898;// 0x1F00(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_7B8D995B4C9F6E8C9006609DE9608CEA;// 0x2028(0x0040)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_E1FAAA1A4F7A6544C90711A9373173A8;// 0x2068(0x0038)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_48EB5A4F4EED3C81711A8EBCF63456DE;// 0x20A0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_44A781B845956F32DA7D3696031AAA30;// 0x20E0(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_302F73694C262B1EDA0B6DA6DE667BE7;// 0x21C0(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_32127BC849DE805510F624AC5B81C060;// 0x2298(0x0048)
	struct FAnimNode_ApplyAdditive                     AnimGraphNode_ApplyAdditive_A5B473C34E1598633CBA4388F7954C9C;// 0x22E0(0x00F0)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_2FAF93D24AD775F79D91A5B2C51573DE;// 0x23D0(0x00C0)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_46DECDB84ED63547D6265EB488BC8523;// 0x2490(0x01E0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_CAEBFD664746CBCA7E1F238A86E8DAC2;// 0x2670(0x0138)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_474E904F4BE0B1B379B554BB14D2C5B1;// 0x27A8(0x0040)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_B15A3C22451B72350A9A3AAFC77AD2B3;// 0x27E8(0x0040)
	int                                                ArrayIndex;                                               // 0x2828(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHitDirection;                                            // 0x282C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPointDmgTaken;                                           // 0x2830(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mRadialDmgTaken;                                          // 0x2831(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsThreatened;                                            // 0x2832(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x2833(0x0001) MISSED OFFSET
	float                                              mAG_InvertedAimYaw;                                       // 0x2834(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAg_IdleToWalkTransition;                                 // 0x2838(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAGIsFalling;                                             // 0x2839(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToIdleTransition;                                 // 0x283A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToRunTransition;                                  // 0x283B(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_RunToWalkTransition;                                  // 0x283C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsWalking;                                            // 0x283D(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_LandToWalkTransition;                                 // 0x283E(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x1];                                       // 0x283F(0x0001) MISSED OFFSET
	struct FRotator                                    mAG_SurfaceRotationClamp;                                 // 0x2840(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationPelvis;                                // 0x284C(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationSpine;                                 // 0x2858(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_WalkLeanRotationSpine;                                // 0x2864(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Hog.Anim_Hog_C");
		return ptr;
	}


	void CalculateAnimGraphVariables();
	void OnPointDamageTaken(struct FVector* shootDIrection);
	void OnAnyDamageTaken();
	void OnRadialDamageTaken();
	void AnimNotify_Notify_Hog_LeftIdle();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_Hog(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
