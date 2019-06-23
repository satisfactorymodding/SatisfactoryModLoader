#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_3PColorGun_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_3PColorGun.Anim_3PColorGun_C
// 0x0328 (0x0688 - 0x0360)
class UAnim_3PColorGun_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_C04AFF824C2274357E73418EF766148E;      // 0x0368(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_791EC1B44098FA5D466EFA89ADD252B9;// 0x03A8(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_D2A21FB843ED1F7D9FA4729F4A5A811C;// 0x0448(0x0040)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_ADA24DB44675385862759AA7E5C82EB7;// 0x0488(0x0070)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_828011D64EB9833F4DBAFABAC9A342C5;// 0x04F8(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_D78CD3AC4ADE941B49ACE5A92702A99A;// 0x0538(0x00E0)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_6A088DEC4FB9A9D1846BCFB693BB12EB;      // 0x0618(0x0068)
	bool                                               mIsEquipped;                                              // 0x0680(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsReloading;                                             // 0x0681(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasAmmunition;                                           // 0x0682(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x0683(0x0001) MISSED OFFSET
	float                                              mSpeed;                                                   // 0x0684(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_3PColorGun.Anim_3PColorGun_C");
		return ptr;
	}


	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void ExecuteUbergraph_Anim_3PColorGun(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
