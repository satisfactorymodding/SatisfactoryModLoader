#include "Patching/WidgetBlueprintHookManager.h"

#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Engine/Engine.h"
#include "UObject/Package.h"

DEFINE_LOG_CATEGORY(LogWidgetBlueprintHookManager);

class UPanelWidgetAccessor : UPanelWidget {
public:
	static UClass* GetPanelSlotClass(const UPanelWidget* PanelWidget) {
		return static_cast<const UPanelWidgetAccessor*>(PanelWidget)->GetSlotClass();
	}

	static TArray<UPanelSlot*>& GetPanelSlots(UPanelWidget* PanelWidget) {
		return static_cast<UPanelWidgetAccessor*>(PanelWidget)->Slots;
	}
	UPanelWidgetAccessor() = delete;
};

bool WidgetBlueprintHookParentValidator::ValidateWidgetBase(UWidget* Widget, bool bCheckVariableName) {
	if (Widget == NULL) {
		return false;
	}
	if (bCheckVariableName) {
		//If we are not the variable, bail out
		if (!Widget->bIsVariable) {
			return false;
		}
		//If we have a generated name, skip the widget
		#if WITH_EDITOR
		if (Widget->IsGeneratedName()) {
			return false;
		}
#endif
	}
	return true;
}

bool WidgetBlueprintHookParentValidator::ValidateDirectWidget(UWidget* Widget, UPanelWidget*& OutPanelWidget, bool bCheckVariableName) {
	if (!ValidateWidgetBase(Widget, bCheckVariableName)) {
		return false;
	}
	UPanelWidget* PanelWidget = Cast<UPanelWidget>(Widget);
	if (PanelWidget == NULL) {
		return false;
	}
	//We do not allow hooking up to parent widgets that only support one child
	if (!PanelWidget->CanHaveMultipleChildren()) {
		return false;
	}
	OutPanelWidget = PanelWidget;
	return true;
}

bool WidgetBlueprintHookParentValidator::ValidateIndirectChildWidget(UWidget* Widget, UPanelWidget*& OutPanelWidget, bool bCheckVariableName) {
	if (!ValidateWidgetBase(Widget, bCheckVariableName)) {
		return false;
	}
	if (Widget->Slot == NULL) {
		return false;
	}
	UPanelWidget* ParentPanelWidget = Widget->Slot->Parent;
	return ValidateDirectWidget(ParentPanelWidget, OutPanelWidget, false);
}

bool WidgetBlueprintHookParentValidator::ValidateParentWidget(UWidget* Widget, EWidgetBlueprintHookParentType ParentType, UPanelWidget*& OutParentWidget, bool bCheckVariableName) {
	if (ParentType == EWidgetBlueprintHookParentType::Direct) {
		return ValidateDirectWidget(Widget, OutParentWidget, bCheckVariableName);
	}
	if (ParentType == EWidgetBlueprintHookParentType::Indirect_Child) {
		return ValidateIndirectChildWidget(Widget, OutParentWidget, bCheckVariableName);
	}
	return false;
}

UWidgetBlueprintHookData::UWidgetBlueprintHookData() {
	this->ParentSlotIndex = INDEX_NONE;
	this->NewWidgetTemplate = NULL;
	this->PanelSlotTemplate = NULL;
}

void UWidgetBlueprintHookData::SetWidgetClass(TSoftClassPtr<UUserWidget> InWidgetClass) {
	this->WidgetClass = InWidgetClass;
	ReinitializePanelSlotTemplate();
}

void UWidgetBlueprintHookData::SetParentWidgetType(EWidgetBlueprintHookParentType InParentWidgetType) {
	this->ParentWidgetType = InParentWidgetType;
	ReinitializePanelSlotTemplate();
}

void UWidgetBlueprintHookData::SetParentWidgetName(FName InParentWidgetName) {
	this->ParentWidgetName = InParentWidgetName;
	ReinitializePanelSlotTemplate();
}

void UWidgetBlueprintHookData::SetNewWidgetName(FName InNewWidgetName) {
	this->NewWidgetName = InNewWidgetName;
	ReinitializeNewWidgetTemplate();
	ReinitializePanelSlotTemplate();
}

void UWidgetBlueprintHookData::SetNewWidgetClass(TSubclassOf<UUserWidget> InNewWidgetClass) {
	this->NewWidgetClass = InNewWidgetClass;
	ReinitializeNewWidgetTemplate();
}

