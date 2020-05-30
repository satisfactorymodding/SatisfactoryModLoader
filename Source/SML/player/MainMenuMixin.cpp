#include "MainMenuMixin.h"

#include "RichTextBlock.h"
#include "mod/blueprint_hooking.h"
#include "util/Logging.h"
#include "mod/ModHandler.h"
#include "SatisfactoryModLoader.h"
#include "WidgetBlueprintLibrary.h"
#include "util/ReflectionHelper.h"
#include "util/UMGHelper.h"
#define LOCTEXT_NAMESPACE "SML"

TArray<FString> CreateMenuInfoText() {
	const FModHandler& modHandler = SML::GetModHandler();
	const int32 modsLoaded = modHandler.GetLoadedMods().Num();
	TArray<FString> resultText;
	resultText.Add(FString::Printf(TEXT("Satisfactory Mod Loader v.%s"), *SML::GetModLoaderVersion().String()));
	resultText.Add(FString::Printf(TEXT("%lu mod(s) loaded"), modsLoaded));
	resultText.Add(FString::Printf(TEXT("Bootstrapper v.%s"), *SML::GetBootstrapperVersion().String()));
	if (SML::GetSmlConfig().bDevelopmentMode) {
		resultText.Add(TEXT("Development mode enabled."));
	}
	return resultText;
}

UWidget* CreateSubMenuBackground(UWidget* OwnerWidget, UWidget* Content, FName WidgetName) {
	UClass* BackgroundClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/Widget_SubMenuBackground.Widget_SubMenuBackground_C"));
	UUserWidget* NewWidget = UUserWidget::CreateWidgetInstance(*OwnerWidget, BackgroundClass, WidgetName);
	UNamedSlot* ContentSlot = FReflectionHelper::GetObjectPropertyValue<UNamedSlot>(NewWidget, TEXT("mContent"));
	ContentSlot->ClearChildren();
	ContentSlot->SetContent(Content);
	return NewWidget;
}

UUserWidget* CreateFrontEndButton(UWidget* ParentPanel, FName ObjectName, const FText& DisplayName) {
	UClass* FrontEndButtonClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/Widget_FrontEnd_Button.Widget_FrontEnd_Button_C"));
	UUserWidget* ButtonWidget = NewObject<UUserWidget>(ParentPanel, FrontEndButtonClass, ObjectName);
	FReflectionHelper::SetPropertyValue<UTextProperty>(ButtonWidget, TEXT("mDisplayText"), DisplayName);
	return ButtonWidget;
}

void FillModContentPane(UVerticalBox* ContentPane, const FModInfo& ModInfo) {
	//Mod title with bigger size
	UTextBlock* ModTitle = NewObject<UTextBlock>(ContentPane, TEXT("ModTitle"));
	ModTitle->Text = FText::FromString(ModInfo.Name);
	ModTitle->Font.Size = 20;
	UVerticalBoxSlot* TitleSlot = ContentPane->AddChildToVerticalBox(ModTitle);
	TitleSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	TitleSlot->SetPadding(FMargin{0.0f, 20.0f, 0.0f, 10.0f});
	
	//TODO mod logo here

	//Mod version and authors
	UHorizontalBox* InfoBox = NewObject<UHorizontalBox>(ContentPane, TEXT("InfoBox"));
	UTextBlock* ModVersion = NewObject<UTextBlock>(InfoBox, TEXT("ModVersion"));
	ModVersion->Text = FText::FromString(FString::Printf(TEXT("v%s"), *ModInfo.Version.String()));
	ModVersion->Font.Size = 10;
	InfoBox->AddChildToHorizontalBox(ModVersion)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
	if (ModInfo.Authors.Num() > 0) {
		UTextBlock* ModAuthors = NewObject<UTextBlock>(InfoBox, TEXT("ModAuthors"));
		const FString Authors = FString::Printf(TEXT("by %s"), *FString::Join(ModInfo.Authors, TEXT(", ")));
		ModAuthors->Text = FText::FromString(Authors);
		InfoBox->AddChildToHorizontalBox(ModAuthors)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);
	}
	UVerticalBoxSlot* InfoBoxSlot = ContentPane->AddChildToVerticalBox(InfoBox);
	InfoBoxSlot->SetPadding(FMargin{30.0f, 10.0f, 30.0f, 10.0f});
	
	//Mod description and mod configuration options
	URichTextBlock* RichTextBlock = NewObject<URichTextBlock>(ContentPane, TEXT("DescriptionText"));
	RichTextBlock->SetText(FText::FromString(ModInfo.Description));
	UVerticalBoxSlot* DescriptionSlot = ContentPane->AddChildToVerticalBox(RichTextBlock);
	DescriptionSlot->SetPadding(FMargin{30.0f, 10.0f, 30.0f, 10.0f});
}

