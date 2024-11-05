// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSubsystem.h"
#include "Engine/DeveloperSettings.h"
#include "FGSubsystemClasses.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Subsystem Classes" ) )
class FACTORYGAME_API UFGSubsystemClasses : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UFGSubsystemClasses();
	
	static const UFGSubsystemClasses* Get() { return GetDefault<UFGSubsystemClasses>(); };
	
	/** Subsystem to handle narrative messages in the game */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr<class AFGStorySubsystem> mStorySubsystemClass;
	/** Subsystem to handle time of day. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGTimeOfDaySubsystem > mTimeSubsystemClass;
	/** Subsystem that handles the rail network, signals and all the trains in the game. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGRailroadSubsystem > mRailroadSubsystemClass;
	/** Subsystem that handles all the circuit simulations in the game, e.g. power grid. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGCircuitSubsystem > mCircuitSubsystemClass;
	/** Subsystem to handle all schematics and recipes in the game. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGSchematicManager > mSchematicManagerClass;
	/** Subsystem to handle the game phase. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGGamePhaseManager > mGamePhaseManagerClass;
	/** Subsystem to handle all research (M.A.M.) done in the game */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGResearchManager > mResearchManagerClass;
	/** Subsystem to handle the tutorial. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGTutorialIntroManager > mTutorialIntroManagerClass;
	/** Subsystem that handles radioactivity in the world. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGRadioactivitySubsystem > mRadioactivitySubsystemClass;
	/** Subsystem that handles the chat messages. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGChatManager > mChatManagerClass;
	/** Subsystem that handles the central storage. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGCentralStorageSubsystem > mCentralStorageSubsystemClass;
	/** Subsystem that handles the map */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGMapManager > mMapManagerClass;
	/** Subsystem to manage all the buildables in the game. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGBuildableSubsystem > mBuildableSubsystemClass;
	/** Subsystem to manage all the lightweight buildables in the game (Foundations, Walls). */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGLightweightBuildableSubsystem > mLightweightBuildableSubsystemClass;
	/** Subsystem used to remove foliage on the map. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGFoliageRemovalSubsystem > mFoliageRemovalSubsystemClass;
	/** Subsystem used to show effects near the player. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGProximitySubsystem > mProximitySubsystemClass;
	/** Subsystem responsible for handling unlocks */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGUnlockSubsystem > mUnlockSubsystem;
	/** Subsystem that handles the resource sink system */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGResourceSinkSubsystem > mResourceSinkSubsystemClass;
	/** Handles administration task of servers */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGAdminInterface > mAdminInterfaceClass;
	/** Handles regrowth of item pickups */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGItemRegrowSubsystem > mItemRegrowSubsystemClass;
	/** Handles all vehicles */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGVehicleSubsystem > mVehicleSubsystemClass;
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGEventSubsystem> mEventSubsystemClass;
	/** Handles world grid and data for those cells */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGWorldGridSubsystem > mWorldGridSubsystemClass;
	/** Handles all drone stations */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGDroneSubsystem > mDroneSubsystemClass;
	/* Handles instance updating for conveyor items. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGConveyorItemSubsystem > mConveyorItemSubsystemClass;
	/** Handles statistics of the game. Number of buildings built */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGStatisticsSubsystem > mStatisticsSubsystemClass;
	/** Handles sign data replication */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGSignSubsystem > mSignSubsystemClass;
	/** Handles actions relevant for photo mode, Camera adjustments, Simple sequences etc. */ 
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGPhotoModeManager > mPhotoModeManagerClass;
	/** Handles everything related to creatures. */ 
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGCreatureSubsystem > mCreatureSubsystemClass;
	/** Helps scanning of objects */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGScannableSubsystem > mScannableSubsystemClass;
	/** Responsible for Blueprint related functionality (in game blueprints, ie. templated buildings )*/
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGBlueprintSubsystem > mBlueprintSubsystem;
	UPROPERTY( Config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGIconDatabaseSubsystem > mIconDatabaseSubsystem;
	UPROPERTY( Config, EditDefaultsOnly, Category = "Subsystem" )
	TSoftClassPtr< class AFGWorldEventSubsystem > mWorldEventSubsystem;
};

