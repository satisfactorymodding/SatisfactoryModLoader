// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGBuildableStorage.h"
#include "FGFactoryBlueprintTypes.h"
#include "FGPlayerController.h"
#include "ItemAmount.h"
#include "FGBuildableBlueprintDesigner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRecordDataChanged, FBlueprintRecord, blueprintRecord );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBlueprintCostChanged, const TArray< FItemAmount >&, cost );

UENUM( BlueprintType )
enum class EBlueprintDesignerLoadResult : uint8
{
	BDLR_Success							UMETA( DisplayName = "Success" ),
	BDLR_InvalidDescriptor					UMETA( DisplayName = "Invalid Descriptor" ),
	BDLR_CannotAfford						UMETA( DisplayName = "Cannot Afford" ),
	BDLR_MissingFile						UMETA( DisplayName = "Missing Blueprint File" ),
	BDLR_MissingRecipes						UMETA( DisplayName = "Missing Recipes"),
	BDLR_IncorrectDimensions				UMETA( DisplayName = "Incorrect Dimensions"),
	BDLR_Undefined							UMETA( DisplayName = "Undefined Failure")
};


/**
 * The core class for designing blueprints. Handles loading / saving existing blueprints
 */
UCLASS()
class FACTORYGAME_API AFGBuildableBlueprintDesigner : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableBlueprintDesigner();

	//Begin UObject Interface
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	//~End UObject Interface
	
	//Begin AActor Interface
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End AActor Interface
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	// Begin Dismantle Interface
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const override;
	virtual void GetDismantleDependencies_Implementation(TArray<AActor*>& out_dismantleDependencies) const override;
	virtual bool SupportsDismantleDisqualifiers_Implementation() const override { return true; }
	virtual void GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const override;
	// end Dismantle interface

	// Begin AFGBuildable interface
	virtual void RegisterInteractingPlayer_Implementation(AFGCharacterPlayer* player) override;
	// End AFGBuildable interface

	/** Draws the tiles for visualizing the Rectangular prism */
	static void BuildTiledMeshes( UInstancedStaticMeshComponent* tiledMeshComp, const FIntVector& dims );

	/** This shouldnt be used in the end as we should catch all added buildables when constructed */
	void GatherBuildables(TArray< AFGBuildable* >& out_Buildables );

	/** When a buildable is constructed it informs the designer of its existence. This way we don't need to gather them to serialize */
	void OnBuildableConstructedInsideDesigner( AFGBuildable* buildable ); 
	void OnBuildableDismantledInsideDesigner( AFGBuildable* buildable );

	/** Called when the buildable cost changes inside of the blueprint designer. Used to recompute the cost */
	void OnBuildableChangedInsideDesigner( AFGBuildable* buildable );

	/** Calculates the item amount of all buildables inside the blueprint designer (for reporting to UI) */
	void CalculateBlueprintCost( TArray<FItemAmount>& cost ) const;
	
	UFUNCTION( BlueprintCallable, Category="Blueprint Designer" )
	void SaveBlueprint( FBlueprintRecord blueprintRecord, AFGPlayerController* controller );

	/**
	 * Dismantles buildings inside the designer
	 * @param character - Optional. The player to potentially return dismantled items to (if null, interacting player array is used)
	 */
	UFUNCTION( BlueprintCallable, Category="Blueprint Designer" )
	void DismantleCurrentBuildables( AFGPlayerController* controller );

	/** Gets the refund amount for dismantling current buildables */
	void GetCurrentBuildablesDismantleRefund( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled );

	UFUNCTION( BlueprintCallable, Category="Blueprint Designer" )
	EBlueprintDesignerLoadResult LoadBlueprintIntoDesigner( UFGBlueprintDescriptor* blueprintDescriptor, AFGPlayerController* controller );

	UFUNCTION( BlueprintPure, Category="Blueprint Designer" )
	bool IsEdittingExistingBlueprint() { return mCurrentRecordData.IsValid(); }

	UFUNCTION( BlueprintPure, Category="Blueprint Designer" )
	FBlueprintRecord GetCurrentBlueprintRecord() { return mCurrentRecordData; }

	UFUNCTION( BlueprintPure, Category="Blueprint Designer" )
	FORCEINLINE UFGBlueprintDescriptor* GetCurrentDescriptor() { return mCurrentBlueprintDescriptor; }

	UFUNCTION( BlueprintPure, Category="Blueprint Designer" )
	FORCEINLINE class UBoxComponent* GetCollisionComponent() { return mCollisionComponent; }

	UFUNCTION( BlueprintPure, Category="Blueprint Designer" )
	FORCEINLINE FIntVector GetBlueprintDimensions() const { return mDimensions; }

	FVector GetBlueprintDesignerSize() const;
	
	/** Checks if a given buildable is placed along the edge of the designer. Checks both location and rotation */
	bool IsTransformOnPerimeterOfDesigner( const FTransform& trans ) const;
	
	bool IsLocationOnPerimeterOfDesigner( const FVector& location ) const;

	bool IsLocationInsideDesigner( const FVector& location ) const;
	
	// Gets the transform where loading/saving should occur in the designer
	void GetOffsetTransform( FTransform& out_transform ) const;

	/** For cost calculations use the interacting player */
	UFGInventoryComponent* GetInteractingPlayerInventory( );

	/** Can the desired blueprint be afforded? */
	bool CanAffordToLoad( UFGBlueprintDescriptor* blueprintDesc, UFGInventoryComponent* playerInv );

	/** A blueprint was loaded, remove the items from the inventories. Should only be done if we already determined it was able to be afforded */
	void RemoveCostToLoad( UFGBlueprintDescriptor* blueprintDescriptor, AFGCharacterPlayer* character );
	
	virtual void OnBuildEffectFinished() override;

	UFGInventoryComponent* GetStorageInventory() { return mStorage->GetStorageInventory(); }

	UFUNCTION()
	void OnRep_Storage();

	UFUNCTION( BlueprintCallable, Category="Blueprint Designer" )
	TArray< FItemAmount > GetItemCost( ) { return mCurrentCost; }

	void OnBuildingsChanged();

	void RecalculateBlueprintCost();
