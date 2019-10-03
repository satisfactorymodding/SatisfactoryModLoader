#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CursorParticle_Glass_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass CursorParticle_Glass.CursorParticle_Glass_C
// 0x0008 (0x0228 - 0x0220)
class UCursorParticle_Glass_C : public UBP_CursorParticle_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0220(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass CursorParticle_Glass.CursorParticle_Glass_C");
		return ptr;
	}


	void Construct();
	void ExecuteUbergraph_CursorParticle_Glass(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
