#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_HasTrackPath_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTD_HasTrackPath.BTD_HasTrackPath_C
// 0x0008 (0x00A8 - 0x00A0)
class UBTD_HasTrackPath_C : public UBTDecorator_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTD_HasTrackPath.BTD_HasTrackPath_C");
		return ptr;
	}


	bool PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ReceiveExecutionStartAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ReceiveExecutionFinishAI(class AAIController** OwnerController, class APawn** ControlledPawn, TEnumAsByte<EBTNodeResult>* NodeResult);
	void ExecuteUbergraph_BTD_HasTrackPath(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
