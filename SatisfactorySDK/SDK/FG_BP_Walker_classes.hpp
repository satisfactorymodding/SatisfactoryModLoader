#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

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
// 0x000A (0x097A - 0x0970)
class ABP_Walker_C : public AFGEnemy
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0970(0x0008) (Transient, DuplicateTransient)
	bool                                               mStuckInMovement;                                         // 0x0978(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDebug;                                                   // 0x0979(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

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
