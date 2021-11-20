// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "Buildables/FGBuildableFactoryBuilding.h"
#include "FGBuildableBeam.generated.h"

UCLASS()
class FACTORYGAME_API UFGBeamAttachmentPoint : public UFGAttachmentPointType
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableBeam : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
public:
	AFGBuildableBeam();

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End Actor interface

	// Begin AFGBuildable interface
	virtual void GetAttachmentPoints( TArray< const FFGAttachmentPoint* >& out_points ) const override;
	// End AFGBuildable interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface
	
	// Begin IFGDismantleInterface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	// End IFGDismantleInterface

	float GetSize() const { return mSize; }

	float GetDefaultLength() const { return mDefaultLength; }
	float GetMaxLength() const { return mMaxLength; }

	float GetLength() const { return mLength; }
	void SetLength( float NewLength );

protected:
	UFUNCTION()
	void OnRep_Length();

protected:
	/** Size of the beam. */
	UPROPERTY( EditDefaultsOnly, Category = "Beam" )
	float mSize;

	/** Default length of the beam. Used to properly scale the beam later. */
	UPROPERTY( EditDefaultsOnly, Category = "Beam" )
	float mDefaultLength;

	/** Max allowed length of the beam. */
	UPROPERTY( EditDefaultsOnly, Category = "Beam" )
	float mMaxLength;

	/** Length of the beam. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Length )
	float mLength;

private:
	FFGAttachmentPoint mFrontAttachmentPoint;
};
