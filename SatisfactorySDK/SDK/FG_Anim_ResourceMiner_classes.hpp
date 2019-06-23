#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_ResourceMiner_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_ResourceMiner.Anim_ResourceMiner_C
// 0x0158 (0x04B8 - 0x0360)
class UAnim_ResourceMiner_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_3CD0AC4940446AE4D3B0E1A721C0118C;      // 0x0368(0x0040)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_9E67F44A4B8B59A5F5927296BC135F1B;      // 0x03A8(0x0068)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_B91B875F413AC3C2F8983C8EDB09AD9C;// 0x0410(0x0070)
	TArray<int>                                        mAK_RTPC_Randomizer;                                      // 0x0480(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                RTPC_Selection;                                           // 0x0490(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                RTPC_Memory_01;                                           // 0x0494(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                RTPC_Memory_02;                                           // 0x0498(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x049C(0x0004) MISSED OFFSET
	TArray<int>                                        mListOfPlayedSounds;                                      // 0x04A0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                mSoundToPlay;                                             // 0x04B0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mNumSounds;                                               // 0x04B4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_ResourceMiner.Anim_ResourceMiner_C");
		return ptr;
	}


	void AnimNotify_MineComplete();
	void AnimNotify_StopMining();
	void AnimNotify_MineVfx();
	void AnimNotify_StartCameraShake();
	void AnimNotify_PickRingSound();
	void AnimNotify_SecondMineVfx();
	void ExecuteUbergraph_Anim_ResourceMiner(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
