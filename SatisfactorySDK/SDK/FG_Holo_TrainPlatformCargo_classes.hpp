#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Holo_TrainPlatformCargo_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Holo_TrainPlatformCargo.Holo_TrainPlatformCargo_C
// 0x0008 (0x04A8 - 0x04A0)
class AHolo_TrainPlatformCargo_C : public AFGTrainStationHologram
{
public:
	class UStaticMeshComponent*                        BuildingMeshProxy;                                        // 0x04A0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Holo_TrainPlatformCargo.Holo_TrainPlatformCargo_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
