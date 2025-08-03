// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CommonSessionTypes.h"
#include "ControlFlow.h"
#include "SessionCreationSettings.h"
#include "SessionMigrationSequence.h"

#include "SessionJoiningSequence.generated.h"

class USessionInformation;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class USessionJoiningSequence : public USessionMigrationSequence
{
	GENERATED_BODY()
public:
	void Initialize(const FSessionJoinParams& InJoinParams, UCommonSessionSubsystem *Subsystem);
	virtual bool Start() override;
	
	// <FL> [BGR] Error collection to select propper one for user messaging
	bool HasErrors() const override { return !Errors.IsEmpty(); }

protected:
	virtual void NotifySequenceFinished() override;
	// </FL>

private:
	void JoinSession(TSharedRef<FControlFlowNode>, FCommonSession Session);
	void ClientTravel();
	void CleanupSessions(TSharedRef<FControlFlowNode> SubFlow);
	void JoinSessions(TSharedRef<FControlFlowNode> SubFlow);
	
	void IncrementBackendIndex();
	
	UPROPERTY()
	TObjectPtr<ULocalUserInfo> LocalUserInfo;

	UPROPERTY()
	TObjectPtr<UOnlineIntegrationBackend> SessionBackend;

	UPROPERTY()
	FSessionJoinParams JoinParams;

	// <FL> [BGR] Error collection to select propper one for user messaging
	TArray<TTuple<FGameplayTag, UE::Online::FOnlineError>> Errors;
	// </FL>

	// TMap<FName, FCommonSession> SessionHandleMap;
	TMap<FName, TSharedPtr<const UE::Online::ISession>> SessionPtrMap;

	TSharedPtr<FControlFlow> ControlFlow;
	int32 BackendIndex = 0;
	int32 MirrorSessionLookupLoopIndex = 0;
	int32 SessionJoinLoopIndex = 0;

	// <FL> [BGR] EOS response timeout
protected:

	UPROPERTY(Config)
	float SessionJoiningTimeout = -1.0f;

private:
	FTimerHandle TimeoutHandle;

	void OnTimeout();
	// </FL>
};

