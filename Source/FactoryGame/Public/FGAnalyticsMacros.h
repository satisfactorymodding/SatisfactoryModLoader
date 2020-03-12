#pragma once
#include "UnrealString.h"

/** StatHat */
//////////////////////////////////////////////////////////////////////////

/** Dynamic Stat keys, these require some form dynamic data value  */
//#define ANAL_SCHEMATIC_UNLOCK(__INSTANCE__) FString::Printf(TEXT("Schematic_Purchase.%s"), __INSTANCE__)
//#define ANAL_SPAWN_BUILDABLE_NAME(__INSTANCE__) FString::Printf(TEXT("BldFactory_Spawn.%s"), __INSTANCE__)

/** Unique static stat keys */
#define ANAL_BUILDABLE TEXT("AllBuildable_Spawn")
#define ANAL_SCHEMATIC_UNLOCK TEXT("Schematic_Purchase")
#define ANAL_RESEARCH_CLAIM TEXT("MAMResearch_Claim")
#define ANAL_RESEARCH_DISCOVERED TEXT("MAMResearch_DiscoveredTime")

#define ANAL_NEW_GAME_TOTAL TEXT("NewGame_Started.Total")
#define ANAL_PLAY_DURATION TEXT("PlayDuration")
#define ANAL_TOTAL_PLAY_DURATION_TOTAL TEXT("Total")
#define ANAL_TOTAL_PLAY_DURATION_SESSION TEXT("Session")


/** Google Analytics */
//////////////////////////////////////////////////////////////////////////

#define ANAL_PAGE_INTERACT "/interact-widget/"
#define ANAL_HEARTBEAT "/heartbeat/"

// Real-Time sessions time out after ~5 minutes on google analytics
#define ANAL_HEARTBEAT_INTERVAL 5.f * 60.f
