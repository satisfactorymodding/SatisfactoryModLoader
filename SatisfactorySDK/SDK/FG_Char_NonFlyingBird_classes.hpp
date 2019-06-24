#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_NonFlyingBird_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_NonFlyingBird.Char_NonFlyingBird_C
// 0x0019 (0x0989 - 0x0970)
class AChar_NonFlyingBird_C : public AFGCreature
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0970(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FScriptMulticastDelegate                    OnLandedDelegate;                                         // 0x0978(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	bool                                               mIsLuring;                                                // 0x0988(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_NonFlyingBird.Char_NonFlyingBird_C");
		return ptr;
	}


	void OnRep_mIsLuring();
	void SetLuring(bool isLuring);
	void UserConstructionScript();
	void ReceiveTick(float* DeltaSeconds);
	void TryToJump();
	void OnLanded(struct FHitResult* Hit);
	void ReceiveDied();
	void NotifyOnTakeDamage(class AActor** damagedActor, float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser);
	void ExecuteUbergraph_Char_NonFlyingBird(int EntryPoint);
	void OnLandedDelegate__DelegateSignature(class AChar_NonFlyingBird_C* selfPawn);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
