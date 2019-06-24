#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_JetPack_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_JetPack.Equip_JetPack_C
// 0x0048 (0x0418 - 0x03D0)
class AEquip_JetPack_C : public AFGJetPack
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03D0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x03D8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mThrustPower;                                             // 0x03E0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mVelocityZExtreme;                                        // 0x03E4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mVelocityZExtremesDamper;                                 // 0x03E8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mJumpBeforeThrustTime;                                    // 0x03EC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxFuel;                                                 // 0x03F0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCurrentFuel;                                             // 0x03F4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	float                                              mFuelRegenRate;                                           // 0x03F8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFuelConsumeRate;                                         // 0x03FC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mThrustCooldown;                                          // 0x0400(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFuelWorth;                                               // 0x0404(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mPaidForFuel;                                             // 0x0408(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mThrustAirControl;                                        // 0x040C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDefaultAirControl;                                       // 0x0410(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRTPCInterval;                                            // 0x0414(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_JetPack.Equip_JetPack_C");
		return ptr;
	}


	float GetMaxFuel();
	float GetCurrentFuel();
	struct FVector GetNewVelocityWhenThrusting(float* Delta);
	bool CanThrust();
	void UserConstructionScript();
	void OnStartThrusting();
	void OnStopThrusting();
	void ReceiveTick(float* DeltaSeconds);
	void ConsumeFuel(float Delta);
	void RegenerateFuel(float Delta);
	void ReceiveBeginPlay();
	void WasEquipped();
	void WasUnEquipped();
	void ExecuteUbergraph_Equip_JetPack(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
