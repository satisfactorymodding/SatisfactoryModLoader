#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SelfDrivingLocomotiveController_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C
// 0x0008 (0x0440 - 0x0438)
class ABP_SelfDrivingLocomotiveController_C : public AAIController
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0438(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveBeginPlay();
	void OnPossess(class APawn** PossessedPawn);
	void OnUnpossess(class APawn** UnpossessedPawn);
	void ExecuteUbergraph_BP_SelfDrivingLocomotiveController(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
