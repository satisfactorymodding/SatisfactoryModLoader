#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_HealthGainDescriptor_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_HealthGainDescriptor.BP_HealthGainDescriptor_C
// 0x0004 (0x016C - 0x0168)
class UBP_HealthGainDescriptor_C : public UFGConsumableDescriptor
{
public:
	float                                              mHealthGain;                                              // 0x0168(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_HealthGainDescriptor.BP_HealthGainDescriptor_C");
		return ptr;
	}


	void ConsumedBy(class AFGCharacterPlayer** Player);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
