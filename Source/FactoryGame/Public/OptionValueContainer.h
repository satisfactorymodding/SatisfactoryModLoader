// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** Enum that specifies what state an option value is in */
UENUM( BlueprintType )
enum class EOptionValueState : uint8
{
	Applied, // The that is applied to the cvar and what you receive if you get a value from game user settings. The exception is if you haven't changed the value you will get the default value. Apply will also contain isntanty updated values.
    Pending, // Have we changed but not saved a value
    InstantlyUpdated, // Values that are directly applied when changed. These values are what we should revert to if we revert options changes
    PendingSessionRestart, // Have we changed a value that only should be applied when we restart the session. If we are in the main menu no values will be associated with this state
    //SessionRestart, // Have we changed a value that should should be applied when we restart the session. Changes to these in main menu get applied directly
    PendingGameRestart, // Have we changed a value that only should be applied when we restart the game.
    //GameRestart, // Have we changed a value that should should be applied when we restart the game. 
    Default // The default value of this option
};

UENUM( BlueprintType )
enum class EOptionApplyType : uint8
{
	OAT_Normal					UMETA( DisplayName = "Normal" ),
    OAT_UpdateInstantly			UMETA( DisplayName = "Update Instantly" ),
    OAT_RequireSessionRestart	UMETA( DisplayName = "Require Session Restart" ),
    OAT_RequireGameRestart		UMETA( DisplayName = "Require Game Restart" ),
};

/**
 * 
 */
class FACTORYGAME_API OptionValueContainer
{

public:
	int32 GetActiveIntValue( FString cvar ) const;
	float GetActiveFloatValue( FString cvar ) const;

	int32 GetIntDisplayValue( FString cvar ) const;
	float GetFloatDisplayValue( FString cvar ) const;

	TMap< FString, int32 > GetIntValues( EOptionValueState valueType ) const;
	TMap< FString, float > GetFloatValues( EOptionValueState valueType ) const;
	
	/* Setters */
	void SetBoolValue( EOptionValueState valueType, FString cvar, bool value );
	void SetIntValue( EOptionValueState valueType, FString cvar, int32 value );
	void SetFloatValue( EOptionValueState valueType, FString cvar, float value );

	void SetIntValue( FString cvar, int32 value );
	void SetFloatValue( FString cvar, float value );

	void ApplyIntValue( FString cvar, int32 value );
	void ApplyFloatValue( FString cvar, float value );

	void InitDefaultIntValue( FString cvar, int32 value, EOptionApplyType optionApplyType );
	void InitDefaultFloatValue( FString cvar, float value, EOptionApplyType optionApplyType );

	bool HasAnyUnsavedOptionValueChanges() const;
	bool HasPendingApplyOptionValue( FString cvar ) const;
	bool HasPendingSessionRestartOptionValue( FString cvar ) const;
	bool HasPendingGameRestartOptionValue( FString cvar ) const;
	bool HasAnyPendingSessionRestartOptionValues() const;
	bool HasAnyPendingGameRestartOptionValues() const;

	void ApplyPendingChanges();
	void ApplyRestartSessionRequiredChanges();
	void ApplyRestartGameRequiredChanges();

	void ResetOptionValue( FString cvar );
	void ResetPendingChanges();
	void ResetValuesToDefault();

	void RemoveValues( EOptionValueState valueType );
	
	void GetOptionsDebugData( TArray<FString>& out_debugData );

private:
	void RemoveValue( EOptionValueState valueType, FString cvar );
	
	/* Does this container contain a value for the given value apply type and cvar  */
	bool ContainsValue( EOptionValueState valueType, FString cvar ) const;

	/* Does this container contain a value for any of the given value apply types and cvar  */
	bool ContainsValue( TArray< EOptionValueState > valueTypes, FString cvar ) const;
	
	/* Does this container contain any value for the given value apply type */
	bool ContainsValues( EOptionValueState valueType ) const;

	/* Does this container contain any value for any of the given value apply types */
	bool ContainsValues( TArray< EOptionValueState > valueTypes ) const;

	/* Getters. Returns true if value exists. */
	bool GetBoolValue( EOptionValueState valueType, FString cvar, bool& out_value ) const;
	bool GetIntValue( EOptionValueState valueType, FString cvar, int32& out_value ) const;
	bool GetFloatValue( EOptionValueState valueType, FString cvar, float& out_value ) const;

	bool GetBoolValue( EOptionValueState valueType, FString cvar ) const;
	int32 GetIntValue( EOptionValueState valueType, FString cvar ) const;
	float GetFloatValue( EOptionValueState valueType, FString cvar ) const;

	void ResetIntValue( FString cvar );
	void ResetFloatValue( FString cvar );

	/** Update the console variable with a new int value */
	void SetCvarValue( FString cvar, int32 value );
	
	/** Update the console variable with a new float value */
	void SetCvarValue( FString cvar, float value );

private:
	TMap<EOptionValueState, TMap< FString, int32 > > mIntValues;
	TMap<EOptionValueState, TMap< FString, float > > mFloatValues;

	// Special options mapping to know if an option has special states like require restart of game etc.
	TMap< FString, EOptionApplyType > mCvarToApplyType;
};
