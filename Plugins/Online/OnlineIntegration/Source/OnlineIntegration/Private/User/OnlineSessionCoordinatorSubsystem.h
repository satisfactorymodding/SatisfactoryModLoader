// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorldSubsystem.h"

#include "OnlineSessionCoordinatorSubsystem.generated.h"

class USessionInformation;
class USessionDefinition;
class UOnlineSessionBackendLink;
class UOnlineIntegrationControllerComponent;

USTRUCT()
struct FPerBackendSessionMemberData
{
	GENERATED_BODY()

	/**
	 * The session backend link for the online session stored on this backend.
	 */
	UPROPERTY()
	FString MirrorSessionIdStr;

	/**
	 * The host of the session. This is the player that created the session.
	 */
	UPROPERTY()
	TObjectPtr<UOnlineIntegrationControllerComponent> Host;

	/**
	 * If the creation of a mirror session for this backend is currently pending, this will be set to the player that is hosting it.
	 */
	UPROPERTY()
	TObjectPtr<UOnlineIntegrationControllerComponent> PendingHost;

	/**
	 * All the session members playing on this backend.
	 */
	UPROPERTY()
	TSet<TObjectPtr<UOnlineIntegrationControllerComponent>> Members;
	
	UPROPERTY()
	TSet<TObjectPtr<UOnlineIntegrationControllerComponent>> PendingMembers;

	/**
	 * Whether this session is hosted by a local player.
	 */
	bool bIsNativeSession = false;

	/**
	 * Whether this session is the main session (implies it is also native).
	 */
	bool bIsMainSession = false;
};

/**
 * World subsystem responsible for tracking and coordinating mirror session ownership and creation. 
 */
UCLASS()
class ONLINEINTEGRATION_API UOnlineSessionCoordinatorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void RegisterControllerComponent(UOnlineIntegrationControllerComponent* ControllerComponent);
	void UnregisterControllerComponent(UOnlineIntegrationControllerComponent* ControllerComponent);
	void BroadcastPresenceUpdate(FDateTime TimeStamp);
protected:
	void MirrorSessionCreated(UOnlineIntegrationControllerComponent* HostingControllerComponent, const FString& SessionIdstr);
	
	// Begin UWorldSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	// End UWorldSubsystem interface

	UPROPERTY()
	TMap<FName, FPerBackendSessionMemberData> PerBackendSessionMemberData;

	UPROPERTY()
	TObjectPtr<USessionDefinition> SessionDefinition;
	
	UPROPERTY()
	TObjectPtr<USessionInformation> SessionInformation;
};
