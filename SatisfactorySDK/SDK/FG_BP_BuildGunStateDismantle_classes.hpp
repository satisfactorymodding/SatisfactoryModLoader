#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGunStateDismantle_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C
// 0x0010 (0x0090 - 0x0080)
class UBP_BuildGunStateDismantle_C : public UFGBuildGunStateDismantle
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0080(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UWidget_DismantleMode_C*                     mDismantleUI;                                             // 0x0088(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C");
		return ptr;
	}


	void TickState(float* DeltaTime);
	void SecondaryFire();
	void BeginState();
	void EndState();
	void OnStartDismantle();
	void OnStopDismantle();
	void ExecuteUbergraph_BP_BuildGunStateDismantle(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
