#include "OnlineUserRegistryEOSAccountMapperExtension.h"

void UOnlineUserRegistryEOSAccountMapperExtension::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

TOptional<TFuture<UOnlineUserInfo*>> UOnlineUserRegistryEOSAccountMapperExtension::ResolveOnlineUser(
	ULocalUserInfo* LocalUser, UOnlineUserBackendLink* BackendLink) {
	return IOnlineUserRegistryExtension::ResolveOnlineUser(LocalUser, BackendLink);
}

void UOnlineUserRegistryEOSAccountMapperExtension::UserBackendLinkInitialized(UOnlineUserBackendLink* UserBackendLink) {
	IOnlineUserRegistryExtension::UserBackendLinkInitialized(UserBackendLink);
}

void UOnlineUserRegistryEOSAccountMapperExtension::Tick(float DeltaTime) {
}

TStatId UOnlineUserRegistryEOSAccountMapperExtension::GetStatId() const {
	return TStatId{};
}

bool UOnlineUserRegistryEOSAccountMapperExtension::IsTickable() const {
	return FTickableGameObject::IsTickable();
}

bool UOnlineUserRegistryEOSAccountMapperExtension::IsTickableWhenPaused() const {
	return FTickableGameObject::IsTickableWhenPaused();
}

void UOnlineUserRegistryEOSAccountMapperExtension::WorkOnResolves(ULocalUserInfo* LocalUser) {
}
