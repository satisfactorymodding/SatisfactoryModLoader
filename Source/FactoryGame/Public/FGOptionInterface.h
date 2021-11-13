// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGOptionsSettings.h"
#include "UObject/Interface.h"
#include "FGOptionInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam( FOptionUpdated, FString, updatedCvar );

UINTERFACE( Blueprintable, meta = ( CannotImplementInterfaceInBlueprint ) )
class UFGOptionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FACTORYGAME_API IFGOptionInterface
{
	GENERATED_BODY()

public:
	/** Get the currently active option value for a bool */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetBoolOptionValue( const FString& cvar ) const = 0;

	/** Get the current UI value for a bool. Doesn't always match the active value. Should only be used in the options menu. */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetBoolUIDisplayValue( const FString& cvar ) const = 0;

	/** Set a option value for a bool, will need to be applied to take affect and/or get saved */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SetBoolOptionValue( const FString& cvar, bool value ) = 0;

	/** Get the currently active option value for an integer */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual int32 GetIntOptionValue( const FString& cvar ) const = 0;

	/** Get the current UI value for an integer. Doesn't always match the active value. Should only be used in the options menu. */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual int32 GetIntUIDisplayValue( const FString& cvar ) const = 0;

	/** Set the option value for an integer, will need to be applied to take affect and/or get saved */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SetIntOptionValue( const FString& cvar, int32 newValue ) = 0;
	
	/** Get the option value for a float */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual float GetFloatOptionValue( const FString& cvar ) const = 0;

	/** Get the current UI value for an float. Doesn't always match the active value. Should only be used in the options menu. */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual float GetFloatUIDisplayValue( const FString& cvar ) const = 0;

	/** Set the option value for an float, will need to be applied to take affect and/or get saved */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SetFloatOptionValue( const FString& cvar, float newValue ) = 0;

	/** Returns true if we have any option changes that haven't been applied yet */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool HasAnyUnsavedOptionValueChanges() const = 0;

	/** Returns true if we have a option change that haven't been applied yet for this cvar*/
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool HasPendingApplyOptionValue( const FString& cvar ) const = 0;

	/** Returns true if we have a pending option value waiting to be applied for this cvar after we restart game or session */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool HasPendingAnyRestartOptionValue( const FString& cvar ) const = 0;

	/** Returns true if we require restart of the session for any settings to apply */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetRequireSessionRestart() const = 0;

	/** Returns true if we require restart of the game for any settings to apply */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetRequireGameRestart() const = 0;

	/** Subscribe to changes for this option. The given delegate will be called when cvar is updated */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) = 0;

	/** Unsubscribe to changes for this option */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void UnsubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) = 0;

	/** Unsubscribe to all changes for options this object have subscribed to */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void UnsubscribeToAllDynamicOptionUpdate( UObject* boundObject ) = 0;

	/** Get all option widgets of a certain category */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual TArray<class UFGDynamicOptionsRow*> GetOptionWidgetsInCategory( UUserWidget* owningWidget, EOptionCategory category ) = 0;
	
};
