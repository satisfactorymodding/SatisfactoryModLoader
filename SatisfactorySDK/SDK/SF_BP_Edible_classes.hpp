#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_Edible_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Edible.BP_Edible_C
// 0x0010 (0x03B8 - 0x03A8)
class ABP_Edible_C : public ABP_Pickup_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03A8(0x0008) (Transient, DuplicateTransient)
	class UStaticMeshComponent*                        BushMesh;                                                 // 0x03B0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Edible.BP_Edible_C");
		return ptr;
	}


	void UpdateVisiblityState();
	void UserConstructionScript();
	void PlayPickupEffect();
	void ReceiveBeginPlay();
	void ExecuteUbergraph_BP_Edible(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
