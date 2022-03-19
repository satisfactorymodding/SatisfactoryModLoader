#include "Configuration/Properties/WidgetExtension/CP_Integer.h"


UCP_Integer::UCP_Integer() {
	MinValue = 0;
	MaxValue = 1;
}


TArray<FName> UCP_Integer::GetEnumNames() const {
	if (EnumClass) {
		TArray<FName> Out;
		int32 EnumCount = EnumClass->ContainsExistingMax() ? EnumClass->NumEnums() - 1 : EnumClass->NumEnums();
		for (int32 i = 0; i < EnumCount; i++) {
			Out.Add(*EnumClass->GetDisplayNameTextByIndex(i).ToString());
		}
		return Out;
	}
	return TArray<FName>();
}
