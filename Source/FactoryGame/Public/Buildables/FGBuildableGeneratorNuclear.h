// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableGeneratorFuel.h"
#include "FGBuildableGeneratorNuclear.generated.h"

/**
 * A generator that runs on nuclear fuel and produces waste.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorNuclear : public AFGBuildableGeneratorFuel
{
	GENERATED_BODY()
public:
	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;

protected:

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	// Begin AFGBuildableGeneratorFuel
	virtual void LoadFuel() override;
	// End AFGBuildableGeneratorFuel
	
	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	// End AFGBuildableGenerator interface

	/** We can only load fuel if waste is not full */
	virtual bool CanLoadFuel() const override;

	/** Try to produce nuclear waste and put it in the output inventory */
	void TryProduceWaste();

	/** Returns the inventory for waste in the nuclear generator */
	UFUNCTION( BlueprintPure, Category = "Nuclear" )
	FORCEINLINE class UFGInventoryComponent* GetWasteInventory() const { return mOutputInventory; }
private:
	/** Spent fuel rods goes here. */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mOutputInventory;

	/** Waste left to produce from the current fuel rod*/
	UPROPERTY( SaveGame )
	int32 mWasteLeftFromCurrentFuel;

};
