#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Flower_ApplyDamage_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Flower_ApplyDamage.Flower_ApplyDamage_C
// 0x0000 (0x0038 - 0x0038)
class UFlower_ApplyDamage_C : public UAnimNotify
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Flower_ApplyDamage.Flower_ApplyDamage_C");
		return ptr;
	}


	bool Received_Notify(class USkeletalMeshComponent** MeshComp, class UAnimSequenceBase** Animation);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
