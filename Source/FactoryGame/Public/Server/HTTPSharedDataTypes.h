// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGDSSharedTypes.h"
#include "HTTPSharedDataTypes.generated.h"

/**
 * Container for a generic request payload that can be used for containing request or response bodies,
 * along with their content type and charset (e.g. encoding).
 * Also serves as a base class for multipart body parts.
 */
class FACTORYGAME_API FFGRequestPayload : public TSharedFromThis<FFGRequestPayload>
{
public:
	FFGRequestPayload( const FString& InContentType, TArray<uint8>&& InPayload, const TMap<FString, FString>& ContentAttributes );
	FFGRequestPayload( const FString& InContentType, const FString& InPayload );
	virtual ~FFGRequestPayload() = default;
	
	// Returns the content type of the body part, without the charset information
	FORCEINLINE FString GetContentType() const { return ContentType; }
	// Returns the additional attributes set for the content type
	FORCEINLINE TMap<FString, FString> GetContentTypeAttributes() const { return ContentTypeAttributes; }

	// Returns the charset of the content in this payload
	FString GetContentCharset() const;

	// Returns the payload of the body part as raw binary data
	FORCEINLINE const TArray<uint8>& GetPayload() const { return Payload; }
	FORCEINLINE TArray<uint8>& GetPayloadMutable() { return Payload; }
	FORCEINLINE int32 GetContentLength() const { return Payload.Num(); }

	// Returns the content type, including the additional attributes set (such as charset)
	FString GetContentTypeWithAttributes() const;

	// Returns the formatted value of a content disposition header
	virtual FString GetContentDisposition() const;

	// Returns the payload of the body part as a string, using the content charset for decoding it, and falling back to the default encoding.
	FString GetPayloadAsString() const;

	// If this is a form data or a response body that is an attachment, returns the filename of this attachment
	FORCEINLINE FString GetAttachmentFilename() const { return AttachmentFilename; }

	// Updates the attachment filename to the specified one
	void SetAttachmentFilename( const FString& InAttachmentFilename );

	// Updates the charset of the content in this payload
	void SetContentCharset( const FString& InCharset );

	// Updates the attribute value on this payload
	void SetContentAttribute( const FString& InAttributeName, const FString& InAttributeValue );

	// Returns the content attribute if set, or an empty string
	FString GetContentAttribute( const FString& InAttributeName ) const;
protected:
	FString ContentType;
	TMap<FString, FString> ContentTypeAttributes;
	TArray<uint8> Payload;
	FString AttachmentFilename;
};

/**
 * Describes a single MultiPart body part with additional information about
 * Note that Payload in question has already been decoded using it's transfer encoding
 */
class FACTORYGAME_API FFGRequestBodyPart : public FFGRequestPayload
{
public:
	FFGRequestBodyPart( const FString& InContentType, TArray<uint8>&& InPayload, const TMap<FString, FString>& ContentAttributes );
	FFGRequestBodyPart( const FString& InContentType, const FString& InPayload );

	// Returns the name of the form field this multipart has been attached to.
	FORCEINLINE FString GetFormFieldName() const { return FormFieldName; }
	FORCEINLINE const TMap<FString, TArray<FString>>& GetBodyPartHeaders() const { return BodyPartHeaders; }

	// Returns the header value with the specified name, or the empty array if the header is not set
	TArray<FString> GetBodyPartHeader( const FString& HeaderName ) const;

	void SetFormFieldName( const FString& InFormFieldName );
	void SetBodyHeader( const FString& InHeaderName, const FString& InHeaderValue );
	void AppendBodyHeaders( const TMap<FString, TArray<FString>>& InBodyHeaders );
	virtual FString GetContentDisposition() const override;
protected:
	FString FormFieldName;
	TMap<FString, TArray<FString>> BodyPartHeaders;
};

// Allows capturing the multipart request body parts by name, or emitting them into the response body
USTRUCT( BlueprintType, meta = ( BlueprintInternalUseOnly = "true" ))
struct FACTORYGAME_API FFGMultipartDataWrapper : public FFGImplicitRequestParameterBase
{
	GENERATED_BODY()

	TSharedPtr<FFGRequestBodyPart> MultipartData;

	// Operators for conveniently de-referencing the context. Keep in mind that these will assert on nullptr context.
	FFGRequestBodyPart* operator->() const;
	FFGRequestBodyPart& operator*() const;
	operator FFGRequestBodyPart*() const;
};

/**
 * Allows capturing the Raw Response Body when it cannot be parsed by the Client API Manager
 * When this argument is populated, the rest of the parameters of the response handler are completely ignored and as such
 * you should not expect them to be populated.
 * 
 * This is primarily useful for file downloads.
 */
USTRUCT( BlueprintType, meta = ( BlueprintInternalUseOnly = "true" ))
struct FACTORYGAME_API FFGResponseDataWrapper : public FFGImplicitRequestParameterBase
{
	GENERATED_BODY()

	TSharedPtr<FFGRequestPayload> ResponsePayload;
};

// This parameter can be used as an out variable in the request handler to allow to respond with file uploads instead of normal JSON data.
USTRUCT( BlueprintType, meta = ( BlueprintInternalUseOnly = "true" ))
struct FACTORYGAME_API FFGFileResponseWrapper : public FFGImplicitRequestParameterBase
{
	GENERATED_BODY()

	TSharedPtr<FFGRequestPayload> FileResponse;
};
