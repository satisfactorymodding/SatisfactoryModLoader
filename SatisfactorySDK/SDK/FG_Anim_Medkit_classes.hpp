#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Medkit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Medkit.Anim_Medkit_C
// 0x00B0 (0x0410 - 0x0360)
class UAnim_Medkit_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_1FE5AE6340A8FCA9DEDCCEA348AC2669;      // 0x0368(0x0040)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_CC71A28D47B109D2EBAFCBAD69F9F099;      // 0x03A8(0x0068)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Medkit.Anim_Medkit_C");
		return ptr;
	}


	void ExecuteUbergraph_Anim_Medkit(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
