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
UCLASS()
class USessionJoiningSequence : public USessionMigrationSequence
{
	GENERATED_BODY()
public:
	void Initialize(const FSessionJoinParams& InJoinParams, UCommonSessionSubsystem *Subsystem);
	virtual bool Start() override;
	
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

	// TMap<FName, FCommonSession> SessionHandleMap;
	TMap<FName, TSharedPtr<const UE::Online::ISession>> SessionPtrMap;

	TSharedPtr<FControlFlow> ControlFlow;
	int32 BackendIndex = 0;
	int32 MirrorSessionLookupLoopIndex = 0;
	int32 SessionJoinLoopIndex = 0;
};

