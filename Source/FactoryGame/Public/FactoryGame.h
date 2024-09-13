// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreTypes.h"
#include "UObject/NameTypes.h"
#include "Logging/LogMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

enum ENetMode;
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
static const FName SHOWDEBUG_FACTORY( TEXT( "Factory" ) );
static const FName SHOWDEBUG_FACTORYCONNECTIONS( TEXT( "FactoryConnections" ) );
static const FName SHOWDEBUG_CIRCUITS( TEXT( "Circuits" ) );
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
static const FName SHOWDEBUG_SELF_DRIVING( TEXT( "SelfDriving" ) );
static const FName SHOWDEBUG_FOG_OF_WAR( TEXT( "FogOfWar" ) );
static const FName SHOWDEBUG_MAP_MARKERS( TEXT( "MapMarkers" ) );
static const FName SHOWDEBUG_CENTRAL_STORAGE( TEXT( "CentralStorage" ) );
static const FName SHOWDEBUG_BLUEPRINT_PROXY( TEXT( "BlueprintProxy" ) );
static const FName SHOWDEBUG_TEST_MANAGER( TEXT( "TestManager" ) );
static const FName SHOWDEBUG_TIME_OF_DAY( TEXT( "TimeOfDay" ) );

/** User settings string Ids that are used globally. */
static const FString GAME_RULE_NO_UNLOCK_COST = "FG.GameRules.NoUnlockCost";

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

extern const ECollisionChannel TC_BuildGun;
extern const ECollisionChannel TC_WeaponInstantHit;
extern const ECollisionChannel TC_WorldGrid;
extern const ECollisionChannel TC_Interact;

extern const ECollisionChannel OC_Projectile;
extern const ECollisionChannel OC_Hologram;
extern const ECollisionChannel OC_Resource;
extern const ECollisionChannel OC_Clearance;
extern const ECollisionChannel OC_VehicleWheelQuery;
extern const ECollisionChannel OC_WorldGrid;
extern const ECollisionChannel OC_ClearanceDetector;
extern const ECollisionChannel OC_RailroadVehicle;
extern const ECollisionChannel OC_MapGeneration;
extern const ECollisionChannel OC_BlueprintProxy;
extern const ECollisionChannel OC_WireMesh;

FACTORYGAME_API const TCHAR* NetModeToString( ENetMode netMode );
FACTORYGAME_API FString EnumToStringInternal( const class UEnum* enumClass, int64 enumValue );
FACTORYGAME_API int64 StringToEnumInternal( const class UEnum* enumClass, const FString& enumNameString, int64 fallbackValue );

/** Quick function for converting reflected UEnum value into a human readable string */
template<typename T>
FString EnumToString( T enumValue )
{
	return EnumToStringInternal( StaticEnum<T>(), static_cast<int64>(enumValue) );
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
