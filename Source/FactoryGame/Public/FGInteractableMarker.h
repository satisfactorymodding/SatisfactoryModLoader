// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Components/SplineMeshComponent.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGInteractableMarker.generated.h"

UCLASS()
class FACTORYGAME_API AFGInteractableMarker : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFGInteractableMarker();

	virtual void Tick( float dt ) override;

	UFUNCTION( BlueprintCallable, Category = "InteractableMarker" )
	void SetTrackedActor( class AActor* trackedActor );

	UFUNCTION(BlueprintPure, Category = "InteractableMarker" )
	FORCEINLINE AActor* GetTrackedActor() { return mTrackedActor; }

	UFUNCTION( BlueprintImplementableEvent, Category = "InteractableMarker" )
	void OnSetActorTracked();

protected:
	virtual void BeginPlay() override;

	UPROPERTY( VisibleAnywhere, Category = "InteractableMarker" )
	class UWidgetComponent* mIconWidget;

	UPROPERTY( VisibleAnywhere, Category = "InteractableMarker" )
	class USplineMeshComponent* mSplineMesh;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "InteractableMarker" )
	float mDesiredScreenRadius;

	UPROPERTY()
	class AActor* mTrackedActor;

private:
	UPROPERTY()
	class AFGPlayerController* mCachePlayerController;

public:
	FORCEINLINE ~AFGInteractableMarker() = default;
};
