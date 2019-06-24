#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorLiftMk1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C
// 0x0018 (0x07D8 - 0x07C0)
class ABuild_ConveyorLiftMk1_C : public AFGBuildableConveyorLift
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x07C0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        FogPlane1;                                                // 0x07C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane0;                                                // 0x07D0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayConstructSound();
	void ExecuteUbergraph_Build_ConveyorLiftMk1(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
