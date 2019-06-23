#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Planet_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Planet.BP_Planet_C
// 0x0048 (0x0370 - 0x0328)
class ABP_Planet_C : public AFGPlanet
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0328(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      SkeletalMesh;                                             // 0x0330(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UMaterialInterface*                          mMaterial;                                                // 0x0338(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UMaterialInstanceDynamic*                    mMaterialInstance;                                        // 0x0340(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UCurveFloat*                                 mOpacityCurve;                                            // 0x0348(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mInitialLocation;                                         // 0x0350(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0354(0x0004) MISSED OFFSET
	class UAnimSequence*                               mAnimToPlay;                                              // 0x0358(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               FadeOutRim;                                               // 0x0360(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               FadeInRim;                                                // 0x0361(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x0362(0x0006) MISSED OFFSET
	class UCurveFloat*                                 mRimLightCurve;                                           // 0x0368(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Planet.BP_Planet_C");
		return ptr;
	}


	bool ShouldSave();
	void GatherDependencies(TArray<class UObject*>* out_dependentObjects);
	bool NeedTransform();
	void UpdateMaterialParameters();
	void UserConstructionScript();
	void PostSaveGame(int SaveVersion, int GameVersion);
	void PreLoadGame(int SaveVersion, int GameVersion);
	void ReceiveBeginPlay();
	void ReceiveTick(float* DeltaSeconds);
	void UpdatePreview();
	void PreSaveGame(int SaveVersion, int GameVersion);
	void PostLoadGame(int SaveVersion, int GameVersion);
	void ExecuteUbergraph_BP_Planet(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
