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
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

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
	// End IFGActorRepresentationInterface

	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;

	/** @return The crates inventory; cannot be null. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	class UFGInventoryComponent* GetInventory() const { return mInventory; }

	/** Bound to mItemFilter to filter what items can be used in the item slots. */
	UFUNCTION()
	bool FilterInventoryClasses( TSubclassOf< UObject > object, int32 idx ) const;

	void SetupInventoryFilter();



	/** Called when we want a crate to be visible on the compasse. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Compass" )
	void OnRequestReprecentMarker();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	void SetIconType( EFGCrateIconType type );
private:
	/** The inventory of this crate */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInventory;

	/** Players interacting with this crate, used to toggle dormancy */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mInteractingPlayers;

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Compass" )
	EFGCrateIconType mIconType;

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FText mMapText;

};
