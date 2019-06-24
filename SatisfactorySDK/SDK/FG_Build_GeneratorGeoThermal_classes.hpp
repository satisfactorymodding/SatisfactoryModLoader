#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_GeneratorGeoThermal_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_GeneratorGeoThermal.Build_GeneratorGeoThermal_C
// 0x0059 (0x06C1 - 0x0668)
class ABuild_GeneratorGeoThermal_C : public AFGBuildableGeneratorGeoThermal
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0668(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USphereComponent*                            Snap;                                                     // 0x0670(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGPowerConnectionComponent*                 PowerConnection;                                          // 0x0678(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       LeftLadder;                                               // 0x0680(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       RightLadder;                                              // 0x0688(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryLegsComponent*                     FGFactoryLegs;                                            // 0x0690(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGColoredInstanceMeshProxy*                 FGColoredInstanceMeshProxy;                               // 0x0698(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_ProductionIndicatorInstanced_C*          BP_ProductionIndicatorInstanced;                          // 0x06A0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USkeletalMeshComponent*                      MainMesh_skl;                                             // 0x06A8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USphereComponent*                            Resources;                                                // 0x06B0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               Clearance;                                                // 0x06B8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mProductionEffectsRunning;                                // 0x06C0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_GeneratorGeoThermal.Build_GeneratorGeoThermal_C");
		return ptr;
	}


	void UserConstructionScript();
	void GainedSignificance();
	void LostSignificance();
	void StartProductionLoopEffects();
	void StopProductionLoopEffects();
	void ExecuteUbergraph_Build_GeneratorGeoThermal(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
