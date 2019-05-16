#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BTT_SetVectorKey_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_SetVectorKey.BTT_SetVectorKey_C
// 0x003D (0x00DD - 0x00A0)
class UBTT_SetVectorKey_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mVectorKey;                                               // 0x00A8(0x0028) (Edit, BlueprintVisible)
	struct FVector                                     mValue;                                                   // 0x00D0(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	bool                                               mSucceed;                                                 // 0x00DC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_SetVectorKey.BTT_SetVectorKey_C");
		return ptr;
	}


	void ReceiveExecute(class AActor** OwnerActor);
	void ExecuteUbergraph_BTT_SetVectorKey(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
