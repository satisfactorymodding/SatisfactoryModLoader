#include "Settings/StringValueSelector.h"

TSubclassOf<class UFGOptionsValueController> UStringValueSelector::GetValueSelectorWidgetClass() const {
	return DefaultTextEditWidget;
}

#if WITH_EDITOR
bool UStringValueSelector::CanEditChange(const FProperty* InProperty) const {
	const bool ParentVal = Super::CanEditChange(InProperty);

	const FName PropertyName = InProperty->GetFName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UStringValueSelector, DefaultTextEditWidget))
	{
		// Only allow the Blueprint implementation located in SML to change this property value
		return ParentVal && this->GetPathName().Contains("SML");
	}

	return ParentVal;
}
#endif