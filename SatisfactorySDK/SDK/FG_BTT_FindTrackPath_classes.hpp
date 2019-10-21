#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FindTrackPath_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_FindTrackPath.BTT_FindTrackPath_C
// 0x0019 (0x00B9 - 0x00A0)
class UBTT_FindTrackPath_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class AFGLocomotive*                               mLocomotive;                                              // 0x00A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class AAIController*                               mController;                                              // 0x00B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	ESelfDrivingLocomotiveError                        mError;                                                   // 0x00B8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_FindTrackPath.BTT_FindTrackPath_C");
		return ptr;
	}


	void FindPath(class AFGTrain* Train, class AFGTrainStationIdentifier* Station, bool* Success, struct FRailroadPathFindingResult* Result, class AFGLocomotive** Locomotive);
	void ReportError(const struct FText& MESSAGE);
	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_FindTrackPath(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
