#include "ModInitializerComponent.h"
#include "Engine/World.h"
#include "Stack.h"
#include "util/Logging.h"

bool CallActorFunction(AActor* actor, const FName& functionName) {
	UFunction* function = actor->FindFunction(functionName);
	if (function == nullptr) {
		return false;
	}
	FFrame frame = FFrame(actor, function, nullptr);
	actor->CallFunction(frame, nullptr, function);
	return true;
}

#define STEP_INITIALIZATION(expectedState, nextState) if(!StepInitialization(this, expectedState, nextState)) return;

bool StepInitialization(UModInitializerComponent* component, EInitializationState expectedState, EInitializationState nextState) {
	if (component->InitializationState == expectedState) {
		component->InitializationState = nextState;
		return true;
	}
	return false;
}

UModInitializerComponent::UModInitializerComponent() {
	this->InitializationState = EInitializationState::CONSTRUCTION;
}


void UModInitializerComponent::InitializeModActors() {
	this->InitializationState = EInitializationState::CONSTRUCTION;
	STEP_INITIALIZATION(EInitializationState::CONSTRUCTION, EInitializationState::INITIALIZATION);
	SML::Logging::info(TEXT("Initializing mod content packages..."));
	for (AActor* actor : this->ModInitializerActorList) {
		if (actor != nullptr) {
			CallActorFunction(actor, FName(TEXT("Init")));
		}
	}
}

void UModInitializerComponent::PostInitializeModActors() {
	SML::Logging::info(TEXT("Foobar!@"));
	STEP_INITIALIZATION(EInitializationState::INITIALIZATION, EInitializationState::POST_INITIALIZATION);
	SML::Logging::info(TEXT("Post-initializing mod content packages..."));
	for (AActor* actor : this->ModInitializerActorList) {
		if (actor != nullptr) {
			CallActorFunction(actor, FName(TEXT("PostInit")));
		}
	}
}


