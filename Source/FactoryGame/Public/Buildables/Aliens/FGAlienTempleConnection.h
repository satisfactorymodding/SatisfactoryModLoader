// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "Buildables/Aliens/FGAlienTempleCondition.h"
#include "FGFluidIntegrantInterface.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGAlienTempleConnection.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FACTORYGAME_API AFGAlienTempleConnection : public AFGBuildableFactory, public IFGFluidIntegrantInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE TArray<UFGAlienTempleCondition*> GetConditionObject() { return mConditions; }

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Begin FluidIntegrant Interface
	virtual FFluidBox* GetFluidBox() override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End FluidIntegrant Interface
	
private:
	UPROPERTY(EditAnywhere, Instanced, Category="Connection")
	TArray<UFGAlienTempleCondition*> mConditions;

	/** Cached input component from blueprint. */
	UPROPERTY()
	class UFGPipeConnectionComponent* mInputConnection;
	
	/** Simulation data for this fluid integrant. */
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;
};
