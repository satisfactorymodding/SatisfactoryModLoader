// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGGameState.h"
#include "FGGenericListModel.h"
#include "FGSaveManagerInterface.h"
#include "FGSessionInformationModel.generated.h"

class USessionDefinition;
struct FCustomOnlineSessionSetting;
class AFGGameState;
class USessionInformation;
class UFGGamePhase;

UENUM(BlueprintType)
enum class EFactorySessionState: uint8
{
	Loading,
	IntroSequence,
	Running,
	Paused
};

/**
 * Read only view of the session information that is driven by online session metadata. Set up as a model for easy access from UMG
 */
UCLASS()
class FACTORYGAME_API UFGSessionInformationModel : public UFGGenericListModel
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable )
	void SetOnlineSessionInfo( USessionInformation* inOnlineSessionInfo );

	USessionInformation* GetOnlineSession() const
	{
		return mOnlineSessionInfo;
	}
	
	void InitializeState( APlayerController* firstPlayerController, AFGGameState* inGameState );
	void SetSessionState(EFactorySessionState inSessionState, FTimespan inGameDuration);

	UFUNCTION()
	void SetCrossPlayAllowed( bool bAllowCrossPlay );
	// In a crossplay session, a player's primary backend might not be the platform he's playing on.
	// e.g. If you are playing on platform A and your friend has an Epic account that is linked to platform A and B.
	//      Even when he is playing on platform B, his primary backend is still A from your perspective.
	UFUNCTION()
	void SetOriginLocalPlatformName( FString OLPName );

	// <FL> [MartinC] Set the platform avatar URL of the session host
	UFUNCTION()
	void SetPlatformAvatarURL( FString AvatarURL );

	void AddPlayerToSession(AFGPlayerState* inPlayerState);
	void RemovePlayerFromSession(AFGPlayerState* inPlayerState);

	static TArray< FCustomOnlineSessionSetting > GetInitialSessionSettingsFromSaveHeader( const FSaveHeader& saveHeader );
	static TArray< FCustomOnlineSessionSetting > GetInitialSessionSettingsForNewGame( const FString& sessionName, bool isCreativeModeEnabled );

protected:
	
	void OnSessionAttributesAdded( const TArray<FCustomOnlineSessionSetting>& newAttributes );
	void OnSessionAttributesRemoved( const TArray<FName>& removedAttributes );
	void OnSessionAttributesUpdated( const TArray<FCustomOnlineSessionSetting>& updatedAttributes );

	void RebuildRows();
	

	void SetCreativeModeEnabled( bool isEnabled );

#if( PLATFORM_PS5 || PLATFORM_XSX )
public:
#endif	  //( PLATFORM_PS5 || PLATFORM_XSX )

	UFUNCTION()
	void SetSessionName(const FString& inSessionName);

protected:

	UFUNCTION()
	void SetCurrentGamePhase(UFGGamePhase* inCurrentPhase, bool bSuppressNarrativeMessages);


	UFUNCTION()
	void SetActiveSchematic(TSubclassOf<UFGSchematic> inActiveSchematic);

	UFUNCTION()
	void ReadyToReadFromSubsystems();
	
	void InitializeStateFromSubsystems(bool flushMetadata);
	
	UPROPERTY()
	TObjectPtr<AFGGameState> mGameState;
	
	UPROPERTY()
	TObjectPtr<APlayerController> mFirstLocalPlayerController;

	UPROPERTY( BlueprintReadWrite, BlueprintSetter=SetOnlineSessionInfo, FieldNotify )
	TObjectPtr< USessionInformation > mOnlineSessionInfo;

#if( PLATFORM_PS5 || PLATFORM_XSX )
public:
#endif	  //( PLATFORM_PS5 || PLATFORM_XSX )
	UPROPERTY( BlueprintReadOnly, FieldNotify )
	FString mSessionName;

protected:
	UPROPERTY( BlueprintReadOnly, FieldNotify )
	FDateTime mLastUpdateUTCTimestamp;

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	FTimespan mLastUpdateDuration;

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	EFactorySessionState mSessionState;

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	FString mVersionString;

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	bool mIsCreativeModeEnabled = false;

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	int32 mNumSessionMembers = 0;

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	int32 mMaxSessionMembers = 0;

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	TObjectPtr<UFGGamePhase> mCurrentGamePhase;

	//<FL>[KonradA]
	UPROPERTY( BlueprintReadOnly, FieldNotify )
	bool mbAllowCrossPlay = true;
	//</FL>

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	FName mOriginLocalPlatformName;

	//<FL>[MartinC] Platform avatar URL of the host
	UPROPERTY( BlueprintReadOnly, FieldNotify )
	FString mPlatformAvatarURL;
	//</FL>

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	TSubclassOf<UFGSchematic> mActiveSchematic;
	
	FDelegateHandle mSessionSettingsUpdatedDelegateHandle;
	FDelegateHandle mSessionSettingsAddedDelegateHandle;
	FDelegateHandle mSessionSettingsRemovedDelegateHandle;
};
