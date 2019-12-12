// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#if WITH_EDITOR
#include "UnrealEdMisc.h"
#endif

#include "FGSaveInterface.h"
#include "FGExponentialHeightFog.h"
#include "GameFramework/WorldSettings.h"
#include "FGSubsystem.h"
#include "FGWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGWorldSettings : public AWorldSettings, public IFGSaveInterface
{
	GENERATED_BODY() 
public:
	/** Ctor */
	AFGWorldSettings();

	/** Getter for buildablesubsystem */
	FORCEINLINE class AFGBuildableSubsystem* GetBuildableSubsystem() const { return mBuildableSubsystem; }

	/** Get the foundation subsystem. */
	FORCEINLINE class AFGFoundationSubsystem* GetFoundationSubsystem() { return mFoundationSubsystem; }

	FORCEINLINE class AFGFoliageRemovalSubsystem* GetFoliageRemovalSubsystem() const { return mFoliageRemovalSubsystem; }

	// Begin UObject interface
	virtual void BeginDestroy() override;
	// End UObject interface

	// Begin AActor interface
#if WITH_EDITOR
	virtual void CheckForErrors() override;
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;
#endif
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void PreInitializeComponents() override;
	// End AActor interface
	
	// Begin AWorldSettings interface
	virtual void NotifyBeginPlay() override;
	// End AWorldSettings interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Get the exponential height fog for this map */
	FORCEINLINE class AExponentialHeightFog* GetExponentialHeightFog() const{ return mExponentialHeightFog; }

	/** Get the sky sphere for this map */
	FORCEINLINE class AFGSkySphere* GetSkySphere() const { return mSkySphere; }

	/** Get the event to post when we start the level */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Level|Audio" )
	FORCEINLINE class UAkAudioEvent* GetLevelStartedAkEvent() const{ return mLevelStartedEvent; }

	/** Save we will load by default when entering the map */
	FORCEINLINE FString GetDefaultSave() const{ return mDefaultLoadSave; }

	/** Get the default start time of the current time of day in hours */
	FORCEINLINE float GetStartingTimeOfDay() const{ return mStartTimeOfDay; }

	/** Get the default start time of the current time of day in hours */
	FORCEINLINE class AFGMinimapCaptureActor* GetMinimapCaptureActor() const{ return mMinimapCaptureActor; }

	/** Update the world bounds */
	UFUNCTION( Category="FactoryGame|Level", meta=(CallInEditor="true") )
	void UpdateWorldBounds();
protected:
	/** Called whenever a actor is spawned in editor */
	void OnActorSpawned( AActor* actor );

#if WITH_EDITOR
	void HandleMapChanged( class UWorld* newWorld, EMapChangeType mapChangeType );
#endif
private:
	/** Helper to spawn subsystems. */
	template< class C >
	void SpawnSubsystem( C*& out_spawnedSubsystem, TSubclassOf< AFGSubsystem > spawnClass, FName spawnName )
	{
		// @todo: Refactor, haxx as we didn't think about that there are several world infos in one world
		// Avoid spawning subsystems if not in a persistent level, as we never expected a level to not be persistent
		if( !GetLevel() || !GetLevel()->IsPersistentLevel() )
		{
			return;
		}

		if( out_spawnedSubsystem )
		{
			UE_LOG( LogGame, Error, TEXT( "AFGWorldSettings::SpawnSubsystem failed for '%s', already spawned or loaded." ), *spawnName.ToString() );
			return;
		}

		if( !spawnClass )
		{
			UE_LOG( LogGame, Error, TEXT( "AFGWorldSettings::SpawnSubsystem failed for '%s', no class given." ), *spawnName.ToString() );
			return;
		}

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Name = spawnName;

		out_spawnedSubsystem = GetWorld()->SpawnActor< C >( spawnClass, spawnParams );
		check( out_spawnedSubsystem );
	}
public:
	// @todo: Verify that this really is ALL volumes, if we stream one volume in, is it really added to the same array
	/** All the fog volumes currently streamed in, sorted in ascending order of priority. */
	UPROPERTY(transient)
	TArray< class AFGDynamicExponentialFogVolume* > mFogVolumes;

	// @todo: Verify that this really is ALL volumes, if we stream one volume in, is it really added to the same array
	/** All the ambient volumes currently streamed in */
	UPROPERTY( transient )
	TArray< class AFGAmbientVolume* > mAmbientVolumes;

	// @todo: Verify that this really is ALL volumes, if we stream one volume in, is it really added to the same array
	/** All the water volumes currently streamed in */
	UPROPERTY( transient )
	TArray< class AFGWaterVolume* > mWaterVolumes;

	/** The default settings of the exponential height fog to apply */
	UPROPERTY( EditInstanceOnly, Category = "HeightFog" )
	FExponentialFogSettings mDefaultHeightFogSettings;
protected:
	/** Set the height fog that's placed in the world here */
	UPROPERTY( EditInstanceOnly, Category = "HeightFog" )
	class AExponentialHeightFog* mExponentialHeightFog;

	/** Set the sky sphere that's placed in the world here */
	UPROPERTY( EditInstanceOnly, Category = "HeightFog" )
	class AFGSkySphere* mSkySphere;

	/** The minimap capture actor of this level, might be null */
	UPROPERTY( EditInstanceOnly, Category = "Minimap" )
	class AFGMinimapCaptureActor* mMinimapCaptureActor;

	/** Different events for different levels, so they can start different playlists */
	UPROPERTY( EditInstanceOnly, Category = "Audio" )
	class UAkAudioEvent* mLevelStartedEvent;

	/** Save game that we should load by default when entering the map */
	UPROPERTY( EditInstanceOnly, Category="Save" )
	FString mDefaultLoadSave;
	
	/** Time of day to start the day (in hours)*/
	UPROPERTY( EditInstanceOnly, Category = "Time", meta = ( UIMin = 0, UIMax = 24, ClampMin = 0, ClampMax = 24 ) )
	float mStartTimeOfDay;
private:
	UPROPERTY( SaveGame )
	class AFGBuildableSubsystem* mBuildableSubsystem;
	UPROPERTY( SaveGame )
	class AFGFoundationSubsystem* mFoundationSubsystem;
	UPROPERTY()
	class AFGAudioVolumeSubsystem* mAudioVolumeSubsystem;
	UPROPERTY()
	class AFGFoliageRemovalSubsystem* mFoliageRemovalSubsystem;

#if WITH_EDITORONLY_DATA
	/** Set the hour you want to preview here, 16.25 means 16h 15min */
	UPROPERTY( EditInstanceOnly, Category = "Time", meta = ( UIMin = 0, UIMax = 24, ClampMin = 0, ClampMax = 24 ) )
	float mPreviewHour;

	/** Used to get callbacks whenever a actor is spawned, so we can populate mExponentialHeightFog */
	FDelegateHandle mActorSpawnedDelegateHandle;

	/** For updateing time of day when map changes in editor */
	FDelegateHandle mOnMapChangedDelegateHandle;
#endif
};
