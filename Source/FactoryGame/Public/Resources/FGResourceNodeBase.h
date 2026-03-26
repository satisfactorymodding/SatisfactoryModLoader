// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGActorRepresentationInterface.h"
#include "FGClearanceInterface.h"
#include "FGExtractableResourceInterface.h"
#include "FGResourceDescriptor.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "FGUseableInterface.h"
#include "Engine/StaticMeshActor.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGResourceNodeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnResourceClassOverrideReplication, AFGResourceNodeBase*, TSubclassOf<UFGResourceDescriptor>,
                                        TSubclassOf<UFGResourceDescriptor> );

class UFGResourceNodeData;

/** Enum that specifies what type of a resource node this is. Used mostly for simplify UI work and not having to look/cast specific classes. */
UENUM( BlueprintType )
enum class EResourceNodeType : uint8
{
	Node,
    FrackingSatellite,
    FrackingCore,
	Geyser,
	Deposit,

	Invalid
};

/** Mesh type used for the node. To override mesh and materials on nodes that are randomized **/
UENUM( BlueprintType )
enum class ENodeMeshType: uint8
{
	MT_Node,
	MT_Core,
	MT_Crack,
	MT_Satellite,
	MT_DesertCore,
	MT_DesertCrack,
	MT_DesertSatellite
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

/** A Static Mesh Actor that should be used for all node meshes in the world. Else Random Nodes Game Mode will not work with the related node. */
UCLASS()
class FACTORYGAME_API AFGNodeMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UPROPERTY( EditInstanceOnly, Category = "Resources" )
	TSoftObjectPtr< class AFGResourceNodeBase > mNodeActor;

	UPROPERTY( EditInstanceOnly, Category = "Resources" )
	ENodeMeshType mNodeMeshType = ENodeMeshType::MT_Node;

	void SetNodeActor( AFGResourceNodeBase* node );

	UFUNCTION( BlueprintCallable, Category = "Resources" )
	bool IsPlayerPositionParameterUpdateOn() const;

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent )
	void OverrideMeshAndMaterials( AFGResourceNodeBase* nodeActor, TSubclassOf< UFGResourceDescriptor > originalDescriptor,
	                               TSubclassOf< UFGResourceDescriptor > overrideDescriptor );


private:
	void OverrideMaterials( const TArray< TObjectPtr< UMaterialInterface > >& materials, UStaticMeshComponent* meshComp );
	void OverrideMeshAndMaterials_Implementation( AFGResourceNodeBase* nodeActor, TSubclassOf< UFGResourceDescriptor > originalDescriptor,
	                                              TSubclassOf< UFGResourceDescriptor > overrideDescriptor );

	TSubclassOf< UFGResourceDescriptor > mMeshVisualData;
	bool mUpdatePlayerPositionParameter = false;
};

UCLASS( Abstract )
class FACTORYGAME_API AFGResourceNodeBase : public AFGStaticReplicatedActor, public IFGExtractableResourceInterface, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface, public IFGClearanceInterface /*, public IFGActorRepresentationInterface*/
{
	GENERATED_BODY()

	friend class AFGResourceNodeManager;

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
	virtual float GetSignificanceRange_Implementation() const override { return mSignificanceRange; }
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
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual bool IsUseable_Implementation() const override { return true; }
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	// End IFGUseableInterface

	// Begin IFGExtractableResourceInterface
	UFUNCTION()
	virtual void SetIsOccupied( bool occupied ) override;
	UFUNCTION()
	virtual bool IsOccupied() const override;
	UFUNCTION()
	virtual bool CanBecomeOccupied() const override;
	UFUNCTION()
	virtual TSubclassOf< UFGResourceDescriptor > GetResourceClass() const override;
	UFUNCTION()
	virtual TSubclassOf< UFGResourceDescriptor > GetResourceClassOverride() const { return mResourceClassOverride; }
	UFUNCTION()
	virtual bool DoesContainResource( TSubclassOf< class UFGResourceDescriptor > ResourceClass) const override;
	UFUNCTION()
	virtual TSubclassOf< UFGResourceDescriptor > GetResourceClassOriginal() const { return mResourceClass; }
	
	
	void SetResourceClass( const TSubclassOf< UFGResourceDescriptor > resource );
	void SetResourceClassOverride( const TSubclassOf< UFGResourceDescriptor > resource );

