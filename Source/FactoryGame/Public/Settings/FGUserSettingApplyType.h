// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "Misc/Variant.h"
#include "UObject/NoExportTypes.h"
#include "FGUserSettingApplyType.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams( FOnPendingAppliedOptionValueChangedDelegate, FString, FVariant );

/**
 * This class and it's derived classes handle the current and pending value of a user setting. It also handles what happens when you apply
 * or reset a setting. It stores a pointer to the setting widget to delegate events to that widget.
 * @todok2 Should we allow the widget to fully override behaviour of this class when needed?
 */
UCLASS()
class FACTORYGAME_API UFGUserSettingApplyType : public UObject
{
	GENERATED_BODY()

public:
	/** Static function to get the UserSettingApplyType for a given owner and a user setting */
	static UFGUserSettingApplyType* GetUserSettingApplyType( IFGOptionInterface* owner, class UFGUserSetting* inUserSetting );

	/** Converts FVariant to it's string representation */
	static FString VariantAsString( const FVariant& Variant );

	/** Converts string to a FVariant using the specified value type */
	static bool StringAsVariant( const FString& String, EVariantTypes VariantType, FVariant& OutVariant );

	/** Initial setup of values and registration of cvar values */
	virtual void Init( class UFGUserSetting* inUserSetting );
	/** Try to register the cvar value if the underlying user setting wants cvar updates */
	void TryRegisterCvarValue();
	/** Update the cvar value if the underlying user setting wants cvar updates  */
	void TryUpdateCvarValue();
	/** Check if the cvar value has been updated. If so, update the value and indirectly broadcast changes to UI. returns true if we found a change */
	bool CheckCvarValueForUpdates();
	
	/** Called when the owning option interface wants to apply pending changes. This will trigger option updated broadcasts.
	 *  Returns true if we actually changed something */ 
	virtual bool OnApply( bool markDirty = true );
	/** Called right before we restart a session */ 
	virtual void OnPreSessionRestart(){};
	/** Called right before we restart the game */  
	virtual void OnPreRestartGame(){};
	
	/** Sets a value. This function and it overridden counterparts behaves differently for different settings and will directly or indirectly
	 *	trigger updates. This is the preferred approach to change settings */ 
	virtual void SetValue(FVariant newValue);
	/** Force set a value. This function will bypass apply cycles and apply the value directly. USE WITH CAUTION */ 
	virtual void ForceSetValue(FVariant newValue, bool bClearPendingValue = true);
	/**
	 * Forcefully updates the current "pending applied" value of this setting
	 * The meaning is specific to the setting implementation:
	 *  - Normal and instantly applied settings will return false and do nothing as their values are applied unconditionally
	 *  - Settings requiring session/game restart will update their internal cached applied value
	 */
	virtual bool ForceSetPendingAppliedValue(FVariant newValue);
	/** Set the default value. Useful when we want to set a new default value to reset to. */ 
	void OverrideDefaultValue(FVariant newDefaultValue);
	/** Called when we want to restore default values. When the player presses reset in the UI */
	virtual void ResetToDefaultValue();
	/** Clear out pending changes. Triggers no updates */ 
	virtual void ClearPendingChanges();
	/** Mark as dirty. This means the value will be saved */ 
	void MarkDirty(){ IsDirty = true; }
	
	/** Broadcast updates so subscriber knows values have been changed */
	void NotifySubscribers();
	/** Purges subscribers that are no longer valid from the list */
	void PurgeDeadSubscribers();
	/** Listen for updates when the user setting changes applied value */
	void AddSubscriber(const FOnOptionUpdated& onOptionUpdatedDelegate);
	void AddSubscriber(const FOptionUpdated& onOptionUpdatedDelegate);
	/** Stop listen for updates when the user setting changes applied value */
	void RemoveSubscriber(const FOnOptionUpdated& onOptionUpdatedDelegate);
	void RemoveSubscriber(const FOptionUpdated& onOptionUpdatedDelegate);
	/** Remove the given object as a subscriber */
	void RemoveObjectAsSubscriber( UObject* boundObject );
	/** Clear out subscribers. Triggers no updates */ 
	void ClearSubscribers(){ Subscribers.Empty(); }
	/** Called when the "pending applied" (applied, but pending game/session restart) value changes for this setting */
	FOnPendingAppliedOptionValueChangedDelegate& OnPendingAppliedOptionValueChanged() { return PendingAppliedOptionValueChanged; }

	/** This is the applied value for the user setting */
	virtual FVariant GetAppliedValue() const { return AppliedValue; }
	/** This is the pending value waiting to be applied for the user setting */
	virtual FVariant GetPendingValue() const { return PendingValue; }
	/** This is the value we want to show in the UI. This is usually the pending value if one exists other wise it's the applied value */
	virtual FVariant GetDisplayValue() const;
	/** This is the default value for the user setting that we want to default to and apply when we reset this setting */
	virtual FVariant GetDefaultValue() const { return DefaultValue; }
	/** Returns a non empty FVariant if we have a value to actually save i.e the value is different from the default value and marked as dirty */
	virtual FVariant GetValueToSave() const;
	/**
	 * Returns a value that is currently "Applied" but is different from the actual "Applied" value.
	 * For example, for settings requiring session/game restart, that would return a value that is pending application and will be applied
	 * once the session has been restarted, or once the game has been restarted
	 * If no such value exists, it will return the applied value instead
	 */
	virtual FVariant GetPendingAppliedValue() const;
	/** Returns true if we have pending changes that haven't been applied yet. */
	virtual bool HasPendingChanges() const;
	virtual bool HasSessionRestartRequiredChanges() const { return false; }
	virtual bool HasGameRestartRequiredChanges() const { return false; }

