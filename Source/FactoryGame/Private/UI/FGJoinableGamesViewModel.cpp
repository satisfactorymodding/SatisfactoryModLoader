// This file has been automatically generated by the Unreal Header Implementation tool

#include "UI/FGJoinableGamesViewModel.h"

void UFGJoinableGamesViewModel::SetLocalUser(ULocalUserInfo* userInfo){ }
void UFGJoinableGamesViewModel::JoinCustomGame(APlayerController* playerController, const FString& sessionIdStr){ }
void UFGJoinableGamesViewModel::FriendAdded(UOnlineFriend* newFriend){ }
void UFGJoinableGamesViewModel::FriendRemoved(UOnlineFriend* deletedFriend){ }
void UFGJoinableGamesViewModel::FriendGameSessionChanged(UObject*, UE::FieldNotification::FFieldId){ }
void UFGJoinableGamesViewModel::LoginStateChanged(ULocalUserInfo* UserInfo, TSharedRef<UE::Online::FAccountInfo> AccountInfo, UOnlineIntegrationBackend* Backend){  }
void UFGJoinableGamesViewModel::OnFriendListReset(ULocalUserInfo* UserInfo){  }
void UFGJoinableGamesViewModel::ReAddFriends(ULocalUserInfo* UserInfo){  }
void UFGJoinableGamesViewModel::UpdateFriendSession(UOnlineFriend* newFriend, USessionInformation* sessionInfo){ }
void UFGJoinableGamesViewModel::UpdateAndFilterListEntries(){  }