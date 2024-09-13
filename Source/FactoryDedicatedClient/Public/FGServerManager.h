// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Networking/FGClientQuerySocket.h"
#include "FGServerUIProxy.h"
#include "Misc/EngineVersion.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/RunnableThread.h"
#include "FGServerManager.generated.h"

class UFGClientCertificateManager;

FACTORYDEDICATEDCLIENT_API DECLARE_LOG_CATEGORY_EXTERN( LogServerManager, All, All );

DECLARE_STATS_GROUP( TEXT( "ServerManager" ), STATGROUP_ServerManager, STATCAT_Advanced );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnServerAddedDelegate, class UFGServerObject*, Server );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnServerAboutToBeRemoved, class UFGServerObject*, Server );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnServerAddedOrFoundDelegate, class UFGServerObject*, Server, bool, bNewServerAdded );
DECLARE_DYNAMIC_DELEGATE_OneParam( FOnServerNotAddedDelegate, FText, ErrorMessage );
DECLARE_DELEGATE_OneParam( FOnServerAddressResolved, const TArray<TSharedPtr<FInternetAddr>>& /** ServerAddress */ );
DECLARE_DELEGATE_RetVal_TwoParams( FFGServerErrorResponse, FValidateServerHealthCheckDelegate, UFGServerObject* /** ServerObject */, const FString& /** CustomData */ );
DECLARE_DELEGATE_RetVal_OneParam( FString, FHealthCheckCustomDataProviderDelegate, UFGServerObject* /** ServerObject */ );

enum class EServerManagerVersion : int32
{
	InitialVersion,

	// Address is now the address as it was entered by the users. It needs to be DNS resolved before it's usable.
	NoDNSCaching,

	// Refactor of the dedicated servers.
	DedicatedServerRework,

	// New versions can be added above this life
	LatestVersionPlusOne,
	LatestVersion = LatestVersionPlusOne - 1
};

/** Data held for each query socket bound to a local address */
struct FClientQuerySocketData
{
	TUniquePtr<FClientQuerySocket> ClientQuerySocket;
	TUniquePtr<FRunnableThread> ClientQueryThread;
};

/** Header that will be written at the beginning of the server manager save data */
struct FServerManagerSaveHeader
{
	FServerManagerSaveHeader();

	void Serialize( FArchive& Ar );

	uint32 FileTypeTag;
	EServerManagerVersion FileVersion;
	FPackageFileVersion PackageFileUEVersion;
	FEngineVersion SavedEngineVersion;
	int32 CustomVersionFormat;
	FCustomVersionContainer CustomVersions;
};

/**
 * Client side server manager class. Holds a list of all know dedicated server and can perform arbitrary operations on them. Should be used as
 * the dedicated server interface on clients
 */
UCLASS( Config = "ServerManager" )
class FACTORYDEDICATEDCLIENT_API UFGServerManager : public UGameInstanceSubsystem, public FTSTickerObjectBase
{
	GENERATED_BODY()
public:
	UFGServerManager();

	// Begin UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// End UGameInstanceSubsystem interface

	// Begin FTSTickerObjectBase interface
	virtual bool Tick(float DeltaTime) override;
	// End FTSTickerObjectBase interface

	// Begin UObject interface
	virtual void Serialize(FArchive& Ar) override;
	// End UObject interface

	/** Returns the NetCL of the client that we are currently running with */
	UFUNCTION( BlueprintPure, Category = "Server Management" )
	static int32 GetClientNetCL();

	/** Returns true if this client is considered modded */
	UFUNCTION( BlueprintPure, Category = "Server Management" )
	static bool IsClientModded();

	/** Returns a list of the servers in the list */
	UFUNCTION( BlueprintPure, Category = "Server Management" )
	const TArray<UFGServerObject*> GetServers() const;

	/** Attempts to find a server in the list by it's hostname and port */
	UFUNCTION( BlueprintPure, Category = "Server Management" )
	UFGServerObject* GetServerByHostname( const FString& Hostname, int32 QueryPort );

	/** Attempts to find a servers in the list by it's raw address */
	void FindServersByAddress( const TSharedPtr<FInternetAddr>& Address, TArray<UFGServerObject*>& OutServers );

	/** Adds a new server to the list. Port can be INDEX_NONE if we are willing to use the default port and also try resolving the SRV record */
	UFUNCTION( BlueprintCallable, Category = "Server Management" )
	void AddServer( const FString& Address, int32 Port, const FOnServerAddedOrFoundDelegate& LocalOnServerAdded, const FOnServerNotAddedDelegate& OnServerNotAdded, bool bTransient = false );
	
	/** Removes the server from the list */
	UFUNCTION( BlueprintCallable, Category = "Server Management" )
	void RemoveServer( UFGServerObject* Server );

	/** Makes a new server interaction handler object to be used by the server instance */
	TScriptInterface<IFGDedicatedServerUIProxy> MakeServerInteractionHandler();

	/** Queues a query packet to be sent to the specified server address */
	void SendQueryToAddress( const TSharedPtr<FInternetAddr>& ServerAddress );

	/** Performs address resolution and fires the delegate with it's results */
	static void ResolveQueryAddressForServer( const FString& Hostname, int32 Port, const FOnServerAddressResolved& OnServerAddressResolved );

	/** Writes the current state of the save manager to the file */
	bool SaveServerManagerSaveGame();
protected:
#if WITH_EDITOR
	/** Used to automatically create an entry for the dedicated server in PIE */
	void OnPendingNetGameConnectionCreated( UPendingNetGame* PendingNetGame );
	/** Used to automatically reconnect to the PIE server on reload */
	void OnHandleDisconnect( class UWorld* InWorld, class UNetDriver* NetDriver );
	/** Sends the client to the absolute client travel to the DS */
	void SetPendingClientTravelToDS( FString AbsoluteTravelURL );
	UFUNCTION()
	void OnLocalPIEServerAddedOrFound( UFGServerObject* ServerObject, bool bServerAdded );
#endif
	void AddServerInternal( const TArray<TSharedPtr<FInternetAddr>>& ResolvedQueryAddresses, FString Hostname, int32 FallbackPort, FOnServerAddedOrFoundDelegate LocalOnServerAdded, FOnServerNotAddedDelegate OnServerNotAdded, bool bTransient );

	void CreateLocalQuerySockets();
	void DestroyLocalQuerySockets();

	bool LoadServerManagerSaveGame();

	/** Processes pending query responses from all the bound query sockets */
	void ProcessPendingQueryResponses();
public:
	UPROPERTY( BlueprintAssignable, Category = "Server Management" )
	FOnServerAddedDelegate OnServerAdded;

	UPROPERTY( BlueprintAssignable, Category = "Server Management" )
	FOnServerAboutToBeRemoved OnServerAboutToBeRemoved;

	/**
	 * Delegate that can be used to modify the behavior of the Server API health check and to take account of CustomData parameter
	 * The delegate should return a non-empty error message to fail the handshake and mark the server as incompatible, or an empty string to succeed.
	 * If the delegate is not bound, custom data is ignored.
	 */
	FValidateServerHealthCheckDelegate OnValidateServerHealthCheck;

	/**
	 * Allows providing custom data to the health check request sent to the Server API
	 * This can be used to check for modded compatibility for example on the server.
	 */
	FHealthCheckCustomDataProviderDelegate HealthCheckCustomDataProvider;
protected:
	UPROPERTY()
	TArray<UFGServerObject*> mServers;

	TArray<FClientQuerySocketData> mQuerySockets;

	FString mServerManagerFilename;
};

