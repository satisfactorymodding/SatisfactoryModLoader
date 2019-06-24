#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Stinger_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Stinger.Anim_Stinger_C
// 0x1270 (0x16F0 - 0x0480)
class UAnim_Stinger_C : public UFGCharacterAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0480(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_A653D14F4EA5B577D47B81996EC99AE4;// 0x0488(0x00D8)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_7F0BB5E746EE5DF82A6E63A5EB192E6E;// 0x0560(0x0040)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_917300B54723E76D1DAF099A98D9A9C0;// 0x05A0(0x00D0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_28BF328C4C9B66A77048BAB5B2056693;// 0x0670(0x00D8)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_BA357FC34A434AC38E84C7BFF40162B8;// 0x0748(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_2B455CF44A154311EDB713BB99F25003;// 0x0880(0x0138)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_339EEF9A429F37F3BC4D97A3C5CA6B34;// 0x09B8(0x0048)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_0AD1E1024C9B91A1B20AF2B7451EB85E;// 0x0A00(0x0040)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_B1A8E687451D84C2E49886A4AE7595A1;// 0x0A40(0x0048)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_F04E11194CCA8FE033B51FA8F1B9AC1F;// 0x0A88(0x0138)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E7C457894554D21C37ED0296F95916E6;// 0x0BC0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_0EE7E4A041B1191F3FD70DBD9079926F;// 0x0C08(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_0531F7B843C850150DE6099D2CD9CD53;// 0x0C50(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D0AD864A4965CEC37EE8E29713E43FE6;// 0x0C98(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_88F340DF4671A691C61A58966EC04653;// 0x0CE0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_AA87EEFA411B42E0F012BEB25E269804;// 0x0D80(0x0040)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_3FE02EC8422D54F95D15D7ADE283BCD6;// 0x0DC0(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_9CC5433E4E7BF22BC7E8E9872C5DCCEF;// 0x0EE8(0x0040)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_6BDCD6784D1422FE6B9B698FEC9F5CAD;// 0x0F28(0x0038)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_55F650354378526E1B6F38A99273AFE7;// 0x0F60(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_54683F7E4FBAB962E6C2AA839FDA6644;// 0x0FA0(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_6D8F685F4F8E0B5E7503608911BF1365;// 0x1080(0x0048)
	struct FAnimNode_ApplyAdditive                     AnimGraphNode_ApplyAdditive_3F34DA5C470E17DFAE75C8A9A5AE1C68;// 0x10C8(0x00F0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_CEC44834434907999C30748EFCA8941C;// 0x11B8(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_1B61169E49B8ECE6497B9AB41A4024E1;// 0x1290(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_284FC22142EADC5988887D90C9AEE4D2;// 0x12D8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_BBFCDCFE4E7E82AF2C967B8CA25CC0EC;// 0x1320(0x0048)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_F95EBD244FBB005E37056D99E0AADFB1;// 0x1368(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_94231E804256C6B396EDA786A605DCA5;// 0x13F8(0x0040)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_70A3FBA44ED11C3C879C0B9C18B2E320;// 0x1438(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_B58CBA124C38725617D23E97F9293619;// 0x14C8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_CA5BEE41427F29A0E2FEDFB91EBEC2F5;// 0x1508(0x00E0)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_70C39D4E40DFEDB7947DA797E7765CDE;      // 0x15E8(0x0068)
	struct FAnimNode_Root                              AnimGraphNode_Root_049FAEFB421E2412BAEC68A3CBC45F58;      // 0x1650(0x0040)
	class USkeletalMeshComponent*                      mSkeletalmeshComponent;                                   // 0x1690(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	TArray<struct FEnemyFootstepStruct>                SoundMap;                                                 // 0x1698(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                ArrayIndex;                                               // 0x16A8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPlayStop;                                                // 0x16AC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPlayRunStop;                                             // 0x16AD(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x16AE(0x0002) MISSED OFFSET
	float                                              mHitDirection;                                            // 0x16B0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPointDmgTaken;                                           // 0x16B4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mRadialDmgTaken;                                          // 0x16B5(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToIdleTransition;                                 // 0x16B6(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAg_IdleToWalkTransition;                                 // 0x16B7(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_SurfaceRotationClamp;                                 // 0x16B8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsRunning;                                            // 0x16C4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x16C5(0x0003) MISSED OFFSET
	struct FRotator                                    mAG_RunLeanRotationPelvis;                                // 0x16C8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              NewVar_1;                                                 // 0x16D4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationSpine;                                 // 0x16D8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationHead;                                  // 0x16E4(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Stinger.Anim_Stinger_C");
		return ptr;
	}


	void CalculateAnimGraphVariables();
	void OnRadialDamageTaken();
	void OnPointDamageTaken(struct FVector* shootDIrection);
	void AnimNotify_Notify_Stinger_Entered_Idle();
	void AnimNotify_Notify_Stinger_Entered_Walk();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_Stinger(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
