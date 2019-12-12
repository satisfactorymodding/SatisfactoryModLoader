// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "../FGSaveInterface.h"
#include "FGResourceDescriptor.h"
#include "../FGUseableInterface.h"
#include "../FGActorRepresentationInterface.h"
#include "../FGSignificanceInterface.h"
#include "Components/BoxComponent.h"
#include "FGResourceNode.generated.h"

class UFGResourceDescriptor;

/** How much resources this node contains, a rich vein will deplete later */
UENUM( BlueprintType )
enum EResourceAmount
{
	RA_Poor UMETA(DisplayName="Poor"),
	RA_Normal UMETA( DisplayName = "Normal" ),
	RA_Rich UMETA( DisplayName = "Rich" ),
	RA_Infinite UMETA( DisplayName = "Infinite"),
	RA_MAX UMETA( Hidden )
};

/** How how fast it is to mine the resource */
UENUM()
enum EResourcePurity
{
	RP_Inpure UMETA( DisplayName = "Impure" ),
	RP_Normal UMETA( DisplayName = "Normal" ),
	RP_Pure UMETA( DisplayName = "Pure" ),
	RP_MAX UMETA( Hidden )
};

USTRUCT( BlueprintType )
struct FPurityTextPair
{
	GENERATED_BODY()

	FPurityTextPair() :
		Text( FText() ),
		Purity( EResourcePurity::RP_Inpure )
	{
	}

	/** Localizable text */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	FText Text;

	/** Enum to localize */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TEnumAsByte< EResourcePurity > Purity;
};

/**
* Use state when inventory of player looking at the node has a full inventory
*/
UCLASS()
class UFGUseState_NodeFullInventory : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_NodeFullInventory() : Super() { mIsUsableState = false; }
};

/**
* The resource we are trying to pick can't be on a conveyor belt.
*/
UCLASS()
class UFGUseState_NonConveyorResource : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_NonConveyorResource() : Super() { mIsUsableState = false; }
};

UCLASS(Blueprintable,abstract)
class FACTORYGAME_API AFGResourceNode : public AActor, public IFGSaveInterface, public IFGUseableInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:	
	/** Decide on what properties to replicate */
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Sets default values for this actor's properties
	AFGResourceNode();

	// Begin UObject interface
	virtual void PostLoad() override;
	// End UObject interface

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor interface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	//~ End IFGUseableInterface

	/** Localized name */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FText GetResourceName() const;

	/** What kind of form is the resource in */
	EResourceForm GetResourceForm() const;

	/** Setup the resource so it's usable, sets up amount left */
	UFUNCTION(BlueprintCallable, Category="Resources")
	void InitResource( TSubclassOf<UFGResourceDescriptor> resourceClass, EResourceAmount amount, EResourcePurity purity );

	/** For UI */
	UFUNCTION(BlueprintPure,Category="Resources")
	FText GetResoucesLeftText() const;

	/** For UI */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FText GetResoucePurityText() const;

	/** For UI, returns the enum */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FORCEINLINE EResourcePurity GetResoucePurity(){ return mPurity; }

	/** Query the resource node what kind of resource class is of */
	UFUNCTION(BlueprintPure,Category="Resources")
	TSubclassOf<UFGResourceDescriptor> GetResourceClass() const;

	/** Get a speed multiplier when extracting from this resource */
	UFUNCTION(BlueprintPure,Category="Resources")
	float GetExtractionSpeedMultiplier() const;

	/** If true, this node will NEVER join another cluster of nodes, regardless of proximity. */
	UFUNCTION( BlueprintPure, Category="Resources" )
	bool GetIsLonerNode() const { return mIsLonerNode; }

	/** Call this to extract a resources from the node, and it will return how many resources you can extract from it */
	int32 ExtractResource( int32 amount );

	UFUNCTION(BlueprintPure,Category="Resources")
	bool HasAnyResources() const;

	/** Set if the node is occupied by something */
	UFUNCTION( BlueprintCallable, Category = "Resources" )
	void SetIsOccupied( bool occupied );

	/** Let the client know when we changed. mIsOccupied */
	UFUNCTION()
	void OnRep_IsOccupied();

	/** Let's blueprint know that we have changed occupied states */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resources" )
	void OnIsOccupiedChanged( bool newIsOccupied );

	/** Return true if the resource is occupied */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	bool IsOccupied() const; 

	/** The range of a resource for a amount */
	const FInt32Interval& GetResourceAmount( EResourceAmount amount ) const;

	/** Get a random resource amount */
	int32 GetRandomResourceAmount( EResourceAmount amount ) const;

	/** Opens or closes the picking ui */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resources" )
	void ToggleResourcePickUI( AFGCharacterPlayer* player );
	
	/** Gives one resource to a player */
	UFUNCTION( BlueprintCallable )
	virtual void ExtractResourceAndGiveToPlayer( AFGCharacterPlayer* toPlayer, int32 amount = 1 );

	/** Is this resource node valid for placing an extractor on? */
	UFUNCTION( BlueprintPure, Category = "Resources" ) 
	FORCEINLINE bool CanPlaceResourceExtractor() { return mCanPlaceResourceExtractor; }

	/**Getter for extract multiplier */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FORCEINLINE int32 GetExtractMultiplier() const { return mExtractMultiplier; }

	/** Returns the mAmount */
	UFUNCTION( BlueprintCallable )
	FORCEINLINE EResourceAmount GetResourceAmount() const { return mAmount; }

	/** Cleanup function for UI. Placed here so that both nodes and deposits can take the same code path */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "UI" )
	void ClearWidget();

	int32 GetNumResourcesPerExtract() const;

