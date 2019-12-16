#pragma once
#include "Components/ActorComponent.h"
#include "ModInitializerComponent.generated.h"

UENUM()
enum class EInitializationState: uint8 {
	CONSTRUCTION,
	INITIALIZATION,
	POST_INITIALIZATION,
	FINISHED
};

UCLASS()
class SML_API UModInitializerComponent : public UActorComponent {
	GENERATED_BODY()
public:
	UModInitializerComponent();
	
	UPROPERTY()
	TArray<AActor*> ModInitializerActorList;

	UPROPERTY()
	EInitializationState InitializationState;
	
	void InitializeModActors();
	void PostInitializeModActors();
};
