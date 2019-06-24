#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_SchematicCAT1_ADA-S17Message_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass SchematicCAT1_ADA-S17Message.SchematicCAT1_ADA-S17Message_C
// 0x0000 (0x02F0 - 0x02F0)
class USchematicCAT1_ADA_S17Message_C : public UWidget_AudioMessage_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass SchematicCAT1_ADA-S17Message.SchematicCAT1_ADA-S17Message_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
