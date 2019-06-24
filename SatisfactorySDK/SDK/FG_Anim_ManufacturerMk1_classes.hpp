#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_ManufacturerMk1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_ManufacturerMk1.Anim_ManufacturerMk1_C
// 0x0B81 (0x0EE1 - 0x0360)
class UAnim_ManufacturerMk1_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_E866FDE24797CD5F69EB46AEC57C529B;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_FA726F7444281E7281A8ECBC930CFD58;// 0x03A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5F6C2EB1457A8837BCEF2FB321C95FE7;// 0x03F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6792BB424B071CD96567C7AD7663E0B1;// 0x0438(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_457C1B174B16BE0CF73C23982F383B06;// 0x0480(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1DD95CA145CE257DB557138EBF6CCD3C;// 0x04C8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_1FC8F7124976038CA71E9389D1D72354;// 0x0568(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A6041BE0497DB1695E1092A3B6E7B225;// 0x05A8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_0907B90C4FD0805CDF3D50991784DF2A;// 0x0648(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CB944E444C6800E012C59F818598A7A8;// 0x0688(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_299B8E554500A3EF90C450B2F95E5B60;// 0x0728(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_11C755314269FFBA4D01E68E81C6CEDE;// 0x0768(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_84EBFD6D4CF390E0CCC84AB78247D0F3;// 0x0848(0x00D8)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1CEFF83543FDFC2AA7280490EC14ED04;// 0x0920(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_56A39FA24B70F097CAE83FB5EF656952;// 0x0968(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F5FD74CF4665DC291CF9D7B1F5DE98AA;// 0x09B0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E6ABA23E42EA726002BC46939CEDDF17;// 0x09F8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F8A2A869435ADC182CD538962103861E;// 0x0A40(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_E948DF4B42FC43EBB614A98201F5601D;// 0x0AE0(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_83DFB309404CB2392D86348CF19E61EE;// 0x0B20(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_608000764B46C8C221199FAD05152414;// 0x0BC0(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_657CE7B54D77FAB01E30B78C7DE0D0A6;// 0x0C00(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_E03E3DCF4006B2D497BA45AAA31F28FD;// 0x0CA0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_8B33ED4E429EB6149D141A9515D21771;// 0x0CE0(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_9DB38B79476B3AEC15DC6DBE6B3EB570;// 0x0DC0(0x00D0)
	struct FAnimNode_RefPose                           AnimGraphNode_LocalRefPose_3CF960704FFDD2F6265A7EA8470F2BB2;// 0x0E90(0x0038)
	float                                              mDeltaTime;                                               // 0x0EC8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeNotProducing;                                        // 0x0ECC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRampItUpTime;                                            // 0x0ED0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRampDownTime;                                            // 0x0ED4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsProducing;                                             // 0x0ED8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasPower;                                                // 0x0ED9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0EDA(0x0002) MISSED OFFSET
	float                                              mAnimPlayRate;                                            // 0x0EDC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsIndustrial;                                            // 0x0EE0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_ManufacturerMk1.Anim_ManufacturerMk1_C");
		return ptr;
	}


	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void BlueprintInitializeAnimation();
	void AnimNotify_ConstructorComplexEnteredProducing();
	void AnimNotify_ConstructorComplexLeftProducing();
	void AnimNotify_ConstructorComplexLeftOffline();
	void AnimNotify_ConstructorAdvEnteredOffline();
	void HasPowerChanged(bool State);
	void ExecuteUbergraph_Anim_ManufacturerMk1(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
