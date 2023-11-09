// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "OnlineAsyncOperation.h"
#include "OnlineIntegrationTypes.h"
#include "Engine/Engine.h"
#include "SessionMigrationSequence.generated.h"

class FControlFlowNode;
class UCommonSessionSubsystem;
class ULocalUserInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionSetupComplete);

/**
 * w
 */
UCLASS()
class ONLINEINTEGRATION_API USessionMigrationSequence : public UOnlineAsyncOperation
{
	GENERATED_BODY()

protected:
	virtual void Cancel() override;
	void DestroySession(TSharedRef<FControlFlowNode>, ULocalUserInfo* LocalUser, EOnlineIntegrationUnmappedContext Context);
	
	void NotifySessionSetupComplete() const;
	
	void BindTravelDelegates();

	UPROPERTY()
	TObjectPtr<UCommonSessionSubsystem> CommonSessionSubsystem;

	/** Called when we have finished only session operations */
	UPROPERTY(BlueprintAssignable)
	FOnSessionSetupComplete OnSessionSetupComplete;

private:
	/** Called when traveling to a session fails */
	virtual void TravelLocalSessionFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ReasonString);

	/** Called after traveling to the new hosted session map */
	virtual void HandlePostLoadMap(UWorld* World);
	
	FDelegateHandle OnTravelFailureDelegateHandle;
	FDelegateHandle OnPostLoadMapWithWorldDelegateHandle;
};


