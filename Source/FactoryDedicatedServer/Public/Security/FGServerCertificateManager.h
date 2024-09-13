// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Server/FGTLSTypes.h"
#include "FGServerSettings.h"
#include "SocketSubsystem.h"
#include "FGServerCertificateManager.generated.h"

class UFGServerAPIManager;
UCLASS( Within = "FGServerAPIManager" )
class FACTORYDEDICATEDSERVER_API UFGServerCertificateManager : public UObject
{
	GENERATED_BODY()
public:
	// Wraps the provided socket into the SSL tunnel
	FSocket* CreateSecureSocket( FUniqueSocket&& InUnderlyingSocket );

	void SetUserCertificatePath( const FString& InUserCertificatePath, const FString& InUserPrivateKeyPath );
	
	UFGServerAPIManager* GetOuterServerAPIManager() const;
protected:
	/** Re-generates the self signed certificate and stores it in the instance variables */
	FFGGeneratedCertificateData GenerateSelfSignedCertificate();
	
	void InitializeSSLContext( TOSSLDataWrapper<EOSSLDataType::SSLContext> SslContext );

	// The override for the user certificate path
	TOptional<TPair<FString, FString>> UserCertificatePath;
};