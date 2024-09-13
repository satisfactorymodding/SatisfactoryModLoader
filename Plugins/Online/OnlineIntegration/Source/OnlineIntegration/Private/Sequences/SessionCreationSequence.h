// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CommonSessionSubsystem.h"
#include "ControlFlowNode.h"
#include "MVVMViewModelBase.h"
#include "SessionMigrationSequence.h"
#include "OnlineInteractionHandlers.h"
#include "SessionCreationSequence.generated.h"


class FControlFlowNode;
class FControlFlow;
class FControlFlowBranch;
/**
 * 
 */
UCLASS(Within=CommonSessionSubsystem, Hidden)
class USessionCreationSequence final: public USessionMigrationSequence
{
	GENERATED_BODY()
public:
	void Initialize(const FCommonSessionCreationSettings& SessionSettings);

protected:
	virtual bool Start() override;
	virtual bool IsHostingSession() const override;
	virtual void OnTravelFinished(UWorld* World) override;

	EConditionalLoopResult SessionCleanupLoop(TSharedRef<FConditionalLoop> LoopNodeRef);
	void CreateMainSession(TSharedRef<FControlFlowNode>);
	EConditionalLoopResult MirrorSessionCreationLoop(TSharedRef<FConditionalLoop> LoopNodeRef);
	EConditionalLoopResult SessionMetadataUpdateLoop(TSharedRef<FConditionalLoop> LoopNodeRef);
	
	void IncrementSessionCleanupLoopIndex();
	void IncrementMirrorSessionCreationLoopIndex();
	void IncrementSessionMetadataUpdateLoopIndex();
	
	void CreateSession(TSharedRef<FControlFlowNode>, UOnlineIntegrationBackend* Backend);
	void StoreSessionMetadata(TSharedRef<FControlFlowNode>, UOnlineIntegrationBackend* Backend);
	void Travel();
	void NotifySetupComplete();
	
	UPROPERTY(BlueprintReadOnly)
	FCommonSessionCreationSettings SessionCreationSettings;

	UPROPERTY()
	TScriptInterface<ISessionCreationInteractionHandler> InteractionHandler;

	UPROPERTY()
	TObjectPtr<UOnlineIntegrationBackend> SessionBackend;

	UPROPERTY()
	TObjectPtr<UOnlineIntegrationState> OnlineIntegrationState;

	TOptional<EOfflineSessionPromptResult> OfflineSessionPromptResult;
	TSharedPtr<FControlFlow> ControlFlow;
	TSharedPtr<FControlFlowNode> PreconditionsWaitingNode;
	TMap<FName, TSharedRef<const UE::Online::ISession>> SessionCache;
	
	int32 SessionCleanupLoopIndex = 0;
	int32 MirrorSessionCreationLoopIndex = 0;
	int32 SessionMetadataUpdateLoopIndex = 0;
};
