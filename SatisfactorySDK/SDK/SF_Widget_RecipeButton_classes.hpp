#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_RecipeButton_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_RecipeButton.Widget_RecipeButton_C
// 0x0060 (0x0270 - 0x0210)
class UWidget_RecipeButton_C : public UFGButtonWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0210(0x0008) (Transient, DuplicateTransient)
	class UMenuAnchor*                                 mRightClickMenu;                                          // 0x0218(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_ListButton_C*                        Widget_ListButton;                                        // 0x0220(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UClass*                                      mRecipeClass;                                             // 0x0228(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UWidget_ManualManufacturing_C*               Workbench;                                                // 0x0230(0x0008) (Edit, BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       mCachedInventory;                                         // 0x0238(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       NewVar_1;                                                 // 0x0240(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               isAffordable;                                             // 0x0248(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0249(0x0007) MISSED OFFSET
	struct FItemAmount                                 mItemAmount;                                              // 0x0250(0x0010) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FScriptMulticastDelegate                    UpdateWindowWidgetOffset;                                 // 0x0260(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_RecipeButton.Widget_RecipeButton_C");
		return ptr;
	}


	void ClearButtonSelection();
	class UWidget* GetCustomTooltip();
	ESlateVisibility GetRightClickMenuVisibility();
	class UWidget* CreateRightClickMenu();
	struct FLinearColor GetButtonHoverColor();
	struct FSlateColor GetTextHoverColor();
	bool IsButtonEnabled();
	void GetNumCanProduce(int* Result);
	ESlateVisibility GetNumCanProduceVisibility();
	struct FText GetNumCanProduceText();
	void CheckIngredients();
	struct FSlateBrush GetRecipeIcon();
	struct FLinearColor GetIconColor();
	struct FEventReply OnMouseButtonDown(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent);
	struct FText GetRecipeDisplayName();
	void Construct();
	void Tick(struct FGeometry* MyGeometry, float* InDeltaTime);
	void OnClicked();
	void OnHovered();
	void OnPressed();
	void OnMouseLeave(struct FPointerEvent* MouseEvent);
	void UpdateWindowWidgetOffset_Event();
	void ExecuteUbergraph_Widget_RecipeButton(int EntryPoint);
	void UpdateWindowWidgetOffset__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
