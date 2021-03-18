// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableLadder.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableLadder : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableLadder();

public:

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor Interface

	// Begin Buildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	// End Buildable interface

	/** Gets the height of the ladder. */
	UFUNCTION( BlueprintPure )
	float GetLadderHeight() const { return mMeshHeight * mNumSegments; }

	/** Gets the width of the ladder. */
	UFUNCTION( BlueprintPure )
	float GetLadderWidth() const { return mWidth; }

	/** Gets the height of one segment of the ladder. */
	UFUNCTION( BlueprintPure )
	float GetLadderMeshHeight() const { return mMeshHeight; }

	/** Gets the max number of segments the ladder can consist of. */
	UFUNCTION( BlueprintPure )
	int32 GetMaxLadderSegmentCount() const { return mMaxSegmentCount; }

	UStaticMesh* GetLadderSegmentMesh() const { return mLadderSegmentMesh; }

	/** Sets the amount of segments the ladder consists of. */
	void SetNumSegments( int32 Num, bool ForceUpdate = false );

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

private:
	UFUNCTION()
	void OnRep_NumSegments();

protected:

	/** Width of the ladder */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	float mWidth;

	/** Height of one segment of the ladder. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	float mMeshHeight;

	/** Mesh used for each segment of the ladder. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	UStaticMesh* mLadderSegmentMesh;

	/** Maximum number of segments for the ladder. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	int32 mMaxSegmentCount;

	/** Number of segments the ladder extends past the first one. */
	UPROPERTY( VisibleAnywhere, SaveGame, ReplicatedUsing = OnRep_NumSegments, Category = "Ladder" )
	int32 mNumSegments;

	/** Instanced Mesh Component. */
	UPROPERTY( VisibleAnywhere )
	TArray< UStaticMeshComponent* > mLadderMeshes;

	/** Clearance Box */
	UPROPERTY( VisibleAnywhere )
	class UBoxComponent* mClearanceBox;

	/** Ladder component on the front. */
	UPROPERTY( VisibleAnywhere )
	class UFGLadderComponent* mFrontLadderComponent;

	/** Ladder component on the back. */
	UPROPERTY( VisibleAnywhere )
	class UFGLadderComponent* mBackLadderComponent;
};