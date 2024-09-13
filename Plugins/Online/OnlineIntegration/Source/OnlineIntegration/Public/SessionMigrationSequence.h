// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "OnlineAsyncOperation.h"
#include "OnlineIntegrationTypes.h"
#include "Engine/Engine.h"
#include "SessionMigrationSequence.generated.h"

class UOnlineIntegrationBackend;
class FControlFlowNode;
class UCommonSessionSubsystem;
class ULocalUserInfo;
class UOnlineIntegrationSubsystem;
class USessionInformation;

using FOnSessionSetupComplete = TDelegate<void(USessionInformation*)>;

/**
 * w
 */
UCLASS(Hidden, Abstract, NotBlueprintable)
class ONLINEINTEGRATION_API USessionMigrationSequence : public UOnlineAsyncOperation
{
	GENERATED_BODY()
public:
	virtual bool Start();

	FDelegateHandle AddOnSessionSetupCompleteDelegate(FOnSessionSetupComplete Delegate);
	virtual bool IsHostingSession() const;
	
protected:
	virtual void Cancel() override;
	void DestroySession(TSharedRef<FControlFlowNode>, ULocalUserInfo* LocalUser, UOnlineIntegrationBackend* Backend);
	void NotifySessionSetupComplete(USessionInformation* OnlineSessionInfo) const;
	void BindTravelDelegates();

	UPROPERTY()
	TObjectPtr<UCommonSessionSubsystem> CommonSessionSubsystem;

	UPROPERTY()
	TObjectPtr<UOnlineIntegrationSubsystem> OnlineIntegrationSubsystem;

	/** Called when we have finished only session operations */
	TMulticastDelegate<void(USessionInformation*)> OnSessionSetupComplete;

	virtual void OnTravelFinished(UWorld* World);
	virtual void OnTravelFailure();
private:
	/** Called when traveling to a session fails */
	void TravelLocalSessionFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ReasonString);

	/** Called after traveling to the new hosted session map */
	void HandlePostLoadMap(UWorld* World);
	
	FDelegateHandle OnTravelFailureDelegateHandle;
	FDelegateHandle OnPostLoadMapWithWorldDelegateHandle;
};