void UWidgetBlueprintHookData::ReinitializeNewWidgetTemplate() {
	const UClass* CurrentWidgetTemplateClass = NewWidgetTemplate ? NewWidgetTemplate->GetClass() : NULL;

	//Re-initialize with the new class if it does not match currently
	if (CurrentWidgetTemplateClass != NewWidgetClass) {
		//Thrash the old object so it does not occupy the name we have now
		if (NewWidgetTemplate != NULL) {
			NewWidgetTemplate->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_ForceNoResetLoaders);
		}
		if (NewWidgetClass != NULL) {
			UUserWidget* OldWidgetTemplate = NewWidgetTemplate;
			
			//The object needs RF_Public, otherwise a blueprint referencing an instance of UWidgetBlueprintHookData
			//(or another object containing it) will cause a cooking error, since it would be referencing a private object
			//in another package
			NewWidgetTemplate = NewObject<UUserWidget>(this, NewWidgetClass, NewWidgetName, RF_Public | RF_ArchetypeObject | RF_Transactional);

			//Transfer properties from the old object to the new one
			if (OldWidgetTemplate && NewWidgetTemplate) {
				UEngine::CopyPropertiesForUnrelatedObjects(OldWidgetTemplate, NewWidgetTemplate);
			}
			NewWidgetTemplate->Modify();
		} else {
			//If we have no class anymore
			NewWidgetTemplate = NULL;
		}
	}
	
	//Rename the component if its name does not match the variable name
	if (NewWidgetTemplate != NULL) {
		if (NewWidgetTemplate->GetFName() != NewWidgetName) {
			NewWidgetTemplate->Rename(*NewWidgetName.ToString(), NULL, REN_DontCreateRedirectors | REN_ForceNoResetLoaders);
		}
	}
}

void UWidgetBlueprintHookData::ReinitializePanelSlotTemplate() {
	if (const UPanelWidget* PanelWidget = ResolveParentWidget()) {
		PanelSlotClass = UPanelWidgetAccessor::GetPanelSlotClass(PanelWidget);
	} else {
		PanelSlotClass = NULL;
	}
	
	const UClass* CurrentPanelSlotClass = PanelSlotTemplate ? PanelSlotTemplate->GetClass() : NULL;
	const FString PanelSlotName = NewWidgetName.ToString() + TEXT("_Slot");

	//Re-initialize with the new class if it does not match currently
	if (CurrentPanelSlotClass != PanelSlotClass) {
		//Thrash the old object so it does not occupy the name we have now
		if (PanelSlotTemplate != NULL) {
			PanelSlotTemplate->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_ForceNoResetLoaders);
		}
		if (PanelSlotClass != NULL) {
			UPanelSlot* OldPanelSlotTemplate = PanelSlotTemplate;
			//The object needs RF_Public, otherwise a blueprint referencing an instance of UWidgetBlueprintHookData
			//(or another object containing it) will cause a cooking error, since it would be referencing a private object
			//in another package
			PanelSlotTemplate = NewObject<UPanelSlot>(this, PanelSlotClass, *PanelSlotName, RF_Public | RF_ArchetypeObject | RF_Transactional);

			//Transfer properties from the old object to the new one
			if (OldPanelSlotTemplate && PanelSlotTemplate) {
				UEngine::CopyPropertiesForUnrelatedObjects(OldPanelSlotTemplate, PanelSlotTemplate);
			}
			PanelSlotTemplate->Modify();
		} else {
			//If we have no class anymore
			PanelSlotTemplate = NULL;
		}
	}
	
	//Rename the component if its name does not match the variable name
	if (PanelSlotTemplate != NULL) {
		if (PanelSlotTemplate->GetName() != PanelSlotName) {
			PanelSlotTemplate->Rename(*PanelSlotName, NULL, REN_DontCreateRedirectors | REN_ForceNoResetLoaders);
		}
	}
}

#if WITH_EDITOR

void UWidgetBlueprintHookData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.MemberProperty->GetFName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, WidgetClass) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, ParentWidgetType) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, ParentWidgetName)) {
		ReinitializePanelSlotTemplate();
		
	} else if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, NewWidgetClass)) {
		ReinitializeNewWidgetTemplate();
		
	} else if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, NewWidgetName)) {
		ReinitializePanelSlotTemplate();
		ReinitializeNewWidgetTemplate();
	}
}

#endif

TArray<FString> UWidgetBlueprintHookData::GetParentWidgetNames() const {
	const UWidgetBlueprintGeneratedClass* WidgetBlueprintClass = Cast<UWidgetBlueprintGeneratedClass>(WidgetClass.LoadSynchronous());
	if (WidgetBlueprintClass == NULL) {
		return TArray<FString>();
	}

	TArray<FString> ResultWidgetNames;

	WidgetBlueprintClass->GetWidgetTreeArchetype()->ForEachWidget([&](UWidget* Widget){
		UPanelWidget* ResultParentWidget;
		if (WidgetBlueprintHookParentValidator::ValidateParentWidget(Widget, ParentWidgetType, ResultParentWidget, true)) {
			ResultWidgetNames.Add(Widget->GetName());
		}
	});
	return ResultWidgetNames;
}

