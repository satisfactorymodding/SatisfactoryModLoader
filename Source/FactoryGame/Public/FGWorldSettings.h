// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSaveInterface.h"
#include "FGAtmosphereVolume.h"
#include "GameFramework/WorldSettings.h"
#include "FWPSaveDataMigrationContext.h"
#include "FactoryGame.h"
#include "Engine/Level.h"

#if WITH_EDITOR
#include "UnrealEdMisc.h"
#endif

#include "FGWorldSettings.generated.h"

class AFGTimeOfDaySubsystem;

UCLASS()
class FACTORYGAME_API AFGWorldSettings : public AWorldSettings, public IFGSaveInterface
{
	GENERATED_BODY() 
public:
	/** Ctor */
	AFGWorldSettings();

	/** Getters for the subsystems */
	FORCEINLINE class AFGBuildableSubsystem* GetBuildableSubsystem() const { return mBuildableSubsystem; }
	FORCEINLINE class AFGLightweightBuildableSubsystem* GetLightweightBuildableSubsystem() const { return mLightweightBuildableSubsystem; }
	FORCEINLINE class AFGFoliageRemovalSubsystem* GetFoliageRemovalSubsystem() const { return mFoliageRemovalSubsystem; }
	FORCEINLINE class AFGConveyorItemSubsystem* GetConveyorItemSubsystem() const { return mConveyorItemSubsystem; }
	FORCEINLINE class AFGPhotoModeManager* GetPhotoModeManager() const { return mPhotoModeManager; }
	FORCEINLINE AFGTimeOfDaySubsystem* GetTimeOfDaySubsystem() const { return mTimeOfDaySubsystem; }

	// Begin UObject interface
	virtual void BeginDestroy() override;
	// Magic GC function, if it exists, it will be called by the GC
	virtual void Serialize( FArchive& ar ) override;
	// End UObject interface

	// Begin AActor interface
#if WITH_EDITOR
	virtual void CheckForErrors() override;
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;
#endif
	
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
	class AExponentialHeightFog* GetExponentialHeightFog() const;

	/** Get the sky atmosphere actor, if one is loaded in the map */
	class ASkyAtmosphere* GetSkyAtmosphere() const; 

	/** Get the sky sphere for this map */
	class AFGSkySphere* GetSkySphere() const;

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

	/** Renames the time subsystem to have a correct name (TimeSubsystem) */
	UFUNCTION( Category="FactoryGame|Level", meta=(CallInEditor="true") )
	void RenameTimeSubsystem();
protected:

#if WITH_EDITOR
	void HandleMapChanged( class UWorld* newWorld, EMapChangeType mapChangeType );
#endif
private:
	/** Helper to spawn subsystems. */
	template< class C >
	void SpawnSubsystem( C*& out_spawnedSubsystem, TSubclassOf< AInfo > spawnClass, FName spawnName )
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
		fgcheck( out_spawnedSubsystem );
	}
public:
	// @todo: Verify that this really is ALL volumes, if we stream one volume in, is it really added to the same array
	/** All the fog volumes currently streamed in, sorted in ascending order of priority. */
	UPROPERTY(transient)
	TArray< class AFGAtmosphereVolume* > mFogVolumes;

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

#if WITH_EDITORONLY_DATA	
	/** This is the grid name that all InstancedFoliageActors will be placed on. Only used with world partition. */
	UPROPERTY(EditInstanceOnly, Category = "Foliage")
	FName mFoliageRuntimeGrid;
#endif

#if WITH_EDITOR
	void SetFoliageRemovalSubsystem(AFGFoliageRemovalSubsystem* foliageRemovalSubsystem)
	{
		mFoliageRemovalSubsystem = foliageRemovalSubsystem;
		Modify();
	}
#endif
	
	UPROPERTY( VisibleAnywhere )
	FWorldPartitionValidationData SaveGameValidationData;

	UPROPERTY( VisibleAnywhere )
	TMap<FString, FWPCellIdentifier> WPActorCellMapping;
	
protected:
	/** Set the height fog that's placed in the world here */
	UPROPERTY( EditInstanceOnly, Category = "HeightFog" )
	TSoftObjectPtr< class AExponentialHeightFog > mExponentialHeightFog;

	UPROPERTY( EditInstanceOnly, Category = "HeightFog" )
	TSoftObjectPtr< class ASkyAtmosphere > mSkyAtmosphere = nullptr;

	/** Set the sky sphere that's placed in the world here */
	UPROPERTY( EditInstanceOnly, Category = "HeightFog" )
	TSoftObjectPtr< class AFGSkySphere > mSkySphere = nullptr;

	/** The minimap capture actor of this level, might be null */
	UPROPERTY( EditInstanceOnly, Category = "Minimap" )
	class AFGMinimapCaptureActor* mMinimapCaptureActor;

	/** Time of day subsystem that should be placed into the map */
	UPROPERTY( EditInstanceOnly, Category = "Time" )
	AFGTimeOfDaySubsystem* mTimeOfDaySubsystem;

	/** Different events for different levels, so they can start different playlists */
	UPROPERTY( EditInstanceOnly, Category = "Audio" )
	class UAkAudioEvent* mLevelStartedEvent;

	/** Save game that we should load by default when entering the map */
	UPROPERTY( EditInstanceOnly, Category="Save" )
	FString mDefaultLoadSave;
	
	/** Time of day to start the day (in hours) */
	UPROPERTY( EditInstanceOnly, Category = "Time", meta = ( UIMin = 0, UIMax = 24, ClampMin = 0, ClampMax = 24 ) )
	float mStartTimeOfDay;


private:
	UPROPERTY( SaveGame )
	class AFGBuildableSubsystem* mBuildableSubsystem;

	UPROPERTY( SaveGame )
	class AFGLightweightBuildableSubsystem* mLightweightBuildableSubsystem;

	UPROPERTY()
	class AFGAudioVolumeSubsystem* mAudioVolumeSubsystem;
	UPROPERTY()
	class AFGFoliageRemovalSubsystem* mFoliageRemovalSubsystem;

	UPROPERTY()
	class AFGConveyorItemSubsystem* mConveyorItemSubsystem;
	UPROPERTY()
	class AFGPhotoModeManager* mPhotoModeManager;

#if WITH_EDITORONLY_DATA
	/** Set the hour you want to preview here, 16.25 means 16h 15min */
	UPROPERTY( EditInstanceOnly, Category = "Time", meta = ( UIMin = 0, UIMax = 24, ClampMin = 0, ClampMax = 24 ) )
	float mPreviewHour;

	/** Used to get callbacks whenever a actor is spawned, so we can populate mExponentialHeightFog */
	FDelegateHandle mActorSpawnedDelegateHandle;

	/** For updating time of day when map changes in editor */
	FDelegateHandle mOnMapChangedDelegateHandle;
#endif
};
