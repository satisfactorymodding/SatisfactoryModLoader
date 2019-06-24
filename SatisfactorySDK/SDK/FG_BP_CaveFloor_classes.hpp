#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CaveFloor_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_CaveFloor.BP_CaveFloor_C
// 0x007A (0x03A2 - 0x0328)
class ABP_CaveFloor_C : public AActor
{
public:
	class USceneComponent*                             TopScene;                                                 // 0x0328(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USplineComponent*                            Spline;                                                   // 0x0330(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UMaterialInstance*                           mSplineMaterial;                                          // 0x0338(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                NumberOfSplinePoints;                                     // 0x0340(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0344(0x0004) MISSED OFFSET
	TArray<struct FCaveData>                           CaveDataArray;                                            // 0x0348(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	class UStaticMesh*                                 mCaveMesh;                                                // 0x0358(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FCaveData                                   CaveMeshDefaults;                                         // 0x0360(0x0018) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mEntranceMesh;                                            // 0x0378(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 mExitMesh;                                                // 0x0380(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               DrawCavePointNumbers;                                     // 0x0388(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0389(0x0007) MISSED OFFSET
	class FString                                      CurrentCavePoint;                                         // 0x0390(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool                                               mSwitchEntrenceAndExit;                                   // 0x03A0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mEnableCollision;                                         // 0x03A1(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_CaveFloor.BP_CaveFloor_C");
		return ptr;
	}


	void GetEntrenceAndExitIndex(int* entrence, int* Exit);
	void GetStaticMeshForIndex(int Index, class UStaticMesh** NewParam);
	void BuildCaveElement();
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