UButtonClickHandlerWidget::UButtonClickHandlerWidget() {
	Visibility = ESlateVisibility::Collapsed;
}

void UButtonClickHandlerWidget::OnButtonClicked() const {
	bool NewSelected = !FReflectionHelper::GetPropertyValue<UBoolProperty>(SelfButton, TEXT("isSelected"));
	FReflectionHelper::CallScriptFunction(SelfButton, TEXT("SetSelected"), NewSelected);
	//In either case, we need to clear children widgets now
	ContentBox->ClearChildren();
	//If we are selected now, populate content box
	if (NewSelected) {
		FillModContentPane(ContentBox, ModInfo);
	}
}

void PopulateModButtonList(UVerticalBox* ButtonContainer, UVerticalBox* ContentBox) {
	const FModHandler& ModHandler = SML::GetModHandler();
	
	for (const FString& ModId : ModHandler.GetLoadedMods()) {
		UButtonClickHandlerWidget* ClickHandler = NewObject<UButtonClickHandlerWidget>(ButtonContainer);
		ButtonContainer->AddChild(ClickHandler);
		const FModInfo& ModInfo = ModHandler.GetLoadedMod(ModId).ModInfo;
		UUserWidget* ModButton = CreateFrontEndButton(ButtonContainer, *ModId, FText::FromString(ModInfo.Name));
		UButton* ButtonHandle = FReflectionHelper::GetObjectPropertyValue<UButton>(ModButton, TEXT("mFrontEndButton"));
		ClickHandler->ModInfo = ModInfo;
		ClickHandler->ContentBox = ContentBox;
		ClickHandler->SelfButton = ModButton;
		FScriptDelegate MyScriptDelegate;
		MyScriptDelegate.BindUFunction(ClickHandler, TEXT("OnButtonClicked"));
		ButtonHandle->OnClicked.Add(MyScriptDelegate);
		ButtonContainer->AddChild(ModButton);
	}
}

UWidget* CreateModSubMenuWidget(UWidget* OwningWidget) {
	UClass* MenuBaseClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/BP_MenuBase.BP_MenuBase_C"));
	UUserWidget* NewWidget = UUserWidget::CreateWidgetInstance(*OwningWidget, MenuBaseClass, TEXT("ModListSubMenu"));
	FReflectionHelper::SetPropertyValue<UObjectProperty>(NewWidget, TEXT("mOwningMenu"), OwningWidget);
	
	UHorizontalBox* RootBox = NewObject<UHorizontalBox>(OwningWidget);
	NewWidget->WidgetTree->RootWidget = RootBox;
	UVerticalBox* ModListMenu = NewObject<UVerticalBox>(RootBox, TEXT("mModList"));
	
	UWidget* MenuBackgroundWrapper = CreateSubMenuBackground(RootBox, ModListMenu, TEXT("ModListView"));
	UHorizontalBoxSlot* LeftPanelSlot = RootBox->AddChildToHorizontalBox(MenuBackgroundWrapper);
	LeftPanelSlot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;
	LeftPanelSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
	LeftPanelSlot->Size.SizeRule = ESlateSizeRule::Automatic;

	UClass* ScrollBoxClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/InGame/-Shared/Widget_Scrollbox.Widget_Scrollbox_C"));
	UUserWidget* ScrollBoxWidget = UUserWidget::CreateWidgetInstance(*OwningWidget, ScrollBoxClass, TEXT("ScrollBox"));
	UWidget* ContentMenuBackgroundWrapper = CreateSubMenuBackground(RootBox, ScrollBoxWidget, TEXT("ModListContent"));
	UHorizontalBoxSlot* RightPanelSlot = RootBox->AddChildToHorizontalBox(ContentMenuBackgroundWrapper);
	RightPanelSlot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;
	RightPanelSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
	RightPanelSlot->Size.SizeRule = ESlateSizeRule::Fill;

	UNamedSlot* ScrollBoxSlot = FReflectionHelper::GetObjectPropertyValue<UNamedSlot>(ScrollBoxWidget, TEXT("mScrollableContent"));
	ScrollBoxSlot->ClearChildren();
	UVerticalBox* ContentBox = NewObject<UVerticalBox>(ScrollBoxWidget, TEXT("ScrollContent"));
	ScrollBoxSlot->SetContent(ContentBox);
	PopulateModButtonList(ModListMenu, ContentBox);
	
	return NewWidget;
}

