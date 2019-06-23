#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexEntry_Buildings_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_CodexEntry_Buildings.Widget_CodexEntry_Buildings_C
// 0x0010 (0x0270 - 0x0260)
class UWidget_CodexEntry_Buildings_C : public UWidget_CodexEntryParent_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0260(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UClass*                                      BuildingType;                                             // 0x0268(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_CodexEntry_Buildings.Widget_CodexEntry_Buildings_C");
		return ptr;
	}


	void PreConstruct(bool* IsDesignTime);
	void ExecuteUbergraph_Widget_CodexEntry_Buildings(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
