#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_Equipment_Parent_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_HUDBox_Equipment_Parent.Widget_HUDBox_Equipment_Parent_C
// 0x0010 (0x0218 - 0x0208)
class UWidget_HUDBox_Equipment_Parent_C : public UUserWidget
{
public:
	class AFGEquipment*                                mEquipment;                                               // 0x0208(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class UWidget_HUDBox_C*                            mHudBoxParent;                                            // 0x0210(0x0008) (Edit, BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_HUDBox_Equipment_Parent.Widget_HUDBox_Equipment_Parent_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
