#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SelfDrivingController_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_SelfDrivingController.BP_SelfDrivingController_C
// 0x0010 (0x0448 - 0x0438)
class ABP_SelfDrivingController_C : public AAIController
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0438(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FName                                       mWantsTargetBBKeyName;                                    // 0x0440(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_SelfDrivingController.BP_SelfDrivingController_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnPossess(class APawn** PossessedPawn);
	void OnUnpossess(class APawn** UnpossessedPawn);
	void ExecuteUbergraph_BP_SelfDrivingController(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
