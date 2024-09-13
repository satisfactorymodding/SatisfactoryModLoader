// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGClientAPIManager.h"
#include "Security/FGClientCertificateManager.h"
#include "Server/FGServerAPIManagerInternals.h"
#include "UObject/StructOnScope.h"
#include "UObject/GCObject.h"

class IHttpRequest;
class IHttpResponse;

class FACTORYDEDICATEDCLIENT_API FFGPendingClientRequestStateImpl : public IFGPendingClientRequestState, public FGCObject
{
public:
	FFGPendingClientRequestStateImpl( UFGClientAPIManager* InClientAPIManager, const FFGPooledRequestData& RequestData, const FFGRequestEmitterFunctionDefinition& EmitterFunctionDefinition );

	void SetupResponseHandler( UObject* InResponseHandlerObject );

	// Begin IFGPendingClientRequestState interface
	virtual bool IsComplete() const override;
	virtual FFGServerErrorResponse GetErrorResponse() const override;
	virtual FFGOnPendingClientRequestCompletedDelegate& OnRequestCompleted() override;
	virtual FFGPendingClientRequestProgressDelegate& OnRequestProgress() override;
	// End IFGPendingClientRequestState interface

	// Begin FGCObject interface
	virtual FString GetReferencerName() const override;
	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;
	// End FGCObject interface

	FORCEINLINE UFGClientAPIManager* GetClientAPIManager() const { return ClientAPIManager.Get(); }
private:
	friend class UFGClientAPIManager;
	friend class UFGClientCertificateManager;

	void BroadcastRequestCompleted( const FFGServerErrorResponse& InErrorResponse );

	TWeakObjectPtr<UFGClientAPIManager> ClientAPIManager;
	FFGWeakPooledRequestData RequestData{};
	FFGRequestEmitterFunctionDefinition RequestEmitterFunctionDefinition{};
	FStructOnScope ResponseParameterStruct{};
	TOptional<FFGServerErrorResponse> ServerErrorResponse{}; 
	UObject* ResponseHandlerObject{};
	UFunction* ResponseHandler{};
	FFGOnPendingClientRequestCompletedDelegate OnRequestCompletedDelegate;
	FFGPendingClientRequestProgressDelegate RequestProgressDelegate;
};
