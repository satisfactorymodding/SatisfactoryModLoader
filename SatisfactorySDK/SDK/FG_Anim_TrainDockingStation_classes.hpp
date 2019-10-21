#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_TrainDockingStation_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_TrainDockingStation.Anim_TrainDockingStation_C
// 0x0EEA (0x124A - 0x0360)
class UAnim_TrainDockingStation_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_3D57FFBF494021190E489E8BA90B9A5B;      // 0x0368(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8EAF874A442BF6966DA940AFA8A36562;// 0x03A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_74ECF724409FAC11D74545B086B7B846;// 0x03F0(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_13336352489EA524C7C3A0B8F4A8F65F;// 0x0438(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_B9C097444B0FFB109FBAFE9905E6B918;// 0x04A8(0x00D0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_C34F6B9949B6382D19921EA5D9780765;// 0x0578(0x00D0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_609A23C64A8B891FB23ACFBC0C57B1F9;// 0x0648(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_98943DB244602EDDC01811A3BA3C9410;// 0x0728(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E3909E494C99ACC905FB9CB576FB3F93;// 0x07C8(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C45FD1E84132FECDBCEE029B69518FCF;// 0x0868(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_21902A3A4CF5FEE38F1446A591F9BEFD;// 0x0908(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_7B5B6FE14B701C1854097684FF64CE46;// 0x09A8(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_7BFD640A484322C9F3E277B9F5FB67EC;// 0x09E8(0x0070)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_D0B659A041B3D51C01DF608DF397C9B8;// 0x0A58(0x00D0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_90A8CE2E4BB8E0DEE0E445AAF1BD1D3D;// 0x0B28(0x00D0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_040583FA40B242ADF87B8B8F76DBF9D5;// 0x0BF8(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_217465314DEDE72EDAFE71BED43689B3;// 0x0CD8(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_448ACD4F4C13463C27DE65B7E9BA4AAE;// 0x0D78(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A75FCC744AFE798711B8C1BE62311FA1;// 0x0E18(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0906509342A8D34B5FAC3998C080B798;// 0x0EB8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C6E394F84AAE843BE3C4009CDC395DB4;// 0x0F58(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_E9B62A62473FA92BB5F91C93635560DA;// 0x0F98(0x00E0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_2B01A8AF4B7AD8047DA2848608740769;// 0x1078(0x0138)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_B3E12A534FA5EC1E0AB6EB9EECCDE802;// 0x11B0(0x0040)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_01A73604409F0F625E2373937C4A9F98;// 0x11F0(0x0040)
	bool                                               mHasPower;                                                // 0x1230(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	ETrainPlatformDockingStatus                        mDockingStatus;                                           // 0x1231(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsFullLoad;                                              // 0x1232(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsFullUnload;                                            // 0x1233(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mTranslationOffset;                                       // 0x1234(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mStartOffset;                                             // 0x1240(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mEndOffset;                                               // 0x1241(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x1242(0x0002) MISSED OFFSET
	float                                              mOffsetAlpha;                                             // 0x1244(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_EnterTransferState;                                   // 0x1248(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_EnterOfflineState;                                    // 0x1249(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_TrainDockingStation.Anim_TrainDockingStation_C");
		return ptr;
	}


	void CalculateAnimGraphValues();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void AnimNotify_StartOffset();
	void AnimNotify_EndOffset();
	void ExecuteUbergraph_Anim_TrainDockingStation(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
