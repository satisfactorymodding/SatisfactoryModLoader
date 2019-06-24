#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_WalkBackSlowly_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_WalkBackSlowly.BTT_WalkBackSlowly_C
// 0x0008 (0x00A8 - 0x00A0)
class UBTT_WalkBackSlowly_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_WalkBackSlowly.BTT_WalkBackSlowly_C");
		return ptr;
	}


	void ReceiveExecute(class AActor** OwnerActor);
	void WalkBackComplete();
	void ReceiveAbort(class AActor** OwnerActor);
	void ExecuteUbergraph_BTT_WalkBackSlowly(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
