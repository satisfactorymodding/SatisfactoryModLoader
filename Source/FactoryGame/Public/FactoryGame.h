// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#ifndef __FACTORYGAME_H__
#define __FACTORYGAME_H__

#include "EngineMinimal.h"
#include "EngineUtils.h"

#include "Net/UnrealNetwork.h"
#include "Net/RepLayout.h"
#include "Net/DataReplication.h"
#include "Engine/ActorChannel.h"

#include "UnitHelpers.h"

DECLARE_STATS_GROUP( TEXT( "AtmosphereUpdater" ), STATGROUP_AtmosphereUpdater, STATCAT_Advanced );
DECLARE_STATS_GROUP( TEXT( "FactoryTick" ), STATGROUP_FactoryTick, STATCAT_Advanced );
DECLARE_STATS_GROUP( TEXT( "Sound Events auto-resume on animations" ), STATGROUP_SoundEventAutoResume, STATCAT_Advanced );
DECLARE_STATS_GROUP( TEXT( "Execute on Interface" ), STATGROUP_ExecuteInterface, STATCAT_Advanced );


// Useful for removing stuff that shouldn't be in public versions
#ifndef IS_PUBLIC_BUILD
#define IS_PUBLIC_BUILD 0
#endif

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
static const FName SHOWDEBUG_CREATURES( TEXT( "Creatures" ) );
static const FName SHOWDEBUG_POOLER( TEXT( "Pooler" ) );
static const FName SHOWDEBUG_SELF_DRIVING( TEXT( "SelfDriving" ) );

/** Common show debug colors */
static const FLinearColor DEBUG_TEXTWHITE( 0.9f, 0.9f, 0.9f );
static const FLinearColor DEBUG_TEXTGREEN( 0.86f, 0.f, 0.f );
static const FLinearColor DEBUG_TEXTYELLOW( 0.86f, 0.69f, 0.f );
static const FLinearColor DEBUG_TEXTRED( 0.f, 0.69f, 0.f );

/** Colors for splitting up indexes into different colors. */
const TArray< FColor > DEBUG_COLORS =
{
	// Do not add black to this list, it is reserved for INDEX_NONE.
	FColorList::Red,
	FColorList::Green,
	FColorList::Blue,
	FColorList::Cyan,
	FColorList::Magenta,
	FColorList::Yellow
};

/** A semi unique color for an index to color things, see colors above, checks the index and returns black for INDEX_NONE */
FORCEINLINE FColor Debug_GetColorForAnIndex( int32 index ) { return index >= 0 ? DEBUG_COLORS[ index % DEBUG_COLORS.Num() ] : FColor::Black; }
FORCEINLINE FColor Debug_GetColorForAnIndex( int32 index, const TArray< FColor >& colors ) { return index >= 0 ? colors[ index % colors.Num() ] : FColor::Black; }

DECLARE_CYCLE_STAT_EXTERN( TEXT( "NetIncrementalSerialize Array" ), STAT_NetIncrementalArray, STATGROUP_ServerCPU, FACTORYGAME_API );
DECLARE_CYCLE_STAT_EXTERN( TEXT( "NetIncrementalSerialize Array BuildMap" ), STAT_NetIncrementalArray_BuildMap, STATGROUP_ServerCPU, FACTORYGAME_API );

/** Logs */
DECLARE_LOG_CATEGORY_EXTERN( LogGame, Log, All );
DECLARE_LOG_CATEGORY_EXTERN( LogFactory, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogNetConveyorBelt, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogNetFoliageRemoval, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogPower, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogCircuit, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogSchematics, Log, All );
DECLARE_LOG_CATEGORY_EXTERN( LogRailroad, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogBuildGun, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogHologram, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogSave, Display, All );
DECLARE_LOG_CATEGORY_EXTERN( LogWidget, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogEquipment, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogBuilding, Warning, All );
#if IS_PUBLIC_BUILD
DECLARE_LOG_CATEGORY_EXTERN( LogConveyorNetDelta, NoLogging, Warning );
DECLARE_LOG_CATEGORY_EXTERN( LogConveyorSpacingNetDelta, NoLogging, Warning );
#else
DECLARE_LOG_CATEGORY_EXTERN( LogConveyorNetDelta, NoLogging, All );
DECLARE_LOG_CATEGORY_EXTERN( LogConveyorSpacingNetDelta, NoLogging, All );
#endif
DECLARE_LOG_CATEGORY_EXTERN( LogPipes, Warning, All );
DECLARE_LOG_CATEGORY_EXTERN( LogSeasonalEvents, Log, All );
DECLARE_LOG_CATEGORY_EXTERN( LogSigns, Log, All );
DECLARE_LOG_CATEGORY_EXTERN( LogAnimInstanceFactory, Log, All );


