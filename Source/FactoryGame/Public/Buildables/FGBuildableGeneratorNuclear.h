// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableGeneratorFuel.h"
#include "../Replication/FGReplicationDetailActor_GeneratorNuclear.h"
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
	virtual bool HasPower() const override;
	virtual bool CanStartPowerProduction_Implementation() const override;
	// End AFGBuildableGenerator interface

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGReplicationDetailActor_GeneratorNuclear::StaticClass(); };
	// End IFGReplicationDetailActorOwnerInterface

	bool IsWasteFull() const;

	/** We can only load fuel if waste is not full */
	virtual bool CanLoadFuel() const override;

	/** Try to produce nuclear waste and put it in the output inventory */
	void TryProduceWaste();

	/** Returns the inventory for waste in the nuclear generator */
	UFUNCTION( BlueprintPure, Category = "Nuclear" )
	FORCEINLINE class UFGInventoryComponent* GetWasteInventory() const { return mOutputInventoryHandler->GetActiveInventoryComponent(); }
private:
	friend class AFGReplicationDetailActor_GeneratorNuclear;

	virtual void OnRep_ReplicationDetailActor() override;

	class AFGReplicationDetailActor_GeneratorNuclear* GetCastRepDetailsActor() const;
public://MODDING EDIT
	/** Spent fuel rods goes here. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;

	UPROPERTY()
	UFGReplicationDetailInventoryComponent* mOutputInventoryHandler;
private://MODDING EDIT
	/** Waste left to produce from the current fuel rod*/
	UPROPERTY( SaveGame )
	int32 mWasteLeftFromCurrentFuel;


public:
	FORCEINLINE ~AFGBuildableGeneratorNuclear() = default;
};
