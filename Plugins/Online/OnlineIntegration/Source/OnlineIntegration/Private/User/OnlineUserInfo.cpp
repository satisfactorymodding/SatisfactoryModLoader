// This file has been automatically generated by the Unreal Header Implementation tool

#include "User/OnlineUserInfo.h"

#include "GameplayTagContainerViewModel.h"

UOnlineUserInfo::UOnlineUserInfo(){ }
UOnlineUserBackendLink* UOnlineUserInfo::GetUserBackend(const UOnlineIntegrationBackend* Backend){ return nullptr; }
const UOnlineUserBackendLink* UOnlineUserInfo::GetUserBackend(const UOnlineIntegrationBackend* Backend) const{ return nullptr; }
UOnlineUserBackendLink* UOnlineUserInfo::GetPrimaryBackendLink(){ return nullptr; }
const UOnlineUserBackendLink* UOnlineUserInfo::GetPrimaryBackendLink() const{ return nullptr; }
UOnlineUserBackendLink* UOnlineUserInfo::GetBackendByIndex(int32 Index){ return nullptr; }
UOnlineUserBackendLink* UOnlineUserInfo::GetUserBackendByProvider(FName ProviderName) const{ return nullptr; }
TArray<UOnlineUserBackendLink*> UOnlineUserInfo::GetUserBackendLinks() const{ return TArray<UOnlineUserBackendLink*>(); }
int32 UOnlineUserInfo::NumBackendLinks() const{ return int32(); }
const UGameplayTagContainerViewModel& UOnlineUserInfo::GetTagContainer() const{ return *NewObject<UGameplayTagContainerViewModel>(); }
UOnlineUserBackendLink* UOnlineUserInfo::GetUserBackendEpic() const{ return nullptr; }
UOnlineUserBackendLink* UOnlineUserInfo::GetUserBackendLinkForAccountId(UE::Online::FAccountId AccountId) const{ return nullptr; }
