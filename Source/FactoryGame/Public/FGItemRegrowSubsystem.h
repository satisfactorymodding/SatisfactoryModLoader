// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGItemRegrowSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGItemRegrowSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	AFGItemRegrowSubsystem();

	// Begin AActor interface
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

	/** Get the resource sink subsystem, this should always return something unless you call it really early. */
	static AFGItemRegrowSubsystem* Get( UWorld* world );

	/** Get the item regrow subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ItemRegrow", DisplayName = "GetItemRegrowSubsystem", Meta = (DefaultToSelf = "worldContext") )
	static AFGItemRegrowSubsystem* Get( UObject* worldContext );

	void AddPickup( class AFGItemPickup* inPickup );
	void RemovePickup( class AFGItemPickup* inPickup );
protected:
private:
	/** all pickups we want to check for regrowth */
	UPROPERTY()
	TArray< class AFGItemPickup* > mPickups;
	/** */
	int32 mCurrentIndex;

	/** How many items to check per frame */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame | ItemRegrow" )
	int32 mMaxPerTick;

public:
	FORCEINLINE ~AFGItemRegrowSubsystem() = default;
};
