#include "Patching/WidgetBlueprintHookManager.h"
#include "SatisfactoryModLoader.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Components/BorderSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/ScaleBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WrapBoxSlot.h"
#include "Engine/Engine.h"
#include "Patching/NativeHookManager.h"
#include "UObject/Package.h"

#if WITH_EDITOR
	// Fast path can be used if we are running Standalone (-game or -server) and not running a Commandlet
	#define GAllowUsingFastWidgetTreeHookPath !GIsEditor && !IsRunningCommandlet()
#else
	// Fast path can be used at all times in non-editor builds
	#define GAllowUsingFastWidgetTreeHookPath true
#endif

DEFINE_LOG_CATEGORY(LogWidgetBlueprintHookManager);

class UPanelWidgetAccessor : UPanelWidget {
public:
	static UClass* GetPanelSlotClass(const UPanelWidget* PanelWidget) {
		return static_cast<const UPanelWidgetAccessor*>(PanelWidget)->GetSlotClass();
	}

	static TArray<TObjectPtr<UPanelSlot>>& GetPanelSlots(UPanelWidget* PanelWidget) {
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
	if (ParentType == EWidgetBlueprintHookParentType::Direct || ParentType == EWidgetBlueprintHookParentType::Direct_Any) {
		return ValidateDirectWidget(Widget, OutParentWidget, bCheckVariableName);
	}
	if (ParentType == EWidgetBlueprintHookParentType::Indirect_Child) {
		return ValidateIndirectChildWidget(Widget, OutParentWidget, bCheckVariableName);
	}
	return false;
}

void UWidgetBlueprintHookSlot_Generic::SetupPanelSlot(UPanelSlot* InPanelSlot) {
	Super::SetupPanelSlot(InPanelSlot);
	if (UBorderSlot* BorderSlot = Cast<UBorderSlot>(InPanelSlot)) {
		BorderSlot->SetPadding(Padding);
		BorderSlot->SetHorizontalAlignment(HorizontalAlignment);
		BorderSlot->SetVerticalAlignment(VerticalAlignment);
	} else if (UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(InPanelSlot)) {
		HorizontalBoxSlot->SetSize(Size);
		HorizontalBoxSlot->SetPadding(Padding);
		HorizontalBoxSlot->SetHorizontalAlignment(HorizontalAlignment);
		HorizontalBoxSlot->SetVerticalAlignment(VerticalAlignment);
	} else if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(InPanelSlot)) {
		OverlaySlot->SetPadding(Padding);
		OverlaySlot->SetHorizontalAlignment(HorizontalAlignment);
		OverlaySlot->SetVerticalAlignment(VerticalAlignment);
	} else if (UScaleBoxSlot* ScaleBoxSlot = Cast<UScaleBoxSlot>(InPanelSlot)) {
		ScaleBoxSlot->SetHorizontalAlignment(HorizontalAlignment);
		ScaleBoxSlot->SetVerticalAlignment(VerticalAlignment);
	} else if (UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(InPanelSlot)) {
		HorizontalBoxSlot->SetSize(Size);
		VerticalBoxSlot->SetPadding(Padding);
		VerticalBoxSlot->SetHorizontalAlignment(HorizontalAlignment);
		VerticalBoxSlot->SetVerticalAlignment(VerticalAlignment);
	} else if (UWrapBoxSlot* WrapBoxSlot = Cast<UWrapBoxSlot>(InPanelSlot)) {
		WrapBoxSlot->SetPadding(Padding);
		WrapBoxSlot->SetHorizontalAlignment(HorizontalAlignment);
		WrapBoxSlot->SetVerticalAlignment(VerticalAlignment);
	}
}

void UWidgetBlueprintHookSlot_Canvas::SetupPanelSlot(UPanelSlot* InPanelSlot) {
	Super::SetupPanelSlot(InPanelSlot);
	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(InPanelSlot)) {
		CanvasPanelSlot->SetLayout(LayoutData);
		CanvasPanelSlot->SetAutoSize(bAutoSize);
		CanvasPanelSlot->SetZOrder(ZOrder);
	}
}