#if WITH_EDITOR

	bool IsGeyserDescButNotGeyserNode();

	/** When this is changed in the editor, propagate the changes to the preview window */
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;

	virtual void CheckForErrors() override;
#endif

	/** Used by the descriptor, so that all meshes in the world can get their mesh updated */
	void UpdateMeshFromDescriptor( bool needRegister = true );

	/** Used by the radar tower to show this actor on the map */
	void AddRevealedOnMapBy( UObject* newObject );

	/** Used by the radar tower to hide this actor on the map */
	void RemoveRevealedOnMapBy( UObject* oldObject );
protected:
	/**
	 * Setup the decal component if needed
	 * @param needRegister - if true, then we need to register new components
	 *
	 **/
	void ConditionallySetupComponents( bool needRegister );

	/** Setup radiation emitters for radioactive resources. */
	virtual void InitRadioactivity();

	/** Called when a resource is extracted. Never called on infinite resource nodes. */
	virtual void UpdateRadioactivity();

protected:
	/** Type of resource */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	TSubclassOf<UFGResourceDescriptor> mResourceClass;

	/** How pure the resource is */
	UPROPERTY(EditInstanceOnly, Category= "Resources" )
	TEnumAsByte<EResourcePurity> mPurity;

	/** How pure the resource is */
	UPROPERTY( EditInstanceOnly, Category = "Resources" )
	TEnumAsByte<EResourceAmount> mAmount;

	/** The mesh we use for displaying the resource if it has a ground mesh */
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources")
	UStaticMeshComponent* mStaticMeshComponent;

	/** the decal that used for displaying the resource */
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	UDecalComponent* mDecalComponent;

	/** If we have no static mesh but a decal, then we use this for collision*/
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	UBoxComponent* mBoxComponent;

	/** How much resources is left in this node */
	UPROPERTY( SaveGame, Replicated, EditInstanceOnly, BlueprintReadOnly, Category="Resources")
	int32 mResourcesLeft;

	/** If true, then we are occupied by something */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsOccupied, BlueprintReadOnly, Category = "Resources" )
	bool mIsOccupied;

	/** Radar tower modifies this to show this resource node in the map */
	UPROPERTY( SaveGame, Replicated )
	TArray< UObject* > mRevealedOnMapBy;

	/** If true, this node will NEVER join another cluster of nodes, regardless of proximity. */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	bool mIsLonerNode;

	/** Can this resource node be used for placing resource extractors on */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	bool mCanPlaceResourceExtractor;

	/** is this node a geyser node? */
	bool mIsGeyserNode;

	/** Multiplier that is applied in the end of extraction calculations. Is used for making deposits extract more than regular nodes */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	int32 mExtractMultiplier;

	/** Should we display the default mesh? */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	bool mUseDefaultMesh;

	/** Text mapped to resource purity */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TArray< FPurityTextPair > mPurityTextArray;
public:
	/** Can this resource node be used for placing portable miners on */
	bool mCanPlacePortableMiner;

	/** Particle system component  */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	class UParticleSystem* mHighlightParticleSystemTemplate;

	/** Particle system component  */
	UPROPERTY()
	class UParticleSystemComponent* mHighlightParticleSystemComponent;

	/** Bool for is we should spawn particle */
	UPROPERTY( Replicated, EditDefaultsOnly, SaveGame, Category = "Resources" ) 
	bool mDoSpawnParticle;
};