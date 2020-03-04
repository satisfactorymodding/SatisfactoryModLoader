// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "../FGResourceSettings.h"
#include "FGResourceNode.h"
#include "FGResourceDeposit.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGResourceDeposit : public AFGResourceNode
{
	GENERATED_BODY()
	
public:	
	AFGResourceDeposit();

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin UObject interface
	virtual void PostLoad() override;
	// End UObject interface

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	/** Determine what type of resource node this is by a random factor */
	void RollResourceType();

	/** Tries to up the resource type to be the one specified in override variable */
	void TrySetDesiredResourceType();

	/** Sets up all the data for this node */
	void SetupResourceInfo();

	/** Gives one resource to a player */
	virtual void ExtractResourceAndGiveToPlayer( AFGCharacterPlayer* toPlayer, int32 amount = 1 ) override;

	/** Function used to play effects and change mesh when a deposit is emptied */
	UFUNCTION( BlueprintImplementableEvent, Category = "Deposit" )
	void PlayDepletedEffect( TSubclassOf< class UFGResourceDescriptor > descriptor );

	/** Is deposit empty? */
	UFUNCTION( BlueprintPure, Category = "Deposit" )
	FORCEINLINE bool IsDepositEmpty() { return mIsEmptied; }

	/**How much to mine per cycle */
	UFUNCTION( BlueprintPure, Category = "Deposit" )
	FORCEINLINE int32 GetMineAmount() { return mMineAmount; }
protected:
	/** Called on client when resource deposit has been emptied */
	UFUNCTION()
	void OnRep_ResourceDepositEmptied();

	virtual void InitRadioactivity() override;
	virtual void UpdateRadioactivity() override;

private:
	/** Valid if mLootTableIndex is not INDEX_NONE */
	UPROPERTY()
	FResourceDepositPackage mResourceDepositPackage;

	/** Index in the resource deposit table */
	UPROPERTY( SaveGame, Replicated )
	int32 mResourceDepositTableIndex;

	/** is deposit emptied */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_ResourceDepositEmptied )
	bool mIsEmptied;

	/** How much to mine per cycle */
	UPROPERTY( SaveGame, Replicated )
	int32 mMineAmount;
public:
	/** The mesh we use for displaying the resource deposit */
	UPROPERTY( BlueprintReadWrite, VisibleAnywhere, Category = "Resources" )
	UStaticMeshComponent* mDepositMeshComponent;

	UPROPERTY( EditInstanceOnly, Category = "Resources" )
	TSubclassOf< class UFGResourceDescriptor > mOverrideResourceClass;

public:
	FORCEINLINE ~AFGResourceDeposit() = default;
};