	UFUNCTION()
	virtual FVector GetPlacementLocation( const FVector& hitLocation ) const override;
	UFUNCTION()
	virtual FRotator GetPlacementRotation( const FVector& hitLocation ) const override;
	UFUNCTION()
	virtual bool HasAnyResources() const override { return false; }
	UFUNCTION()
	virtual int32 ExtractResource( int32 amount ) override { return 0; }
	UFUNCTION()
	virtual float GetExtractionSpeedMultiplier() const override { return 0; }
	UFUNCTION()
	virtual bool CanPlaceResourceExtractor() const override { return false; }
	// End IFGExtractableResourceInterface

	// Begin IFGClearanceInterface
	virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;
	// End IFGClearanceInterface

	/** Get what type of a resource node is this */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	EResourceNodeType GetResourceNodeType() const { return mResourceNodeType; }

	/** Localized name */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FText GetResourceName() const;


	/** What kind of form is the resource in */
	EResourceForm GetResourceForm() const;

	/** Let the client know when we changed. mIsOccupied */
	UFUNCTION()
	virtual void OnRep_IsOccupied();

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
	void UpdateMeshFromDescriptor( bool needRegister, UMaterial* decalMaterial );
	
	void ScanResourceNode_Local( float lifeSpan );
	UFUNCTION()
	void RemoveResourceNodeScan_Local();

	void ScanResourceNodeScan_Server();
	void RemoveResourceNodeScan_Server();
	
	FOnResourceClassOverrideReplication OnResourceClassOverrideReplication;

	UMaterial* GetDecalMaterial();
	
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
	void ConditionallySetupComponents( bool needRegister, UMaterial* decalMaterial );

	void UpdateHighlightParticleSystem();

	UFUNCTION()
	void OnRep_ServerMapReveals();

	UFUNCTION()
	void OnRep_ResourceClassOverride();
	
private:
	void UpdateNodeRepresentation();


	/** Type of resource */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	TSubclassOf< UFGResourceDescriptor > mResourceClass;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_ResourceClassOverride )
	TSubclassOf< UFGResourceDescriptor > mResourceClassOverride = nullptr;

protected:

	/** the decal that used for displaying the resource */
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	TObjectPtr<UDecalComponent> mDecalComponent;

	/** If we have no static mesh but a decal, then we use this for collision*/
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly, Category = "Resources" )
	TObjectPtr<class UBoxComponent> mBoxComponent;

	/** If true, then we are occupied by something // [Dylan 3/2/2020] - Removed savegame meta */
	UPROPERTY( ReplicatedUsing = OnRep_IsOccupied, BlueprintReadOnly, Category = "Resources" )
	bool mIsOccupied;

	/** Number of times this node is revealed locally by resource scanner. Used to keep track of when to add/remove node from map */
	int32 mLocalMapReveals;

	/** Number of times this node is revealed by the radar towers. Also forces the node to replicate it's data regardless of distance to the player */
	UPROPERTY( ReplicatedUsing = OnRep_ServerMapReveals )
	int32 mServerMapReveals;

	UPROPERTY( Transient )
	TObjectPtr<class UFGResourceNodeRepresentation> mResourceNodeRepresentation;
	
	/** What type of resource node this is. */
	UPROPERTY( EditAnywhere )
	EResourceNodeType mResourceNodeType;

	UPROPERTY( EditAnywhere, Category = "Resources" )
	bool mAllowDecal = true;

public:
	/** Particle system component  */
	UPROPERTY( EditAnywhere, Category = "Resources" )
	TObjectPtr<class UParticleSystem> mHighlightParticleSystemTemplate;

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Resources" )
	UParticleSystem* GetHighlightParticleSystemTemplate() const;
	virtual UParticleSystem* GetHighlightParticleSystemTemplate_Implementation() const;

	/** Particle system component  */
	UPROPERTY()
	TObjectPtr<class UParticleSystemComponent> mHighlightParticleSystemComponent;

	/** Bool for is we should spawn particle - @todo Do we really need to save this? //[Dylan 3/2/2020] */
	UPROPERTY( Replicated, EditDefaultsOnly, SaveGame, Category = "Resources" ) 
	bool mDoSpawnParticle;

	FVector GetBoxExtent() const;
private:
	/** Clearance data of this resource */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TArray< FFGClearanceData > mClearanceData;
	
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
