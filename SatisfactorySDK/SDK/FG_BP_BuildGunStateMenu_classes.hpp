#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGunStateMenu_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildGunStateMenu.BP_BuildGunStateMenu_C
// 0x0020 (0x0070 - 0x0050)
class UBP_BuildGunStateMenu_C : public UFGBuildGunState
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0050(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UClass*                                      mLastSelectedBuildCategory;                               // 0x0058(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class UClass*>                              mLastSelectedSubCategories;                               // 0x0060(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildGunStateMenu.BP_BuildGunStateMenu_C");
		return ptr;
	}


	void EndState();
	void SecondaryFire();
	void BeginState();
	void ExecuteUbergraph_BP_BuildGunStateMenu(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
