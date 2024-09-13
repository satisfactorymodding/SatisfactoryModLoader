// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGClientAPIContext.h"
#include "Server/FGDSSharedTypes.h"
#include "FGClientAPIManager.generated.h"

class FFGRequestPayload;
class FFGCertificateStorageData;
struct FFGRequestEmitterFunctionDefinition;
class IHttpResponse;
class FFGPendingClientRequestStateImpl;
class IHttpRequest;
class UFGClientCertificateManager;
class UFunction;
class FJsonObject;
class FFGRequestBodyPart;

DECLARE_MULTICAST_DELEGATE_OneParam( FFGOnPendingClientRequestCompletedDelegate, const FFGServerErrorResponse& /* ErrorResponse */ );
DECLARE_MULTICAST_DELEGATE_FourParams( FFGPendingClientRequestProgressDelegate, uint64 /* DownloadTotal */, uint64 /* DownloadNow */, uint64 /* UploadTotal */, uint64 /* UploadNow */ );

/** Describes a Server API request in flight */
class FACTORYDEDICATEDCLIENT_API IFGPendingClientRequestState : public TSharedFromThis<IFGPendingClientRequestState>
{
public:
	virtual ~IFGPendingClientRequestState() {}

	// Returns true if the request in question has been completed
	virtual bool IsComplete() const = 0;

	// Returns the error response from the server. Error Code will be empty if there was no error.
	// Should only be called when the request has been completed
	virtual FFGServerErrorResponse GetErrorResponse() const = 0;

	// Delegate fired when this request is completed. If the request is already completed, the delegate is fired immediately
	virtual FFGOnPendingClientRequestCompletedDelegate& OnRequestCompleted() = 0;

	// Delegate fired to notify about the request progress.
	virtual FFGPendingClientRequestProgressDelegate& OnRequestProgress() = 0;
};

/** Container for the IFGPendingClientRequestState so that it can be passed through the reflection system */
USTRUCT( BlueprintType, meta=( BlueprintInternalUseOnly=true ) )
struct FFGPendingClientRequest
{
	GENERATED_BODY()

	TSharedPtr<IFGPendingClientRequestState> InternalState;

	IFGPendingClientRequestState* operator->() const;
	IFGPendingClientRequestState& operator*() const;
	operator IFGPendingClientRequestState*() const;
};

/** A bunch of information associated with a pooled request. A template so that it can be used to hold both strong and weak pointer to the request in different contexts */
template<bool bIsStrongRequestRef>
struct TFGPooledRequestData
{
	using FRequestPtr = std::conditional_t<bIsStrongRequestRef, TSharedPtr<IHttpRequest>, TWeakPtr<IHttpRequest>>;

	TFGPooledRequestData() = default;

	/** Conversion constructor from the opposite type (e.g., weak -> strong or strong -> weak) */
	FORCEINLINE explicit TFGPooledRequestData( const TFGPooledRequestData<!bIsStrongRequestRef>& Other );

	/** A pointer to the current HTTP request this data is about */
	FRequestPtr HttpRequest;
	/** Unique ID of the server that this connection was open to. Makes sure we do not attempt to reuse stale connections on hostname or port changes */
	FString ServerUniqueId;
	/** Storage for certificates */
	TSharedPtr<FFGCertificateStorageData> CertificateStorageData;
};

/** Definitions for the template above. */
using FFGPooledRequestData = TFGPooledRequestData<true>;
using FFGWeakPooledRequestData = TFGPooledRequestData<false>;

/**
 * Client API is an entrypoint to the Client API system that is capable of sending the requests to the Server API and automatically
 * parsing the responses while taking care of aspects such as security, persistence and marshalling/unmarshalling of the data.
 */
UCLASS( Within = "FGServerObject", Config = "Game" )
class FACTORYDEDICATEDCLIENT_API UFGClientAPIManager : public UObject, public IFGClientAPIContext
{
	GENERATED_BODY()
public:
	UFGClientAPIManager();

	// Begin IFGClientAPIContext interface
	virtual UFGClientAPIManager* GetClientAPIManager() const override;
	// End IFGClientAPIContext interface

	/**
	 * Clears the request pool by emptying and disposing of all the pooled requests.
	 * This should be called in case the previously used API configuration is invalid (e.g. Server Address, Port or Hostname have changed)
	 */
	void ClearRequestPool();

	/** Called to un-initialize the Client API Manager. Will forcefully complete and stop all pending requests. */
	void CancelOngoingRequests() const;

	/** Internal function called by the generated code to kick off the request processing */
	TSharedPtr<IFGPendingClientRequestState> Internal_SendRequestToServer( UObject* Context, const UFunction* Function, void* ParameterStack );

	/** Pushes or pulls the Server Error from or to the stack */
	static bool Internal_PushServerErrorToStack( FFGServerErrorResponse& ErrorResponse, bool bPullFromStack, const UFunction* ResponseHandlerFunction, void* ResponseParameterStruct );

