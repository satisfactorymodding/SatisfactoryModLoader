#pragma once
#include "CoreMinimal.h"
#include "FGRemoteCallObject.h"
#include "SessionSettingsManager.h"
#include "Subsystem/ModSubsystem.h"
#include "SessionSettingsSubsystem.generated.h"

UCLASS()
class SML_API ASessionSettingsSubsystem : public AModSubsystem {
	GENERATED_BODY()
public:
	ASessionSettingsSubsystem();
	
	virtual void Init() override;

	static ASessionSettingsSubsystem* Get(UWorld* World);

	void OnSessionSettingUpdated(const FString StrID, FVariant value);
	void PushSettingToSessionSettings( const FString& StrID, FVariant value );

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SessionSettingUpdated(const FString& StrID, const FString& ValueString);

	FOnOptionUpdated OnOptionUpdatedDelegate;

	UFUNCTION()
	void OnRep_SessionSettingsNames();

	UPROPERTY(ReplicatedUsing=OnRep_SessionSettingsNames)
	TArray<FString> SessionSettingsNames;

	bool HasPendingSessionSettingsRequest = false;
	int ReceivedSessionSettings = 0;

	friend class USMLSessionSettingsRemoteCallObject;
};

UCLASS(NotBlueprintable)
class SML_API USMLSessionSettingsRemoteCallObject : public UFGRemoteCallObject {
	GENERATED_BODY()
public:
	USMLSessionSettingsRemoteCallObject();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RequestSessionSettingUpdate(const FString& SessionSettingName, const FString& ValueString);

private:
	UFUNCTION(Server, Reliable)
	void Server_RequestInitialSessionSettings(const int& CurrentIndex);
	
	UFUNCTION(Client, Reliable)
	void Client_RespondInitialSessionSettings(const TArray<FString>& SessionSettingsValues);

	UPROPERTY(Replicated)
	bool mForceNetField_USMLSessionSettingsRemoteCallObject;

	friend class ASessionSettingsSubsystem;
};
