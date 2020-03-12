// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "FGExplosiveDestroyableInterface.h"
#include "Interfaces/Interface_PostProcessVolume.h"
#include "FGGasPillar.generated.h"

UCLASS()
class FACTORYGAME_API AFGGasPillar : public AActor, public IFGSignificanceInterface, public IInterface_PostProcessVolume//, public IFGExplosiveDestroyableInterface, public IFGSaveInterface
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

	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual float GetSignificanceRange() override;

	FORCEINLINE bool IsSignificant(){ return mIsSignificant; }

	//~ Begin IInterface_PostProcessVolume Interface
	virtual bool EncompassesPoint( FVector point, float sphereRadius = 0.f, float* out_distanceToPoint = nullptr ) override;
	virtual FPostProcessVolumeProperties GetProperties() const override;
	//~ End IInterface_PostProcessVolume Interface
	
	/*
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	*/
protected:
	/** Mesh for the gas pillar */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|GasPillar" )
	class UStaticMeshComponent* mMesh;

	/** Collision for when to activate dot component  */
	UPROPERTY( EditAnywhere, Category = "FactoryGame|GasPillar" )
	class USphereComponent* mOverlapCollision;

	/** The component that will do the damage to actors */
	UPROPERTY( EditAnywhere, Category = "FactoryGame|GasPillar" )
	class UFGDotComponent* mDotComponent;

	/** Some damage over time volumes will want a post process effect attached to it*/
	UPROPERTY( EditInstanceOnly, Category = "FactoryGame|GasPillar" )
	TSubclassOf<class UFGSharedPostProcessSettings> mPostProcessSettings;
private:
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Significance" )
	float mSignificanceRange;

	/** Saved significance value */
	bool mIsSignificant;

public:
	FORCEINLINE ~AFGGasPillar() = default;
};