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

	// TODO: Use this to sync the settings to the client on join

	static ASessionSettingsSubsystem* Get(UWorld* World);

	void OnSessionSettingUpdated(const FString StrID, FVariant value);
	void PushSettingToSessionSettings( const FString& StrID, FVariant value );

private:	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SessionSettingUpdated(const FString& StrID, const FString& ValueString);

	FOnOptionUpdated OnOptionUpdatedDelegate;
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
	UPROPERTY(Replicated)
	bool mForceNetField_USMLSessionSettingsRemoteCallObject;
};