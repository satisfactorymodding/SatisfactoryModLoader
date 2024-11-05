// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableGeneratorFuel.h"
#include "FGBuildableGeneratorNuclear.generated.h"


//[FreiholtzK:Tue/15-12-2020] @todo look into making this into a more generic warnign system for all generators if applicable.
UENUM(BlueprintType)
enum class EGeneratorNuclearWarning : uint8
{
	GNW_None,
    GNW_WasteFull,
    GNW_MissmatchBetweenInputAndWaste
};

/**
 * A generator that runs on nuclear fuel and produces waste.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorNuclear : public AFGBuildableGeneratorFuel
{
	GENERATED_BODY()
public:
	AFGBuildableGeneratorNuclear();

	// Replication
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void BeginPlay() override;

	/** Returns the inventory for waste in the nuclear generator */
	UFUNCTION( BlueprintPure, Category = "Nuclear" )
	FORCEINLINE class UFGInventoryComponent* GetWasteInventory() const { return mOutputInventory; }
protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface
	
	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	// End AFGBuildableGenerator interface

	// Begin AFGBuildableGeneratorFuel interface
	virtual bool CanLoadFuel() const override;
	virtual void LoadFuel() override;
	// End AFGBuildableGeneratorFuel interface

	bool IsWasteFull() const;
	
	/** Try to produce nuclear waste and put it in the output inventory */
	void TryProduceWaste();

	/** Returns the current active warning for this nuclear generator */
	UFUNCTION( BlueprintPure, Category = "Nuclear" )
	FORCEINLINE EGeneratorNuclearWarning GetCurrentGeneratorNuclearWarning() const { return mCurrentGeneratorNuclearWarning; }
private:
	/** Check if the waste inventory has space for the waste item of the fuel in the fuel inventory. */
	bool CanFitWasteOfNextFuelClass() const;
	
	/** Spent fuel rods goes here. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;

	/** Waste left to produce from the current fuel rod*/
	UPROPERTY( SaveGame )
	int32 mWasteLeftFromCurrentFuel;

	/** Current active warning on this nuclear generator */
	UPROPERTY( meta = ( FGReplicated ) )
	EGeneratorNuclearWarning mCurrentGeneratorNuclearWarning;
};
