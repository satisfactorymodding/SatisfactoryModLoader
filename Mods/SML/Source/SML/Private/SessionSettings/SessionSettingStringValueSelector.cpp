#include "SessionSettings/SessionSettingStringValueSelector.h"

TSubclassOf<class UFGOptionsValueController> USessionSettingStringValueSelector::GetValueSelectorWidgetClass() const {
	return DefaultTextEditWidget;
}

#if WITH_EDITOR
bool USessionSettingStringValueSelector::CanEditChange(const FProperty* InProperty) const {
	const bool ParentVal = Super::CanEditChange(InProperty);

	const FName PropertyName = InProperty->GetFName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USessionSettingStringValueSelector, DefaultTextEditWidget))
	{
		// Only allow the Blueprint implementation located in SML to change this property value
		return ParentVal && this->GetPathName().Contains("SML");
	}

	return ParentVal;
}
#endif