#include "Patching/BlueprintHookingTypes.h"
#include "Patching/BlueprintHookManager.h"

UBlueprintActorMixin* UBlueprintActorMixin::GetActorMixin(const AActor* InActor, const TSubclassOf<UBlueprintActorMixin> InMixinClass) {
	if (InActor && InMixinClass) {
		if (const UBlueprintMixinHostComponent* MixinHostComponent = InActor->FindComponentByClass<UBlueprintMixinHostComponent>()) {
			return MixinHostComponent->FindMixinByClass(InMixinClass);
		}
	}
	return nullptr;
}

UObject* UBlueprintActorMixin::GetHookObjectInstanceFromTargetMethodInstance(UObject* InObjectInstance, UClass* InHookObjectClass) {
	// We can resolve mixin instance on actors and actor components
	if (const AActor* TargetActor = Cast<AActor>(InObjectInstance)) {
		return GetActorMixin(TargetActor, InHookObjectClass);
	}
	if (const UActorComponent* TargetActorComponent = Cast<UActorComponent>(InObjectInstance)) {
		return GetActorMixin(TargetActorComponent->GetOwner(), InHookObjectClass);
	}
	return nullptr;
}

void UBlueprintActorMixin::DispatchMixinCreated() {
	OnMixinCreated();
	UserConstructionScript();
}

void UBlueprintActorMixin::DispatchBeginPlay() {
	BeginPlay();
	ReceiveBeginPlay();
}

void UBlueprintActorMixin::DispatchTick(float DeltaTime) {
	Tick(DeltaTime);
	ReceiveTick(DeltaTime);
}

void UBlueprintActorMixin::DispatchEndPlay(EEndPlayReason::Type EndPlayReason) {
	ReceiveEndPlay();
	EndPlay(EndPlayReason);
}
