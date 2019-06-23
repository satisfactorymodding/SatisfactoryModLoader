#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_WireBuild_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_MaterialEffect_WireBuild.BP_MaterialEffect_WireBuild_C
// 0x0008 (0x0168 - 0x0160)
class UBP_MaterialEffect_WireBuild_C : public UFGMaterialEffect_Build
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0160(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_MaterialEffect_WireBuild.BP_MaterialEffect_WireBuild_C");
		return ptr;
	}


	void OnStarted();
	void ExecuteUbergraph_BP_MaterialEffect_WireBuild(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
