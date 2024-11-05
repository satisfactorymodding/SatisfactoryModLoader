// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	UFUNCTION()
	void SetSessionName(const FString& inSessionName);

	UFUNCTION()
	void SetCurrentGamePhase(UFGGamePhase* inCurrentPhase);

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

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	FString mSessionName;

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

	UPROPERTY( BlueprintReadOnly, FieldNotify )
	TSubclassOf<UFGSchematic> mActiveSchematic;
	
	FDelegateHandle mSessionSettingsUpdatedDelegateHandle;
	FDelegateHandle mSessionSettingsAddedDelegateHandle;
	FDelegateHandle mSessionSettingsRemovedDelegateHandle;
};