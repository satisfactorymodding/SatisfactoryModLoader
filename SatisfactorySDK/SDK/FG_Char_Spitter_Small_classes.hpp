#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Spitter_Small_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_Spitter_Small.Char_Spitter_Small_C
// 0x000B (0x09C8 - 0x09BD)
class AChar_Spitter_Small_C : public AChar_Spitter_C
{
public:
	unsigned char                                      UnknownData00[0x3];                                       // 0x09BD(0x0003) MISSED OFFSET
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09C0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_Spitter_Small.Char_Spitter_Small_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnCurrentAggroTargetReplicated();
	void ExecuteUbergraph_Char_Spitter_Small(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
