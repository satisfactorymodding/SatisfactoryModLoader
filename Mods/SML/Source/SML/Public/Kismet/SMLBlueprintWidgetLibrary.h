#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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
	 * of the containing UUserWidget) before attempting to retrieve its UWidgetTree outer and consequentially
	 * the owning UUserWidget. The reason for that behavior are named slots, which when used can result in a disparity
	 * between logical location of the widget (inside of the child widget tree's named slot) and its physical location
	 * (its outer is the owning parent widget tree). In that ambiguity, we follow the logical position,
	 * and the immediate owner of the widget would be a child widget tree (although we will still recurse into the parent tree later on)
	 *
	 * Keep in mind that normally widgets should make ZERO assumptions about their container
	 * and use public properties, named slots and delegates instead to facilitate interaction with their host,
	 * but in some particular cases (read "widget blueprint hooking") interacting with host blueprint can be really tricky
	 * because you have no access to its bindings (since your injected widget has no backing FObjectProperty).
	 *
	 * But because in such cases you have a very clear knowledge of your supposed parent widget,
	 * you can utilize it to retrieve its data directly. Such operations should be carefully done
	 * and only used in the context of the widget blueprint hooking.
	 */
	UFUNCTION(BlueprintCallable, Category = "Widget | Advanced", meta = (DefaultToSelf = "CurrentWidget", DeterminesOutputType = "Class"))
	static UUserWidget* FindParentWidgetOfClass(UUserWidget* CurrentWidget, TSubclassOf<UUserWidget> Class, int32 MaxDepth = 0);

	/**
	 * Traverses all of the direct and potentially indirect widgets owned by the provided widget tree
	 * and attempts to find all the widgets matching the provided class.
	 * 
	 * Note that the search process can't break through the sandboxing of child user widgets,
	 * so you must either chain calls to this function on those child widgets or pass the "closest" child if you have access to it.
	 * Examples of this situation include content in named slots or widgets that use other User Widgets in their hierarchy.
	 *
	 * Keep in mind that normally widgets should just use bindings, named slots or manually read properties of the nested
	 * widget trees to access and modify their content, but in some particular cases (read "widget blueprint hooking")
	 * multiple dynamically added widgets might want to interact with each other, and because neither of them can use delegates
	 * or class level properties, they have to resort to manual widget hierarchy lookup. Really dirty, but it works.
	 */
	UFUNCTION(BlueprintCallable, Category = "Widget | Advanced", meta = (DefaultToSelf = "CurrentWidget", DeterminesOutputType = "Class"))
	static TArray<UWidget*> FindChildWidgetsOfClass(UUserWidget* CurrentWidget, TSubclassOf<UWidget> Class, bool bSearchDescendants = false);
};
