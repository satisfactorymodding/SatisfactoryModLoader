#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_GroupPanic_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_GroupPanic.BTT_GroupPanic_C
// 0x0024 (0x00C4 - 0x00A0)
class UBTT_GroupPanic_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	float                                              MaxDistance;                                              // 0x00A8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00AC(0x0004) MISSED OFFSET
	struct FName                                       GroupPanicBBKey;                                          // 0x00B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       DoPanicBBKey;                                             // 0x00B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MaxGroupDelay;                                            // 0x00C0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_GroupPanic.BTT_GroupPanic_C");
		return ptr;
	}


	void ReceiveExecute(class AActor** OwnerActor);
	void ExecuteUbergraph_BTT_GroupPanic(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