	/** Processes the Server Error from the Pending Client Request in a generic way in case it was not handled by the Response Handler. */
	void Internal_ProcessServerError( const FFGRequestEmitterFunctionDefinition& EmitterFunctionDefinition, const FFGServerErrorResponse& ErrorResponse ) const;
private:
	/** Attempts to push the given response payload to the parameter stack if possible. Returns true on success */
	static bool Internal_PushFileResponseToStack( const TSharedPtr<FFGRequestPayload>& ResponsePayload, const UFunction* ResponseHandlerFunction, void* ResponseParameterStruct );

	/** Populates the request data from the parameters stack of the request emitter function */
	static TSharedPtr<FJsonObject> ProcessRequestParameters( const UFunction* Function, void* ParametersStack, const TArray<FName>& IgnoredParamNames, TArray<TSharedPtr<FFGRequestBodyPart>>& OutMultipartData );

	/** Attempts to parse the content body payload as a JSON data */
	static bool ParseJsonResponsePayload( EHttpResponseCodes::Type InResponseCode, const TArray<uint8>& ContentBodyBytes, const FString& ContentCharset, TSharedPtr<FFGPendingClientRequestStateImpl> ClientRequestState );

	/** Processes the Server API data response body and populates the response parameters from it's data */
	static bool ProcessServerDataResponseBody( TSharedPtr<FJsonObject> ResponseBody, TSharedPtr<FFGPendingClientRequestStateImpl> ClientRequestState );

	/** Completes the pending request by parsing the response and firing the response handler and global delegates for it. */
	static void CompletePendingRequest( TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully, TSharedPtr<FFGPendingClientRequestStateImpl> ClientRequestState );
	
	/** Called unconditionally when the request is completed, even if the owning Client API Manager is GC'd. Will free up the resources allocated for the request. */
	static void StaticOnRequestCompleted( TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully, TSharedPtr<FFGPendingClientRequestStateImpl> ClientRequestState );

	/** Copies parameters from the request function to the response function. */
	static void CopyRequestParameters( const UFunction* Function, void* ParametersStack, const TArray<FName>& ParametersToCopy, const UFunction* ResponseFunction, void* ResponseFunctionParametersStack );

	/** Clears the intermediate data on the server request set by the SendRequestToServerInternal so that it does not have any dangling references and can be sent to the pool safely. */
	static void ClearServerRequest( const FFGPooledRequestData& RequestData );

	/** Obtains the server request from the pool, or allocates a new one if the pool is exhausted. Will automatically fill out the URL and Method */
	FFGPooledRequestData ObtainServerRequest();

	/** Allocates a new server request. It needs to be destroyed later by using the DestroyServerRequest */
	FFGPooledRequestData AllocateServerRequest() const;

	/** Potentially retains the server request back into the pool, if the pool capacity is not exhausted. Otherwise, destroys it. */
	void RetainOrDestroyServerRequest( FFGPooledRequestData& RequestData );

	/** De-allocates the server request. Will NOT remove it from the pool, it's a responsibility of the caller to do so. */
	static void DestroyServerRequest( FFGPooledRequestData& RequestData );

	static void PlatformSetProgressDelegate( const TSharedPtr<IHttpRequest>& HttpRequest, FFGPendingClientRequestStateImpl* ClientRequestState );
	static void PlatformResetProgressDelegate( const TSharedPtr<IHttpRequest>& HttpRequest );
	static void PlatformConfigureTimeout( const TSharedPtr<IHttpRequest>& HttpRequest, int32 ConnectTimeout, int32 LowTransferSpeedLimit, int32 LowTransferSpeedTimeout );
protected:
	/** A number of HTTP requests to keep in the pool in case multiple requests need to be made simultaneously. Each pooled request holds an underlying TCP transport! */
	UPROPERTY( Config )
	int32 RequestPoolSize;

	/** Connection timeout for the Server API requests, in seconds */
	UPROPERTY( Config )
	int32 ConnectTimeout;

	/** Minimum transfer speed for the connection to the Server API to have before we abort it */
	UPROPERTY( Config )
	int32 LowTransferSpeedLimit;

	/** Maximum amount of seconds below the transfer limit under which we will time out the connection as too slow */
	UPROPERTY( Config )
	int32 LowTransferSpeedTimeout;

	/** Maximum amount of time for the entire request to take */
	UPROPERTY( Config )
	int32 RequestTimeout;

	/** Requests that are not currently pending but are ready to be sent */
	TArray<FFGPooledRequestData> PooledRequests;

	/** Requests that are currently in flight, e.g. being processed. */
	TArray<TWeakPtr<IHttpRequest>> RequestsInFlight;
};

// Constructor implementation for weak <-> strong pooled data conversion
template<bool bIsStrongRequestRef>
TFGPooledRequestData<bIsStrongRequestRef>::TFGPooledRequestData( const TFGPooledRequestData<!bIsStrongRequestRef>& Other ) :
	ServerUniqueId( Other.ServerUniqueId ), CertificateStorageData( Other.CertificateStorageData )
{
	// If we are a strong ref, Other is a weak ref that needs to be pinned
	if constexpr( bIsStrongRequestRef )
	{
		HttpRequest = Other.HttpRequest.Pin();
	}
	else
	{
		HttpRequest = Other.HttpRequest.ToWeakPtr();
	}
}
