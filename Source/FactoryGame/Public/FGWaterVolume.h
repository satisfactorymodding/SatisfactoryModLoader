// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "UndefinedBool.h"
#include "Interfaces/Interface_PostProcessVolume.h"
#include "GameFramework/PhysicsVolume.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "NavAreas/NavArea.h"
#include "Resources/FGExtractableResourceInterface.h"
#include "FGSignificanceInterface.h"
#include "FGWaterVolume.generated.h"

/**
 * 
 */
UCLASS(HideCategories=(Collision))
class FACTORYGAME_API AFGWaterVolume : public APhysicsVolume, public IFGExtractableResourceInterface, public IInterface_PostProcessVolume, public INavRelevantInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	/** ctor */
	AFGWaterVolume();

	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;

	// Begin APhysicsVolume interface
	virtual bool IsOverlapInVolume( const class USceneComponent& testComponent ) const override;
	// End APhysicsVolume interface

	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual float GetSignificanceRange() override;
	//End

	/** Audio subsystem tells this water volume if the listener is inside */
	void SetCameraIsInside( bool cameraInside, FVector cameraLocation, class AFGPlayerController* PC );

	/** Get the audio settings for this water volume */
	const class UFGWaterAudio* GetAudioSettings() const;

	//~ Begin IInterface_PostProcessVolume Interface
	virtual bool EncompassesPoint( FVector point, float sphereRadius = 0.f, float* out_distanceToPoint = nullptr ) override;
	virtual FPostProcessVolumeProperties GetProperties() const override;
	//~ End IInterface_PostProcessVolume Interface

	//~ Begin AActor Interface
	virtual void PostUnregisterAllComponents( void ) override;
	virtual void PostRegisterAllComponents() override;
	//~ End AActor Interface

	//~ Begin NavInterface
	virtual void GetNavigationData( FNavigationRelevantData& Data ) const override;
	virtual FBox GetNavigationBounds() const override;
	virtual void RebuildNavigationData() override;
	//~ End NavInterface

	/** Getter for significance */
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant; }

	// Begin Extractable Resource Interface
	virtual void SetIsOccupied_Implementation( bool occupied ) override;
	virtual bool IsOccupied_Implementation() const override;
	virtual bool CanBecomeOccupied_Implementation() const override;
	virtual bool HasAnyResources_Implementation() const override;
	virtual TSubclassOf<class UFGResourceDescriptor> GetResourceClass_Implementation() const override;
	virtual int32 ExtractResource_Implementation( int32 amount ) override;
	virtual float GetExtractionSpeedMultiplier_Implementation() const override;
	virtual FVector GetPlacementLocation_Implementation( const FVector& hitLocation ) const override;
	virtual bool CanPlaceResourceExtractor_Implementation() const override;
	// End Extractable Resource Interface

#if WITH_EDITOR
	// Begin UObject interface
	virtual void PostLoad() override;
	virtual void PreSave( const class ITargetPlatform* targetPlatform ) override;
	virtual void PostEditChangeProperty( FPropertyChangedEvent& propertyChangedEvent ) override;
	// End UObject interface

	// Begin AActor interface
	virtual void CheckForErrors() override;
	// End AActor interface
#endif


protected:
	/** Called whenever a primitive component enters the water, used to create effects on the water surface */
	UFUNCTION()
	virtual void OnPrimitiveComponentEntered( UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult );
	
	/** Called whenever a primitive component exits the water, used to create effects on the water surface */
	UFUNCTION()
	virtual void OnPrimitiveComponentExited( UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex );

	/** Called when a pawn enters the water, uses mWaterAudio to create water splosh */
	void OnPawnEntered( APawn* pawn, const FHitResult& enterInfo );
	
	/** Called when a pawn exits the water */
	void OnPawnExited( APawn* pawn );
protected:
	/** Specify what typ of nav area blocker this is ( defaults to null )  */
	UPROPERTY( EditDefaultsOnly, Category = "Navigation" )
	TSubclassOf< UNavArea > mAreaClass;
	
	/** Audio settings for the this water volume */
	UPROPERTY( EditInstanceOnly, Category="Audio")
	TSubclassOf<class UFGWaterAudio> mWaterAudio;

	UPROPERTY( EditDefaultsOnly, Category="Resource" )
	bool mCanPlaceExtractor;

	/** A template of settings for our post process settings */
	UPROPERTY( EditInstanceOnly, Category = "PostProcess" )
	TSubclassOf<class UFGSharedPostProcessSettings> mPostProcessSettings;

#if WITH_EDITORONLY_DATA
	/** Old deprecated data that isn't used anymore, but we want to be sure that the post process volumes will be deleted */
	UPROPERTY()
	class APostProcessVolume* mAssociatedPostProcessVolume_DEPRECATED;
#endif

	/** If true, then the camera is inside the volume */
	bool mCameraIsInside;
private:
	/** Reference to the Water Descriptor specified in FGResourceSettings. Assigned in begin play */
	UPROPERTY()
	TSubclassOf< class UFGResourceDescriptor > mResourceClass;

	/** Is this volume in significance range */
	bool mIsSignificant;

	/** Significance range of water volume */
	float mSignificanceRange;


public:
	FORCEINLINE ~AFGWaterVolume() = default;
};
