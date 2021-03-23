

#include "Util/RuntimeBlueprintFunctionLibrary.h"



UClass* URuntimeBlueprintFunctionLibrary::FindClassByName(FString ClassNameInput)
{
	// prevent crash from wrong user Input
	if (ClassNameInput.Len() == 0)
		return nullptr;

	const TCHAR* ClassName = *ClassNameInput;
	UObject* ClassPackage = ANY_PACKAGE;

	if (UClass* Result = FindObject<UClass>(ANY_PACKAGE, ClassName, false))
		return Result;

	if (UObjectRedirector* RenamedClassRedirector = FindObject<UObjectRedirector>(ANY_PACKAGE, ClassName, true))
		return CastChecked<UClass>(RenamedClassRedirector->DestinationObject);

	return nullptr;
}