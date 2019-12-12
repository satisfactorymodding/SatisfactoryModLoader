// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSettings.h"
#include "FGSubsystemClasses.generated.h"

/**
 * All subsystems
 */
UCLASS( abstract, Config=Game )
class FACTORYGAME_API UFGSubsystemClasses : public UFGSettings
{
	GENERATED_BODY()
public:
	static UFGSubsystemClasses* Get();
public:
	/** The collection containing the world bounds*/
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf<class AFGStorySubsystem> mStorySubsystemClass;

	/** Subsystem to handle time of day. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGTimeOfDaySubsystem > mTimeSubsystemClass;
	/** Subsystem that handles the rail network, signals and all the trains in the game. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGRailroadSubsystem > mRailroadSubsystemClass;
	/** Subsystem that handles all the circuit simulations in the game, e.g. power grid. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGCircuitSubsystem > mCircuitSubsystemClass;
	/** Subsystem to handle all schematics and recipes in the game. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGSchematicManager > mSchematicManagerClass;
	/** Subsystem to handle the game phase. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGGamePhaseManager > mGamePhaseManagerClass;
	/** Subsystem to handle all research (M.A.M.) done in the game */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGResearchManager > mResearchManagerClass;
	/** Subsystem to handle the tutorial. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGTutorialIntroManager > mTutorialIntroManagerClass;
	/** Subsystem that handles radioactivity in the world. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGRadioactivitySubsystem > mRadioactivitySubsystemClass;
	/** Subsystem that handles the chat messages. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGChatManager > mChatManagerClass;
	/** Subsystem that handles the central storage. */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGCentralStorageSubsystem > mCentralStorageSubsystemClass;
	/** Subsystem that handles the map */
	UPROPERTY( EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGMapManager > mMapManagerClass;
	/** Subsystem to manage all the buildables in the game. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGBuildableSubsystem > mBuildableSubsystemClass;
	/** Subsystem used to remove foliage on the map. */
	UPROPERTY( config, EditDefaultsOnly, Category = "Subsystem" )
	TSubclassOf< class AFGFoliageRemovalSubsystem > mFoliageRemovalSubsystemClass;
};
