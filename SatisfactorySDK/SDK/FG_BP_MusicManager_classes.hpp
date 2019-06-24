#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MusicManager_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_MusicManager.BP_MusicManager_C
// 0x0008 (0x0068 - 0x0060)
class UBP_MusicManager_C : public UFGMusicManager
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0060(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_MusicManager.BP_MusicManager_C");
		return ptr;
	}


	void OnPlayerNearBaseChanged(bool* isNear);
	void OnPlayerEnteredArea(class UClass** mapArea);
	void NotifyPostLoadMap(class UWorld** loadedWorld, class AWorldSettings** WorldSettings);
	void Play();
	void Pause();
	void Stop();
	void ExecuteUbergraph_BP_MusicManager(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
