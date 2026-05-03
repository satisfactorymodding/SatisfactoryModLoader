// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SMLWebSocketClient.h"
#include "DiscordBridgeConfig.h"
#include "WhitelistConfig.h"
#include "InGameMessagesConfig.h"
#include "FGChatManager.h"
#include "FGGamePhase.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Dom/JsonObject.h"
#include "IDiscordBridgeProvider.h"
#include "DiscordBridgeSubsystem.generated.h"

// Forward-declared so the header does not pull in TicketSystem's full header chain.
class UTicketSubsystem;

// Forward-declared so the header does not pull in BanSystem's full header chain.
class UBanDiscordSubsystem;

// UFGGamePhase is fully defined by #include "FGGamePhase.h" above; no forward decl needed.
// UFGSchematic is only used as TSubclassOf<UFGSchematic> in method signatures, so a
// forward declaration is sufficient and avoids pulling in the full schematic header.
class UFGSchematic;

// ── Delegate declarations ────────────────────────────────────────────────────

/**
 * Fired on the game thread when a message is received from the bridged Discord
 * channel.  Bind this in Blueprint to forward the message to in-game chat.
 *
 * @param Username  Display name of the Discord user who sent the message.
 * @param Message   Plain text content of the Discord message.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDiscordMessageReceivedDelegate,
                                             const FString&, Username,
                                             const FString&, Message);

/**
 * Fired on the game thread when the Discord Gateway connection is established
 * and the bot has been identified successfully (Ready event received).
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiscordConnectedDelegate);

/**
 * Fired on the game thread when the Discord Gateway connection is lost.
 *
 * @param Reason  Human-readable description of why the connection ended.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordDisconnectedDelegate,
                                            const FString&, Reason);

/**
 * Native multicast delegate fired on the game thread whenever Discord delivers
 * an INTERACTION_CREATE gateway event (button clicks, modal submits, etc.).
 * Other mods (e.g. TicketSystem) subscribe to this to handle their own
 * interaction custom_ids without modifying DiscordBridge.
 *
 * @param DataObj  The full interaction payload JSON object.  Callers must not
 *                 hold a reference to this past the current call stack frame.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FDiscordInteractionReceivedDelegate,
                                    const TSharedPtr<FJsonObject>& /*DataObj*/);

/**
 * Native multicast delegate fired on the game thread for every MESSAGE_CREATE
 * gateway event received from Discord.  Other mods can bind to this to
 * inspect the full message JSON (content, channel_id, member roles, etc.)
 * without depending on DiscordBridge's internal command parsing.
 *
 * @param MessageObj  The full MESSAGE_CREATE data JSON object.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FDiscordRawMessageReceivedDelegate,
                                    const TSharedPtr<FJsonObject>& /*MessageObj*/);

// ── Discord Gateway opcodes (Discord API reference §Gateway Opcodes) ─────────
namespace EDiscordGatewayOpcode
{
	static constexpr int32 Dispatch          = 0;  // Server → Client: an event was dispatched
	static constexpr int32 Heartbeat         = 1;  // Client → Server: keep-alive heartbeat
	static constexpr int32 Identify          = 2;  // Client → Server: trigger authentication
	static constexpr int32 UpdatePresence    = 3;  // Client → Server: update bot presence/status
	static constexpr int32 Reconnect         = 7;  // Server → Client: client should reconnect
	static constexpr int32 InvalidSession    = 9;  // Server → Client: session is invalid
	static constexpr int32 Hello            = 10;  // Server → Client: sent immediately after connecting
	static constexpr int32 HeartbeatAck     = 11;  // Server → Client: heartbeat was acknowledged
}

// ── Discord Gateway intent bit-flags (Discord API reference §Gateway Intents) 
namespace EDiscordGatewayIntent
{
	// Non-privileged
	static constexpr int32 Guilds         = 1 << 0;   //    1
	static constexpr int32 GuildMessages  = 1 << 9;   //  512

	// Privileged – must be enabled in the Discord Developer Portal
	static constexpr int32 GuildMembers   = 1 << 1;   //    2  (Server Members Intent)
	static constexpr int32 MessageContent = 1 << 15;  // 32768 (Message Content Intent)

	// Combined value used when connecting to the Gateway.
	static constexpr int32 All =
		Guilds | GuildMembers | GuildMessages | MessageContent;
	// = 1 + 2 + 512 + 32768 = 33283
}

/**
 * UDiscordBridgeSubsystem
 *
 * A GameInstance-level subsystem that bridges Satisfactory in-game chat with
 * a Discord text channel.
 *
 * How it works
 * ────────────
 *  • Connects to the Discord Gateway (wss://gateway.discord.gg/?v=10&encoding=json)
 *    using USMLWebSocketClient from the SMLWebSocket plugin.
 *  • Authenticates with the configured BotToken and requests two privileged
 *    intents: Server Members Intent and Message Content Intent.
 *  • Discord → Game: MESSAGE_CREATE events on the configured channel fire
 *    OnDiscordMessageReceived so that Blueprint (or another C++ subsystem) can
 *    inject the message into the Satisfactory chat.
 *  • Game → Discord: AFGChatManager::OnChatMessageAdded is bound via a
 *    periodic ticker so that every CMT_PlayerMessage added to the server's
 *    chat history is forwarded to Discord through the REST API.  The delegate
 *    approach avoids funchook entirely, which is necessary because
 *    AddChatMessageToReceived, BroadcastChatMessage, and related functions are
 *    all too short for funchook to patch in the shipped game binary.
 *
 * Setup
 * ─────
 *  1. Create a Discord application and bot in the Discord Developer Portal.
 *  2. Enable the following Privileged Gateway Intents on the Bot page:
 *       – Server Members Intent
 *       – Message Content Intent
 *  3. Invite the bot to your server with "Send Messages" + "Read Message History".
 *  4. Fill in BotToken and ChannelId in Mods/DiscordBridge/Config/DefaultDiscordBridge.ini
 *     (auto-created on first server start) and restart the server.
 *  5. Optionally customise GameToDiscordFormat and DiscordToGameFormat.
 *  6. In Blueprint, bind to OnDiscordMessageReceived and call
 *     SendGameMessageToDiscord() from your chat hooks.
 */
