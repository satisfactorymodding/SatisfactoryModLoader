#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CinematicCamera_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class CinematicCamera.CameraRig_Crane
// 0x0030 (0x0358 - 0x0328)
class ACameraRig_Crane : public AActor
{
public:
	float                                              CranePitch;                                               // 0x0328(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              CraneYaw;                                                 // 0x032C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              CraneArmLength;                                           // 0x0330(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bLockMountPitch;                                          // 0x0334(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bLockMountYaw;                                            // 0x0335(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0336(0x0002) MISSED OFFSET
	class USceneComponent*                             TransformComponent;                                       // 0x0338(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class USceneComponent*                             CraneYawControl;                                          // 0x0340(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class USceneComponent*                             CranePitchControl;                                        // 0x0348(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class USceneComponent*                             CraneCameraMount;                                         // 0x0350(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class CinematicCamera.CameraRig_Crane");
		return ptr;
	}

};


// Class CinematicCamera.CameraRig_Rail
// 0x0020 (0x0348 - 0x0328)
class ACameraRig_Rail : public AActor
{
public:
	float                                              CurrentPositionOnRail;                                    // 0x0328(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bLockOrientationToRail;                                   // 0x032C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x032D(0x0003) MISSED OFFSET
	class USceneComponent*                             TransformComponent;                                       // 0x0330(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class USplineComponent*                            RailSplineComponent;                                      // 0x0338(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class USceneComponent*                             RailCameraMount;                                          // 0x0340(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class CinematicCamera.CameraRig_Rail");
		return ptr;
	}

};


// Class CinematicCamera.CineCameraActor
// 0x0040 (0x0880 - 0x0840)
class ACineCameraActor : public ACameraActor
{
public:
	struct FCameraLookatTrackingSettings               LookatTrackingSettings;                                   // 0x0840(0x0030) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0870(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class CinematicCamera.CineCameraActor");
		return ptr;
	}


	class UCineCameraComponent* GetCineCameraComponent();
};


// Class CinematicCamera.CineCameraComponent
// 0x00C0 (0x0850 - 0x0790)
class UCineCameraComponent : public UCameraComponent
{
public:
	struct FCameraFilmbackSettings                     FilmbackSettings;                                         // 0x0790(0x000C) (Edit, BlueprintVisible)
	struct FCameraLensSettings                         LensSettings;                                             // 0x079C(0x0018) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x07B4(0x0004) MISSED OFFSET
	struct FCameraFocusSettings                        FocusSettings;                                            // 0x07B8(0x0038) (Edit, BlueprintVisible)
	float                                              CurrentFocalLength;                                       // 0x07F0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              CurrentAperture;                                          // 0x07F4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              CurrentFocusDistance;                                     // 0x07F8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData01[0xC];                                       // 0x07FC(0x000C) MISSED OFFSET
	TArray<struct FNamedFilmbackPreset>                FilmbackPresets;                                          // 0x0808(0x0010) (ZeroConstructor, Config)
	TArray<struct FNamedLensPreset>                    LensPresets;                                              // 0x0818(0x0010) (ZeroConstructor, Config)
	class FString                                      DefaultFilmbackPresetName;                                // 0x0828(0x0010) (ZeroConstructor, Config)
	class FString                                      DefaultLensPresetName;                                    // 0x0838(0x0010) (ZeroConstructor, Config)
	float                                              DefaultLensFocalLength;                                   // 0x0848(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float                                              DefaultLensFStop;                                         // 0x084C(0x0004) (ZeroConstructor, Config, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class CinematicCamera.CineCameraComponent");
		return ptr;
	}


	void SetLensPresetByName(const class FString& InPresetName);
	void SetFilmbackPresetByName(const class FString& InPresetName);
	float GetVerticalFieldOfView();
	class FString GetLensPresetName();
	float GetHorizontalFieldOfView();
	class FString GetFilmbackPresetName();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
