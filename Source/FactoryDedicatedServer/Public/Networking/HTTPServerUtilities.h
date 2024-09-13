// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FFGServerErrorResponse;
struct FHttpServerResponse;
class FFGRequestBodyPart;

namespace HTTPServerUtilities
{
	// Splits up the header string from a comma separated list into separate values.
	FACTORYDEDICATEDSERVER_API void SplitHeaderValues( const FString& HeaderValue, TArray<FString>& OutSplitValues );

	// Utility function to wrap FGServerErrorResponse into the server response that can be directly passed to the pending request.
	FACTORYDEDICATEDSERVER_API TUniquePtr<FHttpServerResponse> CreateErrorResponse( const FFGServerErrorResponse& ServerErrorResponse );

	// Processed a multipart request body by decoding the parts contained inside of it.
	FACTORYDEDICATEDSERVER_API bool ParseMultipartRequestBody( const FString& BoundaryString, const TArray<uint8> Payload, TArray<TSharedPtr<FFGRequestBodyPart>>& OutMultipartFragments );

	// Process a single multipart request body part. Returns nullptr if parsing failed.
	FACTORYDEDICATEDSERVER_API TSharedPtr<FFGRequestBodyPart> ProcessMultipartBodyPart( const TArrayView<const uint8>& BodyPartPayload );

	// Attempts to decompress the payload using the encoding provided as an argument
	FACTORYDEDICATEDSERVER_API bool DecompressPayload( const TArray<uint8>& InPayload, const FString& ContentEncoding, TArray<uint8>& OutDecompressedPayload );

	// Attempts to compress the payload using one of the provided compression algorithms. Returns true if the compression succeeded
	FACTORYDEDICATEDSERVER_API bool CompressPayload( FHttpServerResponse* ServerResponse, const TArray<FString>& SupportedCompressionAlgorithms );
}
