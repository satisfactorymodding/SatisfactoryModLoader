// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "FGGenericListModel.h"
#include "GameFramework/PlayerController.h"
#include "MVVMViewModelBase.h"
#include "OnlineFriend.h"
#include "FGJoinableGamesViewModel.generated.h"

class FInternetAddr;
class UOnlineFriend;
class ULocalUserInfo;
class UFGSessionInformationModel;

USTRUCT()
struct FOnlineSessionInfoCache
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<TObjectPtr<UOnlineFriend>> Friends;

	UPROPERTY()
	TObjectPtr< UFGSessionInformationModel > SessionInfoModel;

	//<FL>[KonradA] Metadata for --local-- crossplay filtering
	UPROPERTY()
	bool bIsCrossPlaySession = false;

	UPROPERTY()
	FName HostPlatform;
	//</FL>
};

/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGJoinableGamesViewModel : public UFGGenericListModel
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable )
	void SetLocalUser( ULocalUserInfo* userInfo );

	UFUNCTION( BlueprintCallable )
	void JoinCustomGame( APlayerController* playerController, const FString& sessionIdStr);
	
protected:
	void FriendAdded( UOnlineFriend* newFriend );
	void FriendRemoved( UOnlineFriend* deletedFriend );
	void FriendGameSessionChanged(UObject*, UE::FieldNotification::FFieldId);
	//<FL>[KonradA]
	void LoginStateChanged( ULocalUserInfo* UserInfo, TSharedRef< UE::Online::FAccountInfo > AccountInfo, UOnlineIntegrationBackend* Backend );
	void OnFriendListReset( ULocalUserInfo* UserInfo );
	void ReAddFriends( ULocalUserInfo* UserInfo );
	FDelegateHandle ReAddFriendsDelegateHandle;
	//</FL>

	void UpdateFriendSession( UOnlineFriend* newFriend, USessionInformation* sessionInfo );
	UFUNCTION( BlueprintCallable )
	void UpdateAndFilterListEntries();
	
	UPROPERTY( BlueprintSetter=SetLocalUser, FieldNotify )
	TObjectPtr< ULocalUserInfo > mLocalUser;
	
	UPROPERTY()
	TMap< TObjectPtr< USessionInformation >, FOnlineSessionInfoCache> mJoinableOnlineSessions;

	UPROPERTY()
	TMap< TObjectPtr< UOnlineFriend >, TObjectPtr< USessionInformation > > mFriendSessionMap;

	UPROPERTY()
	TArray< TObjectPtr< UFGGenericListItemDescriptor > > mUnfilteredListEntires;
};
