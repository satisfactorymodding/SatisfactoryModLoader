#include "MainMenuMixin.h"
#include "mod/blueprint_hooking.h"
#include "util/Logging.h"
#include "mod/ModHandler.h"
#include "SatisfactoryModLoader.h"
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

void GRegisterMainMenuHooks() {
	UClass* MenuWidgetClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/MainMenu/BP_MainMenuWidget.BP_MainMenuWidget_C"));
	check(MenuWidgetClass);
	UFunction* ConstructFunction = MenuWidgetClass->FindFunctionByName(TEXT("Construct"));
	HookBlueprintFunction(ConstructFunction, [](FBlueprintHookHelper& HookHelper) {
		UUserWidget* MenuWidget = Cast<UUserWidget>(HookHelper.GetContext());
		UTextBlock* UsernameLabel = FReflectionHelper::GetObjectPropertyValue<UTextBlock>(MenuWidget, TEXT("UsernameLabel"));
		UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(UsernameLabel->GetParent());
		UCanvasPanelSlot* UsernameSlot = Cast<UCanvasPanelSlot>(UsernameLabel->Slot);
		check(ParentCanvas);
		
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

