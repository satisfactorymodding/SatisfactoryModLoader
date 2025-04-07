// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FactoryGame.h"
#include "FGDismantleInterface.h"
#include "FGSaveInterface.h"
#include "GameFramework/Actor.h"
#include "FGBlueprintProxy.generated.h"


class AFGBuildable;

USTRUCT()
struct FBuildableClassLightweightIndices
{
	GENERATED_BODY()

public:
	FBuildableClassLightweightIndices() {}
	FBuildableClassLightweightIndices(TSubclassOf< AFGBuildable > buildableClass ) :
		BuildableClass( buildableClass )
	{}
	
	UPROPERTY( SaveGame )
	TSubclassOf< AFGBuildable > BuildableClass;

	UPROPERTY( SaveGame )
	TArray< int32 > Indices;
};

/** Actor representing a spawned blueprint, with references to each building inside of it. Will automatically destroy when all buildings are gone. */
UCLASS()
class FACTORYGAME_API AFGBlueprintProxy : public AActor, public IFGSaveInterface, public IFGDismantleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGBlueprintProxy();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Used by the buildables in postload to register themselves to their blueprint proxy, so we can reference them through the proxy. */
	void RegisterBuildable( class AFGBuildable* buildable );

	/** Perform a final check to see if we have valid lightweights and buildables. If not self destruct */
	void ValidateExistanceOtherwiseSelfDestruct();

	/** When a buildable is actually converted to a lightweight instance in its begin play it is added through here */
	void RegisterLightweightInstance( TSubclassOf< class AFGBuildable > buildableClass, int32 index );

	/** Used by buildables to unregister themselves from the blueprint proxy. Should only happen when the buildable is no longer considered part of the blueprint. */
	void UnregisterBuildable( class AFGBuildable* buildable );

	/** When a lightweight buildable is removed this is called */
	void UnregisterLightweightInstance( TSubclassOf< class AFGBuildable > buildableClass, int32 index );

	/**
	 * Verifies theres no nullptrs in the buildable array and Checks with the lightweight subsystem if the any lightweights referenced by
	 *  this proxy are indeed valid on the subsystem. This is used by clients to check if they're waiting for data
	 * @return True if all lightweight indices are registered OR if there are no lightweights to consider AND all buildables have been replicated
	*/
	bool AreProxyBuildingsRegisteredAndValid() const;

	UFUNCTION( BlueprintPure, Category = "BlueprintProxy" )
	class UBoxComponent* GetBoundingBox() const { return mBoundingBox; }

	/** Gets the buildables which are part of this blueprint. */
	UFUNCTION( BlueprintPure, Category = "BlueprintProxy" )
	const TArray< class AFGBuildable* >& GetBuildables() const { return mBuildables; }

	/** Appends the buildables that belong to this blueprint to the specified array, returns the amount of buildables added. */
	UFUNCTION( BlueprintPure, Category = "BlueprintProxy" )
	int32 CollectBuildables( TArray< class AFGBuildable* >& out_buildables ) const;

	/** Gets the blueprint descriptor which was used to construct this blueprint. */
	UFUNCTION( BlueprintPure, Category = "BlueprintProxy" )
	class UFGBlueprintDescriptor* GetBlueprintDescriptor() const;

	/** Gets the name of the descriptor this blueprint was built with. */
	UFUNCTION( BlueprintPure, Category = "BlueprintProxy" )
	const FText& GetBlueprintName() const { return mBlueprintName; }

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//~ Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleDependencies_Implementation(TArray<AActor*>& out_dismantleDependencies) const override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	virtual void GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const override;
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	virtual FText GetDismantleDisplayName_Implementation(AFGCharacterPlayer* byCharacter) const override;
	//~ End IFGDismantleInterface

	FORCEINLINE const TArray<FBuildableClassLightweightIndices>& GetLightweightClassAndIndices() const { return mLightweightClassAndIndices; }
	
private:
	UFUNCTION()
	void OnRep_BlueprintName();

	UFUNCTION()
	void OnRep_LocalBounds();

	UFUNCTION()
	void OnRep_LightweightIndices();
	
	void AssignBuildables( const TArray< class AFGBuildable* >& buildables );

	bool HasAnyLightweightInstances() const;

	FBuildableClassLightweightIndices& FindOrAddLightweightIndiceEntry( TSubclassOf< AFGBuildable > buildableClass );
	
#if !UE_BUILD_SHIPPING
	virtual void DisplayDebug( UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos ) override;
#endif

private:
	/** The name of this blueprint, used to get the BlueprintDescriptor. */
	UPROPERTY( ReplicatedUsing = OnRep_BlueprintName, SaveGame )
	FText mBlueprintName;

	/** The bounds of this blueprint, in local space. */
	UPROPERTY( ReplicatedUsing = OnRep_LocalBounds, SaveGame)
	FBox mLocalBounds;
	
	/** The buildables which are part of this blueprint. The buildables will register themselves on PostLoad. */
	UPROPERTY( Replicated )
	TArray< class AFGBuildable* > mBuildables;

	UPROPERTY( ReplicatedUsing=OnRep_LightweightIndices )
	TArray< FBuildableClassLightweightIndices > mLightweightClassAndIndices;

	/** Cached reference to the blueprint descriptor. */
	UPROPERTY()
	class UFGBlueprintDescriptor* mBlueprintDescriptor;

	/** Bounding box of the blueprint. */
	UPROPERTY()
	class UBoxComponent* mBoundingBox;

private:
	friend class AFGBlueprintHologram;
	friend class AFGBlueprintSubsystem;
};