TArray<FString> UWidgetBlueprintHookData::GetParentWidgetNames() const {
	const UWidgetBlueprintGeneratedClass* WidgetBlueprintClass = Cast<UWidgetBlueprintGeneratedClass>(WidgetClass.LoadSynchronous());
	if (WidgetBlueprintClass == NULL) {
		return TArray<FString>();
	}

	TArray<FString> ResultWidgetNames;

	WidgetBlueprintClass->GetWidgetTreeArchetype()->ForEachWidget([&](UWidget* Widget){
		UPanelWidget* ResultParentWidget;
		if (WidgetBlueprintHookParentValidator::ValidateParentWidget(Widget, ParentWidgetType, ResultParentWidget, ParentWidgetType != EWidgetBlueprintHookParentType::Direct_Any)) {
			ResultWidgetNames.Add(Widget->GetName());
		}
	});
	return ResultWidgetNames;
}

UPanelWidget* UWidgetBlueprintHookData::ResolveParentWidgetOnArchetype() const {
	const UWidgetBlueprintGeneratedClass* WidgetBlueprintClass = Cast<UWidgetBlueprintGeneratedClass>(WidgetClass.LoadSynchronous());
	if (WidgetBlueprintClass == nullptr) {
		return nullptr;
	}
	return ResolveParentWidget(WidgetBlueprintClass->GetWidgetTreeArchetype());
}

UPanelWidget* UWidgetBlueprintHookData::ResolveParentWidget(const UWidgetTree* InWidgetTree) const {
	UWidget* ParentWidget = InWidgetTree->FindWidget(ParentWidgetName);
	UPanelWidget* OutParentWidget{};
	if (WidgetBlueprintHookParentValidator::ValidateParentWidget(ParentWidget, ParentWidgetType, OutParentWidget, false)) {
		return OutParentWidget;
	}
	return nullptr;
}

void UWidgetBlueprintHookData::AttachToWidgetInstance(UUserWidget* InWidgetTreeRoot, UPanelWidget* InParentWidget) const {
	if (InParentWidget) {
		UUserWidget* NewUserWidget = UUserWidget::CreateWidgetInstance(*InWidgetTreeRoot, NewWidgetClass, NewWidgetName);
		if (NewUserWidget != nullptr) {
			// Apply slot configuration to the slot if we have one
			UPanelSlot* CreatedPanelSlot = InParentWidget->AddChild(NewUserWidget);
			if (SlotConfiguration && CreatedPanelSlot) {
				SlotConfiguration->SetupPanelSlot(CreatedPanelSlot);
			}
		}
	}
}

static UUserWidget* AttachWidgetToWidgetTreeArchetype(UPanelWidget* ParentWidget, const UWidgetBlueprintHookData* HookData) {
	UWidgetTree* WidgetTree = ParentWidget->GetTypedOuter<UWidgetTree>();
	const UClass* PanelWidgetSlotClass = UPanelWidgetAccessor::GetPanelSlotClass(ParentWidget);

	if (WidgetTree->FindWidget(HookData->NewWidgetName)) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, widget with the name %s already exists"),
			*HookData->GetPathName(), *HookData->NewWidgetName.ToString());
		return nullptr;
	}
	UUserWidget* NewUserWidget = NewObject<UUserWidget>(WidgetTree, HookData->NewWidgetClass, HookData->NewWidgetName, RF_Transient);

	if (NewUserWidget == NULL) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, failed to create new user widget %s"),
			*HookData->GetPathName(), *HookData->NewWidgetClass->GetPathName());
		return nullptr;
	}
	
	UPanelSlot* PanelSlot = NewObject<UPanelSlot>(ParentWidget, PanelWidgetSlotClass, NAME_None, RF_Transient);
	// Apply slot configuration to the slot if we have one
	if (HookData->SlotConfiguration) {
		HookData->SlotConfiguration->SetupPanelSlot(PanelSlot);
	}
	PanelSlot->Content = NewUserWidget;
	PanelSlot->Parent = ParentWidget;

	NewUserWidget->Slot = PanelSlot;
	TArray<TObjectPtr<UPanelSlot>>& MutablePanelSlots = UPanelWidgetAccessor::GetPanelSlots(ParentWidget);
	const int32 ParentSlotIndex = HookData->ParentSlotIndex;

	if (ParentSlotIndex != INDEX_NONE && MutablePanelSlots.IsValidIndex(ParentSlotIndex)) {
		//Insert at the specified position if needed
		MutablePanelSlots.Insert(PanelSlot, ParentSlotIndex);
	} else {
		//Otherwise just append it at the end of the array
		MutablePanelSlots.Add(PanelSlot);
	}
	return NewUserWidget;
}

