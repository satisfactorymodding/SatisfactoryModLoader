#include "Online/FGPlatformPermissionSubsystem.h"

bool UPermissionContext::IsContextValid() const{ return false; }
bool UPermissionContext::TryCreatePermissionContext(UWorld* world){ return false; }
void UFGPlatformPermissionSubsystem::Initialize(FSubsystemCollectionBase& Collection){ Super::Initialize(Collection); }
void UFGPlatformPermissionSubsystem::Deinitialize(){ Super::Deinitialize(); }
bool UFGPlatformPermissionSubsystem::ShouldCreateSubsystem(UObject* Outer) const{ return Super::ShouldCreateSubsystem(Outer); }
bool UFGPlatformPermissionSubsystem::IsSubsystemReady() const{ return false; }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetTextCommunicationPrivilegeForUser(const UE::Online::FAccountId& LastUGCEditBy) const{ return EPrivilegeCheckResult(); }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetCrossplayPrivilege() const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetUGCPrivilege() const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetTextCommunicationPrivilege() const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetViewProfilePrivilegeForUser(APlayerState* RequesteePlayerState) const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetViewProfilePrivilegeForOfflineUser(const FCachedPlayerInfo& RequesteeCachedPlayerInfo) const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetViewProfilePrivilegeForUser(const UE::Online::FAccountId& RequesteeAccountId) const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetViewUGCPrivilegeForUser(const UE::Online::FAccountId& RequesteeAccountId) const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::GetViewUGCPrivilegeForSessionInfo(const USessionInformation* sessionInfo) const{ return EPrivilegeCheckResult();  }
void UFGPlatformPermissionSubsystem::PollPremiumPrivilege(FUserHasPremiumAccountDelegate completeDelegate){ }
void UFGPlatformPermissionSubsystem::PollPremiumPrivilegeQueryDone(EPrivilegeResults privilegeResult){ }
void UFGPlatformPermissionSubsystem::PollPremiumPrivilegeFromCode(FOnPremiumCheckedDone completeDelegate){ }
void UFGPlatformPermissionSubsystem::PollPrivilegeFromCode(EUserPrivilege privilegeToQuery, FOnPrivilegeQueryDone completeDelegate){ }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::CheckPrivilegeValue(const EUserPrivilege& privilege) const{ return EPrivilegeCheckResult();  }
bool UFGPlatformPermissionSubsystem::HasUserThisRight(const UE::Online::FAccountId& accountId, const PlatformSpecificPermissionType& privilege, EPrivilegeCheckResult& out_value) const{ return false; }
void UFGPlatformPermissionSubsystem::NotifyGameStateBeginPlay(AFGGameState* currentGameState){ }
void UFGPlatformPermissionSubsystem::RetrieveCrossplayTextPermission(TOptional<CrossplayTextPermissionResult>& permissionResult) const{ }
void UFGPlatformPermissionSubsystem::PollUserPrivilege(const EUserPrivilege& PrivilegeToQuery, FOnPrivilegeQueryDone Callback){ }
void UFGPlatformPermissionSubsystem::UpdateBindingsAndPrivileges(UWorld* world){ }
void UFGPlatformPermissionSubsystem::UpdatePrivileges(){ }
void UFGPlatformPermissionSubsystem::QueryPermissionInformationForCachedPlayers(const TArray<FCachedPlayerInfo>& gameState){ }
void UFGPlatformPermissionSubsystem::QueryAccountIdList(const TArray<FUniqueNetIdRef>& xboxUserToQuery, const TMap<FUniqueNetIdRef, UE::Online::FAccountId>& xboxUserInfos){ }
void UFGPlatformPermissionSubsystem::BindDelegates(){ }
void UFGPlatformPermissionSubsystem::OnApplicationReactivate(){ }
void UFGPlatformPermissionSubsystem::OnCachedPlayersUpdated(const FPlayerInfoHandle& playerInfoHandle){ }
void UFGPlatformPermissionSubsystem::OnFriendListUpdated(TArray<FUniqueNetIdRepl> friendList){ }
void UFGPlatformPermissionSubsystem::OnPostLoadMap(UWorld* world){ }
void UFGPlatformPermissionSubsystem::OnBackendLoginStatusChanged(ECommonUserLoginStatus loginStatus){ }
ESessionMemberPlatformType UFGPlatformPermissionSubsystem::GetPlatformFromSessionMemberInformation(USessionMemberInformation* sessionMemberInfo) const{ return ESessionMemberPlatformType(); }
FUniqueNetIdPtr UFGPlatformPermissionSubsystem::GetUniqueNetIdFromSessionMemberInformation(USessionMemberInformation* sessionMemberInfo) const{ return FUniqueNetIdPtr(); }
UE::Online::FAccountId UFGPlatformPermissionSubsystem::GetAccountIdFromSessionMemberInformation(USessionMemberInformation* sessionMemberInfo) const{ return UE::Online::FAccountId(); }
EPrivilegeCheckResult UFGPlatformPermissionSubsystem::PrivilegeResultToCheckResult(EPrivilegeResults privilegeResult) const{ return EPrivilegeCheckResult();  }
EPrivilegeCheckResult& UFGPlatformPermissionSubsystem::GetUserPermissionRef(const UE::Online::FAccountId& accountId, const PlatformSpecificPermissionType& privilege){ return *(new EPrivilegeCheckResult);  }
TMap<UE::Online::FAccountId, EPrivilegeCheckResult> UFGPlatformPermissionSubsystem::GetPrivilgeResutsOfAllUsers(const PlatformSpecificPermissionType& privilege) const{ return TMap<UE::Online::FAccountId, EPrivilegeCheckResult>(); }
void UFGPlatformPermissionSubsystem::DisplayPremiumInformation(const FOnShowStoreUIClosedDelegate& OnShowStoreUIClosedDelegate) const{ }