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

USTRUCT()
struct FACTORYGAME_API FBuildableBeamLightweightData
{
	GENERATED_BODY()
	
	/** Length of the beam in meters */
	UPROPERTY(SaveGame)
	float BeamLength{0.0f};
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableBeam : public AFGBuildableFactoryBuildingLightweight
{
	GENERATED_BODY()
public:
	AFGBuildableBeam(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End Actor interface

	// Begin AFGBuildable interface
	virtual void GetAttachmentPoints( TArray< const FFGAttachmentPoint* >& out_points ) const override;
	virtual TArray<FInstanceData> GetActorLightweightInstanceData_Implementation() const override;
	virtual void CreateLightweightBuildableInstanceData(const struct FFGDynamicStruct& typeSpecificData, TArray<FInstanceData>& outLightweightInstanceData) const override;
	virtual FFGDynamicStruct GetLightweightTypeSpecificData() const override;
	virtual void ApplyLightweightTypeSpecificData(const struct FFGDynamicStruct& typeSpecificData) override;
	// End AFGBuildable interface
	
	// Begin IFGDismantleInterface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	virtual int32 GetDismantleRefundReturnsMultiplierForLightweight(const FFGDynamicStruct& typeSpecificData) const override;
	// End IFGDismantleInterface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	float GetSize() const { return mSize; }
	float GetDefaultLength() const { return mDefaultLength; }
	float GetMaxLength() const { return mMaxLength; }
	FORCEINLINE bool IsMeshTiled() const { return bTiledMesh; }

	float GetLength() const { return mLength; }
	void SetLength( float NewLength );
protected:
	/** Returns the dismantle returns multiplier based on the beam length */
	int32 GetDismantleReturnsMultiplierForBeam( float beamLength ) const;
	/** Populates the instance data for the beam */
	void PopulateBeamInstanceData( float beamLength, TArray<FInstanceData>& outInstanceData ) const;
	
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
	UPROPERTY( SaveGame, Replicated )
	float mLength;

	UPROPERTY( EditDefaultsOnly, Category = "Beam" )
	bool bTiledMesh = false;
private:
	FFGAttachmentPoint mFrontAttachmentPoint;
};
