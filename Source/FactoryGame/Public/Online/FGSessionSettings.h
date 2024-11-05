// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CommonSessionSubsystem.h"
#include "CoreMinimal.h"
#include "FGOptionInterfaceImpl.h"
#include "OnlineIntegrationTypes.h"
#include "Sessions/SessionDefinition.h"
#include "Settings/FGUserSetting.h"
#include "Settings/FGUserSettingApplyType.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MVVMViewModelBase.h"
#include "FGSessionSettings.generated.h"

UCLASS()
class FACTORYGAME_API UFGSessionDefinitionOptionModel: public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetDisplaySessionDefinition(USessionDefinition* SessionDefinition)
	{
		UE_MVVM_SET_PROPERTY_VALUE( mDisplaySessionDefinition, SessionDefinition );
	}
	
protected:
	/**
	 * Will be onne of @mCurrentSessionDefinition or @mActiveSessionDefinition depending on whether a session is currently ongoing or not.
	 * It's a convenience so BPs do not have to write complicated logic to determine which one to use. 
	 */
	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mDefaultSessionDefinition;

	/**
	 * The currently configured session definition, the one that will be used if a new session was to be created now. 
	 */
	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mCurrentSessionDefinition;

	/**
	 * The active session definition. The one that has been used to host the current session. Will only be set to a valid value
	 * when currently in a session. 
	 */
	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mActiveSessionDefinition;

	/**
	 * Will be the value actually displayed in the option widget. Might be a pending value, might be a default value. 
	 */
	UPROPERTY( FieldNotify, BlueprintReadWrite, BlueprintSetter=SetDisplaySessionDefinition, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mDisplaySessionDefinition;

	/**
	 * The currently selected session definition, in the session settings UI. This needs to be applied before it will be used.
	 */
	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mPendingSessionDefinition;
};

USTRUCT(BlueprintType)
struct FSessionProfilePath
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Path;

	bool operator==(const FSessionProfilePath& Other) const
	{
		return Path == Other.Path;
	}
};

DECLARE_MULTICAST_DELEGATE_OneParam( FOnSessionDefinitionChanged, USessionDefinition* );

UCLASS()
class UFGSessionSettingsModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	friend class UFGSessionSettings;
public:

	UFUNCTION( BlueprintCallable )
	void SetSessionDefinition( USessionDefinition* SessionDefinition );

	UFUNCTION( BlueprintCallable )
	void SetSessionProfile( const FSessionProfilePath& ProfilePath);
	
	UFUNCTION( BlueprintCallable )
	void SetSessionName( FString SessionName );
	
	UFUNCTION( BlueprintPure, FieldNotify )
	bool HasPendingSessionDefinition() const;

	UFUNCTION( BlueprintPure, FieldNotify )
	bool HasPendingSessionProfile() const;
	
	UFUNCTION( BlueprintPure, FieldNotify )
	bool HasPendingSessionName() const;

	UFUNCTION( BlueprintPure, FieldNotify )
	bool RequiresSessionRestart() const;

	UFUNCTION( BlueprintCallable )
	void Reset();
	
	UFUNCTION( BlueprintCallable, Category = "Session Settings" )
	const FString& GetSessionName() const;

	USessionDefinition* GetSessionDefinition() const;

	UFUNCTION( BlueprintCallable, Category = "Session Settings" )
	FName GetSessionProfile() const;
	bool IsInGameModel() const { return mInGameSettingsModel; }
protected:
	void SetActiveSessionDefinition( USessionDefinition* activeSessionDefinition );
	void SetCurrentSessionDefinition( USessionDefinition* activeSessionDefinition );
	
	UFUNCTION()
	void SetCurrentSessionName(const FString& currentSessionName);
	
	void InitializeModel( UFGSessionSettings* sessionSettings, AFGGameMode* gameMode );
	/**
	 * Will be onne of @mCurrentSessionDefinition or @mActiveSessionDefinition depending on whether a session is currently ongoing or not.
	 * It's a convenience so BPs do not have to write complicated logic to determine which one to use. 
	 */
	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mDefaultSessionDefinition;

	/**
	 * Will be the value actually displayed in the option widget. Might be a pending value, might be a default value. 
	 */
	UPROPERTY( FieldNotify, BlueprintReadWrite, BlueprintSetter=SetSessionDefinition, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mSessionDefinition;

	/**
	 * The session definition that is used to host the current session, as determined by @UFGSessionSettings
	 */
	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mActiveSessionDefinition;

	/**
	 * The session definition that will be used to host the next session. The last applied user preference, or the default.
	 */
	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionDefinition" )
	TObjectPtr< USessionDefinition > mCurrentSessionDefinition;

	// UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionProfile" )
	// FSessionProfilePath mDisplaySessionProfile;

	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionProfile" )
	FSessionSettingsProfile mSessionSettingsProfile;

	UPROPERTY( FieldNotify, BlueprintReadOnly, Category="SessionName" )
	FString mCurrentSessionName;

	UPROPERTY( FieldNotify, BlueprintReadWrite, BlueprintGetter = GetSessionName, BlueprintSetter = SetSessionName, Category="SessionName" )
	FString mSessionName;
	
	UPROPERTY( FieldNotify, BlueprintReadOnly )
	bool mInGameSettingsModel = false;

	UPROPERTY()
	TObjectPtr<UOnlineIntegrationState> mOnlineIntegrationState;

	UPROPERTY()
	TObjectPtr<UFGSessionSettings> mSessionSettings;
};

