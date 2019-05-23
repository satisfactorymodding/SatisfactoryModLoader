#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_EyeTracker_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class EyeTracker.EyeTrackerFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UEyeTrackerFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class EyeTracker.EyeTrackerFunctionLibrary");
		return ptr;
	}


	void SetEyeTrackedPlayer(class APlayerController* PlayerController);
	bool IsStereoGazeDataAvailable();
	bool IsEyeTrackerConnected();
	bool GetStereoGazeData(struct FEyeTrackerStereoGazeData* OutGazeData);
	bool GetGazeData(struct FEyeTrackerGazeData* OutGazeData);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
