// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGResourceNode.h"
#include "FGResourceSettings.h"
#include "FGResourceDeposit.generated.h"

/**
 * A smaller resource deposit that can only be mined by hand.
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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// End AActor interface

	/** Determine what type of resource node this is by a random factor */
	void RollResourceType();

	/** Tries to up the resource type to be the one specified in override variable */
	void TrySetDesiredResourceType( TSubclassOf< UFGResourceDescriptor > resourceDescriptor );

	/** Sets up all the data for this node */
	void SetupResourceInfo();

	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;

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

	void SetOverrideResourceClass( const TSubclassOf< UFGResourceDescriptor > resourceDescriptor );

	const TSoftObjectPtr< AFGResourceNode > GetResourceNodeActor() const { return mResourceNodeActor; }
	void SetResourceNodeActor( const TSoftObjectPtr< AFGResourceNode > resourceNodeActor );
	
protected:
	/** Called to multicast depletion effect VFX and sound */
	UFUNCTION( NetMulticast, Unreliable )
	void Multicast_PlayDepletedEffect();
	
	/** Called on client when resource deposit index is set so that we can correctly setup the mesh / material*/
	UFUNCTION()
	void OnRep_ResourceDepositTableIndex();

	virtual void InitRadioactivity() override;
	virtual void UpdateRadioactivity() override;

	/** If the deposit sits on a larger node this should point to that node. */
	UPROPERTY( EditInstanceOnly )
	TSoftObjectPtr< AFGResourceNode > mResourceNodeActor;
	
private:
	bool IsDepositTableIndexValid() const;
	
	/** Valid if mLootTableIndex is not INDEX_NONE */
	UPROPERTY( )
	FResourceDepositPackage mResourceDepositPackage;

	/** Index in the resource deposit table */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ResourceDepositTableIndex )
	int32 mResourceDepositTableIndex;

	/** is deposit emptied */
	UPROPERTY( SaveGame, Replicated )
	bool mIsEmptied;

	/** How much to mine per cycle */
	UPROPERTY( SaveGame, Replicated )
	int32 mMineAmount;

	UPROPERTY( Transient )
	bool mHasInitializedVisuals = false;
	
public:
	/** The mesh we use for displaying the resource deposit */
	UPROPERTY( BlueprintReadWrite, VisibleAnywhere, Category = "Resources" )
	TObjectPtr<UStaticMeshComponent> mDepositMeshComponent;

	UPROPERTY( EditInstanceOnly, Category = "Resources" )
	TSubclassOf< class UFGResourceDescriptor > mOverrideResourceClass;

	/** Determines if the resource node should be able to be radio active. */
	UPROPERTY( BlueprintReadWrite, EditInstanceOnly, Category = "Resources" )
	bool mCanBeRadioactive = true;
	
};
