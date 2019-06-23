#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexContent_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_CodexContent.Widget_CodexContent_C
// 0x0000 (0x0208 - 0x0208)
class UWidget_CodexContent_C : public UUserWidget
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_CodexContent.Widget_CodexContent_C");
		return ptr;
	}


	void Habada(bool* NewParam);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
