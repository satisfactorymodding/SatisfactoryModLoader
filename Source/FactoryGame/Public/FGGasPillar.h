// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGDestructibleActor.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "FGExplosiveDestroyableInterface.h"
#include "FGGasPillarCloud.h"
#include "Interfaces/Interface_PostProcessVolume.h"
#include "FGGasPillar.generated.h"

class AFGGasPillarDesctructionActor;
UCLASS(Abstract)
class FACTORYGAME_API AFGGasPillar : public AFGDestructibleActor, public IFGSignificanceInterface, public IInterface_PostProcessVolume
{

	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFGGasPillar();

	// AActor
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void PostUnregisterAllComponents( void ) override;
	virtual void PostRegisterAllComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual float GetSignificanceRange() override;

	FORCEINLINE bool IsSignificant(){ return mIsSignificant; }

	/** Returns mesh component */
	UFUNCTION( BlueprintPure, Category = "Gas Pillar" )
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return mMesh; }

	virtual UStaticMeshComponent* GetStaticMeshComponent() override { return mMesh; };
	
	void RemoveGasComponents();
	void NotifyGasCloudOfRemoval();
	
	virtual void OnDestructibleFractured() override;
	virtual void OnDesctructibleDestroyed() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );
	
	//~ Begin IInterface_PostProcessVolume Interface
	virtual bool EncompassesPoint( FVector point, float sphereRadius = 0.f, float* out_distanceToPoint = nullptr ) override;
	virtual FPostProcessVolumeProperties GetProperties() const override;
#if DEBUG_POST_PROCESS_VOLUME_ENABLE
	virtual FString GetDebugName() const override;
#endif
	//~ End IInterface_PostProcessVolume Interface
	
	float GetEffectHeightOffset() const { return mEffectHeightOffset; }

#if WITH_EDITOR
	void SetNearbyGasCloud( class AFGGasPillarCloud* gasCloud )
	{
		// Remove the location from any cloud that may have already registered us
		if( mNearbyGasCloud && gasCloud != mNearbyGasCloud )
		{
			mNearbyGasCloud->NotifyGasPillarRemovedFromInfluence( this );
		}
		mNearbyGasCloud = gasCloud;
		MarkPackageDirty();
	}
#endif

protected:
	/** Mesh for the gas pillar */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|GasPillar" )
	class UStaticMeshComponent* mMesh;

	// Set by GasVolumes when they collect the pillars. Used as a quick reference when destroyed to easily notify nearby clouds without needing to do an expensive runtime overlap
	UPROPERTY( VisibleAnywhere, Category="FactoryGame|GasPillar" )
	TSoftObjectPtr< class AFGGasPillarCloud > mNearbyGasCloud;

	/** An offset for how high the clouds around the pillar should be spawned (so taller pillars can have better gas placement ) */
	UPROPERTY( EditDefaultsOnly, Category="FactoryGame|GasPillar"  )
	float mEffectHeightOffset = 300.f;

	/** Collision for when to activate dot component  */
	UPROPERTY( EditAnywhere, Category = "FactoryGame|GasPillar" )
	class USphereComponent* mOverlapCollision;

	/** The component that will do the damage to actors */
	UPROPERTY( EditAnywhere, Category = "FactoryGame|GasPillar" )
	class UFGDotComponent* mDotComponent;

	/** Some damage over time volumes will want a post process effect attached to it*/
	UPROPERTY( EditInstanceOnly, Category = "FactoryGame|GasPillar" )
	TSubclassOf<class UFGSharedPostProcessSettings> mPostProcessSettings;
	
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Significance" )
	float mSignificanceRange;

	/** Saved significance value */
	bool mIsSignificant;

	/** If weve been destroyed when dont need to manage our removed significance */
	bool mNeedRemoveSignificance = true;

	bool mPostIsEnabled = false;

};