	// virtual bool GetRequireSessionRestart() const;
	// virtual bool GetRequireGameRestart() const;
	/** Returns true if any other value than the default value is applied */
	virtual bool IsDefaultValueApplied() const;

	/** Returns the underlying setting that this apply type affects */
	class UFGUserSetting* GetUserSetting() const { return UserSetting; }

	/** Sets the option row widget used to display the user setting */
	void SetOptionRowWidget( class UFGDynamicOptionsRow* inOptionRowWidget );
	/** Gets the option row widget used to display the user setting */
	class UFGDynamicOptionsRow* GetOptionRowWidget() const { return OptionRowWidget; }

	/** Populates debug data with current values (Applied, Pending, Default) */
	virtual void GetDebugData( TArray<FString>& out_debugData );

	/** Returns the option interface owning this object */
	TScriptInterface<IFGOptionInterface> GetOwnerOptionInterface() const;

	/** Returns true if we are currently in the main menu, as much as the setting application logic is concerned */
	bool IsInMainMenu() const;
protected:
	/** The underlying user setting that this apply type handles */
	UPROPERTY(Transient)
	class UFGUserSetting* UserSetting = nullptr;
	/** The option row widget that displays the user setting */
	UPROPERTY(Transient)
	class UFGDynamicOptionsRow* OptionRowWidget = nullptr;
	
	/** The currently applied value for user setting */
	FVariant AppliedValue = FVariant();
	/** The pending value for user setting waiting to be applied */
	FVariant PendingValue = FVariant();
	/** The default value for user setting that we set when resetting the option to default value. Can be overriden by OverrideDefaultValue */
	FVariant DefaultValue = FVariant();
	/** The subscribers listening for changes to the applied value changes */
	TArray<FOnOptionUpdated> Subscribers;
	/** Called legacy for now since this is the old system. We might end up needing this since FOnOptionUpdated with its FVariant isn't supported by blueprints */
	TArray<FOptionUpdated> LegacySubscribers;
	/** Called when a pending applied option value changes for the given option. */
	FOnPendingAppliedOptionValueChangedDelegate PendingAppliedOptionValueChanged;
	/** Defines it this setting should be saved. Only dirtied when applying values. This means indirect changes won't be saved
	 *	We can't rely on if default value is NOT applied since default value of some settings might sometime depends on other settings */
	bool IsDirty;
};

UCLASS()
class FACTORYGAME_API UFGUserSettingApplyType_UpdateInstantly : public UFGUserSettingApplyType
{
	GENERATED_BODY()

	virtual bool OnApply( bool markDirty = true ) override;
	virtual FVariant GetAppliedValue() const override { return GetDisplayValue(); }
	virtual void SetValue(FVariant newValue) override;
	virtual void ClearPendingChanges() override;
};

UCLASS()
class FACTORYGAME_API UFGUserSettingApplyType_RequireGameRestart : public UFGUserSettingApplyType
{
	GENERATED_BODY()
public:
	virtual bool OnApply( bool markDirty = true ) override;
	virtual void OnPreRestartGame() override;
	virtual void ForceSetValue(FVariant newValue, bool bClearPendingValue) override;
	virtual bool ForceSetPendingAppliedValue(FVariant newValue) override;
	virtual void ResetToDefaultValue() override;
	virtual FVariant GetDisplayValue() const override;
	virtual bool HasGameRestartRequiredChanges() const override;
	virtual FVariant GetValueToSave() const override;
	virtual FVariant GetPendingAppliedValue() const override;
	virtual void GetDebugData( TArray<FString>& out_debugData ) override;
	
	FVariant ValueWaitingForGameRestart = FVariant();
};

UCLASS()
class FACTORYGAME_API UFGUserSettingApplyType_RequireSessionRestart : public UFGUserSettingApplyType
{
	GENERATED_BODY()

public:
	virtual bool OnApply( bool markDirty = true ) override;
	virtual void OnPreSessionRestart() override;
	virtual void ForceSetValue(FVariant newValue, bool bClearPendingValue) override;
	virtual bool ForceSetPendingAppliedValue(FVariant newValue) override;
	virtual void ResetToDefaultValue() override;
	virtual FVariant GetDisplayValue() const override;
	virtual bool HasSessionRestartRequiredChanges() const override;
	virtual FVariant GetValueToSave() const override;
	virtual FVariant GetPendingAppliedValue() const override;
	virtual void GetDebugData( TArray<FString>& out_debugData ) override;
	
	FVariant ValueWaitingForSessionRestart = FVariant();
};
