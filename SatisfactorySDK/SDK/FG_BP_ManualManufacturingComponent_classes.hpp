#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ManualManufacturingComponent_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C
// 0x0018 (0x0288 - 0x0270)
class UBP_ManualManufacturingComponent_C : public UFGWorkBench
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0270(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FScriptMulticastDelegate                    OnCraftCompleted;                                         // 0x0278(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C");
		return ptr;
	}


	void AwardRewards();
	void CraftComplete();
	void ExecuteUbergraph_BP_ManualManufacturingComponent(int EntryPoint);
	void OnCraftCompleted__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
