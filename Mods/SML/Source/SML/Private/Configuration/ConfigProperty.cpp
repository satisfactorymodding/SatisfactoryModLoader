#include "Configuration/ConfigProperty.h"
#include "Configuration/ConfigValueDirtyHandlerInterface.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"

FString UConfigProperty::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[unknown value %s]"), *GetClass()->GetPathName());
}

URawFormatValue* UConfigProperty::Serialize_Implementation(UObject* Outer) const {
    checkf(false, TEXT("Serialize not implemented"));
    return NULL;
}

void UConfigProperty::Deserialize_Implementation(const URawFormatValue* Value) {
    checkf(false, TEXT("Deserialize not implemented"));
}

void UConfigProperty::MarkDirty() {
    //Let closest Outer object implementing IConfigValueDirtyHandlerInterface handle MarkDirty call
    for (UObject* NextOuter = GetOuter(); NextOuter != NULL; NextOuter = NextOuter->GetOuter()) {
        if (NextOuter->Implements<UConfigValueDirtyHandlerInterface>()) {
            IConfigValueDirtyHandlerInterface::Execute_HandleMarkDirty(NextOuter);
            break;
        }
    }
    OnPropertyValueChanged.Broadcast();
}

void UConfigProperty::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject,
    const FString& VariableName) const {
    checkf(false, TEXT("FillConfigStruct not implemented"));
}

bool UConfigProperty::ResetToDefault_Implementation() {
	checkf(false, TEXT("ResetToDefault not implemented"));
	return false;
}

bool UConfigProperty::CanResetNow() const {
	// Return false if this property does allow a user to reset it
	if (!bAllowUserReset || !bParentSectionAllowsUserReset) {
		return false;
	}
	// Return true if this property does not require a world reload
	if (!bRequiresWorldReload) {
		return true;
	}
	// Assume we can reset if for whatever reason we can't get the world
	UWorld* World = GetWorld();
	if (!World) {
		return true;
	}
	// Check whether or not the user is in the main menu since requires world reload is enabled
	// GetAuthGameMode is a server-only function, but in the case we're not the server, then we know we're definitely not in the main menu anyways
	if (AFGGameMode* GameMode = World->GetAuthGameMode<AFGGameMode>()) {
		return GameMode->IsMainMenuGameMode();
	}
	return false;
}

bool UConfigProperty::IsSetToDefaultValue_Implementation() const {
	checkf(false, TEXT("IsSetToDefaultValue not implemented"));
	return false;
}

FString UConfigProperty::GetDefaultValueAsString_Implementation() const {
	checkf(false, TEXT("GetDefaultValueAsString not implemented"));
	return TEXT("");
}

FConfigVariableDescriptor UConfigProperty::CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const {
    checkf(false, TEXT("CreatePropertyDescriptor not implemented"));
    return FConfigVariableDescriptor{};
}

UUserWidget* UConfigProperty::CreateEditorWidget_Implementation(UUserWidget* ParentWidget) const {
    return NULL;
}
