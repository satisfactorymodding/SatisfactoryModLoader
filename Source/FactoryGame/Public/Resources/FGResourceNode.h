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
#include "FGExtractableResourceInterface.h"
#include "../FGActorRepresentationInterface.h"
#include "../FGSignificanceInterface.h"
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
struct FACTORYGAME_API FPurityTextPair
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

public:
	FORCEINLINE ~FPurityTextPair() = default;
};

/**
* Use state when inventory of player looking at the node has a full inventory
*/
UCLASS()
class FACTORYGAME_API UFGUseState_NodeFullInventory : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_NodeFullInventory() : Super() { mIsUsableState = false; }

public:
	FORCEINLINE ~UFGUseState_NodeFullInventory() = default;
};

/**
* The resource we are trying to pick can't be on a conveyor belt.
*/
UCLASS()
class FACTORYGAME_API UFGUseState_NonConveyorResource : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_NonConveyorResource() : Super() { mIsUsableState = false; }

public:
	FORCEINLINE ~UFGUseState_NonConveyorResource() = default;
};

UCLASS(Blueprintable,abstract)
class FACTORYGAME_API AFGResourceNode : public AActor, public IFGExtractableResourceInterface, public IFGSaveInterface, public IFGUseableInterface, public IFGSignificanceInterface
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

	// Begin IFGExtractableResourceInterface
	virtual void SetIsOccupied_Implementation( bool occupied ) override;
	virtual bool IsOccupied_Implementation() const override;
	virtual bool CanBecomeOccupied_Implementation() const override;
	virtual bool HasAnyResources_Implementation() const override;
	virtual TSubclassOf< UFGResourceDescriptor > GetResourceClass_Implementation() const override;
	virtual int32 ExtractResource_Implementation( int32 amount ) override;
	virtual float GetExtractionSpeedMultiplier_Implementation() const override;
	virtual FVector GetPlacementLocation_Implementation( const FVector& hitLocation ) const override;
	virtual bool CanPlaceResourceExtractor_Implementation() const override;
	// End IFGExtractableResourceInterface

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

	/** If true, this node will NEVER join another cluster of nodes, regardless of proximity. */
	UFUNCTION( BlueprintPure, Category="Resources" )
	bool GetIsLonerNode() const { return mIsLonerNode; }

	/** Let the client know when we changed. mIsOccupied */
	UFUNCTION()
	void OnRep_IsOccupied();

	/** Let's blueprint know that we have changed occupied states */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resources" )
	void OnIsOccupiedChanged( bool newIsOccupied );

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

public: // MODDING EDIT: protected -> public
	/** Type of resource */
    // MODDING EDIT: BPReadOnly
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Resources" )
	TSubclassOf<UFGResourceDescriptor> mResourceClass;

	/** How pure the resource is */
    // MODDING EDIT: BPRW
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category= "Resources" )
	TEnumAsByte<EResourcePurity> mPurity;

	/** How pure the resource is */
    // MODDING EDIT: BPRW
	UPROPERTY( EditInstanceOnly, BlueprintReadWrite, Category = "Resources" )
	TEnumAsByte<EResourceAmount> mAmount;

	/** the decal that used for displaying the resource */
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	UDecalComponent* mDecalComponent;

	/** If we have no static mesh but a decal, then we use this for collision*/
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	UBoxComponent* mBoxComponent;

	/** How much resources is left in this node */
	UPROPERTY( SaveGame, Replicated, BlueprintReadWrite, Category="Resources")
	int32 mResourcesLeft;

protected: // MODDING EDIT
	/** If true, then we are occupied by something // [Dylan 3/2/2020] - Removed savegame meta */
	UPROPERTY( ReplicatedUsing = OnRep_IsOccupied, BlueprintReadOnly, Category = "Resources" )
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

	/** Multiplier that is applied in the end of extraction calculations. Is used for making deposits extract more than regular nodes */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	int32 mExtractMultiplier;

	/** Text mapped to resource purity */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TArray< FPurityTextPair > mPurityTextArray;

	/** Last frame we flushed net dormancy */
	uint64 mLastFlushFrame;
public:
	/** Can this resource node be used for placing portable miners on */
	bool mCanPlacePortableMiner;

	/** Particle system component  */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	class UParticleSystem* mHighlightParticleSystemTemplate;

	/** Particle system component  */
	UPROPERTY()
	class UParticleSystemComponent* mHighlightParticleSystemComponent;

	/** Bool for is we should spawn particle - @todo Do we really need to save this? //[Dylan 3/2/2020] */
	UPROPERTY( Replicated, EditDefaultsOnly, SaveGame, Category = "Resources" ) 
	bool mDoSpawnParticle;
private:
	/** Should this be handled by significance manager */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	bool mAddToSignificanceManager;

public:
	FORCEINLINE ~AFGResourceNode() = default;
};