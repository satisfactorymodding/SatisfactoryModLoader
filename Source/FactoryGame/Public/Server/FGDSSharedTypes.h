// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Online/CoreOnline.h"
#include "Interfaces/IHttpResponse.h"
#include "FGDSSharedTypes.generated.h"

class FJsonObject;
enum class EHttpServerResponseCodes : uint16;

// Struct that is used to indicate that this request handler parameter has a special meaning and should be treated separately from the rest
USTRUCT( BlueprintType, meta = ( BlueprintInternalUseOnly = "true" ) )
struct FACTORYGAME_API FFGImplicitRequestParameterBase
{
	GENERATED_BODY()
};

/**
 * Server Error Response is a generic description of an error that has occured either on the Server or the Client,
 * and prevented the request from being handled. It contains general purpose information for identifying what went wrong,
 * such as response code, error code and user-friendly error message, as well as potentially additional information.
 *
 * Server Errors can bubble up on the Client, in case the Response Handler does not decide to Consume it, and will be handled by the generic handler in that case.
 * The Error is empty if IsError() returns false.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGServerErrorResponse : public FFGImplicitRequestParameterBase
{
	GENERATED_BODY()

	// HTTP Code for the response
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Server Error Code" )
	int32 ResponseCode;

	// Error Code for this error, this should be easily distinguishable from other errors and machine readable
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Server Error Code" )
	FString ErrorCode;

	// Human readable error message for this error
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Server Error Code" )
	FString ErrorMessage;

	// Additional information about the error
	TSharedPtr<FJsonObject> ErrorData;

	FFGServerErrorResponse();
	explicit FFGServerErrorResponse( int32 InResponseCode );

	// Returns true if this is an error response. Response is considered an error if it has an error code or it's response code is not in a 2xx range
	bool IsError() const;

	// Consumes this error by resetting it to the default "OK" state.
	void Consume();

	// Creates an error server response with the provided code and message and no additional data
	static FFGServerErrorResponse Error( const FString& ErrorCode, const FString& ErrorMessage = TEXT(""), TOptional<EHttpServerResponseCodes> InResponseCode = TOptional<EHttpServerResponseCodes>() );
	static FFGServerErrorResponse ClientError( const FString& ErrorCode, const FString& ErrorMessage = TEXT(""), EHttpResponseCodes::Type InResponseCode = EHttpResponseCodes::Ok );
	
	// Creates an empty error response with no error
	static FFGServerErrorResponse Ok( TOptional<EHttpServerResponseCodes> InResponseCode = TOptional<EHttpServerResponseCodes>() );
	static FFGServerErrorResponse ClientOk(  EHttpResponseCodes::Type InResponseCode = EHttpResponseCodes::Ok );
};

namespace DedicatedServerUtilities
{
	// API Endpoint for POST requests to the server API
	static const FString GServerAPIEndpoint( TEXT("/api/v1") );

	// Converts the name of the property to it's name in the Server API
	FACTORYGAME_API FString ConvertPropertyNameForServerAPI( const FProperty* Property );

	// Retrieves the magic to use for the query protocol
	FACTORYGAME_API void GetServerQueryProtocolMagic( uint32& OutProtocolMagic, int32& OutProtocolMagicBits );

	// Conversion functions to/from FAccountId. Used for parsing PlayerId header
	FACTORYGAME_API FString AccountIdToString( const UE::Online::FAccountId& AccountId );
	FACTORYGAME_API bool StringToAccountId( const FString& AccountIdString, UE::Online::FAccountId& OutAccountId );
}
