// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGBuildableHologram.h"
#include "Buildables/FGBuildableFactoryBuilding.h"

#include "FGFactoryBuildingHologram.generated.h"

UENUM( Blueprintable, Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EHologramZoopDirections : uint8
{
	HZD_None		= 0			UMETA( displayName = "None" ),
	HZD_Forward		= 1 << 0	UMETA( displayName = "Forward" ),
	HZD_Backward	= 1 << 1	UMETA( displayName = "Backward" ),
	HZD_Left		= 1 << 2	UMETA( displayName = "Left" ),
	HZD_Right		= 1 << 3	UMETA( displayName = "Right" ),
	HZD_Up			= 1 << 4	UMETA( displayName = "Up" ),
	HZD_Down		= 1 << 5	UMETA( displayName = "Down" )
};

UENUM()
enum class EFactoryBuildingHologramBuildStep : uint8
{
	FBHBS_PlacementAndRotation,
	FBHBS_Zoop
};

UENUM()
enum class EFactoryBuildingPlacementRequirements : uint8
{
	FBPR_None			UMETA( displayName = "None" ),
	FBPR_MustSnap		UMETA( displayName = "Must Snap" )
};

UCLASS()
class FACTORYGAME_API AFGFactoryBuildingHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
	
public:
	AFGFactoryBuildingHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* Construct( TArray<AActor*>& out_children, FNetConstructionID constructionID ) override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual void GetSupportedBuildModes_Implementation( TArray<TSubclassOf<UFGHologramBuildModeDescriptor>>& out_buildmodes ) const override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual void OnBuildModeChanged() override;
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual bool CanBeZooped() const override;
	// End AFGHologram interface
	
	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	// End FGConstructionMessageInterface

	virtual void OnPendingConstructionHologramCreated_Implementation( AFGHologram* fromHologram ) override;

protected:
	// Begin AFGBuildableHologram interface
	virtual void CheckValidFloor() override;
	// End AFGBuildableHologram interface

	/**
	 * Get the direction of the edge facing towards us.
	 * A floor is a square with four edges, it has a location and a rotation.
	 *
	 * @param floorLoc - Center of the floor.
	 * @param floorRot - Rotation of the floor.
	 * @param testLoc - Location to test for a facing edge.
	 * @param excludeEdges - Edges to not consider. (Top and bottom is ignored)
	 *
	 * @return Edge direction facing testLoc and facing away from floorLoc.
	 */
	FVector GetFloorEdgeDirection( const FVector& floorLoc, const FRotator& floorRot, const FVector& testLoc, FFoundationSideSelectionFlags excludeEdges = FFoundationSideSelectionFlags::NoEdges ) const;

	/**
	 * Get the offset along the the floors edge.
	 * A floor is a square with four edges, it has a location and a rotation.
	 * @note Assumes that testSize is a multiple of floorSize.
	 *
	 * @param floorLoc - Center of the floor.
	 * @param floorRot - Rotation of the floor.
	 * @param floorSize - Width of the floor.
	 * @param testLoc - Location to test for a facing edge.
	 * @param testSize - Width of the tested object.
	 *
	 * @return Offset from the center of the floors width.
	 */
	FVector GetFloorEdgeOffset( const FVector& floorLoc, const FRotator& floorRot, float floorSize, const FVector& testLoc, float testSize, FFoundationSideSelectionFlags excludeEdges = FFoundationSideSelectionFlags::NoEdges ) const;

	/**
	 * Get the direction of the side of a wall facing towards us.
	 *
	 * @param wallLoc - Bottom center of the wall.
	 * @param wallRot - Rotation of the wall.
	 * @param testLoc - Location to test to get the facing direction to.
	 *
	 * @return Direction of the side facing testLoc.
	 */
	FVector GetWallEdgeDirection( const class AFGBuildableWall* wall, const FVector& testLoc ) const;

	virtual void UpdateZoop();
	virtual void ConstructZoop( TArray<AActor*>& out_children );
	
	virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const;

	void ClearZoopInstances();
	void GenerateZoopInstance( const FTransform& instanceTransform );

	/** Construct one instance of the buildable. */
	AActor* ConstructInstance( TArray<AActor*>& out_children, FNetConstructionID constructionID );

	void SetZoopAmount( const FIntVector& Zoop );

	/** Clamps the desired zoop to be within max zoop range. */
	void ApplyMaxZoopClamp( FIntVector& Zoop );

	void BlockZoopDirectionsBasedOnSnapDirection( const FVector& worldSpaceSnapDirection );
	
	UFUNCTION()
	void OnRep_DesiredZoop();

protected:
	/** Instanced Mesh Components. Used for zooping. */
	UPROPERTY()
	TMap< UStaticMeshComponent*, class UInstancedStaticMeshComponent* > mInstancedMeshComponents;

	/** What kind of placement requirements this hologram has. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	EFactoryBuildingPlacementRequirements mPlacementRequirements;
	
	/** Zoop amount. In what local space directions to extend the building and by how much. */
	UPROPERTY( ReplicatedUsing = OnRep_DesiredZoop )
	FIntVector mDesiredZoop;

	/** Max zoop amount in each local space direction. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram", meta=(UIMin=0, ClampMin=0) )
	int32 mMaxZoopAmount;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram", meta=(Bitmask,BitmaskEnum="EHologramZoopDirections"))
	uint8 mDefaultBlockedZoopDirections;
	
	uint8 mBlockedZoopDirectionMask;

	UPROPERTY( Replicated )
	EFactoryBuildingHologramBuildStep mBuildStep;
	
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeZoop;
};
