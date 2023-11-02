// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGInteractActor.h"
#include "FGSaveInterface.h"
#include "FGActorRepresentationInterface.h"
#include "FGCrate.generated.h"

UENUM( BlueprintType )
enum class EFGCrateIconType : uint8
{
	CIT_DeathIcon
	//Consider adding a different icon for a crate holding the hub item?

};

/**
 * @todo Comment me please!
 */
UCLASS()
class FACTORYGAME_API AFGCrate : public AFGInteractActor, public IFGSaveInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:

	AFGCrate();

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor Interface
	virtual void PostActorCreated() override;
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

	// Begin IFGActorRepresentationInterface
	UFUNCTION()
	virtual bool AddAsRepresentation() override;
	UFUNCTION()
	virtual bool UpdateRepresentation() override;
	UFUNCTION()
	virtual bool RemoveAsRepresentation() override;
	UFUNCTION()
	virtual bool IsActorStatic() override;
	UFUNCTION()
	virtual FVector GetRealActorLocation() override;
	UFUNCTION()
	virtual FRotator GetRealActorRotation() override;
	UFUNCTION()
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION()
	virtual FText GetActorRepresentationText() override;
	UFUNCTION()
	virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION()
	virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION()
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION()
	virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION()
	virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION()
	virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION()
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION()
	virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION()
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION()
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
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

	UFUNCTION( BlueprintCallable, Category = "Crate" )
	void SetIconType( EFGCrateIconType type );

	/** Make sure to call this if you want to add items into the crate, otherwise AddStacks will not add anything! */
	UFUNCTION( BlueprintCallable, Category = "Crate" )
	void SetAllowAddingItems( bool newAllowAddingItems );
private:
	UFUNCTION()
	void OnInventoryItemRemoved( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numRemoved );

	/** This is needed so we can pre-populate the crate with items in the first place */
	bool mAllowAddingItemsIntoInventory{false};
protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Compass" )
	EFGCrateIconType mIconType;
	
private:
	/** The inventory of this crate */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInventory;

	/** Players interacting with this crate, used to toggle dormancy */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mInteractingPlayers;
	
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FText mMapText;

};

