#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "Engine/DataAsset.h"
#include "Subsystems/EngineSubsystem.h"
#include "WidgetBlueprintHookManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWidgetBlueprintHookManager, All, All);

class UWidgetBlueprintHookData;

USTRUCT()
struct SML_API FWidgetBlueprintHookDescriptor {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Default")
	TObjectPtr<UWidgetBlueprintHookData> HookData{};
	
	UPROPERTY(VisibleAnywhere, Category = "Default")
	TObjectPtr<UUserWidget> InstalledWidget{};

	int32 RegistrationCount{0};
};

struct FWidgetBlueprintEditorSlowHookData {
	TSoftObjectPtr<UWidgetBlueprintHookData> HookData;
	int32 RegistrationCount{0};
};

UENUM(BlueprintType)
enum class EWidgetBlueprintHookParentType : uint8 {
	/** Hook directly using the parent widget name */
	Direct UMETA(DisplayName = "Direct"),
	/** Hook indirectly by traversing the widget hierarchy of the provided widget for the closest panel widget */
	Indirect_Child UMETA(DisplayName = "Indirect (Child)"),
	/**
	 * Hook directly using the parent widget name, including elements that aren't variables.
	 * Warning: use this feature with caution as widget structure elements that aren't variables are especially prone to changing across game updates
	 */
	Direct_Any UMETA(DisplayName = "Direct (Any)"),
};

namespace WidgetBlueprintHookParentValidator {
	SML_API bool ValidateParentWidget(UWidget* Widget, EWidgetBlueprintHookParentType ParentType, UPanelWidget*& OutParentWidget, bool bCheckVariableName = true);
	SML_API bool ValidateDirectWidget(UWidget* Widget, UPanelWidget*& OutPanelWidget, bool bCheckVariableName);
	SML_API bool ValidateIndirectChildWidget(UWidget* Widget, UPanelWidget*& OutPanelWidget, bool bCheckVariableName);
	SML_API bool ValidateWidgetBase(UWidget* Widget, bool bCheckVariableName);
}

UCLASS(Abstract)
class SML_API UWidgetBlueprintHookSlot : public UObject
{
	GENERATED_BODY()
public:
	virtual void SetupPanelSlot(UPanelSlot* InPanelSlot) {};
};

UCLASS(EditInlineNew)
class SML_API UWidgetBlueprintHookSlot_Generic : public UWidgetBlueprintHookSlot {
	GENERATED_BODY()
public:
	/** How much space this slot should occupy in the direction of the panel. */
	UPROPERTY(EditAnywhere, Category="Layout", meta = (DisplayAfter = "Padding"))
	FSlateChildSize Size{};

	/** The padding area between the slot and the content it contains. */
	UPROPERTY(EditAnywhere, Category="Layout")
	FMargin Padding{};

	/** The alignment of the object horizontally. */
	UPROPERTY(EditAnywhere, Category="Layout")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment{HAlign_Fill};

	/** The alignment of the object vertically. */
	UPROPERTY(EditAnywhere, Category="Layout")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment{HAlign_Fill};

	// Begin UWidgetBlueprintHookSlot interface
	virtual void SetupPanelSlot(UPanelSlot* InPanelSlot) override;
	// End UWidgetBlueprintHookSlot interface
};

UCLASS(EditInlineNew)
class SML_API UWidgetBlueprintHookSlot_Canvas : public UWidgetBlueprintHookSlot {
	GENERATED_BODY()
public:
	/** The anchoring information for the slot */
	UPROPERTY(EditAnywhere, Category = "Layout")
	FAnchorData LayoutData{};

	/** When AutoSize is true we use the widget's desired size */
	UPROPERTY(EditAnywhere, Category = "Layout")
	bool bAutoSize{false};

	/** The order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top). */
	UPROPERTY(EditAnywhere, Category = "Layout")
	int32 ZOrder{0};