private:
	void GenerateIntersectionBoxes();
	
	UFUNCTION()
	void OnRep_Buildables();

	UFUNCTION()
	void OnRep_RecordData();
	
	UFUNCTION()
	void OnRep_CostChanged();
	
public:
	
	/** Collision Box */
	UPROPERTY( EditAnywhere, Category="Blueprint Designer")
	class UBoxComponent* mCollisionComponent;

	/** Design area box mesh. Should be a 1x1 cube, code will scale to match tile dimensions */
	UPROPERTY( EditAnywhere, Category="Blueprint Designer")
	UStaticMeshComponent* mDesignerBoxMesh;

	/** Colored Mesh Proxy for the Edit Terminal */
	UPROPERTY(EditDefaultsOnly, Category="Blueprint Designer")
	UFGColoredInstanceMeshProxy* mTerminalMesh;

	UPROPERTY(VisibleAnywhere, Category="Blueprint Designer")
	UInstancedStaticMeshComponent* mFloorMeshComponent;

	/** Location to place refunds if invs are full. @TODO This doesnt need to be a scene comp */
	UPROPERTY(VisibleAnywhere, Category="Blueprint Designer")
	USceneComponent* mRefundLocationComponent;
	
	/** Mesh to use for tiling along the floor (800x800x100)*/
	UPROPERTY( EditDefaultsOnly, Category="Blueprint Designer")
	UStaticMesh* mFloorMeshTile;
	
	/** Distance from the edge to place the terminal mesh */
	UPROPERTY( EditDefaultsOnly, Category="Blueprint Designer")
	float mTerminalDistanceFromEdge;

	UPROPERTY( EditDefaultsOnly, Category="Blueprint Designer")
	float mTerminalHalfDepth;
	
	/** Determines the size (in 800 unit increments) of the rectangular prism to encapsulate the area of the Designer */
	UPROPERTY( EditDefaultsOnly, Category="Blueprint Designer" )
	FIntVector mDimensions;

	// Delegate for UI to allow for easy updating of menu when loading a new blueprint
	UPROPERTY( BlueprintAssignable )
	FOnRecordDataChanged OnRecordDataChanged;

	UPROPERTY( BlueprintAssignable )
	FOnBlueprintCostChanged OnBlueprintCostChanged;

	UPROPERTY( EditDefaultsOnly, Category="Blueprint Designer")
	TSubclassOf< class UFGRecipe > mDefaultStorageRecipe;
	
	
private:
	friend class AFGBlueprintDesignerHologram;
	
	UPROPERTY( ReplicatedUsing=OnRep_CostChanged )
	TArray< FItemAmount > mCurrentCost;
	
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_Storage )
	AFGBuildableStorage* mStorage;
	
	/** Location to place refunds that dont fit in player or designer inventory */
	// @TODO This can just be a transform - Im super strapped on time and this is the fastest way for now
	UPROPERTY( EditDefaultsOnly, Category="Blueprint Designer")
	USceneComponent* mStorageLocation;
	
	/** Actors active in the designer (buildings present in the designer) */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_Buildables )
	TArray< class AFGBuildable* > mBuildables;

	/** The header data loaded or set on this designer */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_RecordData )
	FBlueprintRecord mCurrentRecordData;

	UPROPERTY()
	UFGBlueprintDescriptor* mCurrentBlueprintDescriptor;

	UPROPERTY()
	bool mIsDismantlingAll = false;
	
};



