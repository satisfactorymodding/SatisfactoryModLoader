// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGInteractActor.h"
#include "FGSaveInterface.h"
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
UCLASS(Blueprintable)
class FACTORYGAME_API AFGCrate : public AFGInteractActor, public IFGSaveInterface
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

	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};

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

	void SetIconType( EFGCrateIconType type );
private:
	/** The inventory of this crate */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInventory;
protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Compass" )
	EFGCrateIconType mIconType;


public:
	FORCEINLINE ~AFGCrate() = default;
};
