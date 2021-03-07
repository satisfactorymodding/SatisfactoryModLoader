#include "Patching/Patch/MainMenuPatch.h"
#include "Patching/BlueprintHookHelper.h"
#include "Patching/BlueprintHookManager.h"
#include "ModLoading/ModHandler.h"
#include "Reflection/ReflectionHelper.h"
#include "SatisfactoryModLoader.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/Engine.h"

UWidget* CreateModSubMenuWidget(UUserWidget* OwningWidget) {
	UClass* MenuBaseClass = LoadObject<UClass>(NULL, TEXT("/Game/SML/Widget_ModList.Widget_ModList_C"));
	if (MenuBaseClass == NULL) {
		//SML pak is not loaded, so class is not available
		//Mod list menu won't be openable, but game still can work without it
		return NULL;
	}
	UUserWidget* NewWidget = UUserWidget::CreateWidgetInstance(*OwningWidget, MenuBaseClass, TEXT("ModListSubMenu"));
	FReflectionHelper::SetPropertyValue<UObjectProperty>(NewWidget, TEXT("mOwningMenu"), OwningWidget);
	return NewWidget;
}

TArray<FString> FMainMenuPatch::CreateMenuInformationText() {
	const FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
	const int32 ModsLoaded = ModHandler->GetLoadedMods().Num();
	TArray<FString> ResultText;
	
	ResultText.Add(FString::Printf(TEXT("Satisfactory Mod Loader v.%s"), *FSatisfactoryModLoader::GetModLoaderVersion().ToString()));
	ResultText.Add(FString::Printf(TEXT("%lu mod(s) loaded"), ModsLoaded));

	if (FSatisfactoryModLoader::GetSMLConfiguration().bDevelopmentMode) {
		ResultText.Add(TEXT("Development mode enabled."));
	}
	return ResultText;
}

void FMainMenuPatch::ApplyMainMenuPatch(UUserWidget* MenuWidget) {
	UTextBlock* UsernameLabel = FReflectionHelper::GetObjectPropertyValue<UTextBlock>(MenuWidget, TEXT("UsernameLabel"));
	checkf(UsernameLabel, TEXT("UsernameLabel not found"));
	UVerticalBox* ParentVerticalBox = Cast<UVerticalBox>(UsernameLabel->GetParent());
	checkf(ParentVerticalBox, TEXT("UsernameLabel parent is not a vertical box"));
		
	UUserWidget* OptionsButton = FReflectionHelper::GetObjectPropertyValue<UUserWidget>(MenuWidget, TEXT("mButtonOptions"));
	UPanelWidget* SwitcherWidget = FReflectionHelper::GetObjectPropertyValue<UPanelWidget>(MenuWidget, TEXT("mSwitcher"));
	checkf(OptionsButton, TEXT("OptionsButton not found"));
	checkf(SwitcherWidget, TEXT("Switcher Widget not found"));

	UWidget* ModSubMenuWidget = CreateModSubMenuWidget(MenuWidget);
	if (ModSubMenuWidget != NULL) {
		SwitcherWidget->AddChild(ModSubMenuWidget);
	}
		
	UPanelWidget* ParentPanel = OptionsButton->GetParent();
	UClass* FrontEndButtonClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/Widget_FrontEnd_Button.Widget_FrontEnd_Button_C"));
	checkf(FrontEndButtonClass, TEXT("FrontEndButton class not found"));
	UUserWidget* ButtonWidget = UUserWidget::CreateWidgetInstance(*MenuWidget, FrontEndButtonClass, TEXT("mModListButton"));
	FText ButtonText = FText::FromString(TEXT("Mods"));
	FReflectionHelper::CallScriptFunction(ButtonWidget, TEXT("SetTitle"), ButtonText);
	if (ModSubMenuWidget != NULL) {
		FReflectionHelper::SetPropertyValue<UObjectProperty>(ButtonWidget, TEXT("mSwitcherWidget"), SwitcherWidget);
		FReflectionHelper::SetPropertyValue<UObjectProperty>(ButtonWidget, TEXT("mTargetWidget"), ModSubMenuWidget);
	}
	ParentPanel->AddChild(ButtonWidget);
		
	UTextBlock* SMLTextBlock = NewObject<UTextBlock>(ParentVerticalBox);
	SMLTextBlock->Text = FText::FromString(FString::Join(CreateMenuInformationText(), TEXT("\n")));
	SMLTextBlock->SetFont(UsernameLabel->Font);
	SMLTextBlock->SetColorAndOpacity(UsernameLabel->ColorAndOpacity);
	ParentVerticalBox->AddChild(SMLTextBlock);
}

void FMainMenuPatch::RegisterPatch() {
	UClass* MenuWidgetClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/MainMenu/BP_MainMenuWidget.BP_MainMenuWidget_C"));
	checkf(MenuWidgetClass, TEXT("MainMenuWidget blueprint not found"));
	UFunction* ConstructFunction = MenuWidgetClass->FindFunctionByName(TEXT("Construct"));

	UBlueprintHookManager* HookManager = GEngine->GetEngineSubsystem<UBlueprintHookManager>();
	HookManager->HookBlueprintFunction(ConstructFunction, [](FBlueprintHookHelper& HookHelper) {
        FMainMenuPatch::ApplyMainMenuPatch(CastChecked<UUserWidget>(HookHelper.GetContext()));
    }, EPredefinedHookOffset::Return);
}

