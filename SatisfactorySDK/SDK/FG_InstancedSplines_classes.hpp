#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_InstancedSplines_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class InstancedSplines.FGInstancedSplineMeshComponent
// 0x0060 (0x06F0 - 0x0690)
class UFGInstancedSplineMeshComponent : public USplineMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0690(0x0008) MISSED OFFSET
	int                                                InstancingRandomSeed;                                     // 0x0698(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                InstanceStartCullDistance;                                // 0x069C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                InstanceEndCullDistance;                                  // 0x06A0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x06A4(0x0004) MISSED OFFSET
	TArray<int>                                        InstanceReorderTable;                                     // 0x06A8(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData02[0x38];                                      // 0x06B8(0x0038) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class InstancedSplines.FGInstancedSplineMeshComponent");
		return ptr;
	}


	bool UpdateInstanceTransform(int InstanceIndex, const struct FVector& StartPos, const struct FVector& StartTangent, const struct FVector& EndPos, const struct FVector& EndTangent, bool bWorldSpace, bool bMarkRenderStateDirty, bool bTeleport);
	bool RemoveInstance(int InstanceIndex);
	int GetInstanceCount();
	void ClearInstances();
	int AddInstance(const struct FVector& StartPos, const struct FVector& StartTangent, const struct FVector& EndPos, const struct FVector& EndTangent);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
