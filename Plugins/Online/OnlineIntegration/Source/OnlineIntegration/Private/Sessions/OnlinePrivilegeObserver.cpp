#include "Sessions/OnlinePrivilegeObserver.h"

void UFailedPrivilegeCheckResult::Reset(UOnlineIntegrationBackend* InBackend, ECommonUserPrivilege InPrivilege, ECommonUserPrivilegeResult InResult, const FText& InFailureDescription){ }
void UOnlinePrivilegeObserver::Initialize(ULocalUserInfo* userInfo, const USessionDefinition* SessionDefinition){ }
void UOnlinePrivilegeObserver::OnBackendLoginStateChanged(ULocalUserInfo* userInfo, TSharedRef<UE::Online::FAccountInfo> AccountInfo, UOnlineIntegrationBackend* Backend){ }
void UOnlinePrivilegeObserver::OnBackendConnectionStateChanged(UObject*, UE::FieldNotification::FFieldId){ }
void UOnlinePrivilegeObserver::OnApplicationReactivated(){ }
void UOnlinePrivilegeObserver::OnPrivilegeQueryDone(UOnlineIntegrationBackend* Backend, ECommonUserPrivilege Privilege, ECommonUserPrivilegeResult PrivilegeResult){ }
void UOnlinePrivilegeObserver::QueryAllPrivilegesForBackend(UOnlineIntegrationBackend* Backend){ }
