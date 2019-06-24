#pragma once

// Satisfactory SDK

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
// 0x0008 (0x0698 - 0x0690)
class ABuild_StorageIntegrated_C : public AFGBuildableStorage
{
public:
	class UStaticMeshComponent*                        MainMesh;                                                 // 0x0690(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

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
