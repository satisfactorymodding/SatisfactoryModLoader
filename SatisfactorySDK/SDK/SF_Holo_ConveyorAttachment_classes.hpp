#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Holo_ConveyorAttachment_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Holo_ConveyorAttachment.Holo_ConveyorAttachment_C
// 0x0008 (0x0468 - 0x0460)
class AHolo_ConveyorAttachment_C : public AFGConveyorAttachmentHologram
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0460(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Holo_ConveyorAttachment.Holo_ConveyorAttachment_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveConfigureComponents(class AFGBuildable** inBuildable);
	void ExecuteUbergraph_Holo_ConveyorAttachment(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
