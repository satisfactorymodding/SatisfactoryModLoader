// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableGenerator.h"
#include "FGBuildableGeneratorGeoThermal.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorGeoThermal : public AFGBuildableGenerator
{
	GENERATED_BODY()
public:
	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface 

	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	/** Set the extractable resource interface for this generator */
	void SetExtractableResource( TScriptInterface< class IFGExtractableResourceInterface > extractableResource );

protected:
	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	virtual void Factory_StartPowerProduction_Implementation() override;
	virtual void Factory_StopPowerProduction_Implementation() override;
	// End AFGBuildableGenerator interface

private:
	/** DEPRICATED - Use mExtractableResource instead. This exists for save functionality
	*	This is the geyser this generator is placed on
	*/
	UPROPERTY( SaveGame )
	class AFGResourceNode* mExtractResourceNode;

	UPROPERTY( SaveGame, Replicated )
	AActor* mExtractableResource;

public:
	FORCEINLINE ~AFGBuildableGeneratorGeoThermal() = default;
};
