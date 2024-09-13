// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Server/FGDSAuthenticationTypes.h"
#include "UObject/GCObject.h"
#include "FGServerAPIManager.generated.h"

class UFGServerSubsystem;
struct FUniqueNetIdRepl;
class FUniqueNetId;
enum class EPrivilegeLevel : uint8;
class FJsonObject;
class UFGServerCertificateManager;
class FSocketSSL;
class FFGRequestBodyPart;
struct FHttpServerResponse;
struct FHttpRouteHandleInternal;
class FFGRequestHandlerContext;
class UFGServerAPIManager;
struct FHttpServerRequest;
class IHttpRouter;
class FInternetAddr;
struct FFGServerErrorResponse;
enum class EHttpServerResponseCodes : uint16;

typedef TFunction<void(TUniquePtr<FHttpServerResponse>&& Response)> FHttpResultCallback;
typedef TSharedPtr<const FHttpRouteHandleInternal> FHttpRouteHandle;
typedef TFunction<bool(FStructProperty* ParamProp, void* ParamDataPtr, TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext, FString& OutErrorDescription)> FFGServerAPIRequestParamHandler;

USTRUCT()
struct FFGRequestHandlerRegistration
{
	GENERATED_BODY()

	UPROPERTY()
	UObject* HandlerObject{};

	UPROPERTY()
	UFunction* HandlerFunction{};

	FName FunctionName;
	EPrivilegeLevel PrivilegeLevel{};
	bool bIsAsynchronousHandler{false};
	bool bEnableCompression{false};

	UPROPERTY()
	UFunction* AsyncCompleteRequestFunction{};
};

/**
 * An object that can be used to hold a strong reference to the Server API Manager
 * The reason why we need it is because Live Coding seems to invalidate weak pointers, which makes request handling impossible
 */
class FACTORYDEDICATEDSERVER_API FFGServerAPIManagerRef : public FGCObject
{
	TObjectPtr<UFGServerAPIManager> ServerAPIManager{};
public:
	FFGServerAPIManagerRef();
	explicit FFGServerAPIManagerRef( UFGServerAPIManager* InAPIManager );

	FORCEINLINE UFGServerAPIManager* Get() const { return ServerAPIManager; }

	// Begin FGCObject interface
	virtual FString GetReferencerName() const override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End FGCObject interface
};

/**
 * This struct can be added as a parameter to the Request Handlers and it will be automatically populated
 * With the Metadata that is gathered from the current request.
 */
class FACTORYDEDICATEDSERVER_API FFGRequestHandlerContext : public TSharedFromThis<FFGRequestHandlerContext>, public FNoncopyable
{
public:
	FFGRequestHandlerContext( const TSharedRef<const FInternetAddr>& InPlayerAddress, const TMap<FString, TArray<FString>>& InRequestHeaders );
	~FFGRequestHandlerContext();

	// Returns IP Address of the Remote Peer that is making the Request.
	FORCEINLINE TSharedRef<const FInternetAddr> GetPlayerAddress() const { return PlayerAddress; }

	// Returns the Unique Player ID that has been set, if the remote is a game client
	FORCEINLINE UE::Online::FAccountId GetPlayerUniqueId() const { return PlayerUniqueId; }

	// Returns the authentication token that has been provided with the request.
	FORCEINLINE FServerAuthenticationToken GetAuthenticationToken() const { return AuthenticationToken; }

	// Multipart Parts that have been uploaded with this request.
	FORCEINLINE TArray<TSharedPtr<FFGRequestBodyPart>> GetMultipartData() const { return MultipartData; }

	// Returns true if the player is at least this level privileged
	bool IsPrivilegedFor( EPrivilegeLevel MinPrivilegeLevel ) const;

	// Returns the first multipart blob of the given content type
	TSharedPtr<FFGRequestBodyPart> FindFirstMultipartDataOfContentType( const FString& ContentType ) const;

	// Finds the multipart data matching the given form field name
	TSharedPtr<FFGRequestBodyPart> FindFirstMultipartDataOfFormField( const FString& FormFieldName ) const;

	// Adds the response header to this request
	void AddResponseHeader( const FString& HeaderName, const FString& HeaderValue );

	// Completes the request with the provided response. Should not be called manually, use the CompleteRequest function specific to your request handler or do not
	// call anything if your handler is not asynchronous.
	void Internal_CompleteRequest( TUniquePtr<FHttpServerResponse>&& InServerResponse );

	// Shortcut for completing the request with an error response.
	void Internal_CompleteRequestWithError( const FFGServerErrorResponse& InErrorResponse );
protected:
	// Returns a list of compression algorithms supported by the client
	TArray<FString> GetSupportedCompressionAlgorithms() const;
private:
	friend class UFGServerAPIManager;

	TMap<FString, TArray<FString>> RequestHeaders;
	TSharedRef<const FInternetAddr> PlayerAddress;
	UE::Online::FAccountId PlayerUniqueId;
	
	FServerAuthenticationToken AuthenticationToken{};
	TArray<TSharedPtr<FFGRequestBodyPart>> MultipartData;

	// Headers to append to the response returned by the server
	TMap<FString, TArray<FString>> ResponseHeaders;

	// Registration entry for the request handler that is currently processing this request
	TOptional<FFGRequestHandlerRegistration> RequestHandlerRegistration{};

	// Raw JSON body is the JSON payload as it came from the client, including the function name and the data sub-object that can be accessed from RequestJsonBody
	TSharedPtr<FJsonObject> RawJsonBody;

