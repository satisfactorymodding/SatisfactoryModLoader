#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_JetPackMk2_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_JetPackMk2.Equip_JetPackMk2_C
// 0x0008 (0x0418 - 0x0410)
class AEquip_JetPackMk2_C : public AEquip_JetPack_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0410(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_JetPackMk2.Equip_JetPackMk2_C");
		return ptr;
	}


	void UserConstructionScript();
	void ConsumeFuel(float* Delta);
	void ExecuteUbergraph_Equip_JetPackMk2(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
