// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGInteractActor.h"
#include "FGSaveInterface.h"
#include "FGActorRepresentationInterface.h"
#include "Replication/FGConditionalReplicationInterface.h"
#include "FGCrate.generated.h"

/** Types of the crate we have in game */
UENUM( BlueprintType )
enum class EFGCrateType : uint8
{
	CT_None UMETA(DisplayName = "None"),
	CT_DismantleCrate UMETA(DisplayName = "Dismantle Crate"),
	CT_DeathCrate UMETA(DisplayName = "Death Crate"),
};

/**
 * Crates are containers of items that are spawned on demand when the contents do not fill into the player's inventory, or when the player dies
 * They cannot have additional items inserted into them, and self-destruct when they are empty.
 */
UCLASS()
class FACTORYGAME_API AFGCrate : public AFGInteractActor, public IFGSaveInterface, public IFGActorRepresentationInterface, public IFGConditionalReplicationInterface
{
	GENERATED_BODY()
public:
	AFGCrate();

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return true; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	// Begin IFGConditionalReplicationInterface
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual bool IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const override;
	// End IFGConditionalReplicationInterface

	// Begin IFGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText( const FText& newText ) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	//<FL>[KonradA]
	UFUNCTION() virtual TArray< FLocalUserNetIdBundle > GetLastEditedBy() const override { return TArray< struct FLocalUserNetIdBundle >(); }
	UFUNCTION() virtual void SetActorLastEditedBy( const TArray< FLocalUserNetIdBundle >& LastEditedBy ) {}

	// End IFGActorRepresentationInterface

	//~ Begin IFGUseableInterface
	virtual bool IsUseable_Implementation() const override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	//~ End IFGUseableInterface
	
	/** @return The crates inventory; cannot be null. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	class UFGInventoryComponent* GetInventory() const { return mInventory; }

	/** Bound to mItemFilter to filter what items can be used in the item slots. */
	UFUNCTION()
	bool FilterInventoryClasses( TSubclassOf< UObject > object, int32 idx ) const;
	
	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	/** Sets the type of the crate */
	UFUNCTION( BlueprintCallable, Category = "Crate" )
	void SetCrateType( EFGCrateType newCrateType );

	/** Make sure to call this if you want to add items into the crate, otherwise AddStacks will not add anything! */
	UFUNCTION( BlueprintCallable, Category = "Crate" )
	void SetAllowAddingItems( bool newAllowAddingItems );

	/** Returns the type of the crate */
	UFUNCTION( BlueprintPure, Category = "Crate" )
	FORCEINLINE EFGCrateType GetCrateType() const { return mCrateType; }

protected:
	/** Property replicator for conditionally replicating details */
	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;
	
	/** Default type of the crate. Overriden on per instance basis */
	UPROPERTY( EditAnywhere, SaveGame, Replicated, Category = "Crate" )
	EFGCrateType mCrateType;

	/** Compass material for the crate */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	UMaterialInterface* mCompassMaterial;

	/** Name of the crate on the map (before distinction between dismantle and death crates was added) */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FText mMapText;

	/** Name of the dismantle crate on the map and compass */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FText mDismantleCrateText;

	/** Name of the death crate on the map and compass */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FText mDeathCrateText;

	/** Icon of the crate on the map (before distinction between dismantle and death crates was added) */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	UTexture2D* mCrateIcon;

	/** Icon for the dismantle crate */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	UTexture2D* mDismantleCrateIcon;

	/** Icon for the death crate */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	UTexture2D* mDeathCrateIcon;
private:
	UFUNCTION()
	void OnInventoryItemRemoved( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numRemoved, UFGInventoryComponent* targetInventory = nullptr );

	/** This is needed so we can pre-populate the crate with items in the first place */
	bool mAllowAddingItemsIntoInventory{false};

	/** The inventory of this crate */
	UPROPERTY()
	class UFGInventoryComponent* mInventory;

	/** Players interacting with this crate, used to toggle dormancy */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mInteractingPlayers;
};
