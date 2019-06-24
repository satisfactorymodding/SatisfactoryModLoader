#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ObjectScanner_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_ObjectScanner.Attach_ObjectScanner_C
// 0x0020 (0x0388 - 0x0368)
class AAttach_ObjectScanner_C : public AFGObjectScannerAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0368(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UPointLightComponent*                        PointLight;                                               // 0x0370(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USkeletalMeshComponent*                      CrystalScanner_skl;                                       // 0x0378(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             SomeDumbShitThatFixesScaleOrSomething;                    // 0x0380(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_ObjectScanner.Attach_ObjectScanner_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveBeginPlay();
	void ReceiveTick(float* DeltaSeconds);
	void UpdateScannerVisuals();
	void PlayAttachEffects3P();
	void ExecuteUbergraph_Attach_ObjectScanner(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
