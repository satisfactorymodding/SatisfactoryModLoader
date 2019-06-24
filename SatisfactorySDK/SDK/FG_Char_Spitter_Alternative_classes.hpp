#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Spitter_Alternative_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_Spitter_Alternative.Char_Spitter_Alternative_C
// 0x0028 (0x09E5 - 0x09BD)
class AChar_Spitter_Alternative_C : public AChar_Spitter_C
{
public:
	bool                                               mIsStrafing_1;                                            // 0x09BD(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x09BE(0x0002) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnStrafeEnded_1;                                          // 0x09C0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FTimerHandle                                mStrafeHandler_1;                                         // 0x09D0(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FVector                                     mStrafeDirection_1;                                       // 0x09D8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDoStrafeRight_1;                                         // 0x09E4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_Spitter_Alternative.Char_Spitter_Alternative_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnStrafeEnded_0__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
