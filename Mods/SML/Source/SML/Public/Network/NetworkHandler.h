#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "UObject/Object.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NetworkHandler.generated.h"

class UGameInstance;
class UNetDriver;

DECLARE_LOG_CATEGORY_EXTERN(LogModNetworkHandler, Log, All);
DECLARE_DELEGATE_TwoParams(FMessageReceived, class UNetConnection* /*Connection*/, FString /*Data*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FWelcomePlayer, UWorld* /*ServerWorld*/, class UNetConnection* /*Connection*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FConnectionEvent, class UNetConnection* /*Connection*/);

struct FMessageType {
    FString ModReference;
    int32 MessageId;
};

struct FMessageEntry {
    bool bClientHandled;
    bool bServerHandled;
    FMessageReceived MessageReceived;
};

/**
 * Mod Network Handler
 *
 * Mod network handler manages server-client communication during connection setup,
 * before any actor channels are created, player controller initialized or map replicated
 * It can be used to perform early validation and syncing on both server and client side
 *
 * For example, SML uses it to check mods installed on client side in advance
 * before proceeding to player join, and deny join request if mods versions mismatch, or mods are missing
 * Most of the time you want to use normal replication for gameplay-related stuff
 */
UCLASS()
class SML_API UModNetworkHandler : public UEngineSubsystem {
    GENERATED_BODY()
private:
    TMap<FString, TMap<int32, FMessageEntry>> MessageHandlers;
    FWelcomePlayer WelcomePlayerDelegate;
    FConnectionEvent WelcomePlayerDelegateClient;
    FConnectionEvent ClientLoginDelegate;
    FConnectionEvent ClientLoginDelegateServer;
private:
    void ReceiveMessage(class UNetConnection* Connection, const FString& ModId, int32 MessageId, const FString& Content) const;
public:
    /**
     * Delegate called on server after it has received and validate the client join request, and has sent the world load information to the client
     * You can send additional information to the client here,
     * or check information received by client to perform any required validation
     */
    FORCEINLINE FWelcomePlayer& OnWelcomePlayer() { return WelcomePlayerDelegate; }

    /**
     * Delegate called on the client when it has received the welcome message from the server.
     * This is called before the client processes the welcome message, so it has not yet begun the process of loading the map.
     * You can send additional information to the server here,
     * or check information received by the server to perform any required validation
     */
    FORCEINLINE FConnectionEvent& OnWelcomePlayer_Client() { return WelcomePlayerDelegateClient; }

    /**
     * Delegate called on the client after it has sent initial join request to the server
     * Here you can queue additional information to be sent to the server after the SML connection is established (see flowchart), using SendMessage
     */
    FORCEINLINE FConnectionEvent& OnClientInitialJoin() { return ClientLoginDelegate; }

    /**
     * Delegate called on the server when it has received initial join request from client
     * Here you can queue additional information to be sent to the client after the SML connection is established (see flowchart), using SendMessage
     */
    FORCEINLINE FConnectionEvent& OnClientInitialJoin_Server() { return ClientLoginDelegateServer; }

    /**
     * Register new mod message type and return message entry which can be used
     * to set message processing preferences and siding
     */
    FMessageEntry& RegisterMessageType(const FMessageType& MessageType);

    static void CloseWithFailureMessage(class UNetConnection* Connection, const FString& Message);
    
    /**
     * Send registered mod message to this connection to be processed on the remote side
     */
    static void SendMessage(class UNetConnection* Connection, FMessageType MessageType, FString Data);

	/**
	 * Set the connection to support mod messages and send all pending messages
	 */
	static void SetConnectionSupportsModMessages(class UNetConnection* Connection);

	/**
	 * Retrieves the game instance owning the specified net driver
	 */
	static UGameInstance* GetGameInstanceFromNetDriver( const UNetDriver* NetDriver );
private:
    friend class FSatisfactoryModLoader;

    /** Registers hooks associated with network handler */
    static void InitializePatches();
};
