#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_StorageIntegrated_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_StorageIntegrated.Build_StorageIntegrated_C
// 0x0010 (0x0670 - 0x0660)
class ABuild_StorageIntegrated_C : public AFGBuildableStorage
{
public:
	class UBP_BuildingPointLight_C*                    BP_BuildingPointLight;                                    // 0x0660(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        MainMesh;                                                 // 0x0668(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_StorageIntegrated.Build_StorageIntegrated_C");
		return ptr;
	}


	bool CanDismantle();
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
