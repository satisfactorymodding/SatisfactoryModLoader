#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Build_CheatResourceSpawner_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_CheatResourceSpawner.Build_CheatResourceSpawner_C
// 0x0038 (0x0660 - 0x0628)
class ABuild_CheatResourceSpawner_C : public AFGBuildableFactory
{
public:
	class UFGFactoryConnectionComponent*               Output1;                                                  // 0x0628(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        Cylinder;                                                 // 0x0630(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Output0;                                                  // 0x0638(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        OutputBox;                                                // 0x0640(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        MainMesh;                                                 // 0x0648(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                mNumResourcesSpawned;                                     // 0x0650(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0654(0x0004) MISSED OFFSET
	class UClass*                                      mResourceType;                                            // 0x0658(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_CheatResourceSpawner.Build_CheatResourceSpawner_C");
		return ptr;
	}


	void InternalGetOutput(class UClass* Type, class UClass** Output);
	bool Factory_GrabOutput(class UFGFactoryConnectionComponent** Connection, class UClass** Type, struct FInventoryItem* out_item, float* out_OffsetBeyond);
	bool Factory_PeekOutput(class UFGFactoryConnectionComponent** Connection, class UClass** Type, TArray<struct FInventoryItem>* out_items);
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
