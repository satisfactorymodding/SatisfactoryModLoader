#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Persistent_Level_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Persistent_Level.Persistent_Level_C
// 0x0058 (0x0388 - 0x0330)
class APersistent_Level_C : public ALevelScriptActor
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0330(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	int                                                PartyModeCounter;                                         // 0x0338(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x033C(0x0004) MISSED OFFSET
	class ULevelSequencePlayer*                        CurrentSequence;                                          // 0x0340(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_BlueCrater_0_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0348(0x0008) (ZeroConstructor, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_CraterLake_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0350(0x0008) (ZeroConstructor, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_DesertCanyon_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0358(0x0008) (ZeroConstructor, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_DuneDesert_V2_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0360(0x0008) (ZeroConstructor, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_EasternDune_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0368(0x0008) (ZeroConstructor, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_RockyDesert_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0370(0x0008) (ZeroConstructor, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_SnakeyBeach_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0378(0x0008) (ZeroConstructor, IsPlainOldData)
	class ALevelSequenceActor*                         PartyCamera_SouthernForest_ExecuteUbergraph_Persistent_Level_RefProperty;// 0x0380(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Persistent_Level.Persistent_Level_C");
		return ptr;
	}


	void PartyMode();
	void TeleportPlayer();
	void ExecuteUbergraph_Persistent_Level(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
