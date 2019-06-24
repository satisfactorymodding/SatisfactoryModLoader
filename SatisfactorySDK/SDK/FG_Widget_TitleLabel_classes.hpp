#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TitleLabel_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_TitleLabel.Widget_TitleLabel_C
// 0x0028 (0x0230 - 0x0208)
class UWidget_TitleLabel_C : public UUserWidget
{
public:
	class UTextBlock*                                  mTitleText;                                               // 0x0208(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	bool                                               mShouldShowColorPickerButton;                             // 0x0210(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0211(0x0007) MISSED OFFSET
	struct FText                                       mHeaderTitleText;                                         // 0x0218(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_TitleLabel.Widget_TitleLabel_C");
		return ptr;
	}


	void SetFicsItDriverText();
	void SetTitle(const struct FText& Title);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
