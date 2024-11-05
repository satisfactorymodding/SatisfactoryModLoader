// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	void Init( class AFGWheeledVehicle* vehicle );

private:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	//~ End AActor Interface

public:
};
