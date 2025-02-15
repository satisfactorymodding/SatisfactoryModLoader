#pragma once

#include "CoreMinimal.h"
#include "Misc/Variant.h"
#include "Settings/FGUserSetting.h"

#include "SessionSettingStringValueSelector.generated.h"

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, Abstract, AutoExpandCategories="Value")
class SML_API USessionSettingStringValueSelector : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()
	
public:
	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Custom; }

	virtual FVariant GetDefaultValue() const override { return defaultText.ToString(); }

	virtual TSubclassOf<class UFGOptionsValueController> GetValueSelectorWidgetClass() const override;

#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Value")
	FText defaultText;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Value")
	bool isPassword;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Widget" , meta=(EditConditionHides))
	TSubclassOf<class UFGOptionsValueController> DefaultTextEditWidget;
};