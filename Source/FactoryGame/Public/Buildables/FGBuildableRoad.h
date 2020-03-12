// Copyright 2016-2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildable.h"
#include "Components/SplineComponent.h"
#include "../FGSplineComponent.h"
#include "FGBuildableRoad.generated.h"

/**
 * Roads for the wroom wroom.
 */
UCLASS( Meta = (AutoJson = false) )
class FACTORYGAME_API AFGBuildableRoad : public AFGBuildable
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	AFGBuildableRoad();

	FORCEINLINE float GetLength() const { return mSplineComponent->GetSplineLength(); }

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
	
private:
	/** The hologram configures this actor. */
	friend class AFGRoadHologram;

	/** First connection on track */
	UPROPERTY( VisibleAnywhere, Category = "Road" )
	class UFGRoadConnectionComponent* mConnection0;

	/** Second connection on tack */
	UPROPERTY( VisibleAnywhere, Category = "Road" )
	class UFGRoadConnectionComponent* mConnection1;

	/** The spline component for this train track. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UFGSplineComponent* mSplineComponent;

	/** Spline data saved in a compact form for saving and replicating. All the vectors are in local space. */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	TArray< FSplinePointData > mSplineData;

public:
	FORCEINLINE ~AFGBuildableRoad() = default;
};
