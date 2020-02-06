// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSubsystem.h"
#include "FGProximitySubsystem.generated.h"

UCLASS( Blueprintable )
class FACTORYGAME_API AFGProximitySubsystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGProximitySubsystem();

	/** Player entered a new map area */
	UFUNCTION( BlueprintNativeEvent, Category = "Proximity" )
	void OnEnteredMapArea( TSubclassOf< class UFGMapArea > newArea );

	/** Owning controller got a new pawn */
	UFUNCTION( BlueprintNativeEvent, Category = "Proximity" )
	void OnPawnChanged( class APawn* newPawn );
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;
private:
	UPROPERTY()
	class AFGPlayerController* mOwningController;

	UPROPERTY(  )
	USceneComponent* mRootComponent;
};
