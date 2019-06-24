#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_SmallSpitter_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_SmallSpitter.Anim_SmallSpitter_C
// 0x3554 (0x39D4 - 0x0480)
class UAnim_SmallSpitter_C : public UFGCharacterAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0480(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_19942740471395111117E79D84009DF1;// 0x0488(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F6EE12A241242082CA63B59288B742EC;// 0x04D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7615D6894F917658C7D85A8D21882C80;// 0x0518(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B1372EDC45DF5F0D801226A149C4AB96;// 0x0560(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_224DA8E340056D2D79FDBCB50DC67189;// 0x0600(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7F3836C842A512422C3A49802F691082;// 0x0640(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_0A7434284841F3A0CECB55AF1E3A2FB6;// 0x06E0(0x0040)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_6DA93B9A443D0629FD9D57B8E4124825;// 0x0720(0x0048)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_990FEDD142DC5B2B90FDFF8120BAFFDF;// 0x0768(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_2FF5D5D945EC4C3B3BA4229AA5DC8B0F;// 0x07A8(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_1529BAFB4D590A4822B1E785F6CDEED8;// 0x0888(0x00D8)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_23F3614D440B9BA686D0C29A87B40787;      // 0x0960(0x0068)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_2C88480E43F17187EB9A83B6C62F7537;// 0x09C8(0x0040)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_6696549F4D1345D3CE0BF8B007161F91;// 0x0A08(0x00D8)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_B73D0E7141876AFBA70540893646B9D2;// 0x0AE0(0x0040)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_62C4980C47FA1D6E69614E879AC37536;// 0x0B20(0x00D0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_E50D36E14A5C4A2A305C6EA40BBFF82B;// 0x0BF0(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_C666E3B248702D330A6463B13D7E0618;// 0x0D28(0x0138)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_C943682B4EB7E47C9DE4E3B25A0D2AC8;// 0x0E60(0x0048)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_4246FFDD432693769F501B836498D044;// 0x0EA8(0x0040)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_C870128A4BE9784097F9A1A7D18DB9F1;// 0x0EE8(0x0040)
	struct FAnimNode_Root                              AnimGraphNode_Root_03EB723E407BEDEA4E44BABB428332FF;      // 0x0F28(0x0040)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_480463224ED0EE67C190E1990824BCBA;// 0x0F68(0x00C0)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_78781CCC45DB4A32A0F2DB80621507BC;// 0x1028(0x01E0)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_9EC1C19848F03FE93FE4789003A59267;// 0x1208(0x00C0)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_5189ACC84ECAE9DF7D4F5AB72F5E540E;// 0x12C8(0x00C0)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_6D3D52144702BDF9722C69BB51973975;// 0x1388(0x0040)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_937ED59A42FF7CA83BDD7B994433E1AA;// 0x13C8(0x0040)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_0B2C142F41828EFAD5D13BB6AEA184BB;// 0x1408(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3102B22948D677412DD89DB484C6D22B;// 0x1450(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1E3EE85349A364B1FC46AD95D511AA06;// 0x1498(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6A3F0B6849BE362F69BD22ABE4D6C58D;// 0x14E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2608467948BAB45340990FA93BB228F8;// 0x1528(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5D50325E433DBFDD26CB199B103179C3;// 0x1570(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_18A54F284EE39CEAE7B178BCA07B1E5D;// 0x1610(0x0040)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_10D708C245333F512AF6239B1E973250;// 0x1650(0x0128)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_6A39B1AA4AAAE0C71C86829C1F3F09AC;// 0x1778(0x0040)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_DEC52E9A404FD48F91D3F680375857C5;// 0x17B8(0x0038)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_40655CC849EBEA4CBBAD1F9CE34C09DA;// 0x17F0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_CCFBE6194F3D4802A49487BC4980C922;// 0x1830(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_230132F6454F6449E751E29D42D64D9E;// 0x1910(0x0048)
	struct FAnimNode_ApplyAdditive                     AnimGraphNode_ApplyAdditive_67DD69454061AA545945D88E160DEA27;// 0x1958(0x00F0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_E58181F745A722E92B4EDDA9DADDA5B9;// 0x1A48(0x00D8)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_156D32D643C6909026C1E9AFC42A326D;// 0x1B20(0x0048)
	unsigned char                                      UnknownData00[0x8];                                       // 0x1B68(0x0008) MISSED OFFSET
	struct FAnimNode_RigidBody                         AnimGraphNode_RigidBody_789DA35640EECF22D20F57A86AAD4402; // 0x1B70(0x0570)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_109183044A7B4E46670A2D8C69D1789E;// 0x20E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1409EDA34A0595225C4807861C129D94;// 0x2128(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7D9477AF4744C027B26376A951F0F020;// 0x2170(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D8473D8145C7278FC5B1AFAD154D8CF0;// 0x21B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_03EBA1B14615160DFD1DFEBCC1D6D217;// 0x2200(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6F7C35D64C630E211DF61988112FB6A4;// 0x2248(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F2BFD8E9417B922A4A6C66A2298D73EB;// 0x2290(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B2AD22984B1F46D8AA99158597EA0A93;// 0x22D8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2546556C4F249218C80F518ABC78292F;// 0x2320(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_B805DACE47F751F1C4BBC9ACDEBD4142;// 0x23C0(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F434044D44B29B27AAC556940B920010;// 0x2400(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_5F7D80834F382E35B8859C91947A4013;// 0x24A0(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6DEE08844DF3E0A7A09BCE98517DAA24;// 0x24E0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_86FAB2504E4C135E35271DA8C67F8BA2;// 0x2580(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3F4F07424C54FE4B3F289DA48E9BE747;// 0x25C0(0x0048)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_B77B6312406859C0F7DCBF985FF61B02;// 0x2608(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_55AD1E154FAFC8F981ECAAA4CA1FF992;// 0x26D8(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E3F7BFB8406E1570B3E671B1F98E6D6D;// 0x2778(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_D5B817E047DEE8ED76F6A29326CE9374;// 0x2818(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_920281094C54600C45F4A5A16251C446;// 0x2858(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_1D5E88734B1C0F1A2D48D7B45F5A3DFA;// 0x28F8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_78CFA2654ED3C548A7764C88A23050C4;// 0x2938(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_0065A5174A83C3A0F45BF7A7DB4F7505;// 0x2A18(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2D6A0382465D1833544263BFF3E1CE17;// 0x2A58(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7956550A454F68AFBD620CB012F1789E;// 0x2AA0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2B70C0794440185C414A4E849C6F1D6C;// 0x2AE8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_322EAC3E4D673AF58686A7A50E7E6D34;// 0x2B88(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_87E687F9486D562680B77D8094691AE4;// 0x2BC8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_6BA6A8164952F1092F90A9A8D45CB43C;// 0x2C68(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_1386E87A4794BF55BAAB4DBCF9F15FB9;// 0x2CA8(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_A9433F85446A7A6A8CA953B39830C155;// 0x2D88(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5CDF33754E0B7EF9F092F6A11FD769A5;// 0x2DC8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7B4051C84348CD3B2162598F15E1A625;// 0x2E10(0x0048)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_8BD731A64DA189C14BC8A0B81F5A4DAB;// 0x2E58(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_BBB6B33B4E4A2CD4A5F483A20F0B25D9;// 0x2F28(0x00A0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_18515BFA4903427B8DA10E9436DAB180;// 0x2FC8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_41A4B35D4269AB6AF45C72B0B6C0008C;// 0x3068(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3933F442450E0C141328D193112569DD;// 0x30A8(0x00A0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_080580A645C23B7F45E24696998D3AA6;// 0x3148(0x00D0)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_B6FB66E84FB1D66D21F7228E8CEF5F11;// 0x3218(0x0090)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_BBD3DA404A8F45483472FEA1DC5D538F;// 0x32A8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_2C09719A4B4C199D4EBBD585A87EA749;// 0x32E8(0x00E0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_3D95EC1B47D0D61DE61E1F8786DAA2F4;// 0x33C8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_1906396048A42BA45FA1B789C1C56A52;// 0x3408(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_D31B8F3D4C396D9703AFC992CDA94053;// 0x34E8(0x00D8)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_38B4181544FCC0E587C18491ADA53C1D;// 0x35C0(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_ABB842644536808994F7659B96FABAC0;// 0x36F8(0x0138)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_2BFCBFEF4439408F93800DB1AFAB7E01;// 0x3830(0x0138)
	bool                                               mHasAggroTarget;                                          // 0x3968(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x3969(0x0007) MISSED OFFSET
	TArray<struct FEnemyFootstepStruct>                SoundMap;                                                 // 0x3970(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                ArrayIndex;                                               // 0x3980(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHitDirection;                                            // 0x3984(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPointDmgTaken;                                           // 0x3988(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mRadialDmgTaken;                                          // 0x3989(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsFalling;                                            // 0x398A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsWalking;                                            // 0x398B(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToIdleTransition;                                 // 0x398C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAg_IdleToWalkTransition;                                 // 0x398D(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_WalkToRunTransition;                                  // 0x398E(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_RunToWalkTransition;                                  // 0x398F(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAG_InvertedAimPitch;                                     // 0x3990(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_SurfaceRotation;                                      // 0x3994(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAG_InvertedAimYaw;                                       // 0x39A0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_RunLeanRotationPelvis;                                // 0x39A4(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    WalkLeanRotationHead;                                     // 0x39B0(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_WalkLeanRotationSpine;                                // 0x39BC(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_WalkLeanRotationPelvis;                               // 0x39C8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_SmallSpitter.Anim_SmallSpitter_C");
		return ptr;
	}


	void CalculateAnimGraphVariables();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SmallSpitter_AnimGraphNode_TransitionResult_109183044A7B4E46670A2D8C69D1789E();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SmallSpitter_AnimGraphNode_TransitionResult_03EBA1B14615160DFD1DFEBCC1D6D217();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SmallSpitter_AnimGraphNode_TransitionResult_6F7C35D64C630E211DF61988112FB6A4();
	void AnimNotify_SpitterWalkToRunNotify();
	void OnRadialDamageTaken();
	void OnPointDamageTaken(struct FVector* shootDIrection);
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_SmallSpitter(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