/**
 * Implementation of the session settings for the local worlds
 */
UCLASS( BlueprintType, Config = "GameUserSettings" )
class FACTORYGAME_API UFGSessionSettings : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FCommonSessionCreationSettings MakeSessionCreationSettings(APlayerController* Host, const FString& SessionName, const FSoftObjectPath& MapAssetName, const FCreateNewGameParameters& CreateNewGameParameters);

	// Begin UWorldSubsystem interface
	void Initialize(FSubsystemCollectionBase& Collection) override;
	// End UWorldSubsystem

	UFUNCTION(BlueprintCallable)
	void ApplySettingsModel(UFGSessionSettingsModel* Model);

	UFUNCTION( BlueprintCallable, Category = "Session Settings" )
	void SetSessionSettingsProfile( FName ProfileName );
	
	UFUNCTION( BlueprintCallable, Category = "Session Settings" )
	UFGSessionSettingsModel* MakeSessionSettingsModel( AFGGameMode* gameMode );

	UFUNCTION( BlueprintCallable, Category = "Session Settings" )
	FName GetCurrentProfileForSessionDefinition( USessionDefinition* SessionDefinition );

	USessionDefinition* GetCurrentSessionDefinition() const { return mCurrentSessionDefinition; }
	USessionDefinition* GetActiveSessionDefinition() const { return mActiveSessionDefinition; }

	UFUNCTION( BlueprintPure )
	FSessionProfilePath MakeSessionProfilePathFromDefinitionAndProfile( USessionDefinition* SessionDefinition, const FSessionSettingsProfile &Profile ) const;

	UFUNCTION( BlueprintPure )
	FSessionProfilePath MakeSessionProfilePathFromDefinitionAndProfileName( USessionDefinition* SessionDefinition, FName ProfileName ) const;

	UFUNCTION( BlueprintPure )
	USessionDefinition* SessionDefinitionFromProfilePath( const FSessionProfilePath& SessionProfile ) const;

	UFUNCTION( BlueprintPure )
	FName SessionProfileNameFromProfilePath( const FSessionProfilePath& SessionProfile ) const;

	UFUNCTION( BlueprintPure )
	FSessionSettingsProfile SessionProfileFromProfilePath( const FSessionProfilePath& SessionProfile ) const;

	FDelegateHandle AddOnActiveSessionDefinitionChangedDelegate(FOnSessionDefinitionChanged::FDelegate&& Delegate);
	FDelegateHandle AddOnCurrentSessionDefinitionChangedDelegate(FOnSessionDefinitionChanged::FDelegate&& Delegate);
	
protected:
	UFUNCTION()
	void PostLoadMap(UWorld* world);
	void SetActiveSessionDefinition( USessionDefinition* SessionDefinition );

	/**
	 * The currently configured session definition, the one that will be used if a new session was to be created now. 
	 */
	UPROPERTY( BlueprintReadOnly, Transient )
	TObjectPtr< USessionDefinition > mCurrentSessionDefinition;

	/**
	 * The active session definition. The one that has been used to host the current session. Will only be set to a valid value
	 * when currently in a session. 
	 */
	UPROPERTY( BlueprintReadOnly, Transient )
	TObjectPtr< USessionDefinition > mActiveSessionDefinition;
	
	UPROPERTY( Config )
	FName mSessionDefinitionName;

	UPROPERTY( Config, BlueprintReadOnly )
	FName mSessionSettingsProfile;

	UPROPERTY( Config )
	TMap< FName, FName > mLastUsedProfilePerSessionDefinition;

	FOnSessionDefinitionChanged mOnActiveSessionDefinitionChanged;
	FOnSessionDefinitionChanged mOnCurrentSessionDefinitionChanged;
};
