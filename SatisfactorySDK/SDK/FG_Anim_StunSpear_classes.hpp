#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_StunSpear_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_StunSpear.Anim_StunSpear_C
// 0x0860 (0x0BC0 - 0x0360)
class UAnim_StunSpear_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_7612A1F4467D6BA048F07F93E1A0A017;      // 0x0368(0x0040)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_6EE65AFD4A6212EB2588619E0A07BADE;      // 0x03A8(0x0068)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_FD2C0C9A4C8F644E412530AF0DFE5D17;// 0x0410(0x0040)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_583821FA4F02EF82A1EDF1A2D50C9D52;// 0x0450(0x00A0)
	struct FAnimNode_StateResult                       AnimGraphNode_StateResult_FF3074B34D345C0D556679ABFF8659FE;// 0x04F0(0x0040)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_5C0ABFD144C8A5E68C9240894A6CE176;// 0x0530(0x00E0)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_95C154374EFD89D2B03BCEBF2D64DB24;// 0x0610(0x0040)
	struct FAnimNode_RigidBody                         AnimGraphNode_RigidBody_05A105AB446D527D2ED7FEA4642682BD; // 0x0650(0x0570)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_StunSpear.Anim_StunSpear_C");
		return ptr;
	}


	void AnimNotify_Notify_StunSpearAttack();
	void ExecuteUbergraph_Anim_StunSpear(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
