#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_GeneratorNuclear_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_GeneratorNuclear.Anim_GeneratorNuclear_C
// 0x1054 (0x1A04 - 0x09B0)
class UAnim_GeneratorNuclear_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_64A2C3FC465386BD9890F1A9BEC44056;      // 0x09B8(0x0040)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9163C569409C26ED15FD1DA8B776A1C7;// 0x09F8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_A199EAF749FC8238C1FA1397534A6A35;// 0x0A40(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8C1514974F251CA990E4618D4EEB8735;// 0x0A88(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_385E07084DE1A61F7003E09567906972;// 0x0AD0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_AE4D40B745397AAD3394DD89FC04A75B;// 0x0B18(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E4D0D0A24B8011F50DB112A8578189C1;// 0x0B60(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C27D632147F1C47A7C53929AF65BEE9D;// 0x0BA8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FF2587974CD29363E015F294EE1E9A5C;// 0x0BF0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_11F254A24F48487E01257C93E2BAB9E0;// 0x0C90(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8876CB99479DDAA69818DCB287EE0458;// 0x0CD0(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_C375C3564D4569028E42BC94D70359C1;// 0x0D70(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_CF16F210439A31D95C5B42B7E6811AF3;// 0x0DB0(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_375AFFEE410E743BAC16BFA9BDFACFE3;// 0x0E20(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6BA54CE24ED1F016DF9442B01F5833D5;// 0x0E60(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_69BC6E114F1A6953209488B1EE97CAD9;// 0x0F00(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_2A18980F4D6FD0019D9919A9952FC919;// 0x0F40(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_2681919640AF8BB1E95B61A798787651;// 0x0FB0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_ED63C6B447FEA8AFB46C468A64127373;// 0x0FF0(0x00E0)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3998C8AC4F4574CF5F69EF93D7DAF994;// 0x10D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_DA807C6245D8FC0BA610C5820007736A;// 0x1118(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1FE535C844BF172FEE1EF8A17C1FA58D;// 0x1160(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_CB8BD25B4612CE13B24F65951F2203EF;// 0x11A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1C3BB1224CE9047C126E7697B278299C;// 0x11F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_98BBF23444201F37B2E976BDD074AD4D;// 0x1238(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_692434174956461622D8BDA8D75FB590;// 0x1280(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_25245A324CD0B49FF4F0C497D5EE883D;// 0x12C8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_51B4923A4FAB1351C8DA39B7A6F13654;// 0x1368(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_3F9974C44D56522299826A95113D4329;// 0x13A8(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_78A59B6A47962663B88A42943307F9CA;// 0x1418(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_47E8DA7D479A54AB326325A064BED1A2;// 0x1458(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_9B01706044319C98B082D8B86070027D;// 0x14F8(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D2E943BA4933CD845E01A0812AFAA7C6;// 0x1538(0x00A0)
	struct FAnimNode_BlendListByInt                    AnimGraphNode_BlendListByInt_3501BDCD4737CAE8560B4988227040D6;// 0x15D8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_9DD254B44EFAF66495978B9CABB876EA;// 0x16A8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_452C3BF5447F8F74576B9781EFC60208;// 0x1748(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_921F4FC3408963F742A79086F0DE5CD6;// 0x1788(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_7948777B41BBD60B3CED2A9CEDAEE252;// 0x17F8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_FE54578746B9E7B88D9A47896B78C6B9;// 0x1838(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_555902594A20E9FEF085CF9FFB59BB5D;// 0x1918(0x00D8)
	bool                                               mReadyForReload;                                          // 0x19F0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x19F1(0x0003) MISSED OFFSET
	float                                              mReloadTimer;                                             // 0x19F4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FTimerHandle                                mTimer;                                                   // 0x19F8(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	int                                                mRandomReloadAnim;                                        // 0x1A00(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_GeneratorNuclear.Anim_GeneratorNuclear_C");
		return ptr;
	}


	void SetupReloadTimer();
	void ReloadTimer();
	void AnimNotify_GenNuclearEnteredReloadState();
	void AnimNotify_GenNuclearStartupVfx();
	void AnimNotify_GenNuclearShutdownVfx();
	void AnimNotify_GenNuclearEnteredProducing();
	void AnimNotify_GenNuclearLeftProducing();
	void AnimNotify_PlayWatersplashvfx_notify();
	void ExecuteUbergraph_Anim_GeneratorNuclear(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
