#include "mod/blueprint_hooking.h"
#include "util/Logging.h"

void GRegisterBuildMenuHooks() {
	UClass* BuildMenuWidgetClass = LoadObject<UClass>(nullptr, TEXT("/Game/FactoryGame/Interface/UI/InGame/BuildMenu/Prototype/Widget_BuildMenu.Widget_BuildMenu_C"));
	check(BuildMenuWidgetClass);
	UFunction* ConstructFunction = BuildMenuWidgetClass->FindFunctionByName(TEXT("Construct"));
	check(ConstructFunction);
	HookBlueprintFunction(ConstructFunction, [](FBlueprintHookHelper& HookHelper) {
		//Reflectively retrieve button container
		UUserWidget* BuildMenuWidget = Cast<UUserWidget>(HookHelper.GetContext());
		UObjectProperty* Property = Cast<UObjectProperty>(BuildMenuWidget->GetClass()->FindPropertyByName(TEXT("mCategoryButtonsContainer")));
		checkf(Property, TEXT("mCategoryButtonsContainer not found"));
		
		//Resolve category buttons container, then root size box in it
		UUserWidget* CategoryButtonsContainer = Cast<UUserWidget>(Property->GetObjectPropertyValue_InContainer(BuildMenuWidget));
		USizeBox* RootWidget = Cast<USizeBox>(CategoryButtonsContainer->WidgetTree->RootWidget);
		checkf(RootWidget, TEXT("CategoryButtonsContainer widget root widget is not a size box!"));
		UWidget* ContentWidget = RootWidget->GetContent();

		RootWidget->SetMaxDesiredHeight(600);
		RootWidget->bOverride_MaxDesiredHeight = true;
		
		//Create scroll box, populate it and set content
		UScrollBox* ScrollBox = NewObject<UScrollBox>(RootWidget);
		ScrollBox->SetScrollbarThickness(FVector2D(2.0f, 2.0f));
		RootWidget->SetContent(ScrollBox);
		ScrollBox->AddChild(ContentWidget);
	}, EPredefinedHookOffset::Return);
}