void GRegisterMainMenuHooks() {
	UClass* MenuWidgetClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/MainMenu/BP_MainMenuWidget.BP_MainMenuWidget_C"));
	checkf(MenuWidgetClass, TEXT("MainMenuWidget blueprint not found"));
	UFunction* ConstructFunction = MenuWidgetClass->FindFunctionByName(TEXT("Construct"));
	
	HookBlueprintFunction(ConstructFunction, [](FBlueprintHookHelper& HookHelper) {
		UUserWidget* MenuWidget = Cast<UUserWidget>(HookHelper.GetContext());
		UTextBlock* UsernameLabel = FReflectionHelper::GetObjectPropertyValue<UTextBlock>(MenuWidget, TEXT("UsernameLabel"));
		checkf(UsernameLabel, TEXT("UsernameLabel not found"));
		UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(UsernameLabel->GetParent());
		UCanvasPanelSlot* UsernameSlot = Cast<UCanvasPanelSlot>(UsernameLabel->Slot);

		UUserWidget* OptionsButton = FReflectionHelper::GetObjectPropertyValue<UUserWidget>(MenuWidget, TEXT("buttonOptions"));
		UPanelWidget* SwitcherWidget = FReflectionHelper::GetObjectPropertyValue<UPanelWidget>(MenuWidget, TEXT("mSwitcher"));
		checkf(OptionsButton, TEXT("OptionsButton not found"));
		checkf(SwitcherWidget, TEXT("Switcher Widget not found"));

		UWidget* ModSubMenuWidget = CreateModSubMenuWidget(MenuWidget);
		SwitcherWidget->AddChild(ModSubMenuWidget);
		
		UPanelWidget* ParentPanel = OptionsButton->GetParent();
		const int32 ChildIndex = ParentPanel->GetChildIndex(OptionsButton);
		UUserWidget* ButtonWidget = CreateFrontEndButton(ParentPanel, TEXT("buttonMods"), LOCTEXT("Menu.ButtonMods", "Mod List"));
		
		FReflectionHelper::SetPropertyValue<UObjectProperty>(ButtonWidget, TEXT("mSwitcherWidget"), SwitcherWidget);
		FReflectionHelper::SetPropertyValue<UObjectProperty>(ButtonWidget, TEXT("mTargetWidget"), ModSubMenuWidget);
		FUMGHelper::InsertChildAtIndex(ParentPanel, ChildIndex, ButtonWidget);
		
		UTextBlock* SMLTextBlock = NewObject<UTextBlock>(ParentCanvas);
		SMLTextBlock->Text = FText::FromString(FString::Join(CreateMenuInfoText(), TEXT("\n")));
		SMLTextBlock->SetFont(UsernameLabel->Font);
		SMLTextBlock->SetColorAndOpacity(UsernameLabel->ColorAndOpacity);
		UCanvasPanelSlot* Slot = ParentCanvas->AddChildToCanvas(SMLTextBlock);
		
		Slot->SetAnchors(UsernameSlot->GetAnchors());
		Slot->SetAlignment(FVector2D{0.0f, 1.0f});
		const FVector2D UsernamePos = UsernameSlot->GetPosition();
		Slot->SetPosition(FVector2D{UsernamePos.X, -120.0f});
		Slot->ZOrder = UsernameSlot->ZOrder;
	}, EPredefinedHookOffset::Return);
}