UCLASS(BlueprintType)
class DISCORDBRIDGE_API UDiscordBridgeSubsystem : public UGameInstanceSubsystem,
                                                  public IDiscordBridgeProvider
{
	GENERATED_BODY()

public:
	// ── USubsystem ────────────────────────────────────────────────────────────

	/** Restrict this subsystem to dedicated servers only. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// ── Delegates ─────────────────────────────────────────────────────────────

	/**
	 * Fired when a message is received from the bridged Discord channel.
	 * Bind this in Blueprint to forward the message to the Satisfactory chat.
	 */
	UPROPERTY(BlueprintAssignable, Category="Discord Bridge")
	FDiscordMessageReceivedDelegate OnDiscordMessageReceived;

	/** Fired when the Discord Gateway connection is ready. */
	UPROPERTY(BlueprintAssignable, Category="Discord Bridge")
	FDiscordConnectedDelegate OnDiscordConnected;

	/** Fired when the Discord Gateway connection is lost. */
	UPROPERTY(BlueprintAssignable, Category="Discord Bridge")
	FDiscordDisconnectedDelegate OnDiscordDisconnected;

	/**
	 * Native multicast delegate fired whenever Discord delivers an
	 * INTERACTION_CREATE gateway event (button clicks, modal submits).
	 * Subscribe from other modules to handle custom interaction custom_ids
	 * without modifying DiscordBridge directly.
	 */
	FDiscordInteractionReceivedDelegate OnDiscordInteractionReceived;

	/**
	 * Native multicast delegate fired on the game thread for every MESSAGE_CREATE
	 * gateway event.  Use this to inspect the full Discord message JSON
	 * (channel_id, member roles, etc.) from external modules.
	 */
	FDiscordRawMessageReceivedDelegate OnDiscordRawMessageReceived;

	// ── Public API ────────────────────────────────────────────────────────────

	/**
	 * Forward a Satisfactory chat message to the bridged Discord channel via
	 * the Discord REST API.
	 *
	 * @param PlayerName  The in-game name of the player who sent the message.
	 *                    Substituted for %PlayerName% in GameToDiscordFormat.
	 * @param Message     The chat message text.
	 *                    Substituted for %Message% in GameToDiscordFormat.
	 */
	UFUNCTION(BlueprintCallable, Category="Discord Bridge")
	void SendGameMessageToDiscord(const FString& PlayerName, const FString& Message);

	/**
	 * Manually trigger a connection to the Discord Gateway.
	 * Called automatically during Initialize() when BotToken and ChannelId are set.
	 */
	UFUNCTION(BlueprintCallable, Category="Discord Bridge")
	void Connect();

	/**
	 * Disconnect from the Discord Gateway and cancel the heartbeat timer.
	 * Called automatically during Deinitialize().
	 */
	UFUNCTION(BlueprintCallable, Category="Discord Bridge")
	void Disconnect();

	/**
	 * Send a presence update to Discord to set the bot's online status.
	 *
	 * @param Status  One of "online", "idle", "dnd", or "invisible".
	 */
	UFUNCTION(BlueprintCallable, Category="Discord Bridge")
	void SendUpdatePresence(const FString& Status);

	/**
	 * Returns true when the Gateway WebSocket is open and the bot has been
	 * identified (Ready event received from Discord).
	 */
	UFUNCTION(BlueprintPure, Category="Discord Bridge")
	bool IsConnected() const { return bGatewayReady; }

	/** Returns the Discord bot token used for REST API authentication.
	 *  Empty when the token is not yet configured. */
	UFUNCTION(BlueprintPure, Category="Discord Bridge")
	virtual const FString& GetBotToken() const override;

	/** Returns the Discord guild (server) ID received from the READY event.
	 *  Empty until the Gateway handshake is complete. */
	UFUNCTION(BlueprintPure, Category="Discord Bridge")
	virtual const FString& GetGuildId() const override;

	/** Returns the Discord user ID of the guild owner.
	 *  Populated after the first GUILD_CREATE event is received; may be empty
	 *  on servers that only receive READY without a full GUILD_CREATE. */
	UFUNCTION(BlueprintPure, Category="Discord Bridge")
	virtual const FString& GetGuildOwnerId() const override;

	/**
	 * Post a plain-text message to any Discord channel via the REST API.
	 * Useful for other mods that need to send messages outside the main bridge
	 * channel (e.g. posting to a dedicated ticket notification channel).
	 *
	 * @param TargetChannelId  Snowflake ID of the destination channel.
	 * @param Message          Plain-text content (Discord markdown supported).
	 */
	virtual void SendDiscordChannelMessage(const FString& TargetChannelId,
	                                       const FString& Message) override;

	/**
	 * Respond to a Discord interaction (button click or modal submit) via the
	 * REST API.  Must be called within ~3 seconds of receiving the interaction
	 * or Discord will show an error to the user.
	 *
	 * @param InteractionId    The interaction "id" field from the payload.
	 * @param InteractionToken The interaction "token" field from the payload.
	 * @param ResponseType     Discord callback type:
	 *                           4 = CHANNEL_MESSAGE_WITH_SOURCE (send a message)
	 *                           5 = DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE
	 *                           6 = DEFERRED_UPDATE_MESSAGE (ack silently)
	 * @param Content          Message text (used when ResponseType == 4).
	 * @param bEphemeral       When true the response is only visible to the
	 *                         user who triggered the interaction.
	 */
	virtual void RespondToInteraction(const FString& InteractionId,
	                                  const FString& InteractionToken,
	                                  int32 ResponseType,
	                                  const FString& Content,
	                                  bool bEphemeral) override;

	virtual void RespondWithModal(const FString& InteractionId,
	                              const FString& InteractionToken,
	                              const FString& ModalCustomId,
	                              const FString& Title,
	                              const FString& Placeholder,
	                              const FString& ComponentCustomId = TEXT("ticket_reason")) override;

	virtual void FollowUpInteraction(const FString& InteractionToken,
	                                 const FString& Message,
	                                 bool bEphemeral) override;

	/**
	 * Send a pre-built JSON message body (content + optional components) to a
	 * Discord channel via the REST API.  Use this when the message includes
	 * action rows / buttons in addition to plain text.
	 *
	 * @param TargetChannelId  Snowflake ID of the destination channel.
	 * @param MessageBody      Fully constructed Discord message JSON object.
	 */
	virtual void SendMessageBodyToChannel(const FString& TargetChannelId,
	                                      const TSharedPtr<FJsonObject>& MessageBody) override;

	/**
	 * Delete a Discord channel via the REST API.
	 * Used by the TicketSystem mod to close/delete ticket channels.
	 *
	 * @param ChannelId  Snowflake ID of the channel to delete.
	 */
	virtual void DeleteDiscordChannel(const FString& ChannelId) override;

	/**
	 * Create a new guild text channel via the Discord REST API and invoke the
	 * provided callback with the new channel's ID on success (empty on failure).
	 *
	 * @param ChannelName        Desired channel name (must conform to Discord naming rules).
	 * @param CategoryId         Optional parent category snowflake ID.  Pass empty to skip.
	 * @param PermissionOverwrites  JSON array of permission-overwrite objects.
	 * @param OnCreated          Called on the game thread with the new channel ID.
	 */
	virtual void CreateDiscordGuildTextChannel(const FString& ChannelName,
	                                           const FString& CategoryId,
	                                           const TArray<TSharedPtr<FJsonValue>>& PermissionOverwrites,
	                                           TFunction<void(const FString& NewChannelId)> OnCreated) override;

	/** Respond to a Discord interaction with a fully constructed message body
	 *  (type 4 = CHANNEL_MESSAGE_WITH_SOURCE), supporting embeds and components.
	 *  Implements IDiscordBridgeProvider::RespondToInteractionWithBody(). */
	virtual void RespondToInteractionWithBody(const FString& InteractionId,
	                                          const FString& InteractionToken,
	                                          const TSharedPtr<FJsonObject>& MessageData,
	                                          bool bEphemeral) override;

	/** Respond to a Discord button interaction by showing a multi-field modal popup
	 *  (type 9 = MODAL).  Implements IDiscordBridgeProvider::RespondWithMultiFieldModal(). */
	virtual void RespondWithMultiFieldModal(const FString& InteractionId,
	                                        const FString& InteractionToken,
	                                        const FString& ModalCustomId,
	                                        const FString& Title,
	                                        const TArray<FModalField>& Fields) override;

	/** Creates a public thread in @p ChannelId and calls @p OnCreated with the
	 *  new thread ID (or an empty string if the Discord API request fails).
	 *  Implements IDiscordBridgeProvider::CreateDiscordThread(). */
	virtual void CreateDiscordThread(
		const FString& ChannelId,
		const FString& ThreadName,
		TFunction<void(const FString& ThreadId)> OnCreated) override;

	/**
	 * Called by OnGameChatMessageAdded every time a player-chat message lands
	 * in the server's history.  Forwards the message to Discord.
	 *
	 * @param PlayerName  Value of FChatMessageStruct::MessageSender (may be empty
	 *                    if the game does not populate it server-side; falls back
	 *                    to "Unknown" inside SendGameMessageToDiscord).
	 * @param MessageText Plain text of the chat message.
	 */
	void HandleIncomingChatMessage(const FString& PlayerName, const FString& MessageText);

	// ── IDiscordBridgeProvider ────────────────────────────────────────────────
	// Subscribe/unsubscribe methods wrap the native multicast delegates above,
	// exposing them through the provider interface used by TicketSystem.

	virtual FDelegateHandle SubscribeInteraction(
		TFunction<void(const TSharedPtr<FJsonObject>&)> Callback) override;
	virtual void UnsubscribeInteraction(FDelegateHandle Handle) override;

	virtual FDelegateHandle SubscribeRawMessage(
		TFunction<void(const TSharedPtr<FJsonObject>&)> Callback) override;
	virtual void UnsubscribeRawMessage(FDelegateHandle Handle) override;

	// ── In-game slash command helpers (callable from SML command actors) ──────

	/**
	 * Process a `/verify <code>` command issued from in-game chat.
	 * Looks up the code in the pending verification table, resolves the player's
	 * EOS PUID, and adds them to the whitelist if the code is valid and unexpired.
	 *
	 * @param PlayerName  In-game display name of the player who typed the command.
	 * @param Code        Verification code string (without the `/verify ` prefix).
	 */
	void HandleInGameVerify(const FString& PlayerName, const FString& Code);

	/** Handle a whitelist management command typed in the Satisfactory in-game chat. */
	void HandleInGameWhitelistCommand(const FString& SubCommand);

	/** Return the configured Discord invite URL (empty string if not set). */
	FString GetDiscordInviteUrl() const;

	/**
	 * Returns true when the Discord account verification feature is enabled
	 * (bWhitelistVerificationEnabled=True in config).
	 * Used by the /commands in-game command to conditionally advertise /verify.
	 */
	bool IsVerificationEnabled() const;

private:
	// ── WebSocket event handlers (called on the game thread) ──────────────────

	UFUNCTION()
	void OnWebSocketConnected();

	UFUNCTION()
	void OnWebSocketMessage(const FString& RawJson);

	UFUNCTION()
	void OnWebSocketClosed(int32 StatusCode, const FString& Reason);

	UFUNCTION()
	void OnWebSocketError(const FString& ErrorMessage);

	UFUNCTION()
	void OnWebSocketReconnecting(int32 AttemptNumber, float DelaySeconds);

	// ── Chat capture (Game → Discord) ─────────────────────────────────────────

	/**
	 * Bound to AFGChatManager::OnChatMessageAdded.  Diffs the current message
	 * list against the previous snapshot and forwards any new CMT_PlayerMessage
	 * entries to Discord.
	 */
	UFUNCTION()
	void OnGameChatMessageAdded();

	/**
	 * Attempts to locate AFGChatManager in the current world and bind
	 * OnGameChatMessageAdded to its OnChatMessageAdded delegate.
	 * Returns true when binding succeeds; the caller's ticker stops on success.
	 */
	bool TryBindToChatManager();

	// ── Discord Gateway protocol ──────────────────────────────────────────────

	/** Dispatch the correct handler based on the Gateway opcode. */
	void HandleGatewayPayload(const FString& RawJson);

	/** op=10: Server sent Hello; start heartbeating and send Identify. */
	void HandleHello(const TSharedPtr<FJsonObject>& DataObj);

	/** op=0: Server dispatched an event. Routes to the correct event handler. */
	void HandleDispatch(const FString& EventType, int32 Sequence,
	                    const TSharedPtr<FJsonObject>& DataObj);

	/** op=11: Server acknowledged our heartbeat. */
	void HandleHeartbeatAck();

	/** op=7: Server asked us to reconnect. */
	void HandleReconnect();

	/** op=9: Session is invalid; re-identify or start fresh. */
	void HandleInvalidSession(bool bResumable);

	/** t=READY: Bot is authenticated and ready. */
	void HandleReady(const TSharedPtr<FJsonObject>& DataObj);

	/** t=RESUMED: Gateway session successfully resumed after reconnect. */
	void HandleResumed();

	/** t=MESSAGE_CREATE: A new message was posted in a channel. */
	void HandleMessageCreate(const TSharedPtr<FJsonObject>& DataObj);

	/**
	 * Automatically relays an incoming Discord message to the Satisfactory in-game
	 * chat via AFGChatManager::BroadcastChatMessage.
	 * Bound to OnDiscordMessageReceived in Initialize() so messages are bridged
	 * without requiring any Blueprint wiring.
	 */
	UFUNCTION()
	void RelayDiscordMessageToGame(const FString& Username, const FString& Message);

	/** Send the Identify payload (op=2) to authenticate the bot. */
	void SendIdentify();

	/**
	 * Send the Resume payload (op=6) to resume an interrupted Gateway session.
	 * Requires SessionId and LastSequenceNumber to be populated.
	 * Discord replays all missed events when the resume succeeds and fires
	 * t=RESUMED; on failure it sends op=9 (Invalid Session, d=false) and we
	 * fall back to a full Identify.
	 */
	void SendResume();

	/** Send a heartbeat (op=1) to keep the Gateway connection alive. */
	void SendHeartbeat();

	/** Send a plain text message to the configured Discord channel via the REST API. */
	void SendStatusMessageToDiscord(const FString& Message);

	/** Send a plain text message to a specific Discord channel via the REST API.
	 *  When TargetChannelId is empty, the call is a no-op. */
	void SendMessageToChannel(const FString& TargetChannelId, const FString& Message);

	/** Serialise a JSON object and send it as a text WebSocket frame. */
	void SendGatewayPayload(const TSharedPtr<FJsonObject>& Payload);

	// ── Heartbeat timer ───────────────────────────────────────────────────────

	/** Timer callback – fires SendHeartbeat() at the interval Discord requested. */
	bool HeartbeatTick(float DeltaTime);

	FTSTicker::FDelegateHandle HeartbeatTickerHandle;
	float HeartbeatIntervalSeconds{0.0f};

	/** Deferred one-shot ticker scheduled by HandleInvalidSession to send a
	 *  Resume or fresh Identify after the Discord-mandated 1–5 s back-off.
	 *  Stored so that Disconnect() can cancel it if the subsystem shuts down
	 *  or a new op=9 arrives before the previous deferred action fires. */
	FTSTicker::FDelegateHandle PendingReidentifyHandle;

	// ── Player count presence ─────────────────────────────────────────────────

	/**
	 * Queries the current connected player count, formats it using
	 * PlayerCountPresenceFormat, and sends a Discord presence update
	 * (op=3) containing a "Watching" activity with the formatted text.
	 * No-ops when the Gateway is not ready or the feature is disabled.
	 */
	void UpdatePlayerCountPresence();

	/** Timer callback – fires UpdatePlayerCountPresence() at the configured interval. */
	bool PlayerCountTick(float DeltaTime);

	FTSTicker::FDelegateHandle PlayerCountTickerHandle;

	// ── Internal state ────────────────────────────────────────────────────────

	/** The WebSocket client connected to the Discord Gateway. */
	UPROPERTY()
	TObjectPtr<USMLWebSocketClient> WebSocketClient{nullptr};

	/** Loaded configuration (populated in Initialize()). */
	FDiscordBridgeConfig Config;

	/** Loaded whitelist configuration (populated in Initialize()). */
	FWhitelistConfig WhitelistConfig;

	/** Loaded in-game broadcast messages configuration (populated in Initialize()). */
	FInGameMessagesConfig InGameMessagesConfig;

	/** Last sequence number received from Discord (used in heartbeats). */
	int32 LastSequenceNumber{-1};

	/** true after the READY dispatch has been received from Discord. */
	bool bGatewayReady{false};

	/**
	 * true when a heartbeat has been sent and we are waiting for the server's
	 * op=11 HeartbeatAck.  If this flag is still true when the next heartbeat
	 * is due, the connection is a zombie (Discord's term) and must be closed so
	 * that USMLWebSocketClient's auto-reconnect can re-establish it.
	 */
	bool bPendingHeartbeatAck{false};

	/**
	 * true after the ServerOnlineMessage has been sent for the current server
	 * session.  Prevents the message from being re-sent on Discord Gateway
	 * reconnects (which happen periodically and trigger a fresh READY event
	 * even when the game server has not restarted).
	 * Reset to false in Disconnect() so that a true server restart sends the
	 * message again on the next connection.
	 */
	bool bServerOnlineMessageSent{false};

	/** Snowflake ID of the bot user; used to filter out self-sent messages. */
	FString BotUserId;

	// ── Gateway session resumption ────────────────────────────────────────────

	/**
	 * Session ID received in the READY event.  Retained across reconnects so
	 * that the bot can send op=6 (Resume) instead of a full op=2 (Identify),
	 * which causes Discord to replay any missed events.
	 * Cleared only on Disconnect() or when op=9 with d=false is received
	 * (indicating the session has expired and cannot be resumed).
	 */
	FString SessionId;

	/**
	 * Gateway URL received in the READY event.  Discord may route the bot to
	 * a specific shard URL for resumption; always prefer this URL when resuming.
	 * Falls back to DiscordGatewayUrl when empty.
	 */
	FString ResumeGatewayUrl;

	// ── Chat manager binding ──────────────────────────────────────────────────

	/**
	 * Periodic ticker that attempts to bind to AFGChatManager::OnChatMessageAdded
	 * once per second until the chat manager is available.  Cleared on success.
	 */
	FTSTicker::FDelegateHandle ChatManagerBindTickHandle;

	/** Weak reference to the chat manager we bound to; used for cleanup. */
	TWeakObjectPtr<AFGChatManager> BoundChatManager;

	/**
	 * Snapshot of mReceivedMessages taken when OnGameChatMessageAdded last ran.
	 * Used to diff against the current message list and detect newly added entries.
	 */
	TArray<FChatMessageStruct> LastKnownMessages;

	// ── Whitelist enforcement ─────────────────────────────────────────────────

	/**
	 * Bound to FGameModeEvents::GameModePostLoginEvent.
	 * Kicks any player that is not on the whitelist when the whitelist is enabled.
	 * Also fires the player join Discord notification when PlayerEventsEnabled is true.
	 */
	void OnPostLogin(AGameModeBase* GameMode, APlayerController* Controller);

	/**
	 * Hooked onto AGameModeBase::Logout via SUBSCRIBE_METHOD_VIRTUAL_AFTER.
	 * Posts a player leave or timeout notification to Discord when
	 * PlayerEventsEnabled is true.
	 */
	void OnLogout(AGameModeBase* GameMode, AController* Exiting);

	/**
	 * Posts a player join notification to Discord.
	 * No-op when PlayerEventsEnabled is false or PlayerJoinMessage is empty.
	 *
	 * @param PlayerName       The in-game name of the player who joined.
	 * @param EOSProductUserId EOS Product User ID (32-char hex) of the joining player, or empty.
	 * @param IpAddress        Remote IP address of the joining player, or empty.
	 */
	void SendPlayerJoinNotification(const FString& PlayerName,
	                                const FString& EOSProductUserId = FString(),
	                                const FString& IpAddress        = FString());

	/**
	 * Fetch all guild members who hold WhitelistRoleId via the Discord REST API
	 * and populate RoleMemberIdToNames / WhitelistRoleMemberNames.
	 * Clears the cache then initiates paginated fetching via FetchWhitelistRoleMembersPage.
	 * Called from HandleReady whenever WhitelistRoleId is configured.
	 */
	void FetchWhitelistRoleMembers();

	/**
	 * Fetch a single page of guild members starting after AfterUserId.
	 * Recurses automatically when the returned page is full (1000 entries),
	 * stopping when a partial page is received (indicating the final page).
	 *
	 * @param AfterUserId  Snowflake ID of the last member from the previous page.
	 *                     Pass an empty string to start from the beginning.
	 */
	void FetchWhitelistRoleMembersPage(const FString& AfterUserId);

	/**
	 * Add or remove a single member's display names in the Discord role member
	 * cache based on whether they currently hold WhitelistRoleId.
	 * Called from GUILD_MEMBER_ADD, GUILD_MEMBER_UPDATE and GUILD_MEMBER_REMOVE
	 * Gateway events.
	 *
	 * @param MemberObj  The member object from the Gateway event payload.
	 * @param bRemoved   When true the member left the guild; purge them unconditionally.
	 */
	void UpdateWhitelistRoleMemberEntry(const TSharedPtr<FJsonObject>& MemberObj,
	                                    bool bRemoved = false);

	/**
	 * Rebuild WhitelistRoleMemberNames (the flat name-lookup set) from the
	 * authoritative RoleMemberIdToNames map.  Must be called after any mutation
	 * of RoleMemberIdToNames.
	 */
	void RebuildWhitelistRoleNameSet();

	/** Handle a whitelist management command received from Discord.
	 *  @param ResponseChannelId  The channel to send the response to.
	 *                            When empty, falls back to the main ChannelId.
	 *  @param AuthorDiscordId    Discord user ID of the sender (used for apply/link). */
	void HandleWhitelistCommand(const FString& SubCommand, const FString& DiscordUsername,
	                            const FString& ResponseChannelId,
	                            const FString& AuthorDiscordId = TEXT(""));

	/** Broadcast a status/feedback message to all connected players via the game chat. */
	void SendGameChatStatusMessage(const FString& Message);

	/**
	 * Send the on-join hint message (JoinHintMessage config key) privately to
	 * the specified player controller via the SML Remote Call Object.
	 * No-op when JoinHintMessage is empty or the RCO is not yet available.
	 *
	 * @param Controller  The player controller of the newly-joined player.
	 * @param PlayerName  In-game display name used for %PlayerName% substitution.
	 */
	void SendJoinHintToPlayer(APlayerController* Controller, const FString& PlayerName);

	/**
	 * Broadcast the on-join message (InGameJoinBroadcast config key) to ALL
	 * connected players via AFGChatManager::BroadcastChatMessage.
	 * No-op when InGameJoinBroadcast is empty.
	 * Completely independent of the whitelist setting.
	 *
	 * @param PlayerName  In-game display name used for %PlayerName% substitution.
	 */
	void SendInGameJoinBroadcast(const FString& PlayerName);

	/**
	 * Posts a colour-coded Discord embed to TargetChannelId for a player event.
	 * Called by SendPlayerJoinNotification and OnLogout when bUseEmbedsForPlayerEvents
	 * is true.
	 *
	 * @param TargetChannelId  Snowflake ID of the destination channel.
	 * @param Title            Embed title, e.g. "Player Joined".
	 * @param Color            Discord sidebar colour as decimal integer.
	 *                           3066993  = green  (join)
	 *                           15158332 = red    (leave)
	 *                           16776960 = orange (timeout)
	 * @param PlayerName       Player name shown in the embed "Player" field.
	 */
	void SendPlayerEventEmbed(const FString& TargetChannelId,
	                          const FString& Title,
	                          int32 Color,
	                          const FString& PlayerName);

	/**
	 * Assign or revoke a Discord role from a guild member via the REST API.
	 * No-op when RoleId, GuildId, or BotToken is empty.
	 *
	 * @param UserId  Discord snowflake of the target member.
	 * @param RoleId  Discord snowflake of the role to grant or revoke.
	 * @param bGrant  true = grant the role, false = revoke it.
	 */
	void ModifyDiscordRole(const FString& UserId, const FString& RoleId, bool bGrant);

	FDelegateHandle PostLoginHandle;

	/** Handle returned by SUBSCRIBE_METHOD_VIRTUAL_AFTER on AGameModeBase::Logout.
	 *  Stored so the handler can be removed in Deinitialize(). */
	FDelegateHandle LogoutHookHandle;

	/** Snowflake ID of the guild (server) the bot is connected to.
	 *  Populated from the first entry in the READY event's guilds array.
	 *  Required for Discord REST role-management calls. */
	FString GuildId;

	/** Snowflake ID of the guild owner.
	 *  Populated from the GUILD_CREATE event; empty until that event fires.
	 *  Used by TicketSystem and other extensions to authorise guild-owner actions. */
	FString GuildOwnerId;

	// ── Discord role member cache (WhitelistRoleId) ───────────────────────────

	/**
	 * Authoritative store: maps each Discord user ID to the set of lowercased
	 * display names associated with that member (nick, global_name, username).
	 * Only members who currently hold WhitelistRoleId are present.
	 * Written from the game thread only (HTTP callbacks + Gateway event handlers).
	 */
	TMap<FString, TArray<FString>> RoleMemberIdToNames;

	/**
	 * Flat lookup set derived from RoleMemberIdToNames.
	 * Contains every lowercased display name of every member who holds
	 * WhitelistRoleId.  Rebuilt via RebuildWhitelistRoleNameSet() after
	 * any change to RoleMemberIdToNames.
	 * Checked in OnPostLogin as a secondary whitelist pass-through so that
	 * players whose in-game name matches a Discord role-member name are not
	 * kicked even if they are not listed in ServerWhitelist.json.
	 */
	TSet<FString> WhitelistRoleMemberNames;

	/**
	 * Temporarily holds the resolved role label for the Discord message that is
	 * currently being processed.  Set in HandleMessageCreate before broadcasting
	 * OnDiscordMessageReceived so that RelayDiscordMessageToGame can substitute
	 * the %Role% placeholder without changing the delegate signature.
	 * Cleared immediately after the relay call.
	 */
	FString CurrentMessageRoleLabel;

	/**
	 * Weak reference to the TicketSubsystem; populated during Initialize() if
	 * TicketSystem is installed.  Using TWeakObjectPtr avoids adding a hard GC
	 * root while still nulling automatically if the object is ever destroyed.
	 */
	TWeakObjectPtr<UTicketSubsystem> CachedTicketSubsystem;

	/**
	 * Weak reference to the BanDiscordSubsystem; populated during Initialize()
	 * when BanSystem is installed alongside DiscordBridge.  Used to inject and
	 * later detach the Discord provider so ban commands receive Discord events.
	 * Using TWeakObjectPtr avoids adding a hard GC root.
	 */
	TWeakObjectPtr<UBanDiscordSubsystem> CachedBanDiscordSubsystem;

	// ── /stats / /playerstats ─────────────────────────────────────────────────

	/** Handle the /stats Discord command — send a server-stats embed. */
	void HandleStatsCommand(const FString& ResponseChannelId);

	/** Handle the /playerstats <name> Discord command — send per-player stats embed. */
	void HandlePlayerStatsCommand(const FString& ResponseChannelId,
	                              const FString& TargetPlayerName);

	// ── Per-player stat counters (populated by FGStatisticsSubsystem hooks) ──

	struct FPlayerStatCounters
	{
		int32 BuildingsBuilt     = 0;
		int32 ItemsPickedUp      = 0;
		int32 BuildingsDismantled = 0;
	};

	/** In-memory per-player statistics map keyed by in-game display name. */
	TMap<FString, FPlayerStatCounters> PlayerStats;

	// ── Reaction voting ───────────────────────────────────────────────────────

	struct FPendingVote
	{
		FString   MessageId;
		FString   ChannelId;
		FString   PlayerName;
		FDateTime ExpiresAt;
	};

	/** Active join votes awaiting expiry check, keyed by Discord message snowflake. */
	TMap<FString, FPendingVote> PendingVotes;

	/** Ticker handles for per-vote expiry timers, keyed by message snowflake so
	 *  fired handles are self-pruned and cancelled handles can be removed by ID.
	 *  Remaining handles are cancelled in Deinitialize() if the subsystem is torn
	 *  down while a vote window is still open. */
	TMap<FString, FTSTicker::FDelegateHandle> VoteKickTimerHandles;

	/** Add 👍/👎 reactions to a join message and optionally track the vote. */
	void AddJoinReactions(const FString& MessageId, const FString& ChannelId,
	                      const FString& PlayerName);

	/** Fetch reaction counts and kick if the 👎 threshold is met. */
	void CheckVoteResult(const FString& MessageId);

	// ── AFK kick ─────────────────────────────────────────────────────────────

	struct FPlayerAfkState
	{
		int32     LastBuildCount    = 0;
		FDateTime LastActivityTime;
		/** World-space location sampled each AFK tick; ZeroVector until first tick. */
		FVector   LastKnownLocation = FVector::ZeroVector;
	};

	/** Per-player AFK idle tracking map keyed by in-game display name. */
	TMap<FString, FPlayerAfkState> AfkStates;

	FTSTicker::FDelegateHandle AfkKickTickerHandle;

	/** Start the AFK kick periodic ticker (no-op when AfkKickMinutes=0). */
	void StartAfkKickTicker();

	/** Ticker callback — checks each player's idle time and kicks AFKers. */
	bool AfkKickTick(float DeltaTime);

	// ── Game phase & schematic unlock announcements ───────────────────────────

	/** Try to bind to AFGGamePhaseManager and AFGSchematicManager delegates.
	 *  Returns true when both are bound (ticker stops); false to keep retrying. */
	bool TryBindToGameSubsystems();

	/** Fired when the server reaches a new game phase. */
	UFUNCTION()
	void OnGamePhaseUpdated(UFGGamePhase* NewPhase, bool bSuppressNarrative);

	/** Fired when the game completion condition is met. */
	UFUNCTION()
	void OnGameCompleted(bool bSuppressNarrative);

	/** Fired when a schematic is purchased/unlocked. */
	UFUNCTION()
	void OnSchematicPurchased(TSubclassOf<UFGSchematic> SchematicClass);

	/** True once AFGGamePhaseManager delegates have been successfully bound. */
	bool bBoundGamePhase = false;

	/** True once AFGSchematicManager delegate has been successfully bound. */
	bool bBoundSchematic = false;

	/** True once UMuteRegistry mute-event delegates have been bound. */
	bool bBoundMuteEvents = false;

	/** Handle for the deferred-bind ticker that calls TryBindToGameSubsystems(). */
	FTSTicker::FDelegateHandle GameSubsystemBindTickHandle;

	/** Handle for the OnPlayerMuted delegate bound to UMuteRegistry. */
	FDelegateHandle MutedEventHandle;

	/** Handle for the OnPlayerUnmuted delegate bound to UMuteRegistry. */
	FDelegateHandle UnmutedEventHandle;

	// ── Scheduled announcements ───────────────────────────────────────────────

	/** Accumulated seconds since last scheduled announcement was posted. */
	float AnnouncementAccumulatedSeconds = 0.0f;

	/** Ticker handle for periodic server announcements. */
	FTSTicker::FDelegateHandle AnnouncementTickerHandle;

	/** Handles for the multi-slot scheduled announcement tickers. */
	TArray<FTSTicker::FDelegateHandle> ScheduledAnnouncementHandles;

	/** Start the announcement ticker when AnnouncementIntervalMinutes > 0. */
	void StartAnnouncementTicker();

	/** Start one ticker per ScheduledAnnouncements entry. */
	void StartScheduledAnnouncementTickers();

	/** Ticker callback — posts the announcement message at the configured interval. */
	bool AnnouncementTick(float DeltaTime);

	// ── Scheduled in-game broadcast messages ─────────────────────────────────

	/** Ticker handles for individual in-game broadcast message tickers. */
	TArray<FTSTicker::FDelegateHandle> InGameMessageTickerHandles;

	/** Start one ticker per InGameMessagesConfig.Messages entry. */
	void StartInGameMessageTickers();

	// ── /server / /online commands ────────────────────────────────────────────

	/** Handle the /server Discord command — post a server info embed. */
	void HandleServerCommand(const FString& ResponseChannelId);

	/** Handle the /online Discord command — post a list of online players with session times. */
	void HandleOnlineCommand(const FString& ResponseChannelId);

	// ── /help / bot info command ──────────────────────────────────────────────

	/**
	 * Post a comprehensive feature/command-reference embed to ResponseChannelId.
	 * Called automatically on the first Gateway READY when BotInfoChannelId is
	 * configured, and in response to the /help command in the bridged channel.
	 *
	 * @param ResponseChannelId  Snowflake ID of the channel to post the embed to.
	 */
	void HandleBotInfoCommand(const FString& ResponseChannelId);

	/**
	 * true after the bot-info embed has been posted for the current server session.
	 * Prevents re-posting on Gateway reconnects (which trigger a fresh READY event).
	 * Reset to false in Disconnect() so the embed is re-posted on a true restart.
	 */
	bool bBotInfoPosted{false};

	// ── Mute event notifications ──────────────────────────────────────────────

	/** Post a mute/unmute notification to the moderator channel when bNotifyMuteEvents=true. */
	void NotifyMuteEvent(const FString& PlayerName, const FString& Uid,
	                     bool bIsMuted, const FString& Reason);

	// ── Slash command registration ────────────────────────────────────────────

	/** Register all Discord application slash commands with the guild via the
	 *  REST bulk-overwrite endpoint. Called on READY when bEnableSlashCommands=true. */
	void RegisterSlashCommands();

	/** Handle an APPLICATION_COMMAND slash command interaction (interaction type 2).
	 *  Called from the INTERACTION_CREATE gateway event handler. */
	void HandleSlashCommandInteraction(const TSharedPtr<FJsonObject>& DataObj);

	/** Handle an APPLICATION_COMMAND_AUTOCOMPLETE interaction (interaction type 4).
	 *  Returns up to 25 matching player names from PlayerSessionRegistry. */
	void HandleAutocompleteInteraction(const TSharedPtr<FJsonObject>& DataObj);

	/** Extract the string value of a named option from a Discord slash command options array.
	 *  Handles both STRING and INTEGER option types.  Returns empty string when not found. */
	static FString GetSlashOptionString(const TArray<TSharedPtr<FJsonValue>>* Options,
	                                    const FString& Name);

	/** Post a whitelist event embed to WhitelistEventsChannelId. */
	void PostWhitelistEvent(const FString& Action, const FString& Target,
	                        const FString& AdminName, int32 Color);

	/** Ticker handle for whitelist expiry check (60-second interval). */
	FTSTicker::FDelegateHandle WhitelistExpiryCheckHandle;

	// ── Whitelist application flow (Feature 3) ────────────────────────────────

	/** Maps Discord user ID → in-game player name for pending whitelist applications. */
	TMap<FString, FString> PendingWhitelistApps;

	/** Maps Discord user ID → submission time for pending whitelist applications (for expiry). */
	TMap<FString, FDateTime> PendingWhitelistAppExpiry;

	// ── Whitelist expiry warnings (Feature 5) ─────────────────────────────────

	/** Player names that have already received an expiry-warning notification.
	 *  Persisted to disk so warnings are not re-sent after a server restart. */
	TSet<FString> WarnedExpiryNames;

	/** Persist WarnedExpiryNames to ProjectSaved/DiscordBridge/WarnedExpiryNames.json. */
	void SaveWarnedExpiryNames() const;

	/** Load WarnedExpiryNames from disk (called during Initialize()). */
	void LoadWarnedExpiryNames();

	// ── Linked account verification (Feature 6) ───────────────────────────────

	/** Maps 6-digit verification code → Discord user ID. */
	TMap<FString, FString> PendingVerifications;

	/** Maps 6-digit verification code → in-game player name submitted by that Discord user. */
	TMap<FString, FString> PendingVerificationNames;

	/** Maps 6-digit verification code → expiry time (10 minutes from creation). */
	TMap<FString, FDateTime> PendingVerificationExpiry;

	// ── Chat-filter auto-warn tracking ────────────────────────────────────────

	/** Per-player timestamps of recent chat-filter hits (for auto-warn threshold). */
	struct FFilterHitRecord
	{
		TArray<FDateTime> HitTimestamps;
	};

	/** Maps player display-name → recent filter-hit timestamps. */
	TMap<FString, FFilterHitRecord> ChatFilterHits;

	/**
	 * Send a Direct Message to a Discord user.
	 * Step 1: POST /users/@me/channels to create a DM channel.
	 * Step 2: POST /channels/<id>/messages to send the message.
	 * No-op when DiscordUserId, Message, or BotToken is empty.
	 */
	void SendDiscordDM(const FString& DiscordUserId, const FString& Message);
};