// FNames of UWidgetBlueprintGeneratedClass objects that have widget hooks. Used to avoid expensive lookup logic for common widget initialization hook in the editor
static TSet<FName> HookedWidgetBlueprintGeneratedClassFNameSet;

void UWidgetBlueprintHookManager::RegisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData) {
	// This should not be done from anywhere other than the game thread
	check(IsInGameThread());

	// Dedicated servers do not use widgets, so skip the registration completely
	if (IsRunningDedicatedServer()) {
		return;
	}
	// Silently ignore any hooking requests if hooking is not allowed in this environment
	if (!FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		return;
	}

	// Make sure we were provided a valid hook asset
	if (!HookData) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Attempt to register invalid widget blueprint hook"));
		return;
	}
	// Validate the hook data before attempting to do anything with it
	if (!HookData->NewWidgetClass || HookData->NewWidgetName.IsNone()) {
		UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, new widget class %s or name %s are invalid"),
			*HookData->GetPathName(), *HookData->NewWidgetClass->GetPathName(), *HookData->NewWidgetName.ToString());
		return;
	}

	// Use fast path by directly inserting the widget into the widget tree hierarchy when we can pin and modify the archetypes. This is only possible outside the editor and when not running a commandlet
	if (GAllowUsingFastWidgetTreeHookPath) {
		FWidgetBlueprintHookDescriptor* RegistrationHookDescriptor = InstalledArchetypeHooks.FindByPredicate([&](const FWidgetBlueprintHookDescriptor& Other) {
			return Other.HookData == HookData;
		});

		// Register a new hook if we do not have an existing registration
		if (RegistrationHookDescriptor == nullptr) {
			UPanelWidget* ParentWidget = HookData->ResolveParentWidgetOnArchetype();
			if (ParentWidget == nullptr) {
				UE_LOG(LogWidgetBlueprintHookManager, Error, TEXT("Failed to hook widget blueprint %s, failed to resolve parent widget %s inside %s"),
					*HookData->GetPathName(), *HookData->ParentWidgetName.ToString(), *HookData->WidgetClass->GetPathName());
				return;
			}
			RegistrationHookDescriptor = &InstalledArchetypeHooks.AddDefaulted_GetRef();
			RegistrationHookDescriptor->HookData = HookData;
			RegistrationHookDescriptor->InstalledWidget = AttachWidgetToWidgetTreeArchetype(ParentWidget, HookData);
		}

		RegistrationHookDescriptor->RegistrationCount++;
	} else {
		// Use a slow path that does not modify the source assets while we are in the editor
		TArray<FWidgetBlueprintEditorSlowHookData>& HookRegistrations = InstalledSlowEditorHooks.FindOrAdd(HookData->WidgetClass.ToSoftObjectPath().GetAssetPath());
		FWidgetBlueprintEditorSlowHookData* CurrentRegistration = HookRegistrations.FindByPredicate([&](const FWidgetBlueprintEditorSlowHookData& Other) {
			return Other.HookData == HookData;
		});

		// Register a new hook if we do not have an existing registration
		if (CurrentRegistration == nullptr) {
			CurrentRegistration = &HookRegistrations.AddDefaulted_GetRef();
			CurrentRegistration->HookData = HookData;
		}
		CurrentRegistration->RegistrationCount++;

		// Make sure the widget class that we are attempting to hook is added into the lookup, so we will run the logic for it
		HookedWidgetBlueprintGeneratedClassFNameSet.Add(HookData->WidgetClass.ToSoftObjectPath().GetAssetPath().GetAssetName());
	}
	UE_LOG(LogWidgetBlueprintHookManager, Log, TEXT("Installed widget blueprint hook %s on WidgetBlueprint %s"),
		*HookData->GetPathName(), *HookData->NewWidgetClass->GetPathName());
}

