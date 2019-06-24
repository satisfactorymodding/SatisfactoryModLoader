#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_SetBoolKey_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_SetBoolKey.BTT_SetBoolKey_C
// 0x0032 (0x00D2 - 0x00A0)
class UBTT_SetBoolKey_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mBoolBBKey;                                               // 0x00A8(0x0028) (Edit, BlueprintVisible)
	bool                                               mValue;                                                   // 0x00D0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mSucceed;                                                 // 0x00D1(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_SetBoolKey.BTT_SetBoolKey_C");
		return ptr;
	}


	void ReceiveExecute(class AActor** OwnerActor);
	void ExecuteUbergraph_BTT_SetBoolKey(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