/** Helpers when using interfaces */
#define VALID_INTERFACE( interface ) IsValid( interface.GetObject() )
#define MAKE_INTERFACE( Interface, VarName, Obj ) \
	TScriptInterface<I##Interface> VarName; \
	if( Obj ) \
	{ \
		fgcheck( ( (UObject*)(Obj) )->GetClass()->ImplementsInterface( U##Interface::StaticClass() ) ); \
		VarName.SetObject( ( Obj ) ); \
		VarName.SetInterface( ( (UObject*)(Obj) )->GetInterfaceAddress( U##Interface::StaticClass() ) ); \
	}

#define SET_INTERFACE( Interface, VarName, Obj ) \
	VarName.SetObject( ( Obj ) ); \
	if( Obj != nullptr ) \
	{ \
		fgcheck( ( (UObject*)( Obj ) )->GetClass()->ImplementsInterface( U##Interface::StaticClass() ) ); \
		VarName.SetInterface( ( (UObject*)( Obj ) )->GetInterfaceAddress( U##Interface::StaticClass() ) ); \
	} \
	else \
	{ \
		VarName.SetInterface( nullptr ); \
	}

// Helper macro for detecting if the class has a function implemented in blueprint (Only usable for BlueprintNativeEvent) @todo What about BlueprintImplementableEvent?
#define HAS_BLUEPRINT_IMPLEMENTATION( VarName, FunctionName, CurrentClass ) \
	static FName FuncName_##FunctionName( #FunctionName ); \
	VarName = BlueprintNodeHelpers::HasBlueprintFunction( FuncName_##FunctionName, *this, *CurrentClass::StaticClass() );

template< class T, size_t N >
constexpr FORCEINLINE size_t ARRAY_SIZE( T( & )[ N ] ) { return N; }

// Has BlueprintNodeHelpers::HasBlueprintFunction in it
#include "BlueprintNodeHelpers.h"

/** Custom collision channels and profiles. */
static const FName CollisionProfileHologram( TEXT( "Hologram" ) );
static const FName CollisionProfileClearance( TEXT( "Clearance" ) );
static const FName CollisionProfileHologramClearance( TEXT( "HologramClearance" ) );
static const FName CollisionProfileWireHologramClearance( TEXT( "WireHologramClearance" ) );
static const FName CollisionProfileResource( TEXT( "Resource" ) );
static const FName CollisionProfileResourceNoCollision( TEXT( "ResourceNoCollision" ) );
static const FName CollisionProfileWireMesh( TEXT( "WireMesh" ) );
static const FName CollisionProfileConveyorSpline( TEXT( "ConveyorSpline" ) );
static const FName CollisionProfileRailroadTrack( TEXT( "RailroadTrack" ) );
static const FName CollisionProfileBuildingMesh( TEXT( "BuildingMesh" ) );
static const FName CollisionProfileClearanceDetector( TEXT( "ClearanceDetector" ) );
static const FName CollisionProfileRailroadVehicle( TEXT( "RailroadVehicle" ) );
static const FName CollisionProfileDerailedRailroadVehicle( TEXT( "DerailedRailroadVehicle" ) );

static const ECollisionChannel TC_BuildGun( ECC_GameTraceChannel5 );
static const ECollisionChannel TC_WeaponInstantHit( ECC_GameTraceChannel6 );
static const ECollisionChannel TC_WorldGrid( ECC_GameTraceChannel9 );

static const ECollisionChannel OC_Projectile( ECC_GameTraceChannel1 );
static const ECollisionChannel OC_Hologram( ECC_GameTraceChannel2 );
static const ECollisionChannel OC_Resource( ECC_GameTraceChannel3 );
static const ECollisionChannel OC_Clearance( ECC_GameTraceChannel4 );
static const ECollisionChannel OC_VehicleWheelQuery( ECC_GameTraceChannel7 );
static const ECollisionChannel OC_HologramClearance( ECC_GameTraceChannel8 );
static const ECollisionChannel OC_WorldGrid( ECC_GameTraceChannel9 );
static const ECollisionChannel OC_ClearanceDetector( ECC_GameTraceChannel10 );
static const ECollisionChannel OC_RailroadVehicle( ECC_GameTraceChannel11 );

/** Input Actions */
static const FName PrimaryFireAction( TEXT( "PrimaryFire" ) );
static const FName SecondaryFireAction( TEXT( "SecondaryFire" ) );
static const FName ReloadAction( TEXT( "Reload" ) );
static const FName BuildGunScrollDownAction( TEXT( "BuildGunScrollDown_PhotoModeFOVDown" ) );
static const FName BuildGunScrollUpAction( TEXT( "BuildGunScrollUp_PhotoModeFOVUp" ) );
static const FName BuildGunScrollModeAction( TEXT( "BuildGunScrollMode" ) );
static const FName BuildGunNoSnapModeAction( TEXT( "ToggleMap_BuildGunNoSnapMode" ) );
static const FName BuildGunSnapToGuideLinesAction( TEXT( "BuildGunSnapToGuideLines_ToggleMultiSelectDismantle" ) );
static const FName BuildGunDismantleToggleMultiSelectStateAction( TEXT( "BuildGunSnapToGuideLines_ToggleMultiSelectDismantle" ) );
static const FName BuildGunDismantleToggleSpecifiedSelectStateAction( TEXT( "ToggleSpecifiedMultiSelectDismantle" ) );
static const FName AttentionPingAction( TEXT( "AttentionPing" ) );
static const FName BuildingSampleAction( TEXT( "TogglePhotoModeUIVisibility_BuildingSample" ) );
static const FName CycleToNextHotbarAction( TEXT( "CycleToNextHotbar" ) );
static const FName CycleToPreviousHotbarAction( TEXT( "CycleToPreviousHotbar" ) );
static const FName PauseAction( TEXT( "PauseGame" ) );
static const FName ChatAction( TEXT( "Chat" ) );
static const FName CycleAmmunitionTypeAction( TEXT( "CycleAmmunitionType" ) );

/** Color Parameters */
static const FName CanPaintPrimaryOrSecondary( TEXT( "CanBePainted" ) ); //Some - Not all - MaterialInterfaces have this property and it should override the "ability" to modify primary and secondary color
static const FName PrimaryColor( TEXT( "PrimaryPaintedMetal_Color" ) );
static const FName SecondaryColor( TEXT( "SecondaryPaintedMetal_Color" ) );

/** Conveyor Parameters */
static const FName ConveyorSpeed( TEXT( "ConveyorSpeed" ) );

/*-----------------------------------------------------------------------------
Example usage:
UE_LOG( LogTemp, Log, TEXT( "Logging some variable: %s" ), SHOWVAR( myVariable ) );

If SHOWVAR does not support a specific type you can overload VarToFString below like:
FORCEINLINE FString VarToFString( MyClass var ){ return FString::Printf( TEXT( "%s" ), MyClass->GetName() ); }
-----------------------------------------------------------------------------*/
#define SHOWVAR( x ) *FString::Printf( TEXT( "%s = %s" ), TEXT( #x ), *VarToFString( x ) )

// Show for enums. Note that you need to provide the enum's type name as we can't get that using code.
#define SHOWENUM( name, x ) *FString::Printf( TEXT( "%s = %s" ), TEXT( #x ), *EnumToFString( FString( #name ), ( int32 )x ) )
#define ENUM_TO_FSTRING( name, x ) EnumToFString( FString( #name ), ( uint32 )x )

// Show for container types.
#define SHOWARRAY( x ) *FString::Printf( TEXT( "%s [%i]:\n%s" ), TEXT( #x ), x.Num(), *ArrayToFString< decltype( x ) >( x ) )
#define SHOWSET( x ) *FString::Printf( TEXT( "%s [%i]:\n%s" ), TEXT( #x ), x.Num(), *SetToFString< decltype( x ) >( x ) )
#define SHOWMAP( x ) *FString::Printf( TEXT( "%s \n%s" ), TEXT( #x ), *MapToFString< decltype( x ) >( x ) )

/** Use this to log larger arrays, SHOWARRAY might not show the entire array. */
#define LOGARRAY( category, verbosity, x ) \
	{ \
		UE_LOG( category, verbosity, TEXT( "%s (%i):" ), TEXT( #x ), x.Num() ); \
		for( int32 i = 0; i < x.Num(); ++i ) \
		{ \
			UE_LOG( category, verbosity, TEXT( "[%i]\t%s" ), i, *VarToFString( x[ i ] ) ); \
		} \
	}

/** Use for easy debugging, note that logs in the temp category should not be submitted, they should be categorized. */
#define QUICKLOG( x, ... ) UE_LOG( LogTemp, Log, TEXT( "QUICKLOG: %s" ), TEXT( x ), ## __VA_ARGS__ );

/** QUICKLOG that marks output with authority/remote depending on the actors role. Note that this is not always synonymous with server/client, use the net mode in that case. */
#define QUICKLOG_AUTHORITY_MARKING( x, ... ) UE_LOG( LogTemp, Log, TEXT( "QUICKLOG: [%s] %s" ), HasAuthority() ? TEXT( "Authority" ) : TEXT( "Remote" ), *FString::Printf( TEXT( x ), __VA_ARGS__ ) );

/** Similar to QUICKLOG but for single variables. */
#define QUICKSHOW( x ) UE_LOG( LogTemp, Log, TEXT( "QUICKSHOW: (%s)   %s" ), ANSI_TO_TCHAR( __FUNCTION__ ), SHOWVAR( x ) ); 
#define QUICKSHOWENUM( name, x ) UE_LOG( LogTemp, Log, TEXT( "QUICKSHOW (%s)   %s" ), ANSI_TO_TCHAR( __FUNCTION__ ), SHOWENUM( name, x ) );
#define QUICKSHOWARRAY( x ) LOGARRAY( LogTemp, Log, TEXT( "QUICKSHOW: (%s)   %s" ), ANSI_TO_TCHAR( __FUNCTION__ ), x );

/** QUICKLOG that appends the net mode. Requires GetWorld(). */
#define QUICKLOG_NETMODE( x, ... ) UE_LOG( LogTemp, Log, TEXT( "(%s) %s" ), NETMODE_STRING, *FString::Printf( TEXT( x ) ), __VA_ARGS__ );

inline FString NetmodeToString( ENetMode NM )
{
	switch( NM )
	{
	case NM_Standalone:
		return TEXT( "Standalone" );
	case NM_DedicatedServer:
		return TEXT( "DedicatedServer" );
	case NM_ListenServer:
		return TEXT( "ListenServer" );
	case NM_Client:
		return FString::Printf( TEXT( "Client %d" ), GPlayInEditorID - 1 );
	case NM_MAX:
		return TEXT( "MAX" );
	default:
		return TEXT( "BadValue" );
	}
}

#define NETMODE_STRING ( NETMODE_STRING_WORLD( GetWorld() ) )
#define NETMODE_STRING_WORLD( world ) ( ( world ) ? *NetmodeToString( ( world )->GetNetMode() ) : TEXT( "Unknown NetMode" ) )
	
#define NETMODE_STRING_CONTEXT( context ) ( NETMODE_STRING_WORLD( ( context )->GetWorld() ) )
#define QUICKNETMODE UE_LOG( LogTemp, Log, TEXT( "%s %s" ), *GetName(), NETMODE_STRING );

#define FUNCTION_STRING ANSI_TO_TCHAR( __FUNCTION__ )

/** Analytics Helper Macros */
#define SEND_TOTAL_TRACK_COUNTER_ANALYTIC(__WORLD__, __SERVICE__, __STAT_KEY__, __STAT_ID__ , __COUNT__)	\
if( auto* analytics = UFGGameInstance::GetAnalyticsServiceFromWorld(__WORLD__) ) analytics->SendTotalTrackedCounterAnalytic( __SERVICE__, __STAT_KEY__, __STAT_ID__, __COUNT__ )

#define SEND_COUNTER_ANALYTIC(__WORLD__, __SERVICE__, __STAT_KEY__ , __COUNT__)	\
if( auto* analytics = UFGGameInstance::GetAnalyticsServiceFromWorld(__WORLD__) ) analytics->SendCounterAnalytic( __SERVICE__, __STAT_KEY__, __COUNT__ )

#define SEND_VALUE_ANALYTIC(__WORLD__, __SERVICE__, __STAT_KEY__, __STAT_ID__, __VALUE__) \
if( auto* analytics = UFGGameInstance::GetAnalyticsServiceFromWorld(__WORLD__) ) analytics->SendValueAnalytic( __SERVICE__, __STAT_KEY__, __STAT_ID__, __VALUE__ )

FORCEINLINE FString VarToFString( FVector2D var ) { return FString::Printf( TEXT( "(X=%f,Y=%f)" ), var.X, var.Y ); }
FORCEINLINE FString VarToFString( FVector var ){ return FString::Printf( TEXT( "(X=%f,Y=%f,Z=%f)" ), var.X, var.Y, var.Z ); }
FORCEINLINE FString VarToFString( FBox var ) { return FString::Printf( TEXT( "(Min=%s,Max=%s)" ), *VarToFString( var.Min ), *VarToFString( var.Min ) ); }
FORCEINLINE FString VarToFString( FString var ){ return FString::Printf( TEXT( "\"%s\"" ), *var ); }
FORCEINLINE FString VarToFString( FText var ){ return FString::Printf( TEXT( "\"%s\"" ), *var.ToString() ); }
FORCEINLINE FString VarToFString( FName var ){ return FString::Printf( TEXT( "\"%s\"" ), *var.ToString() ); }
FORCEINLINE FString VarToFString( float var ){ return FString::Printf( TEXT( "%.2f" ), var ); }
FORCEINLINE FString VarToFString( double var ){ return FString::Printf( TEXT( "%.2f" ), var ); }
FORCEINLINE FString VarToFString( const UObject* var ){ return FString::Printf( TEXT( "%s" ), var ? *var->GetName() : TEXT( "nullpeter" ) ); }
FORCEINLINE FString VarToFString( int var ){ return FString::Printf( TEXT( "%i" ), var ); }
FORCEINLINE FString VarToFString( int64 var ){ return FString::Printf( TEXT( "%i" ), var ); }
FORCEINLINE FString VarToFString( unsigned int var ){ return FString::Printf( TEXT( "%i" ), var ); }
FORCEINLINE FString VarToFString( bool var ){ return FString::Printf( TEXT( "%s" ), var ? TEXT( "ture" ) : TEXT( "flase" ) ); }
FORCEINLINE FString VarToFString( FRotator var ){ return FString::Printf( TEXT( "(Yaw=%f,Pitch=%f,Roll=%f)" ), var.Yaw, var.Pitch, var.Roll ); }
FORCEINLINE FString VarToFString( FTransform var ){ return FString::Printf( TEXT( "(%s)(%s)(%s)" ), *VarToFString( var.GetTranslation() ), *VarToFString( var.GetRotation().Rotator() ), *VarToFString( var.GetScale3D() ) ); }
FORCEINLINE FString VarToFString( FLinearColor var ){ return FString::Printf( TEXT( "(R=%f,G=%f,B=%f,A=%f)" ), var.R, var.G, var.B, var.A ); }
FORCEINLINE FString VarToFString( FColor var ){ return FString::Printf( TEXT( "(R=%i,G=%i,B=%i,A=%i)" ), var.R, var.G, var.B, var.A ); }
FORCEINLINE FString VarToFString( const FUniqueNetId& var ){ return FString::Printf( TEXT( "%s" ), *var.ToString() ); }
FORCEINLINE FString VarToFString( FUniqueNetIdRepl var ){ return FString::Printf( TEXT( "%s" ), *var.ToString() ); }
FORCEINLINE FString VarToFString( FOverlapResult var ){ return FString::Printf( TEXT("%s"), var.Actor.IsValid() ? *var.Actor.Get()->GetName() : *VarToFString(var.Component.Get()) ); }
FORCEINLINE FString VarToFString( void* var ){ return FString::Printf( TEXT( "0x%016I64X" ), ( SIZE_T )var ); }
FORCEINLINE FString VarToFString( FPrimaryAssetId var ){ return var.ToString(); }

template< typename T >
FORCEINLINE FString VarToFString( TArray< T > var )
{
	FString elements;
	for( int32 i = 0; i < var.Num(); ++i )
	{
		if( var.Num() > 1 && i > 0 )
		{
			elements.Append( FString( TEXT( "," ) ) );
		}
		elements.Append( VarToFString( var[ i ] ) );
	}
	return FString::Printf( TEXT( "[%i]{%s}" ), var.Num(), *elements );
}

FORCEINLINE FString EnumToFString( const FString& name, int32 var )
{
	if( UEnum* EnumObject = FindObject< UEnum >( ANY_PACKAGE, *name, true ) )
	{
#if WITH_EDITOR
		return EnumObject->GetDisplayNameTextByValue( var ).ToString();
#else
		return EnumObject->GetNameStringByValue( var );
#endif
	}

	return TEXT( "Invalid Enum" );
}

FORCEINLINE bool IsValidEnumValue( const TCHAR* enumName, const FString& enumValue )
{
	if( UEnum* enumObject = FindObject< UEnum >( ANY_PACKAGE, enumName, true ) )
	{
		return enumObject->IsValidEnumName( FName( *enumValue ) );
	}

	return false;
}

template<typename T>
FORCEINLINE T StringToEnumChecked( const TCHAR* enumName, const FString& enumValue )
{
	UEnum* enumObject = FindObject< UEnum >( ANY_PACKAGE, enumName, true );
	fgcheck(enumObject);

	int32 index = enumObject->GetIndexByName(FName(*enumValue));
	return T((uint8)index);
}

template< class TArrayType >
FORCEINLINE FString ArrayToFString( const TArrayType& tarray )
{
	FString result = "";
	for( int32 i = 0; i < tarray.Num(); ++i )
	{
		result += *FString::Printf( TEXT( "  (%i)\t%s\n" ), i, *VarToFString( tarray[i] ) );
	}
	return result;
}

template< class TMapType >
FORCEINLINE FString MapToFString( const TMapType& tmap )
{
	FString result = "";
	for( auto& elem : tmap )
	{
		result += *FString::Printf( TEXT( "  [%s]\t%s\n" ), *VarToFString(elem.Key), *VarToFString( elem.Value ) );
	}
	return result;
}

static const FString INCLUDE_IN_BUILD( TEXT( "mIncludeInBuilds" ) );
template< class TSetType >
FORCEINLINE FString SetToFString( const TSetType& tset )
{
	FString result = "";
	for( auto& elem : tset )
	{
		result += *FString::Printf( TEXT( "%s\n" ), *VarToFString( elem ) );
	}
	return result;
}

/** Removes the prefix of UEDPC from the mapname */
FString RemoveStandalonePrefix( const FString& string );

#if WITH_EDITOR
// These includes are needed for VISUAL_LOG to work
#include "SlateBasics.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#define VISUAL_LOG( LOG_CATEGORY, WARNING_LEVEL, MESSAGE, ... ) \
	{ \
		UE_LOG( LOG_CATEGORY, WARNING_LEVEL, MESSAGE, ## __VA_ARGS__ ); \
		static TWeakPtr<SNotificationItem> existingNotification; \
		if( !existingNotification.IsValid() ) \
		{ \
			FNotificationInfo info( FText::FromString( FString::Printf( MESSAGE, ## __VA_ARGS__ ) ) ); \
			info.ExpireDuration = 5.0f; \
			info.bUseSuccessFailIcons = true; \
			existingNotification = TWeakPtr<SNotificationItem>( FSlateNotificationManager::Get().AddNotification( info ) ); \
		} \
	}
#else
	#define VISUAL_LOG( LOG_CATEGORY, WARNING_LEVEL, MESSAGE, ... ) \
		UE_LOG( LOG_CATEGORY, WARNING_LEVEL, MESSAGE, __VA_ARGS__ ); 
#endif //WITH_EDITOR

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

#define WITH_CHEATS	(!IS_PUBLIC_BUILD)

#endif //__FACTORYGAME_H__