void UWidgetBlueprintHookManager::UnregisterWidgetBlueprintHook(UWidgetBlueprintHookData* HookData) {
	// This should not be done from anywhere other than the game thread
	check(IsInGameThread());

	// If we can use the fast path, just remove the hooked widget from the archetype
	if (GAllowUsingFastWidgetTreeHookPath) {
		const int32 HookDataIndex = InstalledArchetypeHooks.IndexOfByPredicate([&](const FWidgetBlueprintHookDescriptor& HookDescriptor){
			return HookDescriptor.HookData == HookData;
		});

		// Remove the archetype hook once the registration count reaches zero
		if (HookDataIndex != INDEX_NONE && --InstalledArchetypeHooks[HookDataIndex].RegistrationCount == 0) {
			UUserWidget* HookedUserWidget = InstalledArchetypeHooks[HookDataIndex].InstalledWidget;
			InstalledArchetypeHooks.RemoveAt(HookDataIndex);

			HookedUserWidget->Slot->Parent->RemoveChild(HookedUserWidget);
			HookedUserWidget->SetFlags(RF_Transient);
			HookedUserWidget->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_ForceNoResetLoaders);

			UE_LOG(LogWidgetBlueprintHookManager, Log, TEXT("Removed widget blueprint hook %s from WidgetBlueprint %s"),
				*HookData->GetPathName(), *HookData->WidgetClass->GetPathName());
		}
	} else {
		// If we are in the editor environment, we cannot directly modify the assets, so we have to use a slow global hook instead
		TArray<FWidgetBlueprintEditorSlowHookData>& HookRegistrations = InstalledSlowEditorHooks.FindOrAdd(HookData->WidgetClass.ToSoftObjectPath().GetAssetPath());
		const int32 CurrentRegistrationIndex = HookRegistrations.IndexOfByPredicate([&](const FWidgetBlueprintEditorSlowHookData& Other) {
			return Other.HookData == HookData;
		});

		// Remove the hook registration completely if registration count reaches zero
		if (CurrentRegistrationIndex != INDEX_NONE && --HookRegistrations[CurrentRegistrationIndex].RegistrationCount == 0) {
			HookRegistrations.RemoveAt(CurrentRegistrationIndex);
		}
	}
}

void UWidgetBlueprintHookManager::RegisterStaticHooks() {
	// If we cannot use the archetype modification method in this environment, we need to place a global hook
	if (!GAllowUsingFastWidgetTreeHookPath && FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		//SUBSCRIBE_METHOD_AFTER(UWidgetBlueprintGeneratedClass::InitializeWidget, [](const UBlueprintGeneratedClass* WidgetClass, UUserWidget* WidgetInstance) {
		//	if (HookedWidgetBlueprintGeneratedClassFNameSet.Contains(WidgetClass->GetFName())) {
		//		WidgetBlueprintGeneratedClassInitializeWidget(WidgetClass, WidgetInstance);
		//	}
		//});
	}
}

void UWidgetBlueprintHookManager::WidgetBlueprintGeneratedClassInitializeWidget(const UBlueprintGeneratedClass* WidgetClass, UUserWidget* UserWidget) {
	// Only attempt to hook widgets that are not templates and located in a game world
	const UWorld* WidgetWorld = UserWidget->GetWorld();
	if (!UserWidget->IsTemplate() && WidgetWorld && (WidgetWorld->WorldType == EWorldType::PIE || WidgetWorld->WorldType == EWorldType::Game)) {
		if (UWidgetBlueprintHookManager* HookManager = GEngine->GetEngineSubsystem<UWidgetBlueprintHookManager>()) {
			if (const TArray<FWidgetBlueprintEditorSlowHookData>* RegisteredHooks = HookManager->InstalledSlowEditorHooks.Find(WidgetClass->GetClassPathName())) {

				// Attach each hook to the widget individually
				for (const FWidgetBlueprintEditorSlowHookData& RegisteredHookData : *RegisteredHooks) {
					if (const UWidgetBlueprintHookData* HookData = RegisteredHookData.HookData.LoadSynchronous()) {
						if (UPanelWidget* ParentWidget = HookData->ResolveParentWidget(UserWidget->WidgetTree)) {
							HookData->AttachToWidgetInstance(UserWidget, ParentWidget);
						}
					}
				}
			}
		}
	}
}
