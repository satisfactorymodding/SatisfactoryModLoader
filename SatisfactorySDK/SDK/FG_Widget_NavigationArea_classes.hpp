#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NavigationArea_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_NavigationArea.Widget_NavigationArea_C
// 0x0018 (0x0220 - 0x0208)
class UWidget_NavigationArea_C : public UUserWidget
{
public:
	struct FText                                       mNavigationText;                                          // 0x0208(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_NavigationArea.Widget_NavigationArea_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
