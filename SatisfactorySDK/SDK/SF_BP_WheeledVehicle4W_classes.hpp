#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_WheeledVehicle4W_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_WheeledVehicle4W.BP_WheeledVehicle4W_C
// 0x0008 (0x0860 - 0x0858)
class ABP_WheeledVehicle4W_C : public ABP_WheeledVehicle_C
{
public:
	class UFGWheeledVehicleMovementComponent4W*        FGWheeledVehicleMovementComponent4W;                      // 0x0858(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_WheeledVehicle4W.BP_WheeledVehicle4W_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
