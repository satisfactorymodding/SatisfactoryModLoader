#pragma once

#include "CoreMinimal.h"
#include "Misc/Variant.h"
#include "Settings/FGUserSetting.h"

#include "StringValueSelector.generated.h"

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, Abstract, AutoExpandCategories="Value")
class SML_API UStringValueSelector : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()
	
public:
	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Custom; }

	virtual FVariant GetDefaultValue() const override { return Default; }

	virtual bool ShouldFocusOptionSlotToEdit() const override { return true; }

	virtual TSubclassOf<class UFGOptionsValueController> GetValueSelectorWidgetClass() const override;

#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Value", meta=(DisplayName="Default Value"))
	FString Default;

	// Displayed to the user when no value is entered
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Value")
	FText HintText;

	// When true, use Unreal's password mode for the widget, causing all characters to render as dots
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Value")
	bool IsPassword;

	// Use session setting "Custom Value Selector Widget" if you want to use a different widget
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Widget" , meta=(EditConditionHides))
	TSubclassOf<class UFGOptionsValueController> DefaultTextEditWidget;
};