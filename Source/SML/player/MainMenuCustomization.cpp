#include "RichTextBlock.h"
#include "mod/blueprint_hooking.h"
#include "util/Logging.h"
#include "mod/ModHandler.h"
#include "SatisfactoryModLoader.h"
#include "WidgetBlueprintLibrary.h"
#include "util/ReflectionHelper.h"

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

void GRegisterMainMenuHooks() {
	UClass* MenuWidgetClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/MainMenu/BP_MainMenuWidget.BP_MainMenuWidget_C"));
	checkf(MenuWidgetClass, TEXT("MainMenuWidget blueprint not found"));
	UFunction* ConstructFunction = MenuWidgetClass->FindFunctionByName(TEXT("Construct"));
	
	HookBlueprintFunction(ConstructFunction, [](FBlueprintHookHelper& HookHelper) {
		UUserWidget* MenuWidget = Cast<UUserWidget>(HookHelper.GetContext());
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
		SMLTextBlock->Text = FText::FromString(FString::Join(CreateMenuInfoText(), TEXT("\n")));
		SMLTextBlock->SetFont(UsernameLabel->Font);
		SMLTextBlock->SetColorAndOpacity(UsernameLabel->ColorAndOpacity);
		ParentVerticalBox->AddChild(SMLTextBlock);
		
	}, EPredefinedHookOffset::Return);
}

