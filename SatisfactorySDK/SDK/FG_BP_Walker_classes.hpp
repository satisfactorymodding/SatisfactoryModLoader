#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Walker_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Walker.BP_Walker_C
// 0x000A (0x098A - 0x0980)
class ABP_Walker_C : public AFGEnemy
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0980(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	bool                                               mStuckInMovement;                                         // 0x0988(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDebug;                                                   // 0x0989(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Walker.BP_Walker_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayConsumeItemEffect(class UClass** itemDescriptor, int* amount);
	void ExecuteUbergraph_BP_Walker(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
