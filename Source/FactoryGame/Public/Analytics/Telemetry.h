// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#if WITH_TELEMETRY
#include "FactoryGame.h"
#include "FGGameInstance.h"
#include "DJSONObject.h"
#include "DSTelemetry.h"

/**
 * Submit a telemetry entry with a single value, specify the event key used in the backend database, and give it a value.
 *
 * Example:
 * SUBMIT_STRING_TELEMETRY( GetWorld(), TEXT( "train_change_timetable" ), GetTrainName() );
 */
#define SUBMIT_BOOLEAN_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitBoolean( key, data )
#define SUBMIT_INTEGER_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitInteger( key, data )
#define SUBMIT_STRING_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitString( key, data )
#define SUBMIT_FLOAT_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitFloat( key, data )

/**
 * Set a telemetry state, specify the state key used in the backend database, and give it a value.
 *
 * A state is a value tracked over time that is submitted in conjunction with telemetry entries.
 * Example of a state is the session type: single player, client, listen server, or dedicated server.
 * When this is set, all other telemetry submits will contain this state, e.g. an event called player_died would also contain the session type as its additional state.
 *
 * Example:
 * SET_STATE_BOOLEAN_TELEMETRY( GetWorld(), TEXT( "using_mods" ), ModsLoaded.Num() > 0 );
 */
#define SET_STATE_BOOLEAN_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateBoolean( key, data )
#define SET_STATE_INTEGER_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateInteger( key, data )
#define SET_STATE_STRING_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateString( key, data )
#define SET_STATE_FLOAT_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateFloat( key, data )

/**
 * Submit a composite telemetry value, consisting of multiple different data fields.
 *
 * Start creating a new telemetry object by using BEGIN_JSON_OBJECT_TELEMETRY, here is also where you specify the event key used in the backend database.
 * Submit the object by using END_JSON_OBJECT_TELEMETRY, this works like the SUBMIT_* set of macros.
 *
 * Note: These macros need to be wrapped inside WITH_TELEMETRY macros to be able to be compiled out.
 *       @todo-telemetry For whomever inherits the system: On second thoughts, maybe would have been better to consolidate to one macro SUBMIT_JSON_OBJECT_TELEMETRY and pass the body as a lambda to make it less prone to mistakes?
 *
 * Example:
 * #if WITH_TELEMETRY
 *     BEGIN_JSON_OBJECT_TELEMETRY( GetWorld(), TEXT( "overclock_used" ) )
 *	       object->AddStringField( TEXT( "overclocked_building" ), buildable->GetName() );
 *         object->AddFloatField( TEXT( "overclock_percentage" ), newOverclockPercentage );
 *     END_JSON_OBJECT_TELEMETRY()
 * #endif
 *
 * For a full reference of available fields, see the class UDJSONObject.
 */
#define BEGIN_JSON_OBJECT_TELEMETRY( world, key ) \
	if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) { \
		if( UDJSONObject* object = UDJSONObject::CreateJSONObject( world ) ) { \
			const FString CACHED_KEY = key;

#define END_JSON_OBJECT_TELEMETRY() \
			const bool success = telemetry->SubmitJSONObject( CACHED_KEY, object ); \
			object->ConditionalBeginDestroy(); \
		} \
	}
#else
#define SUBMIT_BOOLEAN_TELEMETRY( world, key, data )
#define SUBMIT_INTEGER_TELEMETRY( world, key, data )
#define SUBMIT_STRING_TELEMETRY( world, key, data )
#define SUBMIT_FLOAT_TELEMETRY( world, key, data )

#define SET_STATE_BOOLEAN_TELEMETRY( world, key, data )
#define SET_STATE_INTEGER_TELEMETRY( world, key, data )
#define SET_STATE_STRING_TELEMETRY( world, key, data )
#define SET_STATE_FLOAT_TELEMETRY( world, key, data )

#define BEGIN_JSON_OBJECT_TELEMETRY( world, key )
#define END_JSON_OBJECT_TELEMETRY()
#endif

// Send telemetry from a non cooked version of the game, this does not work in the editor's PIE mode you need to launch standalone.
const bool TELEMETRY_DEBUG_ENABLED = false;

const FString TELEMETRY_INVALID_STRING = TEXT( "NULL" );
const int32 TELEMETRY_INVALID_INT = -1;
const float TELEMETRY_INVALID_FLOAT = -1.f;
