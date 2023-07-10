#include "Kismet/SMLBlueprintWidgetLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"

UUserWidget* USMLBlueprintWidgetLibrary::FindParentWidgetOfClass(UUserWidget* CurrentWidget, TSubclassOf<UUserWidget> Class, int32 MaxDepth) {
	int32 CurrentDepth = 0;
	while (true) {
		//If current widget is null, return NULL
		if (CurrentWidget == NULL) {
			return NULL;
		}

		//Bail out early if we have exceeded the maximum search depth
		if (MaxDepth && ++CurrentDepth > MaxDepth) {
			return NULL;
		}
		
		//First attempt to resolve the root widget of the logical UMG widget hierarchy
		const UWidget* TreeRootWidget = CurrentWidget;
		while (const UWidget* ParentWidget = TreeRootWidget->GetParent()) {
			TreeRootWidget = ParentWidget;
		}
		
		//The resulting widget should have UWidgetTree as its outer with RootWidget set to itself
		const UWidgetTree* WidgetTree = Cast<UWidgetTree>(TreeRootWidget->GetOuter());

		//If root widget is somehow not owned by the widget tree,
		//chances are we have hit the root of this widget hierarchy
		//Normally, the most common root outer objects are
		//UWidgetTree (nested hierarchy), UGameInstance (when available), UWorld (otherwise)
		if (WidgetTree == NULL) {
			return NULL;
		}
		
		//We should always be the root, check just in case
		if (!ensure(WidgetTree->RootWidget == TreeRootWidget)) {
			return NULL;
		}

		//The owner of the actual UWidgetTree is most likely either UUserWidget, UWidgetBlueprint or UWidgetBlueprintGeneratedClass
		//In latter two cases, the widget tree is a mutable template, which we under any circumstances must not
		//mutate or pass around to the external blueprint code. so if it is a template, we return nothing
		if (WidgetTree->IsTemplate()) {
			return NULL;
		}

		//Otherwise we should be fairly confident it's UUserWidget that is the outer
		UUserWidget* OuterUserWidget = Cast<UUserWidget>(WidgetTree->GetOuter());
		if (!ensure(OuterUserWidget)) {
			return NULL;
		}

		//If it matches our queried up class, return it
		if (OuterUserWidget && OuterUserWidget->IsA(Class)) {
			return OuterUserWidget;
		}
		//Otherwise we interpret it as a new current widget
		CurrentWidget = OuterUserWidget;
	}
}

TArray<UWidget*> USMLBlueprintWidgetLibrary::FindChildWidgetsOfClass(UUserWidget* CurrentWidget, TSubclassOf<UWidget> WidgetClass, bool bSearchDescendants) {
	TArray<UWidget*> ResultWidgets;

	if (CurrentWidget && CurrentWidget->WidgetTree) {
		const UWidgetTree* WidgetTree = CurrentWidget->WidgetTree;
		
		//Absolutely not dealing with template widget trees, they should never get there
		if (WidgetTree->IsTemplate()) {
			return ResultWidgets;
		}

		const auto ForEachWidgetLambda = [&](UWidget* OtherWidget) {
			if (OtherWidget->IsA(WidgetClass)) {
				ResultWidgets.Add(OtherWidget);
			}
		};
		if (bSearchDescendants) {
			WidgetTree->ForEachWidgetAndDescendants(ForEachWidgetLambda);
		} else {
			WidgetTree->ForEachWidget(ForEachWidgetLambda);
		}
	}
	return ResultWidgets;
}

