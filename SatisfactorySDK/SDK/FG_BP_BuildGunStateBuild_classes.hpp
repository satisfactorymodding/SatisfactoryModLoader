#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGunStateBuild_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildGunStateBuild.BP_BuildGunStateBuild_C
// 0x0018 (0x00C0 - 0x00A8)
class UBP_BuildGunStateBuild_C : public UFGBuildGunStateBuild
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UAkAudioEvent*                               mMultiStepConstructionSound;                              // 0x00B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UAkAudioEvent*                               mCancelHologramSound;                                     // 0x00B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildGunStateBuild.BP_BuildGunStateBuild_C");
		return ptr;
	}


	void BeginState();
	void EndState();
	void SecondaryFire();
	void OnActiveDescriptorChanged();
	void OnMultiStepPlacement(bool* isFinalStep);
	void OnResetHologram();
	void PrimaryFire();
	void ExecuteUbergraph_BP_BuildGunStateBuild(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
