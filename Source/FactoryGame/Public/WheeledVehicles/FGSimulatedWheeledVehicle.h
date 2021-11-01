// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Animation/SkeletalMeshActor.h"
#include "FGFactoryColoringTypes.h"
#include "FGUseableInterface.h"
#include "FGSimulatedWheeledVehicle.generated.h"


UCLASS()
class FACTORYGAME_API AFGSimulatedWheeledVehicle : public ASkeletalMeshActor
{
	GENERATED_BODY()

public:
	AFGSimulatedWheeledVehicle();

	void Init( class AFGWheeledVehicle* vehicle );

	void UpdateCustomizationData( class AFGWheeledVehicle* vehicle );
	void ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData );

	void ShowGhostingEffect( bool enabled );

private:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	//~ End AActor Interface

public:
	FVector mBoundingBoxExtent;
	FVector mBoundingBoxOffset;

	class UStaticMeshComponent* mStaticMeshComponent = nullptr;
};
