// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AudioEventsCache.h"
#include "FGSubsystem.h"
#include "Wwise/API/WwiseSoundEngineAPI.h"
#include "FGRainAudioSubsystem.generated.h"

struct RainPropInfo
{
	FVector Location;
	TWeakObjectPtr< UPhysicalMaterial > PhysMaterial;
	TObjectPtr< class UAkComponent > AkComponent;
	TObjectPtr< class UAkSwitchValue > MaterialSwitchValue;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPlayerUnderRainStateUpdated, bool, NewState );

UCLASS( config = Game, Blueprintable, defaultconfig, meta = ( DisplayName = "Rain Audio Subsystem" ) )
class FACTORYGAME_API AFGRainAudioSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFGRainAudioSubsystem();

	static AFGRainAudioSubsystem* Get( class UWorld* world );

	/** Get the rain audio subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Audio", DisplayName = "GetRainAudioSubsystem",
		meta = ( DefaultToSelf = "WorldContext" ) )
	static AFGRainAudioSubsystem* Get( UObject* worldContext );
	
	UFUNCTION(BlueprintCallable, Category = "Audio Rain | Common")
	bool IsRainAudioActive() const { return bIsRainAudioEnabled; }

	UPROPERTY(BlueprintAssignable, Category = "Audio Rain | Common")
	FOnPlayerUnderRainStateUpdated OnPlayerUnderRainStateUpdated;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	void TickRainBuildingSpots();
	void TickRainFoliageSpots();
	void TickRainGroundSpots();
	void TickMaterialTypeRTPC();
	void TickIsInsideRainRTPC();
	void FillNewRainSpots( TArray< FVector >& RainSpotsCandidates, TArray< RainPropInfo >& RainProps, float AttenuationDistance );

	void DisplayDebugSpots();

	//called whenever buildings or foliage are spawned or destroyed
	UFUNCTION()
	void OnBuildingAddedRemoved( AFGBuildable* buildable );

	UFUNCTION()
	void OnFoliageInstanceRemoved();

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	UFUNCTION( BlueprintCallable, Category = "Audio Rain" )
	void EnableRainAudio();

	UFUNCTION( BlueprintCallable, Category = "Audio Rain" )
	void DisableRainAudio();

	void CreateEmitters();
	void DestroyEmitters();

	void UpdatePlayerUnderRainState();

	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Buildings" )
	TSoftObjectPtr< class UAkAudioEvent > mBuildingsRainEvent = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Buildings" )
	int32 mBuildingsSpotsCount{ 3 };

	//Search radius for buildings rain spots
	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Buildings" )
	int32 mBuildingsMaxDistance{ 2000 };

	//Height of the emitter. 1.0f - bounding box height, 0.0f - ground level
	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Buildings" )
	float mBuildingEmitterHeightRatio{ 0.2f };

	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Foliage" )
	TSoftObjectPtr< class UAkAudioEvent > mFoliageRainEvent = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Foliage" )
	int32 mFoliageSpotsCount{ 3 };

	//Search radius for foliage rain spots
	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Foliage" )
	int32 mFoliageMaxDistance{ 1000 };

	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Ground" )
	TSoftObjectPtr< class UAkAudioEvent > mGroundRainEvent = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Ground" )
	int32 mGroundSpotsCount{ 2 };

	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Common" )
	TObjectPtr< class UAkRtpc > mIsInsideRain = nullptr;
	
	//Distance to filter spots between each other to prevent overlapping sounds
	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Common" )
	int32 mSpotFilteringDistance = 300;

	//Time in seconds between rain spots spawning
	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Common" )
	float mTimeBetweenRainSpots = 2.f;

	//Material type to AK state value mapping
	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Common" )
	TMap< TSoftObjectPtr< UPhysicalMaterial >, TObjectPtr< class UAkStateValue > > mMaterialTypeToAkStateMap;

	//Default ak state value to set when no material type is found
	UPROPERTY( EditDefaultsOnly, Category = "Audio Rain | Common" )
	TObjectPtr< class UAkStateValue > mDefaultMaterialTypeState = nullptr;

protected:
	// Material type
	TWeakObjectPtr< UPhysicalMaterial > MostHitMaterial;

	AkUInt32 MaterialStateGroupLacMaterialRain { 0 };

	UPROPERTY()
	TObjectPtr< UAkStateValue > MostHitMaterialState{ nullptr };

	FVector mCurrentLocation{ FVector::ZeroVector };

	TArray< RainPropInfo > RainBuildingProps;
	TArray< RainPropInfo > RainFoliageProps;
	TArray< RainPropInfo > RainGroundProps;
	
	FAudioEventsCache mAudioEventsCache;

	double mLastRainSpotsChangeTime{ 0.0 };
	float mPrevIsInsideRain{ -1.0f };

	bool ForceRefreshRainSpots{ false };
	bool bIsRainAudioEnabled{ false };

	bool bIsPlayerUnderRain = false;
};
