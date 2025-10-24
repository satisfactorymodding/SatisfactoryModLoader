#pragma once

#include "Algo/Reverse.h"
#include "CoreMinimal.h"
#include "Settings/FGUserSetting.h"

#include "SMLIntValueSelector.generated.h"

UCLASS(Blueprintable,
       DefaultToInstanced,
       EditInlineNew,
       AutoExpandCategories = "Value",
       meta = (DisplayName = "Integer Selector (Extended)"))
class SML_API USMLIntValueSelector : public UFGUserSetting_IntSelector {
  GENERATED_BODY()

#if WITH_EDITORONLY_DATA
 protected:
  /**
   * Auto populate the integer selection values from this enum class's values.
   */
  UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Value")
  class UEnum* EnumClass;

  /**
   * If true, the enum values will be displayed in reverse order.
   */
  UPROPERTY(BlueprintReadOnly,
            EditDefaultsOnly,
            Category = "Value",
            meta = (EditCondition = "EnumClass != nullptr", EditConditionHides))
  bool bReverseEnumOrder;

  void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
    Super::PostEditChangeProperty(PropertyChangedEvent);
    if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(USMLIntValueSelector, EnumClass) ||
        PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(USMLIntValueSelector, bReverseEnumOrder)) {
      PopulateIntegerSelectionValues();
    }
  }

 private:
  void PopulateIntegerSelectionValues() {
    if (EnumClass == nullptr) {
      // Don't auto empty the values - the user may still want them.
      return;
    }
    IntegerSelectionValues.Empty();
    int32 EnumCount = EnumClass->ContainsExistingMax() ? EnumClass->NumEnums() - 1 : EnumClass->NumEnums();
    IntegerSelectionValues.Reserve(EnumCount);
    for (int32 EnumIndex = 0; EnumIndex < EnumCount; ++EnumIndex) {
      IntegerSelectionValues.Add(FIntegerSelection(EnumClass->GetDisplayNameTextByIndex(EnumIndex), EnumIndex));
    }
    if (bReverseEnumOrder) {
      Algo::Reverse(IntegerSelectionValues);
    }
  }
#endif

#if WITH_EDITOR
 protected:
  bool CanEditChange(const FProperty* InProperty) const override {
    const bool ParentVal = Super::CanEditChange(InProperty);
    if (!ParentVal) {
      return false;
    }

    if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(USMLIntValueSelector, IntegerSelectionValues)) {
      // Allow editing when the enum class is null.
      return EnumClass == nullptr;
    }

    return true;
  }
#endif
};