	// Processed Request Body to be passed to the Request Handler
	TSharedPtr<FJsonObject> RequestJsonBody;

	// Callback to call to complete the request. Only valid for asynchronous requests.
	FHttpResultCallback OnRequestCompleteCallback;

	// True if the request has already been completed. Double-completing a request is an error.
	bool bRequestCompleted{false};

	// Server API Manager that instigated this request. Keeping a reference to it makes it possible for us to stop all pending requests when the server is shut down.
	TSharedPtr<FFGServerAPIManagerRef> RequestInstigator;
};

/**
 * This is the root class for managing HTTPS connections. It is instantiated on the dedicated server inside
 * the ServerSubsystem. It houses the ServerCertificateManager which handles creating a SSL tunneled socket.
 */
UCLASS( Within=FGServerSubsystem )
class FACTORYDEDICATEDSERVER_API UFGServerAPIManager : public UObject
{
	GENERATED_BODY()

public:
	UFGServerAPIManager();

	bool Initialize( const TArray<TSharedRef<FInternetAddr>>& BindAddresses );
	void Shutdown();

	// Returns the API port the Server API is listening on
	FORCEINLINE uint32 GetAPIPort() const { return mAPIPort; }

	/**
	 * Allows registering new API request handlers into the list
	 * Each handler should have functions marked as request handlers to be able to receive and process the request
	 * It's your responsibility to make sure the handler object stays alive during the server operation
	 */
	void RegisterRequestHandler( UObject* RequestHandler );

	/**
	 * Registers a special parameter handler for the provided parameter type
	 * The handler will run in place of the normal request parsing logic for the given parameter and should populate from the request context,
	 * or return false and provide an error message if it failed to do so.
	 */
	void RegisterParamHandler( UScriptStruct* ScriptStruct, const FFGServerAPIRequestParamHandler& ParamHandler );

	/** Called internally by the CompleteRequest_ functions to nicely wrap the data into the JSON object. */
	static void Internal_CompleteAsyncRequest( const UFunction* CompleteRequestFunction, void* ParametersStack );

	UFGServerSubsystem* GetOuterServerSubsystem() const;
protected:
	// Generic route for creating request handler context that is shared across all request types and endpoints
	TSharedPtr<FFGRequestHandlerContext> CreateRequestHandlerContext( const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete );
	
	// Entry point to the request processing chain for the POST API request. Will parse the body and the endpoint, populate the request handler context and call ProcessAPIRequestInternal
	bool ProcessPostRequest( const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete );

	// True if the passed address belongs to one of the local adapters
	bool IsLocalAddress( const TSharedPtr<FInternetAddr>& InternetAddr );
	
	// Parses the request body using the content type and populates the request handler context
	bool ProcessPostRequestContentBody( TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext, const FString& ContentType, TMap<FString, FString> ContentTypeAttributes, const TArray<uint8>& RequestBodyData ) const;

	// Parses the raw API request JSON, and looks up the handler registration for it. Also makes sure the current user has enough permissions to access it.
	bool ProcessServerAPIBodyJSON( TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext ) const;

	// Executes the request handler by parsing the parameters from the data JSON and attachments, running the handler function, and returning the response
	void ExecuteRequestHandler( TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext );
	
	// Populates the function parameters from the request body.
	void PopulateStackFromRequest( TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext, void* ParametersStack, TArray<FString>& OutMissingParameters, TMap<FString, FString>& OutInvalidParameterValues, TArray<FString>& OutAdditionalErrors ) const;
	
	// Utility function to populate a server response from the data on the parameter stack of the given function. Flags can be used to filter the parameters that will be included.
	static TUniquePtr<FHttpServerResponse> CreateServerResponseFromStack( const UFunction* ResponseFunction, void* ParametersStack, bool bOutParameters, const TArray<FString>& SupportedCompressionAlgorithms );

	// Parses the request authentication header into the authentication token. If token is of the invalid format or the fingerprint is not valid, the request will be assumed unauthorized.
	bool ProcessClientAuthentication( const FString& AuthenticationHeader, TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext ) const;

	// Returns an error response for when the client has failed the authentication
	static void OnClientFailedAuthentication( TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext, EHttpServerResponseCodes ResponseCode,
		const FString& OAuth2ErrorCode, const FString& ErrorDescription, const FString& OAuth2Scope = TEXT("") );

	void BindRoutes();
	void UnbindRoutes() const;
	void RegisterDefaultParameterHandlers();
private:
	UPROPERTY()
	UFGServerCertificateManager* mServerCertificateManager;

	UPROPERTY()
	TMap<FString, FFGRequestHandlerRegistration> mRegisteredHandlers;

	// C++ structs do not need to be referenced (supposedly).
	TMap<UScriptStruct*, FFGServerAPIRequestParamHandler> mRequestParamHandlers;

	// The port specified for handling API Traffic
	uint32 mAPIPort;

	// Router for handling incoming HTTP requests. The socket creation is overriden in the HTTPServerModule to utilize our CertificateManager socket
	TSharedPtr<IHttpRouter> mHTTPRouter;
	FHttpRouteHandle mPostRouteHandle;

	// A cache of local adapter addresses used to quickly look up if the incoming request is coming from a local network adapter.
	TArray<TSharedPtr<FInternetAddr>> LocalAdapterAddresses;
};
