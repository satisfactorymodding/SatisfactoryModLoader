#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	UWidgetBlueprintHookData* HookData;
	
	UPROPERTY(VisibleAnywhere, Category = "Default")
	UUserWidget* InstalledWidget;
};

UENUM(BlueprintType)
enum class EWidgetBlueprintHookParentType : uint8 {
	/** Hook directly using the parent widget name */
	Direct UMETA(DisplayName = "Direct"),
	/** Hook indirectly by traversing the widget hierarchy of the provided widget for the closest panel widget */
	Indirect_Child UMETA(DisplayName = "Indirect (Child)")
};

namespace WidgetBlueprintHookParentValidator {
	SML_API bool ValidateParentWidget(UWidget* Widget, EWidgetBlueprintHookParentType ParentType, UPanelWidget*& OutParentWidget, bool bCheckVariableName = true);

	SML_API bool ValidateDirectWidget(UWidget* Widget, UPanelWidget*& OutPanelWidget, bool bCheckVariableName);
	SML_API bool ValidateIndirectChildWidget(UWidget* Widget, UPanelWidget*& OutPanelWidget, bool bCheckVariableName);
	SML_API bool ValidateWidgetBase(UWidget* Widget, bool bCheckVariableName);
}

/** Data required to hook into the existing widget blueprint */
UCLASS(NotBlueprintable, BlueprintType, EditInlineNew)
class SML_API UWidgetBlueprintHookData : public UDataAsset {
	GENERATED_BODY()
public:
	UWidgetBlueprintHookData();
	
	/** Use this field to leave future you notes about what this hook is supposed to accomplish */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (MultiLine = "true"))
	FString DeveloperComment;

	/** Widget Blueprint to hook */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", BlueprintSetter = SetWidgetClass)
	TSoftClassPtr<UUserWidget> WidgetClass;
	
	/**
	 * Class of the widget blueprint that will be added into the hooked blueprint
	 * Use Widget | Advanced | Find Parent Widget Of Class to access the outer WidgetClass that you have hooked
	 * Because there are no delegates available, that is the only way for you to read the state
	 * of your outer widget blueprint without manually going through outer or parent chains
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", BlueprintSetter = SetNewWidgetClass)
	TSubclassOf<UUserWidget> NewWidgetClass;

	/** Name of the widget to attach */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", BlueprintSetter = SetNewWidgetName)
	FName NewWidgetName;

	/** The template of the new widget that will be added to SCS */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (ShowInnerProperties))
	UUserWidget* NewWidgetTemplate;

	/**
	 * The method that is used for resolving the parent widget for this widget
	 * The Indirect (Child) is useful when your parent container is not a variable but one of your children is
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")
	EWidgetBlueprintHookParentType ParentWidgetType;
	
	/** Name of the parent widget variable to attach this widget to. Must a panel widget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (GetOptions = "GetParentWidgetNames"))
	FName ParentWidgetName;

	/**
	 * When not -1, specifies the index in the parent widget Slots array at which the widget will be inserted
	 * By default the widget will be appended to the array, but you can change the order if needed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")
	int32 ParentSlotIndex;
	
	/** Class of the panel slot of the parent widget we are hooking into */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Advanced")
	TSubclassOf<UPanelSlot> PanelSlotClass;

	/** The panel slot that will be used for the widget */
	UPROPERTY(Instanced, VisibleAnywhere, Category = "Default", BlueprintReadOnly)
	UPanelSlot* PanelSlotTemplate;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintPure)
	TArray<FString> GetParentWidgetNames() const;
	
	/** Updates the blueprint widget class being hooked */
	UFUNCTION(BlueprintSetter)
	void SetWidgetClass(TSoftClassPtr<UUserWidget> InWidgetClass);
	
	/** Updates widget name for the hook */
	UFUNCTION(BlueprintSetter)
	void SetNewWidgetName(FName InNewWidgetName);

	UFUNCTION(BlueprintSetter)
	void SetParentWidgetType(EWidgetBlueprintHookParentType InParentWidgetType);
	
	/** Updates widget class for the inserted widget */
	UFUNCTION(BlueprintSetter)
	void SetNewWidgetClass(TSubclassOf<UUserWidget> InNewWidgetClass);

	/** Updates the name of the parent widget for this hook */
	UFUNCTION(BlueprintSetter)
	void SetParentWidgetName(FName InParentWidgetName);
	
	void ReinitializeNewWidgetTemplate();
	void ReinitializePanelSlotTemplate();
	UPanelWidget* ResolveParentWidget() const;
};

UCLASS()
class SML_API UWidgetBlueprintHookManager : public UEngineSubsystem {
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = "Default")
	TArray<FWidgetBlueprintHookDescriptor> InstalledHooks;
public:
	/** Installs the widget blueprint hook */
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData);

	/** Removes the previously installed widget blueprint hook */
	UFUNCTION(BlueprintCallable)
	void UnregisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData);
};
