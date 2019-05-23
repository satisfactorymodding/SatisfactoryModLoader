#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorBeltMk1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C
// 0x0008 (0x0688 - 0x0680)
class ABuild_ConveyorBeltMk1_C : public AFGBuildableConveyorBelt
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0680(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayConstructSound();
	void ExecuteUbergraph_Build_ConveyorBeltMk1(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
