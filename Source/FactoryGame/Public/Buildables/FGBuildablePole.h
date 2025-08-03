// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildable.h"
#include "FGBuildablePoleBase.h"
#include "FGBuildablePole.generated.h"

USTRUCT( BlueprintType )
struct FPoleVariation
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* StaticMesh;
	
	UPROPERTY( EditDefaultsOnly )
	float Height;

	UPROPERTY( EditDefaultsOnly )
	FFGClearanceData Clearance;
};

/**
 * An arbitrarily high pole.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePole : public AFGBuildablePoleBase
{
	GENERATED_BODY()
public:
	AFGBuildablePole();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End AActor interface

	// Begin AFGBuildable interface
	virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;
	// End AFGBuildable interface
	
	/** Set the pole's height. */
	void SetPoleHeight( float height );

	/** Sets the connection component to be at correct height and registers */
	virtual void SetupConnectionComponent();

	const TArray< FPoleVariation >& GetPoleVariations() const { return mPoleVariations; }
	
	const FPoleVariation* GetBestPoleVariationForHeight( float inHeight ) const;
	int32 GetBestPoleVariationIndexForHeight( float inHeight ) const;

	/* We only have to check mCanContainLightweightInstances for poles, the instance data is made dynamically. */
	bool virtual DoesContainLightweightInstances_Native() const override { return mCanContainLightweightInstances && mPoleVariations.Num() > 0; }
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() const override;

	/** This poles height. */
	UPROPERTY( SaveGame, Replicated )
	float mHeight;

	/** DEPRECATED: This supports length. Pipe poles used to inherit from a different class in 1.0 which had a different name for the height variable. This is here for save migration purposes. */
	UPROPERTY( SaveGame )
	float mLength_DEPRECATED;

	/** Connection component for this pole. */
	UPROPERTY( VisibleAnywhere, Category = "Pole" )
	class UFGConnectionComponent* mSnapOnly0;

	/** Which pole variation index to use */
	UPROPERTY( Replicated, SaveGame )
	int8 mSelectedPoleVersion;
	
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	TArray< FPoleVariation > mPoleVariations;

protected:
#if WITH_EDITORONLY_DATA
	/** Uses the specified variation index when visualizing the pole in the blueprint editor. */
	UPROPERTY( EditDefaultsOnly, Transient, NonTransactional, SkipSerialization, Category = "Pole", DisplayName = "Pole Visualization Index Override (Editor-Only)" )
	int32 mPoleVariationVisualizationOverride;
#endif
};

/**
 * Same as AFGBuildablePole, but we disable replication for customization data
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePole_NoCustomization : public AFGBuildablePole
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
};
