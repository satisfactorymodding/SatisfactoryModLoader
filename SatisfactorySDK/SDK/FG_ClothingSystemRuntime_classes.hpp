#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ClothingSystemRuntime_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class ClothingSystemRuntime.ClothingAssetCustomData
// 0x0000 (0x0028 - 0x0028)
class UClothingAssetCustomData : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ClothingSystemRuntime.ClothingAssetCustomData");
		return ptr;
	}

};


// Class ClothingSystemRuntime.ClothingAsset
// 0x0130 (0x0178 - 0x0048)
class UClothingAsset : public UClothingAssetBase
{
public:
	class UPhysicsAsset*                               PhysicsAsset;                                             // 0x0048(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FClothConfig                                ClothConfig;                                              // 0x0050(0x00D4) (Edit)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0124(0x0004) MISSED OFFSET
	TArray<struct FClothLODData>                       LODData;                                                  // 0x0128(0x0010) (ZeroConstructor)
	TArray<int>                                        LodMap;                                                   // 0x0138(0x0010) (ZeroConstructor)
	TArray<struct FName>                               UsedBoneNames;                                            // 0x0148(0x0010) (ZeroConstructor)
	TArray<int>                                        UsedBoneIndices;                                          // 0x0158(0x0010) (ZeroConstructor)
	int                                                ReferenceBoneIndex;                                       // 0x0168(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x016C(0x0004) MISSED OFFSET
	class UClothingAssetCustomData*                    CustomData;                                               // 0x0170(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ClothingSystemRuntime.ClothingAsset");
		return ptr;
	}

};


// Class ClothingSystemRuntime.ClothingSimulationFactoryNv
// 0x0000 (0x0028 - 0x0028)
class UClothingSimulationFactoryNv : public UClothingSimulationFactory
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ClothingSystemRuntime.ClothingSimulationFactoryNv");
		return ptr;
	}

};


// Class ClothingSystemRuntime.ClothingSimulationInteractorNv
// 0x0010 (0x0040 - 0x0030)
class UClothingSimulationInteractorNv : public UClothingSimulationInteractor
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0030(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ClothingSystemRuntime.ClothingSimulationInteractorNv");
		return ptr;
	}


	void SetAnimDriveSpringStiffness(float InStiffness);
	void SetAnimDriveDamperStiffness(float InStiffness);
	void EnableGravityOverride(const struct FVector& InVector);
	void DisableGravityOverride();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
