// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Online/CoreOnline.h"

#include "OnlineIntegrationControllerComponent.generated.h"

class USessionDefinition;
class UOnlineUserInfo;

USTRUCT()
struct FMirrorSessionCreationParams
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<USessionDefinition> SessionDefinition;

	UPROPERTY()
	FName ActiveSessionProfile;

	UPROPERTY()
	int32 MaxPlayerCount;

	UPROPERTY()
	FString MainSessionId;
};

DECLARE_DELEGATE_TwoParams(FOnMirrorSessionCreated, UOnlineIntegrationControllerComponent* PlayerComponent, const FString& NewSessionIdStr);

USTRUCT()
struct FSessionMemberAccountIdData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<uint8> AccountIdRepData;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Within = PlayerController)
class ONLINEINTEGRATION_API UOnlineIntegrationControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOnlineIntegrationControllerComponent();

	FName GetPlayerPlatformBackend() const;
	UE::Online::FAccountId GetPlatformAccountId() const;

	void HostMirrorSession(const FMirrorSessionCreationParams& SessionCreationParams, FOnMirrorSessionCreated OnSessionCreated);
	void AddSessionMember(UE::Online::FAccountId Member);
	void RemoveSessionMember(UE::Online::FAccountId Member);
	void AddSessionMembers(TArray<UE::Online::FAccountId>& Members);
	void RemoveSessionMembers(TArray<UE::Online::FAccountId>& Members);
	void UpdateSessionTimestampInPresence(FDateTime SessionTimestamp);

	void UpdateMirrorSession(const FString& SessionIdStr);
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	APlayerController* GetPlayerController() const;
	void DestroyMirrorSession();

	UFUNCTION(Server, Reliable)
	void Server_RegisterControllerComponent(const TArray<uint8>& PlatformAccountIdRepData, FName PlatformBackend);
	
	UFUNCTION(Client, Reliable)
	void Client_ReceiveMirrorSession(const FString& SessionIdStr);

	UFUNCTION(Client, Reliable)
	void Client_RequestHostMirrorSession(const FMirrorSessionCreationParams& SessionCreationParams);

	UFUNCTION(Server, Reliable)
	void Server_ReceiveMirrorSession(const FString& SessionIdStr);

	UFUNCTION(Client, Reliable)
	void Client_AddSessionMembers(const TArray<FSessionMemberAccountIdData>& MembersAccountIdData);

	UFUNCTION(Client, Reliable)
	void Client_RemoveSessionMembers(const TArray<FSessionMemberAccountIdData>& MembersAccountIdData);

	UFUNCTION(Client, Reliable)
	void Client_UpdateSessionTimestampInPresence(FDateTime SessionTimestamp);
	/**
	 * The platform backend that the player is using. For example, if this player is playing from Steam, this will be Steam.
	 * On the server, this is set by the client in @Server_RegisterControllerComponent
	 */
	FName PlayerPlatformBackend;
	UE::Online::FAccountId PlatformAccountId;

	TOptional<UE::Online::FOnlineSessionId> HostedMirrorSession;

	FOnMirrorSessionCreated OnMirrorSessionCreated;
};