UPanelWidget* UWidgetBlueprintHookData::ResolveParentWidget() const {
	const UWidgetBlueprintGeneratedClass* WidgetBlueprintClass = Cast<UWidgetBlueprintGeneratedClass>(WidgetClass.LoadSynchronous());
	if (WidgetBlueprintClass == NULL) {
		return NULL;
	}
	
	UWidget* ParentWidget = WidgetBlueprintClass->GetWidgetTreeArchetype()->FindWidget(ParentWidgetName);

	UPanelWidget* OutParentWidget;
	if (WidgetBlueprintHookParentValidator::ValidateParentWidget(ParentWidget, ParentWidgetType, OutParentWidget, false)) {
		return OutParentWidget;
	}
	return NULL;
}

void UWidgetBlueprintHookManager::RegisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData) {
	//Blueprint hooking in editor is extremely dangerous as it modifies the source assets
	//TODO: Hooks can be supported in the editor too by only adding them on the PIE-cloned objects
	if (!FPlatformProperties::RequiresCookedData()) {
		return;
	}
	
	// Widgets are not included on servers
	if (FPlatformProperties::IsServerOnly()) {
		return;
	}

	if (!HookData->NewWidgetClass || HookData->NewWidgetName.IsNone()) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, new widget class %s or name %s are invalid"),
			*HookData->GetPathName(), *HookData->NewWidgetClass->GetPathName(), *HookData->NewWidgetName.ToString());
		return;
	}
	
	UPanelWidget* PanelWidget = HookData->ResolveParentWidget();

	if (PanelWidget == NULL) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, failed to resolve parent widget %s inside %s"),
			*HookData->GetPathName(), *HookData->ParentWidgetName.ToString(), *HookData->WidgetClass->GetPathName());
		return;
	}

	UWidgetTree* WidgetTree = PanelWidget->GetTypedOuter<UWidgetTree>();
	const UClass* PanelWidgetSlotClass = UPanelWidgetAccessor::GetPanelSlotClass(PanelWidget);

	if (WidgetTree->FindWidget(HookData->NewWidgetName)) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, widget with the name %s already exists"),
			*HookData->GetPathName(), *HookData->NewWidgetName.ToString());
		return;
	}
	
	UUserWidget* NewUserWidget = NewObject<UUserWidget>(WidgetTree, HookData->NewWidgetClass, HookData->NewWidgetName, RF_Transient, HookData->NewWidgetTemplate);

	if (NewUserWidget == NULL) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, failed to create new user widget %s"),
			*HookData->GetPathName(), *HookData->NewWidgetClass->GetPathName());
		return;
	}
	
	UPanelSlot* PanelSlot = NewObject<UPanelSlot>(PanelWidget, PanelWidgetSlotClass, NAME_None, RF_Transient, HookData->PanelSlotTemplate);
	PanelSlot->Content = NewUserWidget;
	PanelSlot->Parent = PanelWidget;

	NewUserWidget->Slot = PanelSlot;
	TArray<UPanelSlot*>& MutablePanelSlots = UPanelWidgetAccessor::GetPanelSlots(PanelWidget);
	const int32 ParentSlotIndex = HookData->ParentSlotIndex;

	if (ParentSlotIndex != INDEX_NONE && MutablePanelSlots.IsValidIndex(ParentSlotIndex)) {
		//Insert at the specified position if needed
		MutablePanelSlots.Insert(PanelSlot, ParentSlotIndex);
	} else {
		//Otherwise just append it at the end of the array
		MutablePanelSlots.Add(PanelSlot);
	}

	FWidgetBlueprintHookDescriptor HookDescriptor;
	HookDescriptor.HookData = HookData;
	HookDescriptor.InstalledWidget = NewUserWidget;

	InstalledHooks.Add(HookDescriptor);
	UE_LOG(LogWidgetBlueprintHookManager, Log, TEXT("Installed widget blueprint hook %s on WidgetBlueprint %s"),
		*HookData->GetPathName(), *HookData->NewWidgetClass->GetPathName());
}

void UWidgetBlueprintHookManager::UnregisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData) {
	//Blueprint hooking in editor is extremely dangerous as it modifies the source assets
	//TODO: Hooks can be supported in the editor too by only adding them on the PIE-cloned objects
	if (!FPlatformProperties::RequiresCookedData()) {
		return;
	}

	const int32 HookDataIndex = InstalledHooks.IndexOfByPredicate([&](const FWidgetBlueprintHookDescriptor& HookDescriptor){
		return HookDescriptor.HookData == HookData;
	});

	if (HookDataIndex != INDEX_NONE) {
		UUserWidget* HookedUserWidget = InstalledHooks[HookDataIndex].InstalledWidget;
		InstalledHooks.RemoveAt(HookDataIndex);

		HookedUserWidget->Slot->Parent->RemoveChild(HookedUserWidget);
		HookedUserWidget->SetFlags(RF_Transient);
		HookedUserWidget->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_ForceNoResetLoaders);

		UE_LOG(LogWidgetBlueprintHookManager, Log, TEXT("Removed widget blueprint hook %s from WidgetBlueprint %s"),
			*HookData->GetPathName(), *HookData->WidgetClass->GetPathName());
	}
}
