#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_TruckStation_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_TruckStation.Anim_TruckStation_C
// 0x0BDA (0x0F3A - 0x0360)
class UAnim_TruckStation_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_0EA6F85B414A7371A3319B985D83D47B;      // 0x0368(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B9266FD3469546EFB24EB0AAA526FD77;// 0x03B0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_BA79A65D40E552FCF0E8F2AD451D5B6F;// 0x03F8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_20B21DF34DFEA9E4CE85D38B5CE13911;// 0x0440(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F9EA0CE74905C1C94E83449C36F379BE;// 0x0488(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C791FC074CC5A922542B19A0584A9DF0;// 0x04D0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_F0AE1763417C323B7FF1FB93CB346EFA;// 0x0580(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6CB049B042E7979EA3621180A950BB7C;// 0x05C8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_2EB3BEAB43EAD1FDC81B26A50D138C6E;// 0x0678(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_51FF2F2B4930C9574E7908AD1E6C5170;// 0x06C0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_AE67FF1F46CDA7A3190788ACF0B69FDA;// 0x0770(0x0048)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_C4A7B5014F1E6F59E8FEF29C24DC7618;// 0x07B8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DCDB865D4CBEF8D2EDDFA7918DE0EF33;// 0x0888(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C9384BBA4621736DA70EB4992875AE45;// 0x0938(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_782905224B3414FD5FFF7E9965760888;// 0x09E8(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_23FE9BBA401568EFCD2F5B87B6A72F22;// 0x0A30(0x00E0)
	struct FAnimNode_AnimDynamics                      AnimGraphNode_AnimDynamics_E510AAEB4E91B052CE6C3B88F8F12724;// 0x0B10(0x0380)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_3385EFB443617BB7A03FEA9F73758B2D;// 0x0E90(0x0048)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_B127388C4F2D6C80643DBDA422E02016;// 0x0ED8(0x0048)
	bool                                               mIsProducing;                                             // 0x0F20(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasPower;                                                // 0x0F21(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsUnloading;                                             // 0x0F22(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsLoading;                                               // 0x0F23(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDeltaTime;                                               // 0x0F24(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRampItUpTime;                                            // 0x0F28(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRampDownTime;                                            // 0x0F2C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAnimPlayRate;                                            // 0x0F30(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeNotProducing;                                        // 0x0F34(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_OfflineToLoadTransition;                              // 0x0F38(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_OfflineToUnloadTransition;                            // 0x0F39(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_TruckStation.Anim_TruckStation_C");
		return ptr;
	}


	void CalculateAnimGraphVariables();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_TruckStation_AnimGraphNode_TransitionResult_F9EA0CE74905C1C94E83449C36F379BE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_TruckStation_AnimGraphNode_SequencePlayer_C791FC074CC5A922542B19A0584A9DF0();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_TruckStation_AnimGraphNode_TransitionResult_BA79A65D40E552FCF0E8F2AD451D5B6F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_TruckStation_AnimGraphNode_TransitionResult_20B21DF34DFEA9E4CE85D38B5CE13911();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_TruckStation_AnimGraphNode_BlendListByBool_C4A7B5014F1E6F59E8FEF29C24DC7618();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_TruckStation_AnimGraphNode_TransitionResult_B9266FD3469546EFB24EB0AAA526FD77();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void BlueprintInitializeAnimation();
	void HasPowerChanged(bool State);
	void ExecuteUbergraph_Anim_TruckStation(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
