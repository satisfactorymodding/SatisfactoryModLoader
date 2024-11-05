// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGDSSharedTypes.h"

/** HTTP-related utilities that are useful to have on both Server and Client */
namespace HTTPUtilities
{
	/**
	 * Attempts to parse a header value into it's parts, each representing either a primary header value or some additional information within it.
	 * For example, given a header line:
	 * Content-Disposition: form-data; name="test"; filename="image.jpg"
	 * would be parsed into:
	 * PrimaryValue = "form-data"; AttributeValues = { name = "test", filename = "image.jpg" }
	 */
	FACTORYGAME_API void ParseHeaderValue( const FString& HeaderValue, FString& OutPrimaryValue, TMap<FString, FString>& OutAttributeValues );

	// Decodes the raw binary payload into the string using the provided charset, or returns false if the charset is not supported or known
	FACTORYGAME_API bool DecodeTextPayload( const TArray<uint8>& InPayload, FString InCharset, FString& OutStringPayload );

	// Creates a response describing the list of missing parameters or their invalid values
	FACTORYGAME_API FFGServerErrorResponse CreateMissingParametersResponse( const TArray<FString>& MissingParameters, const TMap<FString, FString>& InvalidParameters, const TArray<FString>& AdditionalErrors );
}
