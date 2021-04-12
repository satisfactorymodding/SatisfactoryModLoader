// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableGeneratorFuel.h"
#include "Replication/FGReplicationDetailActor_GeneratorNuclear.h"
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
	virtual bool Factory_HasPower() const override;
	virtual bool CanStartPowerProduction_Implementation() const override;
	// End AFGBuildableGenerator interface

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGReplicationDetailActor_GeneratorNuclear::StaticClass(); };
	virtual void OnReplicationDetailActorRemoved() override;
	// End IFGReplicationDetailActorOwnerInterface

	bool IsWasteFull() const;

	/** We can only load fuel if waste is not full */
	virtual bool CanLoadFuel() const override;

	/** Try to produce nuclear waste and put it in the output inventory */
	void TryProduceWaste();

public: // MODDING EDIT accessor
	FORCEINLINE class UFGInventoryComponent* GetWasteInventoryAccessor() const { return GetWasteInventory(); };
protected:
	/** Returns the inventory for waste in the nuclear generator */
	UFUNCTION( BlueprintPure, Category = "Nuclear" )
	FORCEINLINE class UFGInventoryComponent* GetWasteInventory() const { return mOutputInventoryHandler->GetActiveInventoryComponent(); }

	/** Returns the current active warning for this nuclear generator */
	UFUNCTION( BlueprintPure, Category = "Nuclear" )
	FORCEINLINE EGeneratorNuclearWarning GetCurrentGeneratorNuclearWarning() const { return mCurrentGeneratorNuclearWarning; }
	
private:
	
	friend class AFGReplicationDetailActor_GeneratorNuclear;

	virtual void OnRep_ReplicationDetailActor() override;

	class AFGReplicationDetailActor_GeneratorNuclear* GetCastRepDetailsActor() const;

	/** Check if the waste inventory has space for the waste item of the fuel in the fuel inventory.
	 *  will return true if fuel inventory is empty
	 */
	bool CanFitWasteOfNextFuelClass() const;

public: //MODDING EDIT public
	/** Spent fuel rods goes here. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;

	UPROPERTY()
	UFGReplicationDetailInventoryComponent* mOutputInventoryHandler;

	/** Waste left to produce from the current fuel rod*/
	UPROPERTY( SaveGame )
	int32 mWasteLeftFromCurrentFuel;

	/** Current active warning on this nuclear generator */
	UPROPERTY( Replicated )
	EGeneratorNuclearWarning mCurrentGeneratorNuclearWarning;

};
