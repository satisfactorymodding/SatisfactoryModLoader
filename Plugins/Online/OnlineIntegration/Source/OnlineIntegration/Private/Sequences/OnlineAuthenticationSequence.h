#pragma once

#include "Auth.h"
#include "ControlFlowNode.h"
#include "MVVMViewModelBase.h"
#include "OnlineAsyncOperation.h"
#include "UObject/Interface.h"
#include "Async/Future.h"
#include "OnlineIntegrationTypes.h"
#include "Online/OnlineResult.h"
#include "OnlineAuthenticationSequence.generated.h"

class ULocalUserInfo;
class FConditionalLoop;
class FControlFlowNode;
class FControlFlow;
class FControlFlowBranch;
class IOnlineAuthenticationHandler;
class UOnlineIntegrationBackend;

UCLASS(Config=Engine, PerObjectConfig)
class UOnlineAuthenticationSequence: public UOnlineAsyncOperation
{
	GENERATED_BODY()
public:
	void Initialize(FPlatformUserId PlatformUserId);
	void Start(FOnOnlineAsyncOperationCompleted_Native::FDelegate&& CompleteDelegate);

	bool HasErrors() const override;

	FPlatformUserId GetPlatformUserId() const
	{
		return PlatformUserId;
	}
protected:
	// Begin UObject interface
	virtual void OverridePerObjectConfigSection(FString& SectionName) override;
	// End UObject interface

private:
	void InitializeUser();

	/// Iterates through all the backends and attempts login if it is configured 
	EConditionalLoopResult LoginLoop(TSharedRef<FConditionalLoop> LoopNodeRef);

	/// Iterates through all the login methods configured for a backend and tries them all until one succeeds or until they are exhausted
	EConditionalLoopResult BackendLoginLoop(TSharedRef<FConditionalLoop> LoopNodeRef);

	void QueryExternalAuthToken(TSharedRef<FControlFlowNode> FlowNodeRef, FString CustomValue, FName ServiceProvider);
	void LoginToProvider(TSharedRef<FControlFlowNode> FlowNodeRef, FName LoginType, FName ServiceProvider);
	void LogoutFromProvider(TSharedRef<FControlFlowNode> FlowNodeRef, FName ServiceProvider, bool bForgetAuth);

	void SetLoginPendingFlag(UOnlineIntegrationBackend* Backend, bool bSet);
	
	void NotifyProgressUpdate(const FText& Update);
	void AuthenticationCompleted();
	void ResetLoginTypeIndex();
	void IncrementBackendIndex();
	void IncrementLoginTypeIndex();
	
	UPROPERTY(Config)
	TArray<FOnlineBackendAuthenticationSettings> AuthenticationSteps;

	TArray<UE::Online::FOnlineError> Errors; 
	
	TSharedPtr<FControlFlow> ControlFlow;
	TWeakObjectPtr<ULocalUserInfo> UserInfo;
	FPlatformUserId PlatformUserId;

	TArray<FString> ErrorsWhiteList;
	
	int32 BackendIndex = 0;
	int32 LoginTypeIndex = 0;
	
	TOptional<UE::Online::TOnlineResult<UE::Online::FAuthQueryExternalAuthToken>> CachedExternalAuthTokenResult;
	TOptional<UE::Online::TOnlineResult<UE::Online::FAuthLogin>> CachedLoginResult;

};
