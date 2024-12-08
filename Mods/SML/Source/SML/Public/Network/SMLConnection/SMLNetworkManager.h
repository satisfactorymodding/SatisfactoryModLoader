#pragma once

#include "CoreMinimal.h"
#include "Util/SemVersion.h"

struct FConnectionMetadata {
	bool bIsInitialized{false};
	TMap<FString, FVersion> InstalledRemoteMods;

	FORCEINLINE bool IsDefault() const { return !bIsInitialized; }
};

class SML_API FSMLNetworkManager {
public:
    /** Handles SML message being received on the server side */
    static void HandleMessageReceived(class UNetConnection* Connection, FString Data);

    /** Handles Initial Join request on both the Client and the Server. Called after sending (client) or when receiving (server) initial NMT_Hello message with endianness/basic network version */
	static void HandleInitialClientJoin(UNetConnection* Connection);

	/** Handles WelcomePlayer call on Server, which is called after key exchange and results in client getting NMT_Welcome */
	static void HandleWelcomePlayer(UWorld* World, UNetConnection* Connection);

	/** Handles WelcomePlayer call on the Client, which is called before the client starts loading the map specified by the server in NMT_Welcome */
	static void HandleWelcomePlayer_Client(UNetConnection* Connection);

    /** Handles AGameModeBase::PostLogin call, which is the first place where APlayerController is available and is called after NMT_Join is received from client */
    static void HandleGameModePostLogin(class AGameModeBase* GameMode, class APlayerController* Controller);

    /** Serializes mod list into packed json string */
    static FString SerializeLocalModList(UNetConnection* Connection);

    /** Parses packaged json mod list string and sets relevant information on connection */
    static bool HandleModListObject( FConnectionMetadata& Metadata, const FString& ModList);

    /** Ensures that Connection has required SML initialization data and kicks player off if it doesn't */
    static void ValidateSMLConnectionData(class UNetConnection* Connection, bool IsServer);
private:
    friend class FSatisfactoryModLoader;
    static TSharedPtr<struct FMessageType> MessageTypeModInit;

    static void RegisterMessageTypeAndHandlers();
};
