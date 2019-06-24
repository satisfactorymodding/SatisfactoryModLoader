#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_FoundryMk1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_FoundryMk1.Build_FoundryMk1_C
// 0x00A1 (0x0749 - 0x06A8)
class ABuild_FoundryMk1_C : public AFGBuildableManufacturer
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x06A8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        FogPlane_03;                                              // 0x06B0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USkeletalMeshComponent*                      MainMesh_skl;                                             // 0x06B8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_BuildingSpotLight_C*                     BuildingLight1;                                           // 0x06C0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryLegsComponent*                     FGFactoryLegs;                                            // 0x06C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_BuildingSpotLight_C*                     BuildingLight;                                            // 0x06D0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGPowerConnectionComponent*                 PowerConnection;                                          // 0x06D8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane_02;                                              // 0x06E0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlance_01;                                             // 0x06E8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGColoredInstanceMeshProxy*                 FGColoredInstanceMeshProxy;                               // 0x06F0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_ProductionIndicatorInstanced_C*          BP_ProductionIndicatorInstanced;                          // 0x06F8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       BP_LadderComponent;                                       // 0x0700(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               Clearance;                                                // 0x0708(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USphereComponent*                            Snap;                                                     // 0x0710(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input1;                                                   // 0x0718(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Output2;                                                  // 0x0720(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input0;                                                   // 0x0728(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mBurnerParticle;                                          // 0x0730(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mHeatParticle01;                                          // 0x0738(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mHeatParticle02;                                          // 0x0740(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mProductionEffectsRunning;                                // 0x0748(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_FoundryMk1.Build_FoundryMk1_C");
		return ptr;
	}


	void RemoveProductionEffects();
	void SetupProductionEffects();
	void RemoveIdleEffects();
	void SetupIdleEffects();
	void UserConstructionScript();
	void StartProductionLoopEffects();
	void StopProductionLoopEffects();
	void StartIdlingLoopEffects();
	void StopIdlingLoopEffects();
	void LostSignificance();
	void GainedSignificance();
	void ExecuteUbergraph_Build_FoundryMk1(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
