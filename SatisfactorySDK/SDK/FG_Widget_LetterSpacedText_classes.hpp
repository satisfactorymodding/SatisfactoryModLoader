#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_LetterSpacedText_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_LetterSpacedText.Widget_LetterSpacedText_C
// 0x00E8 (0x02F0 - 0x0208)
class UWidget_LetterSpacedText_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UHorizontalBox*                              mContent;                                                 // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class FString                                      mText;                                                    // 0x0218(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	class FString                                      TempText;                                                 // 0x0228(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool                                               mCapitalLetters;                                          // 0x0238(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0239(0x0007) MISSED OFFSET
	struct FSlateFontInfo                              mFont;                                                    // 0x0240(0x0058) (Edit, BlueprintVisible)
	struct FSlateColor                                 mColor;                                                   // 0x0298(0x0028) (Edit, BlueprintVisible)
	class FString                                      mSpacingText;                                             // 0x02C0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TEnumAsByte<ETextJustify>                          mJustification;                                           // 0x02D0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x02D1(0x0003) MISSED OFFSET
	float                                              mLetterSpacing;                                           // 0x02D4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<class UWidget_LetterSpacedLetter_C*>        mLetterObjects;                                           // 0x02D8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool                                               mAnimate;                                                 // 0x02E8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x02E9(0x0003) MISSED OFFSET
	float                                              mLetterSpacingTemp;                                       // 0x02EC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_LetterSpacedText.Widget_LetterSpacedText_C");
		return ptr;
	}


	void PreConstruct(bool* IsDesignTime);
	void SetTitle(const class FString& Text);
	void OnAnimateText();
	void Construct();
	void ExecuteUbergraph_Widget_LetterSpacedText(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
