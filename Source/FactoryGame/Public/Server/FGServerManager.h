// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveSystem.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Server/FGServerBeaconClient.h"
#include "Server/FGDedicatedServerTypes.h"
#include "Server/FGServerQuerySocket.h"
#include "GameFramework/SaveGame.h"
#include "FGServerManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogServerManager, Log, Log );
DECLARE_STATS_GROUP( TEXT( "ServerManager" ), STATGROUP_ServerManager, STATCAT_Advanced );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnServerAddedDelegate, class UFGServerObject*, Server );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnServerAboutToBeRemoved, class UFGServerObject*, Server );
DECLARE_DYNAMIC_DELEGATE_OneParam( FOnServerAddedOrFoundDelegate, class UFGServerObject*, Server );
DECLARE_DELEGATE_OneParam( FOnServerAddedOrFoundDelegateNative, class UFGServerObject* );

/**
 * Client side server manager class. Holds a list of all know dedicated server and can perform arbitrary operations on them. Should be used as
 * the dedicated server interface on clients
 */
UCLASS( Config=ServerManager )
class FACTORYGAME_API UFGServerManager : public ULocalPlayerSubsystem, public FTickerObjectBase
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool Tick(float DeltaTime) override;

	UFGServerObject* GetServerByAddress( const FString& Address, int32 QueryPort );

	TScriptInterface<IFGDedicatedServerUIProxy> MakeServerInteractionHandler();

	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;
	
	UFUNCTION( BlueprintCallable, Category = "Server Management" )
	void AddServer( const FString& Address, int32 Port, FOnServerAddedOrFoundDelegate OnceAdded );

	void NativeAddServer( const FString& Address, int32 Port, FOnServerAddedOrFoundDelegateNative OnceAdded );

	UFUNCTION( BlueprintCallable, Category = "Server Management" )
	void RemoveServer( UFGServerObject* Server );

	const TArray<class UFGServerObject*>& GetServers() const;
	
	UPROPERTY( BlueprintAssignable, Category = "Server Management" )
	FOnServerAddedDelegate OnServerAdded;

	UPROPERTY( BlueprintAssignable, Category = "Server Management" )
	FOnServerAboutToBeRemoved OnServerAboutToBeRemoved;

	UFUNCTION( BlueprintCallable, BlueprintPure )
	static int32 GetClientNetCL();
	
	void SaveState();

	void ProcessPollResponses( FClientQuerySocket* Socket );

	FClientQuerySocket* GetQuerySocket( const FName& Protocol );

protected:
	UPROPERTY( BlueprintReadOnly )
	TArray<class UFGServerObject*> mServers;

private:
	TArray< TUniquePtr< FClientQuerySocket > > mServerQuerySockets;
	TArray< TUniquePtr< FRunnableThread > > mServerQueryThreads;
	
	bool mRunningFromConsole = false;

	void CustomSerialize(FArchive& Ar, EServerManagerVersion Version);
};

