#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Sky_Sphere_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Sky_Sphere.BP_Sky_Sphere_C
// 0x0128 (0x1580 - 0x1458)
class ABP_Sky_Sphere_C : public AFGSkySphere
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x1458(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        Sky_Sphere_mesh;                                          // 0x1460(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             Base;                                                     // 0x1468(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UMaterialInstanceDynamic*                    mSkyMaterial;                                             // 0x1470(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class ADirectionalLight*                           mSunLight;                                                // 0x1478(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	float                                              mSunHeight;                                               // 0x1480(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mHorizonFalloff;                                          // 0x1484(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCloudSpeed;                                              // 0x1488(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    mOriginSunRotation;                                       // 0x148C(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    mSunRotationAxis;                                         // 0x1498(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x14A4(0x0004) MISSED OFFSET
	class ASkyLight*                                   mSkyLight;                                                // 0x14A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class ADirectionalLight*                           mMoonLight;                                               // 0x14B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	struct FRotator                                    mOriginMoonRotation;                                      // 0x14B8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    mMoonRotationAxis;                                        // 0x14C4(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mSunRadius;                                               // 0x14D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mMoonRadius;                                              // 0x14D4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FFBrightnessAdjustment                      mSunBrightnessAdjust;                                     // 0x14D8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FFBrightnessAdjustment                      mMoonBrightnessAdjust;                                    // 0x14E0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class ADirectionalLight*                           mDominantLight;                                           // 0x14E8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, Transient, DisableEditOnInstance, IsPlainOldData)
	float                                              mDiscRadius;                                              // 0x14F0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Transient, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x14F4(0x0004) MISSED OFFSET
	class AAtmosphericFog*                             mAtmosphericFog;                                          // 0x14F8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class APostProcessVolume*                          mGlobalPostProcess;                                       // 0x1500(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	struct FRuntimeFloatCurve                          Cubemap_Curve;                                            // 0x1508(0x0078) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Sky_Sphere.BP_Sky_Sphere_C");
		return ptr;
	}


	void SetLightAsDominant(class ADirectionalLight* Light, bool newDominant);
	void newDominantLight(class ADirectionalLight* oldDominantLight, class ADirectionalLight* newDominantLight);
	void CalculateDominantLight();
	void CalculateDiscBrightness(class ALight* Light, const struct FFBrightnessAdjustment& brightnessAdjustment, float* discBrightness);
	void CalculateBrightness(float* Brightness);
	void CalculateLightRotation(const struct FRotator& OriginalRotation, const struct FRotator& RotationAxis, const struct FRuntimeFloatCurve& LightRotationCurve, struct FRotator* NewRotation);
	void UpdateGlobalParameters();
	void UpdateCurvesFromTime();
	void UpdateLightRotation();
	void UpdateMaterialParameters();
	void UserConstructionScript();
	void ReceiveTick(float* DeltaSeconds);
	void ReceiveBeginPlay();
	void UpdatePreview();
	void ApplySkySphereSettings(struct FSkySphereSettings* Settings);
	void ExecuteUbergraph_BP_Sky_Sphere(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
