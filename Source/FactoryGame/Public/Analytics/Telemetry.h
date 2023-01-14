// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#if WITH_TELEMETRY
#include "FactoryGame.h"
#include "FGGameInstance.h"
#include "DJSONObject.h"
#include "DSTelemetry.h"

#define SUBMIT_BOOLEAN_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitBoolean( key, data )
#define SUBMIT_INTEGER_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitInteger( key, data )
#define SUBMIT_STRING_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitString( key, data )
#define SUBMIT_FLOAT_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SubmitFloat( key, data )

#define SET_STATE_BOOLEAN_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateBoolean( key, data )
#define SET_STATE_INTEGER_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateInteger( key, data )
#define SET_STATE_STRING_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateString( key, data )
#define SET_STATE_FLOAT_TELEMETRY( world, key, data ) if( auto telemetry = UFGGameInstance::GetTelemetryInstanceFromWorld( world ) ) telemetry->SetStateFloat( key, data )

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
