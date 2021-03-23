#include "Configuration/Properties/WidgetExtension/CP_Integer.h"

TArray<FName> UCP_Integer::GetEnumNames() const
{
	if (EnumClass)
	{
		TArray<FName> out;
		for (int32 i = 0; i < EnumClass->NumEnums(); i++)
			out.Add(EnumClass->GetNameByIndex(i));
		return out;
	}	
	return TArray<FName>();
}


