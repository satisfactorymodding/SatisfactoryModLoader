// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once


#include "CoreTypes.h"
#include "UObject/NameTypes.h"
#include "Logging/LogMacros.h"
#include "Stats/Stats.h"
#include "UObject/ReflectedTypeAccessors.h"

DECLARE_STATS_GROUP( TEXT( "FactoryQuick" ), STATGROUP_FactoryQuick, STATCAT_Advanced );

#define FACTORY_QUICK_SCOPE_CYCLE_COUNTER(Stat) \
DECLARE_SCOPE_CYCLE_COUNTER(TEXT(#Stat),Stat,STATGROUP_FactoryQuick)

enum ECollisionChannel : int32;

// Defines for custom Ak GameObject IDs, kept in one place for organization purposes
// Any IDs below CUSTOM_GAMEOBJ_MAX (0x400 currently) are valid to be used here
#define AK_CUSTOM_GAME_OBJECT_MUSIC_MANAGER ((AkGameObjectID) 0x10)

// Allows using the name of the current function in the UE_LOG macro as it automatically converts it to TCHARs
#define FUNCTION_STRING ANSI_TO_TCHAR( __FUNCTION__ )

/** Debug flags */
#define DEBUG_SPLINE_HOLOGRAM_AUTO_ROUTER 0
#define DEBUG_FACTORY_IO 0

/** Show debug names */
static const FName SHOWDEBUG_RAIN( TEXT( "Rain" ) );
static const FName SHOWDEBUG_FACTORY( TEXT( "Factory" ) );
static const FName SHOWDEBUG_FACTORYCONNECTIONS( TEXT( "FactoryConnections" ) );
static const FName SHOWDEBUG_CIRCUITS( TEXT( "Circuits" ) );
static const FName SHOWDEBUG_CIRCUIT_GROUPS( TEXT( "CircuitGroups" ) );
static const FName SHOWDEBUG_CIRCUIT_BRIDGES( TEXT( "CircuitBridges" ) );
static const FName SHOWDEBUG_CIRCUIT_CONNECTIONS( TEXT( "CircuitConnections" ) );
static const FName SHOWDEBUG_POWER( TEXT( "Power" ) );
static const FName SHOWDEBUG_TRAINS( TEXT( "Trains" ) );
static const FName SHOWDEBUG_TRAIN_SIGNALS( TEXT( "TrainSignals" ) );
static const FName SHOWDEBUG_TRAIN_SCHEDULER( TEXT( "TrainScheduler" ) );
static const FName SHOWDEBUG_TRAIN_RESERVATIONS( TEXT( "TrainReservations" ) );
static const FName SHOWDEBUG_TRACKS( TEXT( "Tracks" ) );
static const FName SHOWDEBUG_STATIONS( TEXT( "Stations" ) );
static const FName SHOWDEBUG_TRAINCOUPLERS( TEXT( "TrainCouplers" ) );
static const FName SHOWDEBUG_FOUNDATIONS( TEXT( "Foundations" ) );
static const FName SHOWDEBUG_RADIATION( TEXT( "Radiation" ) );
static const FName SHOWDEBUG_RADIATIONSPHERES( TEXT( "RadiationSpheres" ) );
static const FName SHOWDEBUG_RESOURCESINK( TEXT( "ResourceSink" ) );
static const FName SHOWDEBUG_AKAUDIOSOURCES( TEXT( "AkAudioSources" ) );
static const FName SHOWDEBUG_AKAUDIOSOURCEATTENUATIONS( TEXT( "AkAudioSourceAttenuations" ) );
static const FName SHOWDEBUG_PIPE_NETWORKS( TEXT( "PipeNetworks" ) );
static const FName SHOWDEBUG_PIPE_PROBING( TEXT( "PipeProbing" ) );
static const FName SHOWDEBUG_PIPE_DETAILS( TEXT( "PipeDetails" ) );
static const FName SHOWDEBUG_PIPE_PRESSURE( TEXT( "PipePressure" ) );
static const FName SHOWDEBUG_PIPE_PRESSURE_GROUPS( TEXT( "PipePressureGroups" ) );
static const FName SHOWDEBUG_PIPE_DELTA_PRESSURE( TEXT( "PipeDeltaPressure" ) );
static const FName SHOWDEBUG_PIPE_FLOW( TEXT( "PipeFlow" ) );
static const FName SHOWDEBUG_PIPE_MOVE_TO_OVERFILL_RATIO( TEXT( "PipeMoveToOverfillRatio" ) );
static const FName SHOWDEBUG_POOLER( TEXT( "Pooler" ) );
static const FName SHOWDEBUG_FOG_OF_WAR( TEXT( "FogOfWar" ) );
static const FName SHOWDEBUG_MAP_MARKERS( TEXT( "MapMarkers" ) );
static const FName SHOWDEBUG_CENTRAL_STORAGE( TEXT( "CentralStorage" ) );
static const FName SHOWDEBUG_BLUEPRINT_PROXY( TEXT( "BlueprintProxy" ) );
static const FName SHOWDEBUG_TEST_MANAGER( TEXT( "TestManager" ) );
static const FName SHOWDEBUG_TIME_OF_DAY( TEXT( "TimeOfDay" ) );
static const FName SHOWDEBUG_FACTORY_UOBJECTS( TEXT( "FactoryUObjects" ) );
static const FName SHOWDEBUG_KEYBINDINGS( TEXT( "Keybindings" ) );
static const FName SHOWDEBUG_KEYHINTS( TEXT( "KeyHints" ) );
static const FName SHOWDEBUG_AIMASSIST( TEXT( "AimAssist" ) );


/** User settings string Ids that are used globally. */
static const FString GAME_RULE_NO_UNLOCK_COST = "FG.GameRules.NoUnlockCost";
static const FString GAME_MODE_ENERGY_COST_MULTIPLIER = "FG.GameMode.EnergyCostMultiplier";
static const FString GAME_MODE_PARTS_COST_MULTIPLIER = "FG.GameMode.PartsCostMultiplier";
static const FString GAME_MODE_SPACE_PARTS_COST_MULTIPLIER = "FG.GameMode.SpacePartsCostMultiplier";
static const FString GAME_MODE_NODE_RANDOMIZATION = "FG.GameMode.NodeRandomization";
static const FString GAME_MODE_NODE_PURITY_SETTINGS = "FG.GameMode.NodePuritySettings";
static const FString GAME_MODE_NODE_RANDOMIZATION_SEED = "FG.GameMode.NodeRandomizationSeed";
static const FString GAME_RULE_NO_POWER = "FG.GameRules.NoPower";
static const FString GAME_RULE_NO_FUEL_COST = "FG.GameRules.NoFuelCost";
static const FString AGREE_TO_CRASH_UPLOAD = "FG.AgreeToCrashUpload";

/** Logs */
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogGame, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogFactory, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogNetConveyorBelt, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogNetFoliageRemoval, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogPower, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogCircuit, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogSchematics, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogRailroad, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogBuildGun, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogHologram, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogSave, Display, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogWidget, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogEquipment, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogBuilding, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogPipes, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogSeasonalEvents, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogSigns, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogAnimInstanceFactory, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogFactoryBlueprint, Warning, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogInventory, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogBlackBox, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogConveyorChain, Log, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogWeather, Log, All );

// Helper macro for detecting if the class has a function implemented in blueprint (Only usable for BlueprintNativeEvent)
// TODO @Nick: this is such a slow and unnecessary way of looking up whenever UFunction has a script implementation, instead we could just check if it's Script array is not empty
#define HAS_BLUEPRINT_IMPLEMENTATION( VarName, FunctionName, CurrentClass ) \
	static FName FuncName_##FunctionName( #FunctionName ); \
	VarName = BlueprintNodeHelpers::HasBlueprintFunction( FuncName_##FunctionName, *this, *CurrentClass::StaticClass() );

/** Custom collision channels and profiles. */
static const FName CollisionProfileHologram( TEXT( "Hologram" ) );
static const FName CollisionProfileClearance( TEXT( "Clearance" ) );
static const FName CollisionProfileResource( TEXT( "Resource" ) );
static const FName CollisionProfileResourceNoCollision( TEXT( "ResourceNoCollision" ) );
static const FName CollisionProfileWireMesh( TEXT( "WireMesh" ) );
static const FName CollisionProfileConveyorSpline( TEXT( "ConveyorSpline" ) );
static const FName CollisionProfileRailroadTrack( TEXT( "RailroadTrack" ) );
static const FName CollisionProfileBuildingMesh( TEXT( "BuildingMesh" ) );
static const FName CollisionProfileClearanceDetector( TEXT( "ClearanceDetector" ) );
static const FName CollisionProfileRailroadVehicle( TEXT( "RailroadVehicle" ) );
static const FName CollisionProfileDerailedRailroadVehicle( TEXT( "DerailedRailroadVehicle" ) );
static const FName CollisionProfileDerailedRailroadVehicleHologram( TEXT( "DerailedRailroadVehicleHologram" ) );
static const FName CollisionProfilePortableMinerDispenser( TEXT("PortableMinerDispenser") );
static const FName CollisionProfileVehiclePath( TEXT("VehiclePath") );
static const FName CollisionProfileWheeledVehicle( TEXT("WheeledVehicle") );

FACTORYGAME_API extern const ECollisionChannel TC_BuildGun;
FACTORYGAME_API extern const ECollisionChannel TC_WeaponInstantHit;
FACTORYGAME_API extern const ECollisionChannel TC_AudioOpaque;
FACTORYGAME_API extern const ECollisionChannel TC_WorldGrid;
FACTORYGAME_API extern const ECollisionChannel TC_Interact;

FACTORYGAME_API extern const ECollisionChannel OC_Projectile;
FACTORYGAME_API extern const ECollisionChannel OC_Hologram;
FACTORYGAME_API extern const ECollisionChannel OC_Resource;
FACTORYGAME_API extern const ECollisionChannel OC_Clearance;
FACTORYGAME_API extern const ECollisionChannel OC_VehicleWheelQuery;
FACTORYGAME_API extern const ECollisionChannel OC_WorldGrid;
FACTORYGAME_API extern const ECollisionChannel OC_ClearanceDetector;
FACTORYGAME_API extern const ECollisionChannel OC_RailroadVehicle;
FACTORYGAME_API extern const ECollisionChannel OC_MapGeneration;
FACTORYGAME_API extern const ECollisionChannel OC_BlueprintProxy;
FACTORYGAME_API extern const ECollisionChannel OC_VehiclePath;
FACTORYGAME_API extern const ECollisionChannel OC_WireMesh;

// [ZolotukhinN:14/10/2024] This function needs to take ENetMode as an argument, but because ENetMode is an enum with no explicit underlying type, one cannot pre-declare it. So we fallback to the int type here to avoid including the entire EngineBaseTypes.h
FACTORYGAME_API const TCHAR* NetModeToString( int32 netMode );

FACTORYGAME_API FString EnumToStringInternal( const class UEnum* enumClass, int64 enumValue );
FACTORYGAME_API FString EnumToDisplayStringInternal( const class UEnum* enumClass, int64 enumValue );
FACTORYGAME_API int64 StringToEnumInternal( const class UEnum* enumClass, const FString& enumNameString, int64 fallbackValue );

/** Quick functions for converting reflected UEnum value into a human readable string */
template<typename T>
FString EnumToString( T enumValue )
{
	return EnumToStringInternal( StaticEnum<T>(), static_cast<int64>(enumValue) );
}
template< typename T >
FString EnumToDisplayString( T enumValue )
{
	return EnumToDisplayStringInternal( StaticEnum< T >(), static_cast< int64 >( enumValue ) );
}

/** Quick function for converting enum string to the enum value for reflected enum types */
template<typename T>
T StringToEnum( const FString& enumNameString, T fallbackValue )
{
	return static_cast<T>( StringToEnumInternal( StaticEnum<T>(), enumNameString, static_cast<int64>( fallbackValue ) ) );
}

#if UE_BUILD_DEBUG
#define DO_CHECK_DEV									1
#elif UE_BUILD_DEVELOPMENT
#define DO_CHECK_DEV									1
#elif UE_BUILD_TEST
#define DO_CHECK_DEV									0
#elif UE_BUILD_SHIPPING
#define DO_CHECK_DEV									0
#endif

#if DO_CHECK_DEV
	#define checkDev(expr)								fgcheck(expr)
	#define checkfDev(expr, format,  ...)				fgcheckf(expr, format,  __VA_ARGS__)
#else
	#define checkDev(expr)								{ CA_ASSUME(expr); }
	#define checkfDev(expr, format,  ...)				{ CA_ASSUME(expr); }
#endif
