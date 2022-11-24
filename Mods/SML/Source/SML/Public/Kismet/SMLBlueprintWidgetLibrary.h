#pragma once
#include "CoreMinimal.h"
#include "SMLBlueprintWidgetLibrary.generated.h"

UCLASS()
class SML_API USMLBlueprintWidgetLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	/**
	 * Traverses the outer hierarchy of the provided widget and attempts
	 * to find the first widget of the class that be casted to the provided one and returns it
	 * Will break through outer widget trees to find the resulting widget
	 * When traversing the hierarchy, it will always try to come down to the outermost UWidget (that would be UWidgetTree::RootWidget
	 * of the containing UUserWidget) before attempting to retrieve it's UWidgetTree outer and consequentially
	 * the owning UUserWidget. The reason for that behavior are named slots, which when used can result in a disparity
	 * between logical location of the widget (inside of the child widget tree's named slot) and it's physical location
	 * (it's outer is the owning parent widget tree). In that ambiguity, we follow the logical position,
	 * and the immediate owner of the widget would be a child widget tree (although we will still recurse into the parent tree later on)
	 *
	 * Keep in mind that normally widgets should make ZERO assumptions about their container
	 * and use public properties, named slots and delegates instead to facillate interaction with their host,
	 * but in some particular cases (read "widget blueprint hooking") interacting with host blueprint can be really tricky
	 * because you have no access to it's bindings (since your injected widget has no backing FObjectPropeerty).
	 *
	 * But because in such cases you have a very clear knowledge of your supposed parent widget,
	 * you can utilize it to retrieve it's data directly. Such operations should be carefully done
	 * and only used in the context of the widget blueprint hooking.
	 */
	UFUNCTION(BlueprintCallable, Category = "Widget | Advanced", meta = (DefaultToSelf = "CurrentWidget", DeterminesOutputType = "Class"))
	static UUserWidget* FindParentWidgetOfClass(UUserWidget* CurrentWidget, TSubclassOf<UUserWidget> Class, int32 MaxDepth = 0);

	/**
	 * Traverses all of the direct and potentially indirect widgets owned by the provided widget tree
	 * And attempts to find all the widget matching the provided class
	 *
	 * Keep in mind that normally widgets should just use bindings, named slots or manually read properties of the nested
	 * widget trees to access and modify their content, but in some particular cases (read "widget blueprint hooking")
	 * multiple dynamically added widgets might want to interact with each other, and because neither of them can use delegates
	 * or class level properties, they have to resort to manual widget hierarchy lookup. Really dirty, but it works.
	 */
	UFUNCTION(BlueprintCallable, Category = "Widget | Advanced", meta = (DefaultToSelf = "CurrentWidget", DeterminesOutputType = "Class"))
	static TArray<UWidget*> FindChildWidgetsOfClass(UUserWidget* CurrentWidget, TSubclassOf<UWidget> Class, bool bSearchDescendants = false);
};