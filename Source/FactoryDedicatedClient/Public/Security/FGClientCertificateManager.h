// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBlueprintFunctionLibrary.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Server/FGTLSTypes.h"
#include "FGClientCertificateManager.generated.h"

class FFGPendingClientRequestStateImpl;
class UFGServerObject;
class IHttpResponse;
class IHttpRequest;
class FInternetAddr;

/**
 * Certificate entry stores information about a certificate presented by a remote server.
 * This is important in cases where the remote server is hosted on the platform that does not have a valid TLS certificate that can be
 * verified by one of the Certificate Root Authorities, and instead uses a self-signed certificate generated automatically.
 *
 * In that case the Client does not know who is on the other side of the wire, and needs to manually confirm that they trust
 * the certificate presented by the server to be able to establish a secure communication channel.
 * This is where additional information such as the issuer or subject name come handy, as they offer some information to be able
 * to verify the certificate.
 */
USTRUCT( BlueprintType )
struct FACTORYDEDICATEDCLIENT_API FFGServerCertificate
{
	GENERATED_BODY()

	// Underlying OpenSSL certificate
	TOSSLDataWrapper<EOSSLDataType::X509> Certificate;

	friend void operator<<( FArchive& Ar, FFGServerCertificate& ServerCertificate );
	bool Serialize( FArchive& Ar );
	bool Identical( const FFGServerCertificate* ServerCertificate, uint32 PortFlags ) const;
};

/**
 * Used by the UFGClientCertificateManager to store server certificate and verify error
 * Needs to be alive in memory as long as the relevant CURL handle and it's SSL context/instances are alive
 */
class FACTORYDEDICATEDCLIENT_API FFGCertificateStorageData : public TSharedFromThis<FFGCertificateStorageData>
{
public:
	FFGServerCertificate ReceivedServerCertificate{};
	int32 CertVerifyResult{INDEX_NONE};
	TWeakObjectPtr<UFGServerObject> ServerObject{};
};

/**
 * Manages certificates acknowledged by the client when connecting to the dedicated servers.
 * The certificates that are verified by the Root CA authorities are automatically trusted and do not need to be acknowledged by the player.
 */
UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientCertificateManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Configures the Request Certificate from the Server Object.
	 * If the server object does not have an explicit certificate set, it will instead use the default system certificate storage.
	 */
	static void SetupRequestCertificate( const TSharedPtr<IHttpRequest>& HttpRequest, FFGCertificateStorageData* CertificateStorageData );

	/** Clears the certificate data on the request */
	static void ClearRequestCertificate( TSharedPtr<IHttpRequest> HttpRequest );

	/** Returns the formatted server certificate as a human readable string that a person can easily compare */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Certificate Manager" )
	static FString PrintCertificate( const FFGServerCertificate& ServerCertificate );

	/** Generates a short fingerprint for the public key the certificate has been signed with. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Certificate Manager" )
	static FString FormatCertificatePublicKeyFingerprint( const FFGServerCertificate& ServerCertificate );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Certificate Manager" )
	static FString FormatCertificateSubjectName( const FFGServerCertificate& ServerCertificate );
};

template<>
struct TStructOpsTypeTraits<FFGServerCertificate> : TStructOpsTypeTraitsBase2<FFGServerCertificate>
{
	enum
	{
		WithSerializer = true,
		WithIdentical = true
	};
};