	// Begin UWidgetBlueprintHookSlot interface
	virtual void SetupPanelSlot(UPanelSlot* InPanelSlot) override;
	// End UWidgetBlueprintHookSlot interface
};

/** Data required to hook into the existing widget blueprint */
UCLASS(NotBlueprintable, BlueprintType, EditInlineNew)
class SML_API UWidgetBlueprintHookData : public UDataAsset {
	GENERATED_BODY()
public:
	/** Use this field to leave future you notes about what this hook is supposed to accomplish */
	UPROPERTY(EditAnywhere, Category = "Default", meta = (MultiLine = "true"))
	FString DeveloperComment;

	/** Widget Blueprint to hook */
	UPROPERTY(EditAnywhere, Category = "Default")
	TSoftClassPtr<UUserWidget> WidgetClass;

	/**
	 * Class of the widget blueprint that will be added into the hooked blueprint
	 * Use Widget | Advanced | Find Parent Widget Of Class to access the outer WidgetClass that you have hooked
	 * Because there are no delegates available, that is the only way for you to read the state
	 * of your outer widget blueprint without manually going through outer or parent chains
	 */
	UPROPERTY(EditAnywhere, Category = "Default")
	TSubclassOf<UUserWidget> NewWidgetClass{};
	
	/** Name of the widget to attach */
	UPROPERTY(EditAnywhere, Category = "Default")
	FName NewWidgetName;
	
	/**
	 * The method that is used for resolving a parent widget for this widget
	 * The Indirect (Child) is useful when your parent container is not a variable but one of your children is
	 */
	UPROPERTY(EditAnywhere, Category = "Advanced")
	EWidgetBlueprintHookParentType ParentWidgetType{EWidgetBlueprintHookParentType::Direct};
	
	/** Name of the parent widget variable to attach this widget to. Must a panel widget. */
	UPROPERTY(EditAnywhere, Category = "Default", meta = (GetOptions = "GetParentWidgetNames"))
	FName ParentWidgetName;
	
	/**
	 * When not -1, specifies the index in the parent widget Slots array at which the widget will be inserted
	 * By default the widget will be appended to the array, but you can change the order if needed */
	UPROPERTY(EditAnywhere, Category = "Advanced")
	int32 ParentSlotIndex{INDEX_NONE};
	
	/** Configuration for the slot */
	UPROPERTY(EditAnywhere, Instanced, Category = "Default")
	TObjectPtr<UWidgetBlueprintHookSlot> SlotConfiguration{};

	UFUNCTION(BlueprintPure)
	TArray<FString> GetParentWidgetNames() const;
	UPanelWidget* ResolveParentWidgetOnArchetype() const;
	UPanelWidget* ResolveParentWidget(const UWidgetTree* InWidgetTree) const;
	void AttachToWidgetInstance(UUserWidget* InWidgetTreeRoot, UPanelWidget* InParentWidget) const;
};

UCLASS()
class SML_API UWidgetBlueprintHookManager : public UEngineSubsystem {
	GENERATED_BODY()
private:
	/** Hooks that are installed directly on the widget tree archetypes. These are destructive to the original assets */
	UPROPERTY()
	TArray<FWidgetBlueprintHookDescriptor> InstalledArchetypeHooks;

	/** Hooks that are installed externally and trigger on widget instance initialization. Non-destructive, used in Editor & Commandlets */
	TMap<FTopLevelAssetPath, TArray<FWidgetBlueprintEditorSlowHookData>> InstalledSlowEditorHooks;
public:
	/** Installs the widget blueprint hook */
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData);

	/** Removes the previously installed widget blueprint hook */
	UFUNCTION(BlueprintCallable)
	void UnregisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData);

	/** Called from the initialization to register static hooks if necessary */
	static void RegisterStaticHooks();
private:
	static void WidgetBlueprintGeneratedClassInitializeWidget(const UBlueprintGeneratedClass* WidgetClass, UUserWidget* UserWidget);
};
