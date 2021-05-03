// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h" // MODDING EDIT: no PCH
#include "Replication/FGStaticReplicatedActor.h"
#include "FGSaveInterface.h"
#include "Resources/FGResourceDescriptor.h"
#include "Resources/FGExtractableResourceInterface.h"
#include "FGUseableInterface.h"
#include "FGActorRepresentationInterface.h"
#include "FGSignificanceInterface.h"
#include "FGResourceNodeBase.generated.h"

/** Enum that specifies what type of a resource node this is. Used mostly for simplify UI work and not having to look/cast specific classes. */
UENUM( BlueprintType )
enum class EResourceNodeType : uint8
{
	Node,
    FrackingSatellite,
    FrackingCore,
	Geyser
};

/**
* The resource we are trying to pick can't be on a conveyor belt.
*/
UCLASS()
class FACTORYGAME_API UFGUseState_NonConveyorResource : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_NonConveyorResource() : Super() { mIsUsableState = false; }
};

UCLASS( Abstract )
class FACTORYGAME_API AFGResourceNodeBase : public AFGStaticReplicatedActor, public IFGExtractableResourceInterface, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:
	AFGResourceNodeBase();

	/** Decide on what properties to replicate */
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

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
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	//End IFGSignificanceInterface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual bool IsUseable_Implementation() const override { return true; }
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	// End IFGUseableInterface

	// Begin IFGExtractableResourceInterface
	virtual void SetIsOccupied( bool occupied ) override;
	virtual bool IsOccupied() const override;
	virtual bool CanBecomeOccupied() const override;
	virtual TSubclassOf< UFGResourceDescriptor > GetResourceClass() const override;
	virtual FVector GetPlacementLocation( const FVector& hitLocation ) const override;
	virtual bool HasAnyResources() const override { return false; }
	virtual int32 ExtractResource( int32 amount ) override { return 0; }
	virtual float GetExtractionSpeedMultiplier() const override { return 0; }
	virtual bool CanPlaceResourceExtractor() const override { return false; }
	// End IFGExtractableResourceInterface

	/** Get what type of a resource node is this */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	EResourceNodeType GetResourceNodeType() const { return mResourceNodeType; }

	/** Localized name */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FText GetResourceName() const;

	/** What kind of form is the resource in */
	EResourceForm GetResourceForm() const;

	/** If true, this node will NEVER join another cluster of nodes, regardless of proximity. */
	UFUNCTION( BlueprintPure, Category="Resources" )
	bool GetIsLonerNode() const { return mIsLonerNode; }

	/** Let the client know when we changed. mIsOccupied */
	UFUNCTION()
	void OnRep_IsOccupied();

	/** Let's blueprint know that we have changed occupied states */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resources" )
	void OnIsOccupiedChanged( bool newIsOccupied );
	
	UFUNCTION( BlueprintPure, Category = "Resources" )
	bool IsSignificant() const { return mIsSignificant; }

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
	/** @returns the actor that contains the mesh for this node */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	class AActor* GetMeshActor() const { return mMeshActor.Get(); }

	void InitResource( TSubclassOf<UFGResourceDescriptor> resourceClass );

	/**
	 * Setup the decal component if needed
	 * @param needRegister - if true, then we need to register new components
	 *
	 **/
	void ConditionallySetupComponents( bool needRegister );

	void UpdateHighlightParticleSystem();

protected:
	/** Type of resource */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	TSubclassOf<UFGResourceDescriptor> mResourceClass;

	/** the decal that used for displaying the resource */
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	UDecalComponent* mDecalComponent;

	/** If we have no static mesh but a decal, then we use this for collision*/
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	UBoxComponent* mBoxComponent;

	/** If true, then we are occupied by something // [Dylan 3/2/2020] - Removed savegame meta */
	UPROPERTY( ReplicatedUsing = OnRep_IsOccupied, BlueprintReadOnly, Category = "Resources" )
	bool mIsOccupied;

	/** Radar tower modifies this to show this resource node in the map */
	UPROPERTY( SaveGame, Replicated )
	TArray< UObject* > mRevealedOnMapBy;

	/** If true, this node will NEVER join another cluster of nodes, regardless of proximity. */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	bool mIsLonerNode;

	/** What type of a resource node this is. */
	EResourceNodeType mResourceNodeType;

	/** If true, this node will NEVER join another cluster of nodes, regardless of proximity. */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	bool mAllowDecal = true;

public:
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
	/** The actor that contains the mesh for this node */
	UPROPERTY( EditInstanceOnly, Category = "Resources" )
	TSoftObjectPtr< class AActor > mMeshActor;

	/** Should this be handled by significance manager */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	bool mAddToSignificanceManager;

	/** The range to keep the node in significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;

	/** Is this resource node in significance range */
	bool mIsSignificant = false;
};
