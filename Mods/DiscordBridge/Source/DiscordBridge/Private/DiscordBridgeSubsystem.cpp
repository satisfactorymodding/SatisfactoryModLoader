// Copyright Yamahasxviper. All Rights Reserved.

#include "DiscordBridgeSubsystem.h"
#include "TicketSubsystem.h"
#include "BanDiscordSubsystem.h"

#include "BanDatabase.h"
#include "BanSystemConfig.h"
#include "BanDiscordNotifier.h"
#include "BanAuditLog.h"
#include "BanEnforcer.h"
#include "PlayerWarningRegistry.h"

#include "Player/SMLRemoteCallObject.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "FGPlayerController.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/OnlineReplStructs.h"
#include "FGChatManager.h"
#include "FGGamePhaseManager.h"
#include "FGGamePhase.h"
#include "FGSchematicManager.h"
#include "FGSchematic.h"
#include "TimerManager.h"
#include "WhitelistManager.h"
#include "Patching/NativeHookManager.h"
#include "MuteRegistry.h"
#include "PlayerWarningRegistry.h"
#include "PlayerSessionRegistry.h"

DEFINE_LOG_CATEGORY(LogDiscordBridge);

// Discord Gateway endpoint (v10, JSON encoding)
static const FString DiscordGatewayUrl = TEXT("wss://gateway.discord.gg/?v=10&encoding=json");
// Discord REST API base URL
static const FString DiscordApiBase    = TEXT("https://discord.com/api/v10");

// Escapes a string for safe embedding in a JSON string literal.
// Handles \, ", \n, \r, \t, control characters U+0000-U+001F, and lone surrogates.
static FString JsonEscapeStr(const FString& S)
{
	FString Out;
	Out.Reserve(S.Len() + 8);
	for (int32 i = 0; i < S.Len(); ++i)
	{
		const TCHAR C = S[i];
		switch (C)
		{
		case TEXT('"'):  Out += TEXT("\\\""); break;
		case TEXT('\\'): Out += TEXT("\\\\"); break;
		case TEXT('\n'): Out += TEXT("\\n");  break;
		case TEXT('\r'): Out += TEXT("\\r");  break;
		case TEXT('\t'): Out += TEXT("\\t");  break;
		default:
			if (C >= 0xD800 && C <= 0xDFFF)
				Out += TEXT("\uFFFD"); // Lone surrogate — invalid in JSON (RFC 8259 §7); replace with U+FFFD
			else if (C < 0x20)
				Out += FString::Printf(TEXT("\\u%04x"), static_cast<uint32>(C));
			else
				Out += C;
			break;
		}
	}
	return Out;
}

// ─────────────────────────────────────────────────────────────────────────────
// USubsystem lifetime
// ─────────────────────────────────────────────────────────────────────────────

bool UDiscordBridgeSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// Only create this subsystem on dedicated servers.
	// This prevents the bot from running on client or listen-server builds,
	// meaning players do not need this mod (or SML) installed on their own machine.
	return IsRunningDedicatedServer();
}

void UDiscordBridgeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Subscribe to PostLogin to enforce the whitelist and ban list on each player join.
	PostLoginHandle = FGameModeEvents::GameModePostLoginEvent.AddUObject(
		this, &UDiscordBridgeSubsystem::OnPostLogin);

	// Subscribe to AGameModeBase::Logout to detect player leaves and timeouts.
	// SUBSCRIBE_METHOD_VIRTUAL_AFTER installs a global vtable hook the first time
	// and adds this instance's handler to the handler list.  The handle is stored
	// so we can remove exactly this handler in Deinitialize().
	{
		TWeakObjectPtr<UDiscordBridgeSubsystem> WeakThis(this);
		LogoutHookHandle = SUBSCRIBE_METHOD_VIRTUAL_AFTER(
			AGameModeBase::Logout,
			GetMutableDefault<AGameModeBase>(),
			[WeakThis](AGameModeBase* GameMode, AController* Exiting)
			{
				if (UDiscordBridgeSubsystem* Self = WeakThis.Get())
				{
					Self->OnLogout(GameMode, Exiting);
				}
			});
	}

	// Wire up the Discord→game relay once here so it is never double-bound
	// across reconnect cycles (Connect() may be called multiple times).
	OnDiscordMessageReceived.AddDynamic(this, &UDiscordBridgeSubsystem::RelayDiscordMessageToGame);

	// Start a 1-second periodic ticker that tries to find AFGChatManager and
	// bind to its OnChatMessageAdded delegate.  The ticker stops as soon as
	// binding succeeds (TryBindToChatManager returns true).
	ChatManagerBindTickHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateWeakLambda(this, [this](float) -> bool
		{
			return !TryBindToChatManager(); // false = stop ticking
		}),
		1.0f);

	// Load (or auto-create) the JSON config file from Configs/DiscordBridge.cfg.
	Config = FDiscordBridgeConfig::LoadOrCreate();

	// Load the separate whitelist config file (DefaultWhitelist.ini + backup).
	FWhitelistConfig::RestoreDefaultConfigIfNeeded();
	WhitelistConfig = FWhitelistConfig::Load();

	// Restore expiry-warning dedup set so warnings are not re-fired on restart.
	LoadWarnedExpiryNames();

	// Load the in-game broadcast messages config file (DefaultInGameMessages.ini + backup).
	FInGameMessagesConfig::RestoreDefaultConfigIfNeeded();
	InGameMessagesConfig = FInGameMessagesConfig::Load();

	// Load (or create) the whitelist JSON from disk, using the config value as
	// the default only on the very first server start (when no JSON file exists).
	// After the first start the enabled/disabled state is saved in the JSON and
	// survives restarts, so runtime /whitelist on / /whitelist off changes persist.
	// To force-reset to this config value: delete ServerWhitelist.json and restart.
	FWhitelistManager::Load(WhitelistConfig.bWhitelistEnabled);
	FWhitelistManager::SetMaxSlots(WhitelistConfig.MaxWhitelistSlots);

	// Start a 60-second ticker to remove expired whitelist entries and
	// post expiry warnings when WhitelistExpiryWarningHours > 0.
	WhitelistExpiryCheckHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateWeakLambda(this, [this](float) -> bool
		{
			// ── Remove fully-expired entries ────────────────────────────────
			TArray<FString> ExpiredNames;
			FWhitelistManager::RemoveExpiredEntries(ExpiredNames);
			for (const FString& Name : ExpiredNames)
			{
				const FString Msg = FString::Printf(
					TEXT(":clock1: **%s** has been removed from the whitelist (entry expired)."), *Name);
				const FString& NotifyChan = WhitelistConfig.WhitelistEventsChannelId.IsEmpty()
					? Config.ChannelId : WhitelistConfig.WhitelistEventsChannelId;
				if (!NotifyChan.IsEmpty())
				{
					SendMessageToChannel(NotifyChan, Msg);
				}
				WarnedExpiryNames.Remove(Name);
			}
			if (!ExpiredNames.IsEmpty())
				SaveWarnedExpiryNames();

			// ── Post expiry warnings ─────────────────────────────────────────
			if (WhitelistConfig.WhitelistExpiryWarningHours > 0.0f)
			{
				const FDateTime Now       = FDateTime::UtcNow();
				const FTimespan WarnWindow = FTimespan::FromHours(WhitelistConfig.WhitelistExpiryWarningHours);
				for (const FWhitelistEntry& E : FWhitelistManager::GetAllEntries())
				{
					if (E.ExpiresAt.GetTicks() == 0) continue;   // permanent
					if (WarnedExpiryNames.Contains(E.Name)) continue;
					const FTimespan Remaining = E.ExpiresAt - Now;
					if (Remaining > FTimespan::Zero() && Remaining <= WarnWindow)
					{
						WarnedExpiryNames.Add(E.Name);
						SaveWarnedExpiryNames();
						const FString WarnChan = WhitelistConfig.WhitelistEventsChannelId.IsEmpty()
							? Config.ChannelId : WhitelistConfig.WhitelistEventsChannelId;
						if (!WarnChan.IsEmpty())
						{
							const int32 RemDays  = static_cast<int32>(Remaining.GetDays());
							const int32 RemHours = static_cast<int32>(Remaining.GetHours());
							const int32 RemMins  = static_cast<int32>(Remaining.GetMinutes());
							FString WarnMsg;
							if (RemDays > 0)
								WarnMsg = FString::Printf(
									TEXT(":warning: **%s**'s whitelist entry expires in **%dd %dh** (%s UTC)."),
									*E.Name, RemDays, RemHours,
									*E.ExpiresAt.ToString(TEXT("%Y-%m-%d %H:%M")));
							else if (RemHours > 0)
								WarnMsg = FString::Printf(
									TEXT(":warning: **%s**'s whitelist entry expires in **%dh %dm** (%s UTC)."),
									*E.Name, RemHours, RemMins,
									*E.ExpiresAt.ToString(TEXT("%Y-%m-%d %H:%M")));
							else
								WarnMsg = FString::Printf(
									TEXT(":warning: **%s**'s whitelist entry expires in **%dm** (%s UTC)."),
									*E.Name, FMath::Max(1, static_cast<int32>(Remaining.GetTotalMinutes())),
									*E.ExpiresAt.ToString(TEXT("%Y-%m-%d %H:%M")));
							SendMessageToChannel(WarnChan, WarnMsg);
						}
					}
				}
			}

			// ── Clean up expired verification codes ──────────────────────────
			{
				const FDateTime Now = FDateTime::UtcNow();
				TArray<FString> ExpiredCodes;
				for (const auto& Pair : PendingVerificationExpiry)
				{
					if (Pair.Value <= Now)
						ExpiredCodes.Add(Pair.Key);
				}
				for (const FString& Code : ExpiredCodes)
				{
					PendingVerifications.Remove(Code);
					PendingVerificationNames.Remove(Code);
					PendingVerificationExpiry.Remove(Code);
				}
			}

			// ── Clean up expired whitelist applications ───────────────────────
			{
				const FDateTime Now = FDateTime::UtcNow();
				TArray<FString> ExpiredApps;
				for (const auto& Pair : PendingWhitelistAppExpiry)
				{
					if (Pair.Value <= Now)
						ExpiredApps.Add(Pair.Key);
				}
				for (const FString& DiscordId : ExpiredApps)
				{
					PendingWhitelistApps.Remove(DiscordId);
					PendingWhitelistAppExpiry.Remove(DiscordId);
				}
			}

			return true;
		}),
		60.0f);

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Whitelist active = %s (WhitelistEnabled config = %s)"),
	       FWhitelistManager::IsEnabled() ? TEXT("True") : TEXT("False"),
	       WhitelistConfig.bWhitelistEnabled ? TEXT("True") : TEXT("False"));

	if (Config.BotToken.IsEmpty() || Config.ChannelId.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: BotToken or ChannelId is not configured. "
		            "Edit Mods/DiscordBridge/Config/DefaultDiscordBridge.ini to enable the bridge."));
		// Stop the ChatManager bind ticker — it serves no purpose without a bot connection.
		if (ChatManagerBindTickHandle.IsValid())
		{
			FTSTicker::GetCoreTicker().RemoveTicker(ChatManagerBindTickHandle);
			ChatManagerBindTickHandle.Reset();
		}
		return;
	}

	// Log active format strings so operators can verify they were loaded correctly.
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: ServerName           = \"%s\""), *Config.ServerName);
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: GameToDiscordFormat  = \"%s\""), *Config.GameToDiscordFormat);
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: DiscordToGameFormat  = \"%s\""), *Config.DiscordToGameFormat);

	Connect();

	// Start a 5-second deferred ticker to bind to AFGGamePhaseManager and
	// AFGSchematicManager delegates once the world and GameState are ready.
	// The ticker cancels itself after the first successful bind.
	GameSubsystemBindTickHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateWeakLambda(this, [this](float) -> bool
		{
			const bool bDone = TryBindToGameSubsystems();
			if (bDone) GameSubsystemBindTickHandle.Reset();
			return !bDone; // false = stop ticking
		}),
		5.0f);

	// Wire ourselves as the Discord provider into UTicketSubsystem (always
	// present now that TicketSystem is merged into this module).
	Collection.InitializeDependency<UTicketSubsystem>();
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UTicketSubsystem* Tickets = GI->GetSubsystem<UTicketSubsystem>())
		{
			CachedTicketSubsystem = Tickets;
			Tickets->SetProvider(this);
		}
	}

	// Wire ourselves as the Discord provider into UBanDiscordSubsystem so that
	// Discord ban commands are forwarded to BanSystem when it is installed.
	// GetSubsystem<> returns nullptr when BanSystem is not loaded, so this is
	// gracefully skipped on servers that do not have BanSystem installed.
	Collection.InitializeDependency<UBanDiscordSubsystem>();
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanDiscordSubsystem* BanDiscord = GI->GetSubsystem<UBanDiscordSubsystem>())
		{
			CachedBanDiscordSubsystem = BanDiscord;
			BanDiscord->SetProvider(this);
		}
	}

	// Start AFK kick ticker when configured.
	StartAfkKickTicker();

	// Start scheduled announcement ticker when configured.
	StartAnnouncementTicker();
	StartScheduledAnnouncementTickers();

	// Start in-game broadcast message tickers when configured.
	StartInGameMessageTickers();

}

void UDiscordBridgeSubsystem::Deinitialize()
{
	// Detach from TicketSubsystem so it stops processing interactions after we shut down.
	if (UTicketSubsystem* Tickets = CachedTicketSubsystem.Get())
	{
		Tickets->SetProvider(nullptr);
	}
	CachedTicketSubsystem.Reset();

	// Detach from BanDiscordSubsystem so ban commands stop firing after we shut down.
	if (UBanDiscordSubsystem* BanDiscord = CachedBanDiscordSubsystem.Get())
	{
		BanDiscord->SetProvider(nullptr);
	}
	CachedBanDiscordSubsystem.Reset();

	// Stop the chat-manager bind ticker if it is still running.
	FTSTicker::GetCoreTicker().RemoveTicker(ChatManagerBindTickHandle);
	ChatManagerBindTickHandle.Reset();

	// Stop the deferred game-subsystem bind ticker if it is still running.
	FTSTicker::GetCoreTicker().RemoveTicker(GameSubsystemBindTickHandle);
	GameSubsystemBindTickHandle.Reset();

	// Remove the whitelist PostLogin listener.
	FGameModeEvents::GameModePostLoginEvent.Remove(PostLoginHandle);
	PostLoginHandle.Reset();

	// Remove the Logout hook handler installed in Initialize().
	UNSUBSCRIBE_METHOD(AGameModeBase::Logout, LogoutHookHandle);
	LogoutHookHandle.Reset();

	// Unbind from the chat manager's delegate so no stale callbacks fire
	// after this subsystem is destroyed.
	if (BoundChatManager.IsValid())
	{
		BoundChatManager->OnChatMessageAdded.RemoveDynamic(
			this, &UDiscordBridgeSubsystem::OnGameChatMessageAdded);
		BoundChatManager.Reset();
	}

	// Unbind from UMuteRegistry delegates.
	if (bBoundMuteEvents)
	{
		UWorld* W = GetWorld();
		UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
		if (UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr)
		{
			MuteReg->OnPlayerMuted.Remove(MutedEventHandle);
			MuteReg->OnPlayerUnmuted.Remove(UnmutedEventHandle);
		}
		MutedEventHandle.Reset();
		UnmutedEventHandle.Reset();
		bBoundMuteEvents = false;
	}

	// Unbind from AFGGamePhaseManager and AFGSchematicManager delegates.
	{
		UWorld* W = GetWorld();
		if (W && bBoundGamePhase)
		{
			if (AFGGamePhaseManager* PhaseMgr = AFGGamePhaseManager::Get(W))
			{
				PhaseMgr->mOnCurrentGamePhaseUpdated.RemoveDynamic(
					this, &UDiscordBridgeSubsystem::OnGamePhaseUpdated);
				PhaseMgr->mOnGameCompleted.RemoveDynamic(
					this, &UDiscordBridgeSubsystem::OnGameCompleted);
			}
			bBoundGamePhase = false;
		}
		if (W && bBoundSchematic)
		{
			if (AFGSchematicManager* SchMgr = AFGSchematicManager::Get(W))
			{
				SchMgr->PurchasedSchematicDelegate.RemoveDynamic(
					this, &UDiscordBridgeSubsystem::OnSchematicPurchased);
			}
			bBoundSchematic = false;
		}
	}

	// Stop the whitelist expiry ticker.
	FTSTicker::GetCoreTicker().RemoveTicker(WhitelistExpiryCheckHandle);
	WhitelistExpiryCheckHandle.Reset();

	// Stop the AFK kick ticker.
	FTSTicker::GetCoreTicker().RemoveTicker(AfkKickTickerHandle);
	AfkKickTickerHandle.Reset();
	FTSTicker::GetCoreTicker().RemoveTicker(AnnouncementTickerHandle);
	AnnouncementTickerHandle.Reset();

	for (FTSTicker::FDelegateHandle& H : ScheduledAnnouncementHandles)
		FTSTicker::GetCoreTicker().RemoveTicker(H);
	ScheduledAnnouncementHandles.Empty();

	// Stop in-game broadcast message tickers.
	for (FTSTicker::FDelegateHandle& H : InGameMessageTickerHandles)
		FTSTicker::GetCoreTicker().RemoveTicker(H);
	InGameMessageTickerHandles.Empty();

	// Cancel any pending vote-kick window timers.
	for (auto& VotePair : VoteKickTimerHandles)
		FTSTicker::GetCoreTicker().RemoveTicker(VotePair.Value);
	VoteKickTimerHandles.Empty();

	Disconnect();
	Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
// Connection management
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::Connect()
{
	// If a WebSocket client already exists — whether connected, mid-handshake,
	// or mid-reconnect — do not create a second one.  The old client's dynamic
	// delegate callbacks are still bound to this subsystem and would fire on top
	// of the new client's events, causing double Hello / double heartbeat.
	if (WebSocketClient)
	{
		return;
	}

	WebSocketClient = USMLWebSocketClient::CreateWebSocketClient(this);

	// Configure auto-reconnect; Discord may close the connection at any time.
	WebSocketClient->bAutoReconnect              = true;
	WebSocketClient->ReconnectInitialDelaySeconds = 2.0f;
	WebSocketClient->MaxReconnectDelaySeconds     = 30.0f;
	WebSocketClient->MaxReconnectAttempts         = 0; // infinite

	// Bind WebSocket delegates.
	WebSocketClient->OnConnected.AddDynamic(this,  &UDiscordBridgeSubsystem::OnWebSocketConnected);
	WebSocketClient->OnMessage.AddDynamic(this,    &UDiscordBridgeSubsystem::OnWebSocketMessage);
	WebSocketClient->OnClosed.AddDynamic(this,     &UDiscordBridgeSubsystem::OnWebSocketClosed);
	WebSocketClient->OnError.AddDynamic(this,      &UDiscordBridgeSubsystem::OnWebSocketError);
	WebSocketClient->OnReconnecting.AddDynamic(this, &UDiscordBridgeSubsystem::OnWebSocketReconnecting);

	UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Connecting to Discord Gateway…"));
	WebSocketClient->Connect(DiscordGatewayUrl, {}, {});
}

void UDiscordBridgeSubsystem::Disconnect()
{
	// Stop heartbeat ticker.
	FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
	HeartbeatTickerHandle.Reset();

	// Cancel any pending deferred re-identify/resume so it does not fire
	// against a closed or replaced WebSocket after shutdown.
	FTSTicker::GetCoreTicker().RemoveTicker(PendingReidentifyHandle);
	PendingReidentifyHandle.Reset();

	// Stop player count presence ticker.
	FTSTicker::GetCoreTicker().RemoveTicker(PlayerCountTickerHandle);
	PlayerCountTickerHandle.Reset();

	// Signal offline status and post the server-offline notification while
	// the WebSocket is still open so Discord receives both before we close.
	if (bGatewayReady)
	{
		// Setting presence to "invisible" makes the bot appear offline to
		// users immediately, without waiting for Discord to detect the
		// WebSocket disconnection.
		SendUpdatePresence(TEXT("invisible"));

		if (!Config.ServerOfflineMessage.IsEmpty())
		{
			SendStatusMessageToDiscord(Config.ServerOfflineMessage);
		}
	}

	bGatewayReady            = false;
	bPendingHeartbeatAck     = false;
	bServerOnlineMessageSent = false;
	bBotInfoPosted           = false;
	LastSequenceNumber       = -1;
	BotUserId.Empty();
	GuildId.Empty();
	GuildOwnerId.Empty();
	SessionId.Empty();
	ResumeGatewayUrl.Empty();

	if (WebSocketClient)
	{
		// Unbind all dynamic delegates BEFORE calling Close() — Close() may
		// fire OnClosed synchronously, which would otherwise invoke a delegate
		// on an object that is already being torn down.
		WebSocketClient->OnConnected.RemoveDynamic(this,    &UDiscordBridgeSubsystem::OnWebSocketConnected);
		WebSocketClient->OnMessage.RemoveDynamic(this,      &UDiscordBridgeSubsystem::OnWebSocketMessage);
		WebSocketClient->OnClosed.RemoveDynamic(this,       &UDiscordBridgeSubsystem::OnWebSocketClosed);
		WebSocketClient->OnError.RemoveDynamic(this,        &UDiscordBridgeSubsystem::OnWebSocketError);
		WebSocketClient->OnReconnecting.RemoveDynamic(this, &UDiscordBridgeSubsystem::OnWebSocketReconnecting);

		WebSocketClient->bAutoReconnect = false;
		WebSocketClient->Close(1000, TEXT("Client shutting down"));
		WebSocketClient = nullptr;
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// WebSocket event handlers (game thread)
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::OnWebSocketConnected()
{
	UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: WebSocket connection established. Awaiting Hello…"));
	// Discord will send op=10 (Hello) next; we send Identify in response.
}

void UDiscordBridgeSubsystem::OnWebSocketMessage(const FString& RawJson)
{
	HandleGatewayPayload(RawJson);
}

void UDiscordBridgeSubsystem::OnWebSocketClosed(int32 StatusCode, const FString& Reason)
{
	UE_LOG(LogDiscordBridge, Warning,
	       TEXT("DiscordBridge: Gateway connection closed (code=%d, reason='%s')."),
	       StatusCode, *Reason);

	// Detect Discord-specific close codes that indicate a permanent error.
	// For these codes reconnecting with the same credentials will never succeed,
	// so we signal the WebSocket client to stop auto-reconnecting.
	bool bTerminal = false;
	switch (StatusCode)
	{
	case 4004:
		UE_LOG(LogDiscordBridge, Error,
		       TEXT("DiscordBridge: Authentication failed (4004). "
		            "Verify BotToken in Mods/DiscordBridge/Config/DefaultDiscordBridge.ini. "
		            "Auto-reconnect disabled."));
		bTerminal = true;
		break;
	case 4010:
		UE_LOG(LogDiscordBridge, Error, TEXT("DiscordBridge: Invalid shard sent (4010). Auto-reconnect disabled."));
		bTerminal = true;
		break;
	case 4011:
		UE_LOG(LogDiscordBridge, Error, TEXT("DiscordBridge: Sharding required (4011). Auto-reconnect disabled."));
		bTerminal = true;
		break;
	case 4012:
		UE_LOG(LogDiscordBridge, Error, TEXT("DiscordBridge: Invalid Gateway API version (4012). Auto-reconnect disabled."));
		bTerminal = true;
		break;
	case 4013:
		UE_LOG(LogDiscordBridge, Error, TEXT("DiscordBridge: Invalid intent(s) (4013). Auto-reconnect disabled."));
		bTerminal = true;
		break;
	case 4014:
		UE_LOG(LogDiscordBridge, Error,
		       TEXT("DiscordBridge: Disallowed intent(s) (4014). "
		            "Enable Server Members Intent and Message Content Intent "
		            "in the Discord Developer Portal. Auto-reconnect disabled."));
		bTerminal = true;
		break;
	default:
		break;
	}

	if (bTerminal && WebSocketClient)
	{
		// Cancel any deferred Resume/Identify ticker so it does not fire
		// after the connection has been permanently abandoned.
		FTSTicker::GetCoreTicker().RemoveTicker(PendingReidentifyHandle);
		PendingReidentifyHandle.Reset();

		// Stop the player-count presence ticker — it serves no purpose when
		// we are not going to reconnect, and bGatewayReady is already false.
		FTSTicker::GetCoreTicker().RemoveTicker(PlayerCountTickerHandle);
		PlayerCountTickerHandle.Reset();

		// Unbind all dynamic delegates BEFORE calling Close() and nulling the
		// pointer.  Close() can fire OnClosed synchronously; if the delegates
		// are still bound they would re-enter OnWebSocketClosed during teardown,
		// running the heartbeat-removal block a second time.  After Close() the
		// client pointer is no longer usable, so we null it to prevent any
		// subsequent Disconnect() call from operating on a dead object.
		WebSocketClient->OnConnected.RemoveDynamic(this,    &UDiscordBridgeSubsystem::OnWebSocketConnected);
		WebSocketClient->OnMessage.RemoveDynamic(this,      &UDiscordBridgeSubsystem::OnWebSocketMessage);
		WebSocketClient->OnClosed.RemoveDynamic(this,       &UDiscordBridgeSubsystem::OnWebSocketClosed);
		WebSocketClient->OnError.RemoveDynamic(this,        &UDiscordBridgeSubsystem::OnWebSocketError);
		WebSocketClient->OnReconnecting.RemoveDynamic(this, &UDiscordBridgeSubsystem::OnWebSocketReconnecting);

		// Clear bAutoReconnect before Close() so that the reconnect loop exits
		// cleanly without queuing another attempt.
		WebSocketClient->bAutoReconnect = false;
		WebSocketClient->Close(1000, FString::Printf(TEXT("Terminal Discord close code %d"), StatusCode));
		WebSocketClient = nullptr;
	}

	// Cancel heartbeat; it will be restarted on the next successful connection.
	FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
	HeartbeatTickerHandle.Reset();
	bPendingHeartbeatAck = false;

	const bool bWasReady = bGatewayReady;
	bGatewayReady = false;

	if (bWasReady)
	{
		OnDiscordDisconnected.Broadcast(
			FString::Printf(TEXT("Connection closed (code %d): %s"), StatusCode, *Reason));
	}
}

void UDiscordBridgeSubsystem::OnWebSocketError(const FString& ErrorMessage)
{
	UE_LOG(LogDiscordBridge, Error, TEXT("DiscordBridge: WebSocket error: %s"), *ErrorMessage);

	FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
	HeartbeatTickerHandle.Reset();
	bPendingHeartbeatAck = false;

	if (bGatewayReady)
	{
		bGatewayReady = false;
		OnDiscordDisconnected.Broadcast(FString::Printf(TEXT("WebSocket error: %s"), *ErrorMessage));
	}
}

void UDiscordBridgeSubsystem::OnWebSocketReconnecting(int32 AttemptNumber, float DelaySeconds)
{
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Reconnecting to Discord Gateway (attempt %d, delay %.1fs)…"),
	       AttemptNumber, DelaySeconds);

	// Reset Gateway state; we'll re-identify once the WebSocket reconnects.
	FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
	HeartbeatTickerHandle.Reset();
	bPendingHeartbeatAck = false;
	bGatewayReady = false;
}

// ─────────────────────────────────────────────────────────────────────────────
// Discord Gateway protocol
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleGatewayPayload(const FString& RawJson)
{
	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: Failed to parse Gateway JSON: %s"), *RawJson);
		return;
	}

	double OpCodeD = -1.0;
	if (!Root->TryGetNumberField(TEXT("op"), OpCodeD))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: Gateway payload missing 'op' field: %s"), *RawJson);
		return;
	}
	// Guard against out-of-range or non-finite doubles before casting.
	// Discord opcodes are 0–11; anything outside [0, 31] is unknown/malformed.
	if (OpCodeD < 0.0 || OpCodeD > 31.0 || !FMath::IsFinite(OpCodeD))
	{
		UE_LOG(LogDiscordBridge, Warning,
			TEXT("DiscordBridge: Gateway payload has out-of-range opcode (%.0f), ignoring"), OpCodeD);
		return;
	}
	const int32 OpCode = static_cast<int32>(OpCodeD);

	switch (OpCode)
	{
	case EDiscordGatewayOpcode::Dispatch:
	{
		// Update the sequence number first; it is used in heartbeats.
		// TryGetNumberField accepts double&, int32&, and int64& since UE5.3.2.
		// We use double here to guard against a malformed gateway that sends a
		// fractional or out-of-range value (see the range check below).
		double Seq = -1.0;
		if (Root->TryGetNumberField(TEXT("s"), Seq))
		{
			// Guard against out-of-range doubles before casting to int32.
			// Discord sequence numbers are non-negative integers well within
			// INT32_MAX; anything outside [0, INT32_MAX] or non-integer is malformed.
			if (Seq >= 0.0 && Seq <= static_cast<double>(MAX_int32)
			    && FMath::IsFinite(Seq) && FMath::Fmod(Seq, 1.0) == 0.0)
				LastSequenceNumber = static_cast<int32>(Seq);
		}

		FString EventType;
		Root->TryGetStringField(TEXT("t"), EventType);

		const TSharedPtr<FJsonObject>* DataPtr = nullptr;
		Root->TryGetObjectField(TEXT("d"), DataPtr);

		HandleDispatch(EventType, LastSequenceNumber,
		               DataPtr ? *DataPtr : MakeShared<FJsonObject>());
		break;
	}
	case EDiscordGatewayOpcode::Hello:
	{
		const TSharedPtr<FJsonObject>* DataPtr = nullptr;
		if (Root->TryGetObjectField(TEXT("d"), DataPtr) && DataPtr)
		{
			HandleHello(*DataPtr);
		}
		break;
	}
	case EDiscordGatewayOpcode::HeartbeatAck:
		HandleHeartbeatAck();
		break;

	case EDiscordGatewayOpcode::Heartbeat:
		// Server explicitly requested a heartbeat right now.
		SendHeartbeat();
		break;

	case EDiscordGatewayOpcode::Reconnect:
		HandleReconnect();
		break;

	case EDiscordGatewayOpcode::InvalidSession:
	{
		bool bResumable = false;
		Root->TryGetBoolField(TEXT("d"), bResumable);
		HandleInvalidSession(bResumable);
		break;
	}
	default:
		UE_LOG(LogDiscordBridge, VeryVerbose,
		       TEXT("DiscordBridge: Unhandled opcode %d"), OpCode);
		break;
	}
}

void UDiscordBridgeSubsystem::HandleHello(const TSharedPtr<FJsonObject>& DataObj)
{
	// Discord sends the heartbeat interval in milliseconds.
	double HeartbeatMs = 41250.0; // sensible default
	DataObj->TryGetNumberField(TEXT("heartbeat_interval"), HeartbeatMs);
	if (HeartbeatMs >= 1000.0 && HeartbeatMs <= 120000.0)
	{
		HeartbeatIntervalSeconds = static_cast<float>(HeartbeatMs) / 1000.0f;
	}
	else
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: Unexpected heartbeat_interval %.0f ms — using default %.2f s."),
		       HeartbeatMs, HeartbeatIntervalSeconds);
	}

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Hello received. Heartbeat interval: %.2f s"),
	       HeartbeatIntervalSeconds);

	// Cancel any pending deferred re-identify/resume ticker — Hello starts a
	// fresh auth handshake so the old deferred operation is obsolete.
	FTSTicker::GetCoreTicker().RemoveTicker(PendingReidentifyHandle);
	PendingReidentifyHandle.Reset();

	// Start heartbeating with a random jitter so that all bots don't hammer the
	// Gateway simultaneously on mass-reconnects (Discord "thundering herd" concern).
	// Strategy: one-shot ticker after a random [0, interval] delay fires the first
	// heartbeat and then installs the regular repeating ticker.
	// HeartbeatTickerHandle tracks whichever ticker is active so Disconnect() can
	// always cancel it with a single RemoveTicker() call.
	FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
	bPendingHeartbeatAck = false;

	const float JitterSeconds = FMath::FRandRange(0.0f, HeartbeatIntervalSeconds);
	HeartbeatTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateWeakLambda(this, [this](float) -> bool
		{
			// Reset the one-shot handle BEFORE calling SendHeartbeat() so it is
			// not double-removed when FTSTicker cleans up the one-shot after this
			// callback returns.
			HeartbeatTickerHandle.Reset();
			SendHeartbeat();
			// Install the repeating ticker only if the heartbeat was actually sent
			// (SendHeartbeat sets bPendingHeartbeatAck=true on the normal path).
			// In the zombie path SendHeartbeat clears bPendingHeartbeatAck, calls
			// Connect(), and returns early — the new connection's Hello will
			// install the repeating ticker instead.
			if (bPendingHeartbeatAck)
			{
				HeartbeatTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
					FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime) -> bool
					{
						return HeartbeatTick(DeltaTime);
					}),
					HeartbeatIntervalSeconds);
			}
			return false; // one-shot – do not repeat
		}),
		JitterSeconds);

	// If we have an active session, attempt to resume it rather than starting a
	// full Identify.  Discord will replay missed events and fire t=RESUMED on
	// success, or send op=9 (Invalid Session, d=false) if the session expired.
	if (!SessionId.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: Hello received (resume path). Sending Resume for session %s."),
		       *SessionId);
		SendResume();
	}
	else
	{
		// Send Identify so Discord authenticates us.
		SendIdentify();
	}
}

void UDiscordBridgeSubsystem::HandleDispatch(const FString& EventType, int32 Sequence,
                                              const TSharedPtr<FJsonObject>& DataObj)
{
	if (EventType == TEXT("READY"))
	{
		HandleReady(DataObj);
	}
	else if (EventType == TEXT("RESUMED"))
	{
		HandleResumed();
	}
	else if (EventType == TEXT("MESSAGE_CREATE"))
	{
		HandleMessageCreate(DataObj);
	}
	else if (EventType == TEXT("GUILD_CREATE"))
	{
		// GUILD_CREATE carries the full guild object; capture both the guild ID
		// (reliable fallback in case READY's partial guilds array was absent)
		// and the owner ID used by extension modules (e.g. TicketSystem).
		FString IncomingGuildId;
		if (DataObj->TryGetStringField(TEXT("id"), IncomingGuildId) &&
		    !IncomingGuildId.IsEmpty())
		{
			if (GuildId.IsEmpty())
			{
				// First GUILD_CREATE seen — set both GuildId and GuildOwnerId.
				// For bots in multiple guilds the first GUILD_CREATE wins (same
				// policy as the READY handler which picks the first entry in the array).
				GuildId = IncomingGuildId;
				DataObj->TryGetStringField(TEXT("owner_id"), GuildOwnerId);
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Guild ID set from GUILD_CREATE: %s"), *GuildId);
			}
			else if (GuildId == IncomingGuildId)
			{
				// GUILD_CREATE for our already-accepted guild.  This is the normal
				// path on initial connect (READY sets GuildId before GUILD_CREATE
				// fires) and after a resume/reconnect (GuildId is replayed).
				// Refresh GuildOwnerId in case ownership transferred; no warning needed.
				DataObj->TryGetStringField(TEXT("owner_id"), GuildOwnerId);
			}
			else
			{
				// The bot has been added to a second, different guild.  All moderation
				// commands, role lookups, and channel operations target the first guild
				// only.  Log a prominent warning so the server operator can investigate.
				// Do NOT update GuildOwnerId — that would give the wrong guild's owner
				// staff-level permissions in the ticket system and ban panel.
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: Ignoring GUILD_CREATE for guild %s — bot is already ")
				       TEXT("operating in guild %s. Remove the bot from the extra guild to avoid ")
				       TEXT("unexpected behaviour."),
				       *IncomingGuildId, *GuildId);
			}
		}
	}
	else if (EventType == TEXT("INTERACTION_CREATE"))
	{
		// Handle slash command interactions (type 2 = APPLICATION_COMMAND)
		// and autocomplete interactions (type 4 = APPLICATION_COMMAND_AUTOCOMPLETE).
		{
			int32 InteractionType = 0;
			DataObj->TryGetNumberField(TEXT("type"), InteractionType);
			if (InteractionType == 2)
			{
				HandleSlashCommandInteraction(DataObj);
				return;
			}
			if (InteractionType == 4)
			{
				HandleAutocompleteInteraction(DataObj);
				return;
			}
		}

		// Handle whitelist application button interactions before broadcasting.
		{
			const TSharedPtr<FJsonObject>* InteractionDataPtr = nullptr;
			FString CustomId;
			if (DataObj->TryGetObjectField(TEXT("data"), InteractionDataPtr) && InteractionDataPtr)
				(*InteractionDataPtr)->TryGetStringField(TEXT("custom_id"), CustomId);

			if (CustomId.StartsWith(TEXT("wl_approve:")) || CustomId.StartsWith(TEXT("wl_deny:")))
			{
				const bool  bApprove       = CustomId.StartsWith(TEXT("wl_approve:"));
				// Use Len() so the offset stays correct if the prefix string is ever renamed.
				const FString TargetDiscordId = bApprove
					? CustomId.Mid(FString(TEXT("wl_approve:")).Len())
					: CustomId.Mid(FString(TEXT("wl_deny:")).Len());

				// Guard against malformed button custom_ids (e.g. "wl_approve:" with no ID).
				if (TargetDiscordId.IsEmpty())
				{
					FString InteractionId, InteractionToken;
					DataObj->TryGetStringField(TEXT("id"),    InteractionId);
					DataObj->TryGetStringField(TEXT("token"), InteractionToken);
					RespondToInteraction(InteractionId, InteractionToken, 4,
						TEXT(":warning: Malformed button interaction — missing target Discord ID."),
						/*bEphemeral=*/true);
					return;
				}

				FString InteractionId, InteractionToken;
				DataObj->TryGetStringField(TEXT("id"),    InteractionId);
				DataObj->TryGetStringField(TEXT("token"), InteractionToken);

				// Verify that the clicker holds WhitelistCommandRoleId.
				bool bHasRole = WhitelistConfig.WhitelistCommandRoleId.IsEmpty();
				const TSharedPtr<FJsonObject>* MemberObjPtr = nullptr;
				if (DataObj->TryGetObjectField(TEXT("member"), MemberObjPtr) && MemberObjPtr)
				{
					// Guild owner always allowed
					{
						const TSharedPtr<FJsonObject>* UserPtr = nullptr;
						if ((*MemberObjPtr)->TryGetObjectField(TEXT("user"), UserPtr) && UserPtr)
						{
							FString ClickerId;
							(*UserPtr)->TryGetStringField(TEXT("id"), ClickerId);
							if (!GuildOwnerId.IsEmpty() && ClickerId == GuildOwnerId)
								bHasRole = true;
						}
					}
					if (!bHasRole && !WhitelistConfig.WhitelistCommandRoleId.IsEmpty())
					{
						const TArray<TSharedPtr<FJsonValue>>* RolesArr = nullptr;
						if ((*MemberObjPtr)->TryGetArrayField(TEXT("roles"), RolesArr) && RolesArr)
						{
							for (const TSharedPtr<FJsonValue>& RoleVal : *RolesArr)
							{
								FString RId;
								if (RoleVal->TryGetString(RId) && RId == WhitelistConfig.WhitelistCommandRoleId)
								{
									bHasRole = true;
									break;
								}
							}
						}
					}
				}

				if (!bHasRole)
				{
					RespondToInteraction(InteractionId, InteractionToken, 4,
						TEXT(":no_entry: You do not have permission to approve or deny whitelist applications."),
						/*bEphemeral=*/true);
				}
				else if (bApprove)
				{
					const FString* PendingNamePtr = PendingWhitelistApps.Find(TargetDiscordId);
					if (PendingNamePtr && !PendingNamePtr->IsEmpty())
					{
						const FString PlayerNameCopy = *PendingNamePtr;
						PendingWhitelistApps.Remove(TargetDiscordId);
						PendingWhitelistAppExpiry.Remove(TargetDiscordId);

						if (FWhitelistManager::AddPlayer(PlayerNameCopy, TEXT(""), TEXT("[Discord Approval]")))
						{
							RespondToInteraction(InteractionId, InteractionToken, 4,
								FString::Printf(
									TEXT(":white_check_mark: **%s** has been approved and added to the whitelist."),
									*PlayerNameCopy),
								/*bEphemeral=*/false);
							PostWhitelistEvent(
								FString::Printf(TEXT("**%s** approved via application"), *PlayerNameCopy),
								PlayerNameCopy, TEXT("[Discord Approval]"), 3066993);

							if (!WhitelistConfig.WhitelistApprovedDmMessage.IsEmpty())
							{
								const FString DmMsg = WhitelistConfig.WhitelistApprovedDmMessage
									.Replace(TEXT("%PlayerName%"), *PlayerNameCopy);
								SendDiscordDM(TargetDiscordId, DmMsg);
							}
						}
						else
						{
							RespondToInteraction(InteractionId, InteractionToken, 4,
								FString::Printf(
									TEXT(":yellow_circle: **%s** is already on the whitelist."),
									*PlayerNameCopy),
								/*bEphemeral=*/false);
						}
					}
					else
					{
						RespondToInteraction(InteractionId, InteractionToken, 4,
							TEXT(":warning: This application is no longer pending (already processed or expired)."),
							/*bEphemeral=*/true);
					}
				}
				else // wl_deny
				{
					const FString* PendingNamePtr = PendingWhitelistApps.Find(TargetDiscordId);
					if (PendingNamePtr && !PendingNamePtr->IsEmpty())
					{
						const FString PlayerNameCopy = *PendingNamePtr;
						PendingWhitelistApps.Remove(TargetDiscordId);
						PendingWhitelistAppExpiry.Remove(TargetDiscordId);
						RespondToInteraction(InteractionId, InteractionToken, 4,
							FString::Printf(
								TEXT(":red_circle: Whitelist application for **%s** has been denied."),
								*PlayerNameCopy),
							/*bEphemeral=*/false);
					}
					else
					{
						RespondToInteraction(InteractionId, InteractionToken, 4,
							TEXT(":warning: This application is no longer pending (already processed or expired)."),
							/*bEphemeral=*/true);
					}
				}
				// Don't broadcast — handled internally.
				return;
			}
		}

		// Fire the native delegate so extension modules can handle button clicks
		// and modal submits without modifying DiscordBridge directly.
		if (OnDiscordInteractionReceived.IsBound())
		{
			OnDiscordInteractionReceived.Broadcast(DataObj);
		}
	}
	else if (EventType == TEXT("GUILD_MEMBER_ADD") ||
	         EventType == TEXT("GUILD_MEMBER_UPDATE"))
	{
		// Keep the Discord role member cache up to date so the whitelist
		// check in OnPostLogin stays accurate without a full re-fetch.
		if (!WhitelistConfig.WhitelistRoleId.IsEmpty())
		{
			UpdateWhitelistRoleMemberEntry(DataObj);
		}

		// Auto-sync whitelist with Discord role
		if (WhitelistConfig.bSyncWhitelistWithRole && !WhitelistConfig.WhitelistRoleId.IsEmpty())
		{
			const TSharedPtr<FJsonObject>* UserPtr = nullptr;
			if (DataObj->TryGetObjectField(TEXT("user"), UserPtr) && UserPtr)
			{
				FString SyncUserId;
				FString SyncUsername;
				(*UserPtr)->TryGetStringField(TEXT("id"), SyncUserId);
				if (!(*UserPtr)->TryGetStringField(TEXT("global_name"), SyncUsername) || SyncUsername.IsEmpty())
					(*UserPtr)->TryGetStringField(TEXT("username"), SyncUsername);

				const TArray<TSharedPtr<FJsonValue>>* RolesArr = nullptr;
				bool bHasRole = false;
				if (DataObj->TryGetArrayField(TEXT("roles"), RolesArr) && RolesArr)
				{
					for (const TSharedPtr<FJsonValue>& RV : *RolesArr)
					{
						FString RId;
						if (RV->TryGetString(RId) && RId == WhitelistConfig.WhitelistRoleId)
						{
							bHasRole = true;
							break;
						}
					}
				}

				if (EventType == TEXT("GUILD_MEMBER_UPDATE"))
				{
				if (bHasRole && !SyncUsername.IsEmpty())
				{
					if (FWhitelistManager::AddPlayer(SyncUsername, TEXT(""), TEXT("sync-role")))
					{
						PostWhitelistEvent(
							FString::Printf(TEXT("**%s** added via Discord role sync (role assigned)"), *SyncUsername),
							SyncUsername, TEXT("sync-role"), 3066993);
					}
				}
				else if (!bHasRole && !SyncUsername.IsEmpty())
				{
					FWhitelistManager::RemovePlayer(SyncUsername, TEXT(""), TEXT("sync-remove"));
				}
				}
				else // GUILD_MEMBER_ADD
				{
				// A new member who already holds the whitelist role when they join
				// must be auto-added immediately.  Role removal cannot happen via
				// a join event, so only the add path is executed here.
				if (bHasRole && !SyncUsername.IsEmpty())
				{
					if (FWhitelistManager::AddPlayer(SyncUsername, TEXT(""), TEXT("sync-role")))
					{
						PostWhitelistEvent(
							FString::Printf(TEXT("**%s** added via Discord role sync (joined with role)"), *SyncUsername),
							SyncUsername, TEXT("sync-role"), 3066993);
					}
				}
				}
			}
		}
	}
	else if (EventType == TEXT("GUILD_MEMBER_REMOVE"))
	{
		// Member left the guild – remove from cache unconditionally.
		if (!WhitelistConfig.WhitelistRoleId.IsEmpty())
		{
			UpdateWhitelistRoleMemberEntry(DataObj, /*bRemoved=*/true);
		}
	}
	// Other events are received but not processed by this bridge.
}

void UDiscordBridgeSubsystem::HandleHeartbeatAck()
{
	UE_LOG(LogDiscordBridge, VeryVerbose, TEXT("DiscordBridge: Heartbeat acknowledged."));
	bPendingHeartbeatAck = false;
}

void UDiscordBridgeSubsystem::HandleReconnect()
{
	UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Server requested reconnect."));

	// Reset per-connection Gateway state but KEEP SessionId and ResumeGatewayUrl
	// so HandleHello can attempt op=6 Resume instead of a full Identify.
	FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
	HeartbeatTickerHandle.Reset();
	// Cancel any deferred re-identify timer from a prior op=9 to prevent a
	// stale Identify firing on the freshly reconnected (and already
	// authenticating) session, which would result in Discord close 4005.
	FTSTicker::GetCoreTicker().RemoveTicker(PendingReidentifyHandle);
	PendingReidentifyHandle.Reset();
	bPendingHeartbeatAck = false;
	bGatewayReady        = false;
	// BotUserId intentionally NOT cleared: the bot identity is stable across
	// reconnects.  Discord only sends READY (which sets BotUserId) on a fresh
	// Identify, not after a RESUMED.  Clearing it here causes self-message
	// echo, dropped interaction responses, and wrong vote counts if Resume
	// succeeds.  GuildId/GuildOwnerId are refilled by the post-resume
	// GUILD_CREATE events that Discord always sends.
	GuildId.Empty();
	GuildOwnerId.Empty();

	// Restart the WebSocket connection by calling Connect() on the existing
	// client.  Do NOT call Close() here: Close() → EnqueueClose() sets
	// bUserInitiatedClose = true inside FSMLWebSocketRunnable, which exits
	// the reconnect loop permanently and leaves the bot offline.
	// Connect() stops the current thread and starts a fresh runnable with
	// auto-reconnect still enabled.
	// Per Discord spec, reconnect to resume_gateway_url when available.
	if (WebSocketClient)
	{
		const FString ConnectUrl = ResumeGatewayUrl.IsEmpty()
			? DiscordGatewayUrl
			: (ResumeGatewayUrl + TEXT("/?v=10&encoding=json"));
		WebSocketClient->Connect(ConnectUrl, {}, {});
	}
}

void UDiscordBridgeSubsystem::HandleInvalidSession(bool bResumable)
{
	UE_LOG(LogDiscordBridge, Warning,
	       TEXT("DiscordBridge: Invalid session (resumable=%s)."),
	       bResumable ? TEXT("true") : TEXT("false"));

	// Cancel the heartbeat immediately so no further heartbeats are sent on
	// the now-invalid session.  HandleHello will restart it once a new READY
	// is received after re-identifying.
	FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
	HeartbeatTickerHandle.Reset();
	bPendingHeartbeatAck = false;

	// Cancel any previously scheduled re-identify/resume to avoid queuing
	// multiple deferred callbacks if op=9 is received more than once before
	// the deferred action fires.
	FTSTicker::GetCoreTicker().RemoveTicker(PendingReidentifyHandle);
	PendingReidentifyHandle.Reset();

	// Clear all per-session gateway state so stale IDs are never used.
	// BotUserId intentionally NOT cleared: the bot identity is stable across
	// reconnects.  Discord only sends READY (which sets BotUserId) on a fresh
	// Identify, not after a RESUMED.  See HandleReconnect() for details.
	bGatewayReady      = false;
	GuildId.Empty();
	GuildOwnerId.Empty();

	if (bResumable && !SessionId.IsEmpty())
	{
		// Session can be resumed — schedule a Resume attempt in 2 seconds.
		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: Scheduling Resume attempt for session %s in 2s."),
		       *SessionId);
		PendingReidentifyHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateWeakLambda(this, [this](float) -> bool
			{
				PendingReidentifyHandle.Reset();
				SendResume();
				return false; // one-shot – do not repeat
			}),
			2.0f);
	}
	else
	{
		// Session is not resumable — clear session state and do a fresh Identify.
		// Per Discord spec, wait 1–5 seconds before re-identifying.
		SessionId.Empty();
		ResumeGatewayUrl.Empty();
		LastSequenceNumber = -1;

		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: Session expired — scheduling fresh Identify in 2s."));
		PendingReidentifyHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateWeakLambda(this, [this](float) -> bool
			{
				PendingReidentifyHandle.Reset();
				SendIdentify();
				return false; // one-shot – do not repeat
			}),
			2.0f);
	}
}

void UDiscordBridgeSubsystem::HandleReady(const TSharedPtr<FJsonObject>& DataObj)
{
	// Extract the bot user ID so we can filter out self-sent messages.
	const TSharedPtr<FJsonObject>* UserPtr = nullptr;
	if (DataObj->TryGetObjectField(TEXT("user"), UserPtr) && UserPtr)
	{
		(*UserPtr)->TryGetStringField(TEXT("id"), BotUserId);
	}

	// Capture the session ID and resume gateway URL.  These are required to
	// resume the session after a disconnect instead of doing a full re-identify.
	DataObj->TryGetStringField(TEXT("session_id"), SessionId);
	DataObj->TryGetStringField(TEXT("resume_gateway_url"), ResumeGatewayUrl);

	// Extract the guild (server) ID from the first entry in the guilds array.
	// This is needed for Discord REST role-management API calls.
	const TArray<TSharedPtr<FJsonValue>>* GuildsArray = nullptr;
	if (DataObj->TryGetArrayField(TEXT("guilds"), GuildsArray) && GuildsArray && GuildsArray->Num() > 0)
	{
		const TSharedPtr<FJsonObject>* FirstGuild = nullptr;
		if ((*GuildsArray)[0]->TryGetObject(FirstGuild) && FirstGuild)
		{
			(*FirstGuild)->TryGetStringField(TEXT("id"), GuildId);
		}
	}

	bGatewayReady = true;

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Gateway ready. Bot user ID: %s, Guild ID: %s"),
	       *BotUserId, *GuildId);

	// Register slash commands if configured.
	if (Config.bEnableSlashCommands && !GuildId.IsEmpty() && !Config.BotToken.IsEmpty())
	{
		RegisterSlashCommands();
	}

	// Set bot presence. When the player-count feature is enabled, send the first
	// update immediately and start the periodic refresh ticker.  Otherwise just
	// set the bot to "online" with no activity.
	FTSTicker::GetCoreTicker().RemoveTicker(PlayerCountTickerHandle);
	PlayerCountTickerHandle.Reset();

	if (Config.bShowPlayerCountInPresence)
	{
		UpdatePlayerCountPresence();

		const float Interval = FMath::Max(Config.PlayerCountUpdateIntervalSeconds, 15.0f);
		PlayerCountTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime) -> bool
			{
				return PlayerCountTick(DeltaTime);
			}),
			Interval);
	}
	else
	{
		SendUpdatePresence(TEXT("online"));
	}

	// Post the server-online notification message the first time only.
	// Discord periodically forces bots to reconnect, which triggers a fresh
	// READY event even though the game server never went offline.  Guard with
	// bServerOnlineMessageSent so we don't spam the channel every ~hour.
	if (!Config.ServerOnlineMessage.IsEmpty() && !bServerOnlineMessageSent)
	{
		SendStatusMessageToDiscord(Config.ServerOnlineMessage);
		bServerOnlineMessageSent = true;
	}

	// Post the bot feature/command reference to the dedicated info channel the
	// first time the bot connects after a true server restart.  Subsequent
	// Gateway reconnects (which re-fire READY) are suppressed by bBotInfoPosted.
	if (!bBotInfoPosted)
	{
		const FString& InfoTarget = Config.BotInfoChannelId.IsEmpty()
			? FString()
			: Config.BotInfoChannelId;
		if (!InfoTarget.IsEmpty())
		{
			HandleBotInfoCommand(InfoTarget);
			bBotInfoPosted = true;
		}
	}

	// Populate the Discord role member cache so that players who hold
	// WhitelistRoleId are not kicked by the game-server whitelist even when
	// they are not listed in ServerWhitelist.json.
	if (!WhitelistConfig.WhitelistRoleId.IsEmpty())
	{
		FetchWhitelistRoleMembers();
	}

	OnDiscordConnected.Broadcast();
}

void UDiscordBridgeSubsystem::HandleResumed()
{
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Session resumed successfully. Missed events replayed by Discord."));

	bGatewayReady = true;

	// Restart the player count presence ticker that was stopped on reconnect.
	FTSTicker::GetCoreTicker().RemoveTicker(PlayerCountTickerHandle);
	PlayerCountTickerHandle.Reset();

	if (Config.bShowPlayerCountInPresence)
	{
		UpdatePlayerCountPresence();

		const float Interval = FMath::Max(Config.PlayerCountUpdateIntervalSeconds, 15.0f);
		PlayerCountTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime) -> bool
			{
				return PlayerCountTick(DeltaTime);
			}),
			Interval);
	}
	else
	{
		SendUpdatePresence(TEXT("online"));
	}

	OnDiscordConnected.Broadcast();
}

void UDiscordBridgeSubsystem::HandleMessageCreate(const TSharedPtr<FJsonObject>& DataObj)
{
	// Forward the full message JSON to any external subscribers (e.g. TicketSystem).
	// This is done before channel filtering so subscribers can process messages
	// from any channel (e.g. the !ticket-panel command from an admin channel).
	if (OnDiscordRawMessageReceived.IsBound())
	{
		OnDiscordRawMessageReceived.Broadcast(DataObj);
	}

	// Accept messages from the main channel OR the dedicated whitelist channel.
	FString MsgChannelId;
	if (!DataObj->TryGetStringField(TEXT("channel_id"), MsgChannelId))
	{
		return;
	}

	const bool bIsMainChannel      = (MsgChannelId == Config.ChannelId);
	const bool bIsWhitelistChannel = (!WhitelistConfig.WhitelistChannelId.IsEmpty() &&
	                                  MsgChannelId == WhitelistConfig.WhitelistChannelId);

	if (!bIsMainChannel && !bIsWhitelistChannel)
	{
		return;
	}

	// Extract the author object.
	const TSharedPtr<FJsonObject>* AuthorPtr = nullptr;
	if (!DataObj->TryGetObjectField(TEXT("author"), AuthorPtr) || !AuthorPtr)
	{
		return;
	}
	const TSharedPtr<FJsonObject>& Author = *AuthorPtr;

	// Optionally ignore bot messages (including our own) to prevent echo loops.
	if (Config.bIgnoreBotMessages)
	{
		bool bIsBot = false;
		Author->TryGetBoolField(TEXT("bot"), bIsBot);
		if (bIsBot)
		{
			return;
		}
	}
	// Always ignore this bot's own messages regardless of the config flag.
	FString AuthorId;
	Author->TryGetStringField(TEXT("id"), AuthorId);
	if (!BotUserId.IsEmpty() && AuthorId == BotUserId)
	{
		return;
	}

	// Display name priority: server nickname > global display name > username.
	// The member object is included in MESSAGE_CREATE events for guild messages
	// when the GUILD_MEMBERS intent is enabled.
	FString Username;
	const TSharedPtr<FJsonObject>* MemberPtr = nullptr;
	if (DataObj->TryGetObjectField(TEXT("member"), MemberPtr) && MemberPtr)
	{
		(*MemberPtr)->TryGetStringField(TEXT("nick"), Username);
	}
	if (Username.IsEmpty())
	{
		if (!Author->TryGetStringField(TEXT("global_name"), Username) || Username.IsEmpty())
		{
			Author->TryGetStringField(TEXT("username"), Username);
		}
	}
	// Final safety fallback: every Discord user has a username, but guard against
	// unexpected API responses that omit all name fields.
	if (Username.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: Could not extract display name from Discord message author; using 'Discord User'."));
		Username = TEXT("Discord User");
	}

	// For the dedicated whitelist channel: only relay to game when the sender
	// holds the configured whitelist role (if WhitelistRoleId is set).
	if (bIsWhitelistChannel && !WhitelistConfig.WhitelistRoleId.IsEmpty())
	{
		bool bHasRole = false;
		if (MemberPtr)
		{
			const TArray<TSharedPtr<FJsonValue>>* Roles = nullptr;
			if ((*MemberPtr)->TryGetArrayField(TEXT("roles"), Roles) && Roles)
			{
				for (const TSharedPtr<FJsonValue>& RoleVal : *Roles)
				{
					FString RoleId;
					if (RoleVal->TryGetString(RoleId) && RoleId == WhitelistConfig.WhitelistRoleId)
					{
						bHasRole = true;
						break;
					}
				}
			}
		}
		if (!bHasRole)
		{
			UE_LOG(LogDiscordBridge, Log,
			       TEXT("DiscordBridge: Ignoring whitelist-channel message from '%s' – sender lacks whitelist role."),
			       *Username);
			return;
		}
	}

	FString Content;
	DataObj->TryGetStringField(TEXT("content"), Content);
	Content = Content.TrimStartAndEnd();

	if (Content.IsEmpty())
	{
		return; // Embeds-only, sticker-only, or whitespace-only messages; skip.
	}

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Discord message received from '%s' (channel %s): %s"),
	       *Username, *MsgChannelId, *Content);

	// Helper: returns true if the Discord member holds the given required role
	// OR is the guild owner (who always has permission regardless of role config).
	// When RequiredRoleId is empty and the sender is not the guild owner the
	// command is disabled entirely — nobody can run it until a role ID is configured.
	auto HasRequiredRole = [&](const FString& RequiredRoleId) -> bool
	{
		// Guild owner always has permission, even without a role configured.
		if (!GuildOwnerId.IsEmpty() && AuthorId == GuildOwnerId)
		{
			return true;
		}
		if (RequiredRoleId.IsEmpty())
		{
			return false; // No role configured – command is disabled.
		}
		if (!MemberPtr)
		{
			return false;
		}
		const TArray<TSharedPtr<FJsonValue>>* Roles = nullptr;
		if ((*MemberPtr)->TryGetArrayField(TEXT("roles"), Roles) && Roles)
		{
			for (const TSharedPtr<FJsonValue>& RoleVal : *Roles)
			{
				FString RoleId;
				if (RoleVal->TryGetString(RoleId) && RoleId == RequiredRoleId)
				{
					return true;
				}
			}
		}
		return false;
	};

	// ── Resolve %Role% label for the DiscordToGameFormat placeholder ──────────
	// Iterate DiscordRoleLabels in config order; use the first matching entry.
	CurrentMessageRoleLabel.Empty();
	if (!Config.DiscordRoleLabels.IsEmpty() && MemberPtr)
	{
		TArray<FString> SenderRoleIds;
		const TArray<TSharedPtr<FJsonValue>>* RoleVals = nullptr;
		if ((*MemberPtr)->TryGetArrayField(TEXT("roles"), RoleVals) && RoleVals)
		{
			for (const TSharedPtr<FJsonValue>& RV : *RoleVals)
			{
				FString RId;
				if (RV->TryGetString(RId))
					SenderRoleIds.Add(RId);
			}
		}

		for (const FString& Entry : Config.DiscordRoleLabels)
		{
			FString EntryRoleId, EntryLabel;
			if (Entry.Split(TEXT("="), &EntryRoleId, &EntryLabel) &&
			    SenderRoleIds.Contains(EntryRoleId.TrimStartAndEnd()))
			{
				CurrentMessageRoleLabel = EntryLabel.TrimStartAndEnd();
				break;
			}
		}
	}

	OnDiscordMessageReceived.Broadcast(Username, Content);
	CurrentMessageRoleLabel.Empty();
}

void UDiscordBridgeSubsystem::SendResume()
{
	if (SessionId.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: SendResume called with empty SessionId — falling back to Identify."));
		SendIdentify();
		return;
	}

	TSharedPtr<FJsonObject> Data = MakeShared<FJsonObject>();
	Data->SetStringField(TEXT("token"),      Config.BotToken);
	Data->SetStringField(TEXT("session_id"), SessionId);
	Data->SetNumberField(TEXT("seq"),        LastSequenceNumber);

	TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
	Payload->SetNumberField(TEXT("op"), 6); // op=6 RESUME
	Payload->SetObjectField(TEXT("d"),  Data);

	SendGatewayPayload(Payload);

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Resume sent (session_id=%s, seq=%d)."),
	       *SessionId, LastSequenceNumber);
}

void UDiscordBridgeSubsystem::SendIdentify()
{
	// Build the connection properties object.
	// The "os" property is informational; Discord uses it to identify the client
	// platform.  Use the actual compile-time platform so it is accurate for both
	// the Windows and Linux dedicated-server Alpakit targets.
#if PLATFORM_WINDOWS
	static const FString DiscordOs = TEXT("windows");
#elif PLATFORM_LINUX
	static const FString DiscordOs = TEXT("linux");
#else
	static const FString DiscordOs = TEXT("unknown");
#endif
	TSharedPtr<FJsonObject> Props = MakeShared<FJsonObject>();
	Props->SetStringField(TEXT("os"),      DiscordOs);
	Props->SetStringField(TEXT("browser"), TEXT("satisfactory_discord_bridge"));
	Props->SetStringField(TEXT("device"),  TEXT("satisfactory_discord_bridge"));

	// Set the initial presence so the bot appears online immediately upon
	// authentication, before a separate UpdatePresence op is sent.
	TSharedPtr<FJsonObject> InitialPresence = MakeShared<FJsonObject>();
	InitialPresence->SetField(TEXT("since"), MakeShared<FJsonValueNull>());
	InitialPresence->SetArrayField(TEXT("activities"), TArray<TSharedPtr<FJsonValue>>());
	InitialPresence->SetStringField(TEXT("status"), TEXT("online"));
	InitialPresence->SetBoolField(TEXT("afk"), false);

	// Build the Identify data object.
	TSharedPtr<FJsonObject> Data = MakeShared<FJsonObject>();
	Data->SetStringField(TEXT("token"),   Config.BotToken);
	Data->SetNumberField(TEXT("intents"), EDiscordGatewayIntent::All);
	Data->SetObjectField(TEXT("properties"), Props);
	Data->SetObjectField(TEXT("presence"), InitialPresence);

	// Wrap in the Gateway payload envelope.
	TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
	Payload->SetNumberField(TEXT("op"), EDiscordGatewayOpcode::Identify);
	Payload->SetObjectField(TEXT("d"),  Data);

	SendGatewayPayload(Payload);

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Identify sent (intents=%d)."),
	       EDiscordGatewayIntent::All);
}

void UDiscordBridgeSubsystem::SendHeartbeat()
{
	// Zombie-connection detection (per Discord Gateway documentation):
	// If the previous heartbeat was never acknowledged, the connection is a
	// zombie – packets are being sent locally but not reaching Discord.
	// Discord has already marked the bot offline.  Force a fresh connection
	// by calling Connect() so USMLWebSocketClient's auto-reconnect remains enabled.
	if (bPendingHeartbeatAck)
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: Heartbeat not acknowledged – zombie connection detected. "
		            "Reconnecting."));

		// Cancel the heartbeat ticker before reconnecting so no further heartbeats
		// are sent on the dead socket.  HandleHello will restart it on the new connection.
		FTSTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
		HeartbeatTickerHandle.Reset();
		bPendingHeartbeatAck = false;

		// Reset Gateway state but keep SessionId/ResumeGatewayUrl so HandleHello
		// can attempt a Resume instead of a full Identify.
		// BotUserId intentionally NOT cleared: see HandleReconnect() for details.
		bGatewayReady = false;
		GuildId.Empty();
		GuildOwnerId.Empty();

		if (WebSocketClient)
		{
			// Use Connect() instead of Close() to force a fresh connection.
			// Close() → EnqueueClose() sets bUserInitiatedClose = true inside
			// FSMLWebSocketRunnable, which exits the reconnect loop permanently
			// and leaves the bot offline.  Connect() stops the current thread
			// and starts a new runnable with auto-reconnect still enabled.
			const FString ConnectUrl = ResumeGatewayUrl.IsEmpty()
				? DiscordGatewayUrl
				: (ResumeGatewayUrl + TEXT("/?v=10&encoding=json"));
			WebSocketClient->Connect(ConnectUrl, {}, {});
		}
		return;
	}

	TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
	Payload->SetNumberField(TEXT("op"), EDiscordGatewayOpcode::Heartbeat);

	// The heartbeat data field must be the last received sequence number, or
	// a JSON null if no dispatch has been received yet.
	if (LastSequenceNumber >= 0)
	{
		Payload->SetNumberField(TEXT("d"), LastSequenceNumber);
	}
	else
	{
		Payload->SetField(TEXT("d"), MakeShared<FJsonValueNull>());
	}

	SendGatewayPayload(Payload);
	bPendingHeartbeatAck = true;
}

void UDiscordBridgeSubsystem::SendUpdatePresence(const FString& Status)
{
	// Build the presence data object (Discord Gateway op=3).
	TSharedPtr<FJsonObject> Data = MakeShared<FJsonObject>();
	Data->SetField(TEXT("since"),      MakeShared<FJsonValueNull>());
	Data->SetArrayField(TEXT("activities"), TArray<TSharedPtr<FJsonValue>>());
	Data->SetStringField(TEXT("status"), Status);
	Data->SetBoolField(TEXT("afk"),    false);

	TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
	Payload->SetNumberField(TEXT("op"), EDiscordGatewayOpcode::UpdatePresence);
	Payload->SetObjectField(TEXT("d"),  Data);

	SendGatewayPayload(Payload);

	UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Presence updated to '%s'."), *Status);
}

void UDiscordBridgeSubsystem::SendStatusMessageToDiscord(const FString& Message)
{
	if (!Config.bServerStatusMessagesEnabled)
	{
		return;
	}

	// Use the dedicated status channel when configured; fall back to the main channel.
	const FString& TargetChannelId = Config.StatusChannelId.IsEmpty()
		? Config.ChannelId
		: Config.StatusChannelId;
	SendMessageToChannel(TargetChannelId, Message);
}

void UDiscordBridgeSubsystem::SendMessageToChannel(const FString& TargetChannelId,
                                                    const FString& Message)
{
	if (Config.BotToken.IsEmpty() || TargetChannelId.IsEmpty())
	{
		return;
	}

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("content"), Message);

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in SendMessageToChannel."));
		return;
	}

	const FString Url = FString::Printf(
		TEXT("%s/channels/%s/messages"), *DiscordApiBase, *TargetChannelId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);

	Request->OnProcessRequestComplete().BindWeakLambda(
		this,
		[Message](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid())
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: HTTP request failed for status message '%s'."),
				       *Message);
				return;
			}
			if (Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: Discord REST API returned %d: %s"),
				       Resp->GetResponseCode(), *Resp->GetContentAsString());
			}
		});

	Request->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
// Extension API – getters and REST helpers used by external modules
// ─────────────────────────────────────────────────────────────────────────────

const FString& UDiscordBridgeSubsystem::GetBotToken() const
{
	return Config.BotToken;
}

const FString& UDiscordBridgeSubsystem::GetGuildId() const
{
	return GuildId;
}

const FString& UDiscordBridgeSubsystem::GetGuildOwnerId() const
{
	return GuildOwnerId;
}

void UDiscordBridgeSubsystem::SendDiscordChannelMessage(const FString& TargetChannelId,
                                                        const FString& Message)
{
	SendMessageToChannel(TargetChannelId, Message);
}

void UDiscordBridgeSubsystem::RespondToInteraction(const FString& InteractionId,
                                                   const FString& InteractionToken,
                                                   int32 ResponseType,
                                                   const FString& Content,
                                                   bool bEphemeral)
{
	if (Config.BotToken.IsEmpty() || InteractionId.IsEmpty() || InteractionToken.IsEmpty())
	{
		return;
	}

	TSharedPtr<FJsonObject> ResponseData = MakeShared<FJsonObject>();
	if ((ResponseType == 4 || ResponseType == 5) && bEphemeral)
	{
		// Discord flags bitmask: 64 = EPHEMERAL.
		// For type 5 (DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE) the flag must be set
		// in the data object so that the eventual follow-up is also ephemeral.
		ResponseData->SetNumberField(TEXT("flags"), 64);
	}
	if (ResponseType == 4 && !Content.IsEmpty())
	{
		ResponseData->SetStringField(TEXT("content"), Content);
	}

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("type"), ResponseType);
	if (ResponseData->Values.Num() > 0)
	{
		Body->SetObjectField(TEXT("data"), ResponseData);
	}

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in RespondToInteraction."));
		return;
	}

	const FString Url = FString::Printf(
		TEXT("%s/interactions/%s/%s/callback"),
		*DiscordApiBase, *InteractionId, *InteractionToken);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);

	Request->OnProcessRequestComplete().BindLambda(
		[InteractionId](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid())
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: Interaction callback request failed (id=%s)."),
				       *InteractionId);
				return;
			}
			if (Resp->GetResponseCode() != 200 && Resp->GetResponseCode() != 204)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: Interaction callback returned HTTP %d: %s"),
				       Resp->GetResponseCode(), *Resp->GetContentAsString());
			}
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::FollowUpInteraction(const FString& InteractionToken,
                                                  const FString& Message,
                                                  bool bEphemeral)
{
	if (Config.BotToken.IsEmpty() || BotUserId.IsEmpty() || InteractionToken.IsEmpty())
		return;

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("content"), Message);
	if (bEphemeral)
		Body->SetNumberField(TEXT("flags"), 64);

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in FollowUpInteraction."));
		return;
	}

	// POST /webhooks/{application_id}/{token} — creates a follow-up message.
	const FString Url = FString::Printf(
		TEXT("%s/webhooks/%s/%s"),
		*DiscordApiBase, *BotUserId, *InteractionToken);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);
	Request->OnProcessRequestComplete().BindLambda(
		[](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid() ||
			    Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: FollowUpInteraction request failed (HTTP %d)."),
				       Resp.IsValid() ? Resp->GetResponseCode() : 0);
			}
		});
	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::RespondWithModal(const FString& InteractionId,
                                               const FString& InteractionToken,
                                               const FString& ModalCustomId,
                                               const FString& Title,
                                               const FString& Placeholder,
                                               const FString& ComponentCustomId)
{
	if (Config.BotToken.IsEmpty() || InteractionId.IsEmpty() || InteractionToken.IsEmpty())
	{
		return;
	}

	// Build the single paragraph text-input component.
	TSharedPtr<FJsonObject> TextInput = MakeShared<FJsonObject>();
	TextInput->SetNumberField(TEXT("type"),        4); // TEXT_INPUT
	TextInput->SetStringField(TEXT("custom_id"),   ComponentCustomId.IsEmpty() ? TEXT("ticket_reason") : ComponentCustomId);
	TextInput->SetNumberField(TEXT("style"),       2); // PARAGRAPH (multi-line)
	TextInput->SetStringField(TEXT("label"),       TEXT("Reason"));
	TextInput->SetStringField(TEXT("placeholder"), Placeholder);
	TextInput->SetBoolField  (TEXT("required"),    false);
	TextInput->SetNumberField(TEXT("max_length"),  1000);

	TSharedPtr<FJsonObject> ActionRow = MakeShared<FJsonObject>();
	ActionRow->SetNumberField(TEXT("type"), 1); // ACTION_ROW
	ActionRow->SetArrayField(TEXT("components"),
		TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(TextInput) });

	TSharedPtr<FJsonObject> ModalData = MakeShared<FJsonObject>();
	ModalData->SetStringField(TEXT("custom_id"),  ModalCustomId);
	ModalData->SetStringField(TEXT("title"),      Title);
	ModalData->SetArrayField (TEXT("components"),
		TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(ActionRow) });

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("type"), 9); // MODAL
	Body->SetObjectField(TEXT("data"), ModalData);

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in RespondWithModal."));
		return;
	}

	const FString Url = FString::Printf(
		TEXT("%s/interactions/%s/%s/callback"),
		*DiscordApiBase, *InteractionId, *InteractionToken);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);

	Request->OnProcessRequestComplete().BindLambda(
		[InteractionId](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid())
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: RespondWithModal request failed (id=%s)."),
				       *InteractionId);
				return;
			}
			if (Resp->GetResponseCode() != 200 && Resp->GetResponseCode() != 204)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: RespondWithModal returned HTTP %d: %s"),
				       Resp->GetResponseCode(), *Resp->GetContentAsString());
			}
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::SendMessageBodyToChannel(const FString& TargetChannelId,
                                                       const TSharedPtr<FJsonObject>& MessageBody)
{
	if (Config.BotToken.IsEmpty() || TargetChannelId.IsEmpty() || !MessageBody.IsValid())
	{
		return;
	}

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(MessageBody.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in SendMessageBodyToChannel."));
		return;
	}

	const FString Url = FString::Printf(
		TEXT("%s/channels/%s/messages"), *DiscordApiBase, *TargetChannelId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);

	Request->OnProcessRequestComplete().BindWeakLambda(
		this,
		[this, TargetChannelId, BodyString](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid() ||
			    Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: SendMessageBodyToChannel failed (channel=%s, HTTP=%d). Trying fallback."),
				       *TargetChannelId,
				       Resp.IsValid() ? Resp->GetResponseCode() : 0);

				// Fallback webhook: POST the same body to FallbackWebhookUrl when configured.
				if (!Config.FallbackWebhookUrl.IsEmpty())
				{
					TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FbReq =
						FHttpModule::Get().CreateRequest();
					FbReq->SetURL(Config.FallbackWebhookUrl);
					FbReq->SetVerb(TEXT("POST"));
					FbReq->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
					FbReq->SetContentAsString(BodyString);
					FbReq->ProcessRequest();
				}
			}
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::RespondToInteractionWithBody(const FString& InteractionId,
                                                           const FString& InteractionToken,
                                                           const TSharedPtr<FJsonObject>& MessageData,
                                                           bool bEphemeral)
{
	if (Config.BotToken.IsEmpty() || InteractionId.IsEmpty() || InteractionToken.IsEmpty())
		return;

	TSharedPtr<FJsonObject> DataObj = MessageData.IsValid()
		? MakeShared<FJsonObject>(*MessageData)
		: MakeShared<FJsonObject>();

	if (bEphemeral)
		DataObj->SetNumberField(TEXT("flags"), 64);

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("type"), 4); // CHANNEL_MESSAGE_WITH_SOURCE
	Body->SetObjectField(TEXT("data"), DataObj);

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in RespondToInteractionWithBody."));
		return;
	}

	const FString Url = FString::Printf(
		TEXT("%s/interactions/%s/%s/callback"),
		*DiscordApiBase, *InteractionId, *InteractionToken);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);

	Request->OnProcessRequestComplete().BindLambda(
		[InteractionId](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid() ||
			    (Resp->GetResponseCode() != 200 && Resp->GetResponseCode() != 204))
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: RespondToInteractionWithBody returned HTTP %d (id=%s)."),
				       Resp.IsValid() ? Resp->GetResponseCode() : 0, *InteractionId);
			}
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::RespondWithMultiFieldModal(const FString& InteractionId,
                                                         const FString& InteractionToken,
                                                         const FString& ModalCustomId,
                                                         const FString& Title,
                                                         const TArray<FModalField>& Fields)
{
	if (Config.BotToken.IsEmpty() || InteractionId.IsEmpty() || InteractionToken.IsEmpty()
		|| Fields.IsEmpty())
	{
		return;
	}

	// Each FModalField becomes one ACTION_ROW containing a single TEXT_INPUT.
	// Discord allows a maximum of 5 ACTION_ROWs per modal.
	TArray<TSharedPtr<FJsonValue>> Rows;
	for (const FModalField& F : Fields)
	{
		TSharedPtr<FJsonObject> TextInput = MakeShared<FJsonObject>();
		TextInput->SetNumberField(TEXT("type"),      4); // TEXT_INPUT
		TextInput->SetStringField(TEXT("custom_id"), F.CustomId);
		TextInput->SetNumberField(TEXT("style"),     F.bParagraph ? 2 : 1);
		TextInput->SetStringField(TEXT("label"),     F.Label);
		if (!F.Placeholder.IsEmpty())
			TextInput->SetStringField(TEXT("placeholder"), F.Placeholder);
		if (!F.DefaultValue.IsEmpty())
			TextInput->SetStringField(TEXT("value"), F.DefaultValue);
		TextInput->SetBoolField(TEXT("required"), F.bRequired);
		if (F.MinLength > 0)
			TextInput->SetNumberField(TEXT("min_length"), F.MinLength);
		TextInput->SetNumberField(TEXT("max_length"), F.MaxLength > 0 ? F.MaxLength : 200);

		TSharedPtr<FJsonObject> ActionRow = MakeShared<FJsonObject>();
		ActionRow->SetNumberField(TEXT("type"), 1); // ACTION_ROW
		ActionRow->SetArrayField(TEXT("components"),
			TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(TextInput) });

		Rows.Add(MakeShared<FJsonValueObject>(ActionRow));
	}

	TSharedPtr<FJsonObject> ModalData = MakeShared<FJsonObject>();
	ModalData->SetStringField(TEXT("custom_id"),  ModalCustomId);
	ModalData->SetStringField(TEXT("title"),      Title);
	ModalData->SetArrayField (TEXT("components"), Rows);

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("type"), 9); // MODAL
	Body->SetObjectField(TEXT("data"), ModalData);

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in RespondWithMultiFieldModal."));
		return;
	}

	const FString Url = FString::Printf(
		TEXT("%s/interactions/%s/%s/callback"),
		*DiscordApiBase, *InteractionId, *InteractionToken);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);

	Request->OnProcessRequestComplete().BindLambda(
		[InteractionId](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid() ||
			    (Resp->GetResponseCode() != 200 && Resp->GetResponseCode() != 204))
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: RespondWithMultiFieldModal returned HTTP %d (id=%s)."),
				       Resp.IsValid() ? Resp->GetResponseCode() : 0, *InteractionId);
			}
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::CreateDiscordThread(
	const FString& ChannelId,
	const FString& ThreadName,
	TFunction<void(const FString& ThreadId)> OnCreated)
{
	if (Config.BotToken.IsEmpty() || ChannelId.IsEmpty() || ThreadName.IsEmpty())
	{
		if (OnCreated) OnCreated(FString());
		return;
	}

	// Escape the thread name for safe embedding in a JSON string literal.
	const FString SafeName = JsonEscapeStr(ThreadName);

	const FString BodyStr = FString::Printf(
		TEXT("{\"name\":\"%s\",\"type\":11,\"auto_archive_duration\":10080}"),
		*SafeName);

	const FString Url = FString::Printf(
		TEXT("%s/channels/%s/threads"), *DiscordApiBase, *ChannelId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyStr);

	Request->OnProcessRequestComplete().BindLambda(
		[OnCreated, ChannelId, ThreadName](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			FString ThreadId;
			if (bConnected && Resp.IsValid() &&
			    Resp->GetResponseCode() >= 200 && Resp->GetResponseCode() < 300)
			{
				TSharedPtr<FJsonObject> ThreadObj;
				TSharedRef<TJsonReader<>> Reader =
					TJsonReaderFactory<>::Create(Resp->GetContentAsString());
				if (FJsonSerializer::Deserialize(Reader, ThreadObj) && ThreadObj.IsValid())
					ThreadObj->TryGetStringField(TEXT("id"), ThreadId);
			}
			else
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: CreateDiscordThread failed for '%s' in channel %s (HTTP %d)."),
				       *ThreadName, *ChannelId,
				       Resp.IsValid() ? Resp->GetResponseCode() : 0);
			}
			if (OnCreated) OnCreated(ThreadId);
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::DeleteDiscordChannel(const FString& ChannelId)
{
	if (Config.BotToken.IsEmpty() || ChannelId.IsEmpty())
	{
		return;
	}

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Deleting channel %s."), *ChannelId);

	const FString Url = FString::Printf(
		TEXT("%s/channels/%s"), *DiscordApiBase, *ChannelId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("DELETE"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));

	Request->OnProcessRequestComplete().BindLambda(
		[ChannelId](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid())
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: DeleteDiscordChannel request failed (channel=%s)."),
				       *ChannelId);
				return;
			}
			if (Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: DeleteDiscordChannel returned HTTP %d (channel=%s): %s"),
				       Resp->GetResponseCode(), *ChannelId, *Resp->GetContentAsString());
			}
			else
			{
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Channel %s deleted successfully."), *ChannelId);
			}
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::CreateDiscordGuildTextChannel(
	const FString& ChannelName,
	const FString& CategoryId,
	const TArray<TSharedPtr<FJsonValue>>& PermissionOverwrites,
	TFunction<void(const FString& NewChannelId)> OnCreated)
{
	if (Config.BotToken.IsEmpty() || GuildId.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: CreateDiscordGuildTextChannel – BotToken or GuildId empty."));
		if (OnCreated)
		{
			OnCreated(TEXT(""));
		}
		return;
	}

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("name"), ChannelName);
	Body->SetNumberField(TEXT("type"), 0); // GUILD_TEXT
	Body->SetArrayField(TEXT("permission_overwrites"), PermissionOverwrites);
	if (!CategoryId.IsEmpty())
	{
		Body->SetStringField(TEXT("parent_id"), CategoryId);
	}

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in CreateDiscordGuildTextChannel."));
		if (OnCreated)
			OnCreated(TEXT(""));
		return;
	}

	const FString Url = FString::Printf(
		TEXT("%s/guilds/%s/channels"), *DiscordApiBase, *GuildId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);

	Request->OnProcessRequestComplete().BindWeakLambda(
		this,
		[OnCreated = MoveTemp(OnCreated), ChannelName]
		(FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected) mutable
		{
			if (!bConnected || !Resp.IsValid() ||
			    (Resp->GetResponseCode() != 200 && Resp->GetResponseCode() != 201))
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: CreateDiscordGuildTextChannel failed for '%s'. HTTP %d."),
				       *ChannelName,
				       (Resp.IsValid() ? Resp->GetResponseCode() : 0));
				if (OnCreated)
				{
					OnCreated(TEXT(""));
				}
				return;
			}

			TSharedPtr<FJsonObject> ChannelObj;
			TSharedRef<TJsonReader<>> Reader =
				TJsonReaderFactory<>::Create(Resp->GetContentAsString());
			FString NewChannelId;
			if (FJsonSerializer::Deserialize(Reader, ChannelObj) && ChannelObj.IsValid())
			{
				ChannelObj->TryGetStringField(TEXT("id"), NewChannelId);
			}

			if (OnCreated)
			{
				OnCreated(NewChannelId);
			}
		});

	Request->ProcessRequest();
}

void UDiscordBridgeSubsystem::SendGatewayPayload(const TSharedPtr<FJsonObject>& Payload)
{
	if (!WebSocketClient || !WebSocketClient->IsConnected())
	{
		return;
	}

	// Guard: ToSharedRef() asserts-crashes when the pointer is null.
	if (!Payload.IsValid())
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: SendGatewayPayload called with null Payload — skipped."));
		return;
	}

	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	if (!FJsonSerializer::Serialize(Payload.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in SendGatewayPayload."));
		return;
	}

	WebSocketClient->SendText(JsonString);
}

// ─────────────────────────────────────────────────────────────────────────────
// Heartbeat timer
// ─────────────────────────────────────────────────────────────────────────────

bool UDiscordBridgeSubsystem::HeartbeatTick(float /*DeltaTime*/)
{
	SendHeartbeat();
	return true; // keep ticking
}

// ─────────────────────────────────────────────────────────────────────────────
// Player count presence
// ─────────────────────────────────────────────────────────────────────────────

bool UDiscordBridgeSubsystem::PlayerCountTick(float /*DeltaTime*/)
{
	UpdatePlayerCountPresence();
	return true; // keep ticking
}

void UDiscordBridgeSubsystem::UpdatePlayerCountPresence()
{
	if (!bGatewayReady || !Config.bShowPlayerCountInPresence)
	{
		return;
	}

	// Count connected players using the game state's player array.
	// PlayerArray may contain null entries for pending/disconnecting players,
	// so count only valid (non-null) APlayerState pointers.
	int32 PlayerCount = 0;
	if (UWorld* World = GetWorld())
	{
		if (AGameStateBase* GS = World->GetGameState<AGameStateBase>())
		{
			for (APlayerState* PS : GS->PlayerArray)
			{
				if (PS) ++PlayerCount;
			}
		}
	}

	// Apply configured format placeholders.
	FString ActivityText = Config.PlayerCountPresenceFormat;
	ActivityText = ActivityText.Replace(TEXT("%PlayerCount%"), *FString::FromInt(PlayerCount));
	ActivityText = ActivityText.Replace(TEXT("%ServerName%"),  *Config.ServerName);
	ActivityText = ActivityText.TrimStartAndEnd();

	// If the user left the format blank, fall back to just the player count number
	// so Discord never receives an empty activity name.
	if (ActivityText.IsEmpty())
	{
		ActivityText = FString::FromInt(PlayerCount);
	}

	// Build a Discord activity object using the configured activity type.
	// Common types: 0=Playing, 2=Listening to, 3=Watching, 5=Competing in.
	TSharedPtr<FJsonObject> Activity = MakeShared<FJsonObject>();
	Activity->SetNumberField(TEXT("type"), Config.PlayerCountActivityType);
	Activity->SetStringField(TEXT("name"), ActivityText);

	TArray<TSharedPtr<FJsonValue>> Activities;
	Activities.Add(MakeShared<FJsonValueObject>(Activity));

	// Build the presence update payload (op=3).
	TSharedPtr<FJsonObject> Data = MakeShared<FJsonObject>();
	Data->SetField(TEXT("since"),      MakeShared<FJsonValueNull>());
	Data->SetArrayField(TEXT("activities"), Activities);
	Data->SetStringField(TEXT("status"), TEXT("online"));
	Data->SetBoolField(TEXT("afk"),    false);

	TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
	Payload->SetNumberField(TEXT("op"), EDiscordGatewayOpcode::UpdatePresence);
	Payload->SetObjectField(TEXT("d"),  Data);

	SendGatewayPayload(Payload);

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Player count presence updated (%d players) – activity: \"%s\""),
	       PlayerCount, *ActivityText);
}

// ─────────────────────────────────────────────────────────────────────────────
// Chat manager binding (Game → Discord)
// ─────────────────────────────────────────────────────────────────────────────

bool UDiscordBridgeSubsystem::TryBindToChatManager()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	AFGChatManager* ChatMgr = AFGChatManager::Get(World);
	if (!ChatMgr)
	{
		return false;
	}

	ChatMgr->OnChatMessageAdded.AddDynamic(this, &UDiscordBridgeSubsystem::OnGameChatMessageAdded);
	BoundChatManager = ChatMgr;

	// Snapshot the current messages so we only forward NEW ones going forward.
	ChatMgr->GetReceivedChatMessages(LastKnownMessages);

	UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Bound to AFGChatManager::OnChatMessageAdded."));
	return true;
}

void UDiscordBridgeSubsystem::OnGameChatMessageAdded()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AFGChatManager* ChatMgr = AFGChatManager::Get(World);
	if (!ChatMgr)
	{
		return;
	}

	TArray<FChatMessageStruct> CurrentMessages;
	ChatMgr->GetReceivedChatMessages(CurrentMessages);

	// Identify messages present in CurrentMessages but absent from LastKnownMessages.
	// Equality is determined by (ServerTimeStamp, MessageSender, MessageText) so
	// that the diff is correct even when the rolling buffer wraps around.
	for (const FChatMessageStruct& Msg : CurrentMessages)
	{
		if (Msg.MessageType != EFGChatMessageType::CMT_PlayerMessage)
		{
			continue;
		}

		bool bAlreadySeen = false;
		for (const FChatMessageStruct& Known : LastKnownMessages)
		{
			if (Known.ServerTimeStamp == Msg.ServerTimeStamp &&
				Known.MessageSender.EqualTo(Msg.MessageSender) &&
				Known.MessageText.EqualTo(Msg.MessageText))
			{
				bAlreadySeen = true;
				break;
			}
		}

		if (!bAlreadySeen)
		{
			HandleIncomingChatMessage(
				Msg.MessageSender.ToString().TrimStartAndEnd(),
				Msg.MessageText.ToString().TrimStartAndEnd());
		}
	}

	LastKnownMessages = CurrentMessages;
}

// ─────────────────────────────────────────────────────────────────────────────
// Chat-manager hook handler (Game → Discord)
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleIncomingChatMessage(const FString& PlayerName,
                                                         const FString& MessageText)
{
	// Discord relay messages are broadcast as CMT_CustomMessage, which the diff
	// loop in OnGameChatMessageAdded ignores (it only processes CMT_PlayerMessage).
	// Therefore no explicit echo-prevention bookkeeping is required here.

	if (MessageText.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: Skipping player message with empty text from '%s'."),
		       *PlayerName);
		return;
	}

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Player message detected. Sender: '%s', Text: '%s'"),
	       *PlayerName, *MessageText);

	// Feature 1a: Chat relay find/replace — replace matched patterns with *** before forwarding.
	// Feature 1b: Chat relay blocklist — silently drop messages that contain a blocked keyword.
	FString FilteredMessage = MessageText;
	bool    bDropMessage    = false;

	if (Config.ChatRelayBlocklistReplacements.Num() > 0)
	{
		for (const FChatRelayReplacement& R : Config.ChatRelayBlocklistReplacements)
		{
			if (R.Pattern.IsEmpty()) continue;
			// Simple case-insensitive substring replace.
			FString Temp = FilteredMessage;
			FString Replaced;
			int32   SearchStart = 0;
			while (true)
			{
				const int32 Idx = Temp.Find(R.Pattern, ESearchCase::IgnoreCase, ESearchDir::FromStart, SearchStart);
				if (Idx == INDEX_NONE) break;
				Replaced    += Temp.Mid(SearchStart, Idx - SearchStart) + R.Replacement;
				SearchStart  = Idx + R.Pattern.Len();
			}
			if (SearchStart > 0)
			{
				Replaced       += Temp.Mid(SearchStart);
				FilteredMessage = Replaced;
			}
		}
	}

	if (!bDropMessage && Config.ChatRelayBlocklist.Num() > 0)
	{
		for (const FString& Keyword : Config.ChatRelayBlocklist)
		{
			if (!Keyword.IsEmpty() &&
			    FilteredMessage.Contains(Keyword, ESearchCase::IgnoreCase))
			{
				UE_LOG(LogDiscordBridge, Verbose,
				       TEXT("DiscordBridge: Chat message from '%s' blocked by ChatRelayBlocklist (keyword: '%s')."),
				       *PlayerName, *Keyword);
				bDropMessage = true;
				break;
			}
		}
	}

	if (bDropMessage) return;

	// Feature: suppress muted players' messages from the Discord relay.
	// A player who is muted in-game should not have their chat forwarded to Discord.
	{
		const UWorld* WMute = GetWorld();
		UGameInstance* GIMute = WMute ? WMute->GetGameInstance() : nullptr;
		UMuteRegistry* MuteReg = GIMute ? GIMute->GetSubsystem<UMuteRegistry>() : nullptr;
		if (MuteReg && WMute)
		{
			for (FConstPlayerControllerIterator It = WMute->GetPlayerControllerIterator(); It; ++It)
			{
				APlayerController* PC = It->Get();
				if (!PC || !PC->PlayerState) continue;
				if (!PC->PlayerState->GetPlayerName().Equals(PlayerName, ESearchCase::IgnoreCase)) continue;
				const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
				if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
				{
					const FString Uid = UBanDatabase::MakeUid(
						NetId.GetType().ToString().ToUpper(),
						NetId.ToString().ToLower());
					if (MuteReg->IsMuted(Uid))
					{
						UE_LOG(LogDiscordBridge, Verbose,
						       TEXT("DiscordBridge: Suppressing Discord relay for muted player '%s'."),
						       *PlayerName);
						return;
					}
				}
				break;
			}
		}
	}

	// Feature: auto-warn on repeated chat-filter hits.
	// When ChatFilterAutoWarnThreshold > 0, track how many times this player has
	// triggered the filter within ChatFilterAutoWarnWindowMinutes.  On threshold
	// breach, issue an automatic warning via UPlayerWarningRegistry.
	{
		const UBanSystemConfig* BanCfg = UBanSystemConfig::Get();
		if (BanCfg && BanCfg->ChatFilterAutoWarnThreshold > 0 && FilteredMessage != MessageText)
		{
			// Derive the sender's UID from the PlayerState.
			// We look up the active PlayerController by name as a best-effort.
			const UWorld* W = GetWorld();
			UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
			UPlayerWarningRegistry* WarnReg = GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;

			if (WarnReg)
			{
				const FDateTime Now       = FDateTime::UtcNow();
				const int32 EffectiveWindowMinutes = BanCfg->ChatFilterAutoWarnWindowMinutes > 0
					? BanCfg->ChatFilterAutoWarnWindowMinutes : 10;
				const FTimespan Window    = FTimespan::FromMinutes(EffectiveWindowMinutes);

				// Resolve UID and PlayerController for this player once, upfront.
				// Keying ChatFilterHits by UID (when available) prevents name-spoofing
				// and ensures a reconnecting player cannot reset their hit count by
				// rejoining with a slightly different display name.
				FString Uid;
				APlayerController* WarnTargetPC = nullptr;
				if (W)
				{
					for (FConstPlayerControllerIterator It = W->GetPlayerControllerIterator(); It; ++It)
					{
						APlayerController* PC = It->Get();
						if (!PC || !PC->PlayerState) continue;
						if (!PC->PlayerState->GetPlayerName().Equals(PlayerName, ESearchCase::IgnoreCase)) continue;

						const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
						if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
						{
							Uid = UBanDatabase::MakeUid(
								NetId.GetType().ToString().ToUpper(),
								NetId.ToString().ToLower());
						}
						WarnTargetPC = PC;
						break;
					}
				}

				// Use the UID as the map key when available; fall back to display
				// name for players whose network identity has not yet replicated.
				const FString FilterKey = Uid.IsEmpty() ? PlayerName : Uid;

				// Update the hit-count tracker.
				FFilterHitRecord& Rec = ChatFilterHits.FindOrAdd(FilterKey);
				Rec.HitTimestamps.Add(Now);
				// Prune timestamps outside the window.
				Rec.HitTimestamps.RemoveAll([&Now, &Window](const FDateTime& T){ return (Now - T) > Window; });

				const int32 HitCount = Rec.HitTimestamps.Num();
				UE_LOG(LogDiscordBridge, Verbose,
					TEXT("DiscordBridge: ChatFilter hit by '%s' — %d in window (threshold=%d)"),
					*PlayerName, HitCount, BanCfg->ChatFilterAutoWarnThreshold);

				if (HitCount >= BanCfg->ChatFilterAutoWarnThreshold)
				{
					// Reset so they can be warned again after another full window of hits.
					Rec.HitTimestamps.Empty();

					if (!Uid.IsEmpty())
					{
						const FString WarnReason = FString::Printf(
							TEXT("Auto-warn: triggered chat filter %d times within %d minutes"),
							HitCount, EffectiveWindowMinutes);

						FWarningEntry WarnEntry;
						WarnEntry.Uid        = Uid;
						WarnEntry.PlayerName = PlayerName;
						WarnEntry.Reason     = WarnReason;
						WarnEntry.WarnedBy   = TEXT("auto");
						WarnEntry.Points     = 1;

						WarnReg->AddWarning(WarnEntry);
						const int32 AutoWarnCount  = WarnReg->GetWarningCount(Uid);
						const int32 AutoWarnPoints = WarnReg->GetWarningPoints(Uid);
						FBanDiscordNotifier::NotifyWarningIssued(Uid, PlayerName, WarnReason, TEXT("auto"), AutoWarnCount);

						// Write to audit log so auto-warns appear alongside all other warn sources.
						if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
							AuditLog->LogAction(TEXT("warn"), Uid, PlayerName,
							                    TEXT("auto"), TEXT("auto"), WarnReason);

						// Auto-ban escalation — mirrors HandleWarnCommand, BanRestApi, and BanChatCommands.
						{
							const UBanSystemConfig* SysCfg = UBanSystemConfig::Get();
							if (SysCfg)
							{
								int32 BanDurationMinutes = -1;
								if (SysCfg->WarnEscalationTiers.Num() > 0)
								{
									int32 BestThreshold = -1;
									for (const FWarnEscalationTier& Tier : SysCfg->WarnEscalationTiers)
									{
										const bool bHit = (Tier.PointThreshold > 0)
											? (AutoWarnPoints >= Tier.PointThreshold)
											: (AutoWarnCount  >= Tier.WarnCount);
										const int32 ThisThreshold = (Tier.PointThreshold > 0)
											? Tier.PointThreshold : Tier.WarnCount;
										if (bHit && ThisThreshold > BestThreshold)
										{
											BestThreshold      = ThisThreshold;
											BanDurationMinutes = Tier.DurationMinutes;
										}
									}
								}
								else if (SysCfg->AutoBanWarnCount > 0 && AutoWarnCount >= SysCfg->AutoBanWarnCount)
								{
									BanDurationMinutes = SysCfg->AutoBanWarnMinutes;
								}

								if (BanDurationMinutes >= 0)
								{
									if (UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>())
									{
										FBanEntry Existing;
										if (!DB->IsCurrentlyBanned(Uid, Existing))
										{
											FBanEntry AutoBan;
											AutoBan.Uid      = Uid;
											UBanDatabase::ParseUid(Uid, AutoBan.Platform, AutoBan.PlayerUID);
											AutoBan.PlayerName   = PlayerName;
											AutoBan.Reason       = TEXT("Auto-banned: reached warning threshold");
											AutoBan.BannedBy     = TEXT("auto");
											const FDateTime AutoNow = FDateTime::UtcNow();
											AutoBan.BanDate      = AutoNow;
											AutoBan.bIsPermanent = (BanDurationMinutes <= 0);
											AutoBan.ExpireDate   = AutoBan.bIsPermanent
												? FDateTime(0)
												: AutoNow + FTimespan::FromMinutes(BanDurationMinutes);
											if (DB->AddBan(AutoBan))
											{
												if (UWorld* WBan = GI->GetWorld())
													UBanEnforcer::KickConnectedPlayer(WBan, Uid, AutoBan.GetKickMessage());
												FBanDiscordNotifier::NotifyBanCreated(AutoBan);
												FBanDiscordNotifier::NotifyAutoEscalationBan(AutoBan, AutoWarnCount);
												if (UBanAuditLog* AL = GI->GetSubsystem<UBanAuditLog>())
													AL->LogAction(TEXT("ban"), Uid, PlayerName,
													              TEXT("auto"), TEXT("auto"), AutoBan.Reason);
											}
										}
									}
								}
							}
						}

						// Notify the player in-game so they are aware they have been warned.
						if (WarnTargetPC)
						{
							WarnTargetPC->ClientMessage(FString::Printf(
								TEXT("[Warning] You have been automatically warned for inappropriate language. "
								     "(Warning #%d)"),
								AutoWarnCount));
						}
					}
				}
			}
		}
	}

	SendGameMessageToDiscord(PlayerName, FilteredMessage);
}

// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::SendGameMessageToDiscord(const FString& PlayerName,
                                                        const FString& Message)
{
	if (Config.BotToken.IsEmpty() || Config.ChannelId.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: Cannot send message – BotToken or ChannelId not configured."));
		return;
	}

	// Apply the configurable format string.
	// Fall back to a plain "Name: Message" string when the format is empty so
	// the message is never silently discarded due to a misconfigured INI.
	const FString EffectivePlayerName = PlayerName.IsEmpty() ? TEXT("Unknown") : PlayerName;

	FString FormattedContent = Config.GameToDiscordFormat;
	FormattedContent = FormattedContent.Replace(TEXT("%ServerName%"),  *Config.ServerName);
	FormattedContent = FormattedContent.Replace(TEXT("%PlayerName%"), *EffectivePlayerName);
	FormattedContent = FormattedContent.Replace(TEXT("%Message%"),    *Message);

	if (FormattedContent.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: GameToDiscordFormat produced an empty string for player '%s'. "
		            "Check the GameToDiscordFormat setting in DefaultDiscordBridge.ini."),
		       *EffectivePlayerName);
		return;
	}

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Sending to Discord: %s"), *FormattedContent);

	// Build the JSON body: {"content": "…"}
	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("content"), FormattedContent);

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
	if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in SendGameMessageToDiscord."));
		return;
	}

	// Helper lambda to POST the formatted content to a given Discord channel.
	auto PostToChannel = [this, BodyString, FormattedContent, EffectivePlayerName](const FString& TargetChannelId)
	{
		const FString Url = FString::Printf(
			TEXT("%s/channels/%s/messages"), *DiscordApiBase, *TargetChannelId);

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
			FHttpModule::Get().CreateRequest();

		Request->SetURL(Url);
		Request->SetVerb(TEXT("POST"));
		Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
		Request->SetHeader(TEXT("Authorization"),
		                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
		Request->SetContentAsString(BodyString);

		Request->OnProcessRequestComplete().BindWeakLambda(
			this,
			[EffectivePlayerName](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
			{
				if (!bConnected || !Resp.IsValid())
				{
					UE_LOG(LogDiscordBridge, Warning,
					       TEXT("DiscordBridge: HTTP request failed for player '%s'."),
					       *EffectivePlayerName);
					return;
				}
				if (Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
				{
					UE_LOG(LogDiscordBridge, Warning,
					       TEXT("DiscordBridge: Discord REST API returned %d: %s"),
					       Resp->GetResponseCode(), *Resp->GetContentAsString());
				}
			});

		Request->ProcessRequest();
	};

	// POST to the main chat channel.
	PostToChannel(Config.ChannelId);

	// When a dedicated whitelist channel is configured, also post there for
	// players who are on the whitelist (so whitelisted members have their own
	// channel view of whitelisted player activity).
	if (!WhitelistConfig.WhitelistChannelId.IsEmpty() &&
	    WhitelistConfig.WhitelistChannelId != Config.ChannelId &&
	    FWhitelistManager::IsWhitelisted(EffectivePlayerName))
	{
		PostToChannel(WhitelistConfig.WhitelistChannelId);
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Discord → Game chat relay
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::RelayDiscordMessageToGame(const FString& Username,
                                                         const FString& Message)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: No world available – cannot relay Discord message to game chat."));
		return;
	}

	AFGChatManager* ChatManager = AFGChatManager::Get(World);
	if (!ChatManager)
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: ChatManager not found – cannot relay Discord message to game chat."));
		return;
	}

	// Apply the configurable DiscordToGameFormat string to produce the full
	// in-game chat line.  Placeholders: %Username% / %PlayerName% (alias), %Message%, %Role%.
	// Use a fallback if the format is empty so the message is never silently
	// dropped due to a misconfigured INI.
	FString FormattedMessage = Config.DiscordToGameFormat;
	FormattedMessage = FormattedMessage.Replace(TEXT("%Username%"),   *Username);
	FormattedMessage = FormattedMessage.Replace(TEXT("%PlayerName%"), *Username);
	FormattedMessage = FormattedMessage.Replace(TEXT("%Message%"),    *Message);
	FormattedMessage = FormattedMessage.Replace(TEXT("%Role%"),       *CurrentMessageRoleLabel);

	if (FormattedMessage.IsEmpty())
	{
		// Format produced an empty result – fall back to the raw message so the
		// content is always visible rather than silently dropped.
		FormattedMessage = Message;
	}

	FChatMessageStruct ChatMsg;
	// Use CMT_CustomMessage so the game's chat widget renders the message body
	// (MessageText) without requiring a real player controller.  The sender column
	// (MessageSender) is left blank because DiscordToGameFormat now controls the
	// full line of text, including the Discord username prefix.
	// CMT_CustomMessage also means the Game→Discord diff loop (which only processes
	// CMT_PlayerMessage entries) will naturally ignore these relay messages.
	ChatMsg.MessageType   = EFGChatMessageType::CMT_CustomMessage;
	ChatMsg.MessageSender = FText::GetEmpty();
	ChatMsg.MessageText   = FText::FromString(FormattedMessage);

	ChatManager->BroadcastChatMessage(ChatMsg);

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Relayed to game chat – text: '%s'"),
	       *FormattedMessage);
}

// ─────────────────────────────────────────────────────────────────────────────
// Whitelist and ban enforcement
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::OnPostLogin(AGameModeBase* GameMode, APlayerController* Controller)
{
	if (!Controller || Controller->IsLocalController())
	{
		return;
	}

	const APlayerState* PS = Controller->GetPlayerState<APlayerState>();
	const FString PlayerName = PS ? PS->GetPlayerName() : FString();

	// In Satisfactory's CSS UE build, the player name is populated asynchronously
	// from Epic Online Services (via Server_SetPlayerNames RPC) after PostLogin fires.
	// When enforcement is active or player-event notifications are enabled and the
	// name is not yet available, schedule a one-shot deferred retry rather than
	// silently allowing the player through or missing the join notification.
	if (PlayerName.IsEmpty())
	{
		const bool bEnforcementActive = FWhitelistManager::IsEnabled();
		const bool bNeedsDeferred     = bEnforcementActive || Config.bPlayerEventsEnabled;
		if (bNeedsDeferred)
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridge: player joined with an empty name – scheduling deferred check."));

			if (UWorld* World = GetWorld())
			{
				TWeakObjectPtr<AGameModeBase>     WeakGM(GameMode);
				TWeakObjectPtr<APlayerController> WeakPC(Controller);
				TWeakObjectPtr<UWorld>            WeakWorld(World);

				// Retry every 0.5 s, up to MaxRetries times.  A shared handle
				// lets the lambda cancel the repeating timer once done.
				TSharedRef<FTimerHandle> SharedHandle = MakeShared<FTimerHandle>();
				TSharedRef<int32>        RetriesLeft  = MakeShared<int32>(10);

				World->GetTimerManager().SetTimer(*SharedHandle,
					FTimerDelegate::CreateWeakLambda(this,
						[this, WeakGM, WeakPC, WeakWorld, SharedHandle, RetriesLeft, bEnforcementActive]()
					{
						UWorld* W = WeakWorld.Get();

						if (!WeakPC.IsValid())
						{
							// Player already disconnected – stop the timer.
							if (W) { W->GetTimerManager().ClearTimer(*SharedHandle); }
							return;
						}

						const APlayerState* RetryPS   = WeakPC->GetPlayerState<APlayerState>();
						const FString       RetryName = RetryPS ? RetryPS->GetPlayerName() : FString();

						if (!RetryName.IsEmpty())
						{
							// Name is now available – run the whitelist/notification check and stop the timer.
							if (W) { W->GetTimerManager().ClearTimer(*SharedHandle); }
							OnPostLogin(WeakGM.Get(), WeakPC.Get());
							return;
						}

						--(*RetriesLeft);
						if (*RetriesLeft > 0)
						{
							return; // Name not yet populated – try again next tick.
						}

						// All retries exhausted.
						if (W) { W->GetTimerManager().ClearTimer(*SharedHandle); }

						if (bEnforcementActive)
						{
							// Kick to enforce whitelist integrity (fail-closed).
							UE_LOG(LogDiscordBridge, Warning,
							       TEXT("DiscordBridge: player name still empty after deferred check – kicking to enforce whitelist."));

							AGameModeBase* FallbackGM = WeakGM.IsValid() ? WeakGM.Get() : nullptr;
							if (!FallbackGM && W)
							{
								FallbackGM = W->GetAuthGameMode<AGameModeBase>();
							}
							if (FallbackGM && FallbackGM->GameSession && WeakPC.IsValid())
							{
								FallbackGM->GameSession->KickPlayer(
									WeakPC.Get(),
									FText::FromString(
										TEXT("Unable to verify player identity. Please reconnect.")));
							}
						}
						else
						{
							UE_LOG(LogDiscordBridge, Warning,
							       TEXT("DiscordBridge: player name still empty after deferred check – skipping (enforcement disabled)."));
						}
					}),
					0.5f, true);
			}
		}
		else
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridge: player joined with an empty name – skipping check (enforcement disabled)."));
		}
		return;
	}

	// ── Resolve the authoritative game mode ──────────────────────────────────
	// When OnPostLogin is called from the deferred-name retry lambda the GameMode
	// parameter may be null (weak pointer expired).  Fall back to the world's
	// auth game mode so the kick can always be issued.
	AGameModeBase* EffectiveGameMode = GameMode;
	if (!EffectiveGameMode || !EffectiveGameMode->GameSession)
	{
		if (UWorld* W = Controller->GetWorld())
		{
			EffectiveGameMode = W->GetAuthGameMode<AGameModeBase>();
		}
	}

	// ── Resolve EOS PUID ─────────────────────────────────────────────────────
	// Walk the connected controllers to find this player's PlayerState and read
	// their EOS Product User ID via the safe FUniqueNetIdRepl accessors.
	// We iterate rather than using Controller->GetPlayerState directly because
	// OnPostLogin may be called from a deferred retry where Controller is still
	// the same object but PlayerState replication may have completed by now.
	FString ResolvedEOSProductUserId;
	if (UWorld* PW = Controller->GetWorld())
	{
		for (FConstPlayerControllerIterator It = PW->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* JPC = It->Get();
			if (!JPC || !JPC->PlayerState) continue;
			if (JPC->PlayerState->GetPlayerName() != PlayerName) continue;
			const FUniqueNetIdRepl& NetId = JPC->PlayerState->GetUniqueId();
			// Use FUniqueNetIdRepl member accessors only — do NOT dereference
			// via operator-> on CSS DS (EOS V2 inner pointer is not a valid C++ object).
			if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
			{
				ResolvedEOSProductUserId = NetId.ToString().ToLower();
			}
			break;
		}
	}

	// ── Resolve remote IP address ─────────────────────────────────────────────
	FString ResolvedIpAddress;
	if (UNetConnection* Conn = Controller->GetNetConnection())
	{
		ResolvedIpAddress = Conn->LowLevelGetRemoteAddress(/*bAppendPort=*/false);
	}

	// Always log the available platform IDs so server operators can see them in
	// the server log regardless of whether player-event notifications are enabled.
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: player '%s' joined — EOS PUID: %s | IP: %s"),
	       *PlayerName,
	       ResolvedEOSProductUserId.IsEmpty() ? TEXT("(none)") : *ResolvedEOSProductUserId,
	       ResolvedIpAddress.IsEmpty()        ? TEXT("(none)") : *ResolvedIpAddress);

	// ── Whitelist check ───────────────────────────────────────────────────────
	if (!FWhitelistManager::IsEnabled())
	{
		SendPlayerJoinNotification(PlayerName, ResolvedEOSProductUserId, ResolvedIpAddress);
		SendJoinHintToPlayer(Controller, PlayerName);
		SendInGameJoinBroadcast(PlayerName);
		return;
	}

	if (FWhitelistManager::IsWhitelisted(PlayerName, ResolvedEOSProductUserId))
	{
		SendPlayerJoinNotification(PlayerName, ResolvedEOSProductUserId, ResolvedIpAddress);
		SendJoinHintToPlayer(Controller, PlayerName);
		SendInGameJoinBroadcast(PlayerName);
		return;
	}

	// Secondary pass: if WhitelistRoleId is configured, also allow any player
	// whose in-game name matches a Discord display name (nick / global_name /
	// username) of a guild member who holds the whitelist role.  The cache is
	// populated asynchronously after the bot connects; players who join before
	// it is ready follow the JSON-only path above.
	if (!WhitelistConfig.WhitelistRoleId.IsEmpty() &&
	    WhitelistRoleMemberNames.Contains(PlayerName.ToLower()))
	{
		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge Whitelist: allowing '%s' – matches a Discord member with WhitelistRoleId."),
		       *PlayerName);
		SendPlayerJoinNotification(PlayerName, ResolvedEOSProductUserId, ResolvedIpAddress);
		SendJoinHintToPlayer(Controller, PlayerName);
		SendInGameJoinBroadcast(PlayerName);
		return;
	}

	UE_LOG(LogDiscordBridge, Warning,
	       TEXT("DiscordBridge Whitelist: kicking non-whitelisted player '%s'"), *PlayerName);

	if (EffectiveGameMode && EffectiveGameMode->GameSession)
	{
		const FString KickReason = WhitelistConfig.WhitelistKickReason.IsEmpty()
			? TEXT("You are not on the server whitelist. Contact the server admin to be added.")
			: WhitelistConfig.WhitelistKickReason;
		EffectiveGameMode->GameSession->KickPlayer(
			Controller,
			FText::FromString(KickReason));
	}

	// Notify Discord so admins can see the kick in the bridge channel.
	if (!WhitelistConfig.WhitelistKickDiscordMessage.IsEmpty())
	{
		FString Notice = WhitelistConfig.WhitelistKickDiscordMessage;
		Notice = Notice.Replace(TEXT("%PlayerName%"), *PlayerName);
		SendMessageToChannel(Config.ChannelId, Notice);
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Player join / leave / timeout notifications
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::SendPlayerJoinNotification(const FString& PlayerName,
                                                          const FString& EOSProductUserId,
                                                          const FString& IpAddress)
{
	if (!Config.bPlayerEventsEnabled)
	{
		return;
	}

	// ── Public join message (name only, no sensitive data) ───────────────────
	if (!Config.PlayerJoinMessage.IsEmpty() || Config.bUseEmbedsForPlayerEvents)
	{
		const FString EffectiveChannelId = Config.PlayerEventsChannelId.IsEmpty()
			? Config.ChannelId
			: Config.PlayerEventsChannelId;

		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: Player join notification for '%s'"), *PlayerName);

		if (Config.bUseEmbedsForPlayerEvents)
		{
			if (Config.bEnableJoinReactionVoting)
			{
				// Build embed, post it, capture the message ID for reactions.
				TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
				EmbedObj->SetStringField(TEXT("title"), TEXT("Player Joined"));
				EmbedObj->SetNumberField(TEXT("color"), 3066993);
				TSharedPtr<FJsonObject> Field = MakeShared<FJsonObject>();
				Field->SetStringField(TEXT("name"),   TEXT("Player"));
				Field->SetStringField(TEXT("value"),  PlayerName);
				Field->SetBoolField  (TEXT("inline"), true);
				EmbedObj->SetArrayField(TEXT("fields"),
					TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(Field) });
				EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

				TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
				Body->SetArrayField(TEXT("embeds"),
					TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });

				FString BodyStr;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyStr);
				if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
				{
					UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in join notification embed."));
					return;
				}

				const FString Url = FString::Printf(
					TEXT("%s/channels/%s/messages"), *DiscordApiBase, *EffectiveChannelId);
				TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
				Req->SetURL(Url);
				Req->SetVerb(TEXT("POST"));
				Req->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
				Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bot %s"), *Config.BotToken));
				Req->SetContentAsString(BodyStr);

				Req->OnProcessRequestComplete().BindWeakLambda(
					this,
					[this, EffectiveChannelId, PlayerName]
					(FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bOk) mutable
					{
						if (!bOk || !Resp.IsValid() ||
						    Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300) return;

						TSharedPtr<FJsonObject> MsgObj;
						TSharedRef<TJsonReader<>> R = TJsonReaderFactory<>::Create(Resp->GetContentAsString());
						FString MsgId;
						if (FJsonSerializer::Deserialize(R, MsgObj) && MsgObj.IsValid())
							MsgObj->TryGetStringField(TEXT("id"), MsgId);
						if (!MsgId.IsEmpty())
							AddJoinReactions(MsgId, EffectiveChannelId, PlayerName);
					});
				Req->ProcessRequest();
			}
			else
			{
				SendPlayerEventEmbed(EffectiveChannelId, TEXT("Player Joined"), 3066993, PlayerName);
			}
		}
		else if (!Config.PlayerJoinMessage.IsEmpty())
		{
			FString Message = Config.PlayerJoinMessage;
			Message = Message.Replace(TEXT("%PlayerName%"), *PlayerName);
			SendMessageToChannel(EffectiveChannelId, Message);
		}
	}

	// ── Private admin message (EOS PUID + IP, admin channel only) ────────────
	if (!Config.PlayerJoinAdminChannelId.IsEmpty() && !Config.PlayerJoinAdminMessage.IsEmpty())
	{
		FString AdminMessage = Config.PlayerJoinAdminMessage;
		AdminMessage = AdminMessage.Replace(TEXT("%PlayerName%"),        *PlayerName);
		AdminMessage = AdminMessage.Replace(TEXT("%EOSProductUserId%"),  EOSProductUserId.IsEmpty() ? TEXT("") : *EOSProductUserId);
		AdminMessage = AdminMessage.Replace(TEXT("%IpAddress%"),         IpAddress.IsEmpty()        ? TEXT("") : *IpAddress);

		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: Player admin-info notification for '%s'"), *PlayerName);

		SendMessageToChannel(Config.PlayerJoinAdminChannelId, AdminMessage);
	}

	// ── On-join DM welcome ────────────────────────────────────────────────────
	if (!Config.WelcomeMessageDM.IsEmpty())
	{
		// Resolve the player's Discord user ID by matching their in-game name
		// against the display names of WhitelistRoleId members in the cache.
		FString DiscordUserId;
		const FString LoweredName = PlayerName.ToLower();
		for (const TPair<FString, TArray<FString>>& Pair : RoleMemberIdToNames)
		{
			if (Pair.Value.Contains(LoweredName))
			{
				DiscordUserId = Pair.Key;
				break;
			}
		}

		if (!DiscordUserId.IsEmpty())
		{
			FString DmText = Config.WelcomeMessageDM;
			DmText = DmText.Replace(TEXT("%PlayerName%"), *PlayerName);

			// Step 1: create / retrieve the DM channel via POST /users/@me/channels.
			const FString CreateDmUrl =
				FString::Printf(TEXT("%s/users/@me/channels"), *DiscordApiBase);

			TSharedPtr<FJsonObject> DmBody = MakeShared<FJsonObject>();
			DmBody->SetStringField(TEXT("recipient_id"), DiscordUserId);

			FString DmBodyStr;
			TSharedRef<TJsonWriter<>> DmWriter = TJsonWriterFactory<>::Create(&DmBodyStr);
			if (!FJsonSerializer::Serialize(DmBody.ToSharedRef(), DmWriter))
			{
				UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in SendPlayerJoinNotification DM."));
				return;
			}

			TSharedRef<IHttpRequest, ESPMode::ThreadSafe> DmReq =
				FHttpModule::Get().CreateRequest();
			DmReq->SetURL(CreateDmUrl);
			DmReq->SetVerb(TEXT("POST"));
			DmReq->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
			DmReq->SetHeader(TEXT("Authorization"),
				FString::Printf(TEXT("Bot %s"), *Config.BotToken));
			DmReq->SetContentAsString(DmBodyStr);

			DmReq->OnProcessRequestComplete().BindWeakLambda(
				this,
				[this, DmText, DiscordUserId]
				(FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bOk)
				{
					if (!bOk || !Resp.IsValid() ||
					    Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
					{
						UE_LOG(LogDiscordBridge, Warning,
						       TEXT("DiscordBridge: Failed to create DM channel for user %s (HTTP %d)."),
						       *DiscordUserId,
						       Resp.IsValid() ? Resp->GetResponseCode() : 0);
						return;
					}

					TSharedPtr<FJsonObject> DmChannelObj;
					TSharedRef<TJsonReader<>> R =
						TJsonReaderFactory<>::Create(Resp->GetContentAsString());
					FString DmChannelId;
					if (FJsonSerializer::Deserialize(R, DmChannelObj) && DmChannelObj.IsValid())
					{
						DmChannelObj->TryGetStringField(TEXT("id"), DmChannelId);
					}

					if (DmChannelId.IsEmpty())
					{
						UE_LOG(LogDiscordBridge, Warning,
						       TEXT("DiscordBridge: DM channel response did not contain 'id'."));
						return;
					}

					// Step 2: send the welcome message to the DM channel.
					SendMessageToChannel(DmChannelId, DmText);

					UE_LOG(LogDiscordBridge, Log,
					       TEXT("DiscordBridge: Sent welcome DM to Discord user %s via channel %s."),
					       *DiscordUserId, *DmChannelId);
				});

			DmReq->ProcessRequest();
		}
	}
}

void UDiscordBridgeSubsystem::OnLogout(AGameModeBase* /*GameMode*/, AController* Exiting)
{
	// Always clean up per-player state regardless of whether event notifications
	// are enabled, so these maps don't grow without bound over the server lifetime.
	{
		const APlayerController* CleanPC = Cast<APlayerController>(Exiting);
		if (CleanPC && !CleanPC->IsLocalController())
		{
			if (const APlayerState* CleanPS = CleanPC->GetPlayerState<APlayerState>())
			{
				const FString CleanName = CleanPS->GetPlayerName();
				if (!CleanName.IsEmpty())
				{
					AfkStates.Remove(CleanName);
					ChatFilterHits.Remove(CleanName);
					PlayerStats.Remove(CleanName);
				}

				// Also remove ChatFilterHits keyed by UID (used when the network
				// identity was available at the time the filter hit was recorded).
				const FUniqueNetIdRepl& CleanNetId = CleanPS->GetUniqueId();
				if (CleanNetId.IsValid() && CleanNetId.GetType() != FName(TEXT("NONE")))
				{
					const FString CleanUid = UBanDatabase::MakeUid(
						CleanNetId.GetType().ToString().ToUpper(),
						CleanNetId.ToString().ToLower());
					ChatFilterHits.Remove(CleanUid);
				}
			}
		}
	}

	if (!Config.bPlayerEventsEnabled)
	{
		return;
	}

	// Only care about remote player controllers on the dedicated server.
	const APlayerController* PC = Cast<APlayerController>(Exiting);
	if (!PC || PC->IsLocalController())
	{
		return;
	}

	const APlayerState* PS = PC->GetPlayerState<APlayerState>();
	const FString PlayerName = PS ? PS->GetPlayerName() : FString();
	if (PlayerName.IsEmpty())
	{
		return;
	}

	const FString& EffectiveChannelId = Config.PlayerEventsChannelId.IsEmpty()
		? Config.ChannelId
		: Config.PlayerEventsChannelId;

	// Attempt to distinguish a timeout/crash from a clean disconnect.
	// When the net connection has already been cleaned up (null) by the time
	// Logout fires, the player most likely timed out or crashed rather than
	// disconnecting gracefully.  Fall back to PlayerLeaveMessage when
	// PlayerTimeoutMessage is empty so a single leave message covers all cases.
	const bool bIsTimeout = (PC->GetNetConnection() == nullptr);

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Player %s notification for '%s'"),
	       bIsTimeout ? TEXT("timeout") : TEXT("leave"),
	       *PlayerName);

	if (Config.bUseEmbedsForPlayerEvents)
	{
		if (bIsTimeout)
			SendPlayerEventEmbed(EffectiveChannelId, TEXT("Player Timed Out"), 16776960, PlayerName);
		else
			SendPlayerEventEmbed(EffectiveChannelId, TEXT("Player Left"), 15158332, PlayerName);
		return;
	}

	FString Message;
	if (bIsTimeout && !Config.PlayerTimeoutMessage.IsEmpty())
	{
		Message = Config.PlayerTimeoutMessage;
	}
	else if (!Config.PlayerLeaveMessage.IsEmpty())
	{
		Message = Config.PlayerLeaveMessage;
	}

	if (Message.IsEmpty())
	{
		return;
	}

	Message = Message.Replace(TEXT("%PlayerName%"), *PlayerName);
	SendMessageToChannel(EffectiveChannelId, Message);
}

void UDiscordBridgeSubsystem::HandleWhitelistCommand(const FString& SubCommand,
                                                      const FString& DiscordUsername,
                                                      const FString& ResponseChannelId,
                                                      const FString& AuthorDiscordId)
{
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Whitelist command from '%s': '%s'"), *DiscordUsername, *SubCommand);

	FString Response;

	FString Verb, Arg;
	if (!SubCommand.Split(TEXT(" "), &Verb, &Arg, ESearchCase::IgnoreCase))
	{
		Verb = SubCommand.TrimStartAndEnd();
		Arg  = TEXT("");
	}
	Verb = Verb.TrimStartAndEnd().ToLower();
	Arg  = Arg.TrimStartAndEnd();

	if (Verb == TEXT("on"))
	{
		FWhitelistManager::SetEnabled(true, DiscordUsername);
		Response = TEXT(":white_check_mark: Whitelist **enabled**. Only whitelisted players can join.");
		PostWhitelistEvent(TEXT("Whitelist **enabled**"), TEXT(""), DiscordUsername, 3447003);
	}
	else if (Verb == TEXT("off"))
	{
		FWhitelistManager::SetEnabled(false, DiscordUsername);
		Response = TEXT(":no_entry_sign: Whitelist **disabled**. All players can join freely.");
		PostWhitelistEvent(TEXT("Whitelist **disabled**"), TEXT(""), DiscordUsername, 10038562);
	}
	else if (Verb == TEXT("add"))
	{
		if (Arg.IsEmpty())
		{
			Response = TEXT(":warning: Usage: `/whitelist add <PlayerName> [puid:<PUID>] [group:<Group>] [duration]`");
		}
		else
		{
			// Parse tokens: "Alice puid:abc123 group:VIP 7d"
			FString ParsedName = Arg;
			FString ParsedPuid;
			FString ParsedGroup;
			FDateTime ExpiresAt(0);

			{
				TArray<FString> Tokens;
				Arg.ParseIntoArrayWS(Tokens);
				TArray<FString> NameParts;
				for (const FString& Tok : Tokens)
				{
					if (Tok.StartsWith(TEXT("puid:"), ESearchCase::IgnoreCase))
					{
						ParsedPuid = Tok.Mid(5);
					}
					else if (Tok.StartsWith(TEXT("group:"), ESearchCase::IgnoreCase))
					{
						ParsedGroup = Tok.Mid(6);
					}
					else
					{
						NameParts.Add(Tok);
					}
				}
				// Last token may be a duration
				FTimespan Dur;
				if (NameParts.Num() > 0)
				{
					const FString LastTok = NameParts.Last();
					Dur = FWhitelistManager::ParseDuration(LastTok);
					if (!Dur.IsZero())
					{
						NameParts.RemoveAt(NameParts.Num() - 1);
						ExpiresAt = FDateTime::UtcNow() + Dur;
					}
				}
				ParsedName = FString::Join(NameParts, TEXT(" ")).TrimStartAndEnd();
				if (ParsedName.IsEmpty()) ParsedName = Arg;
			}

			// Capacity check
			if (FWhitelistManager::GetMaxSlots() > 0 &&
			    FWhitelistManager::GetAllEntries().Num() >= FWhitelistManager::GetMaxSlots())
			{
				Response = FString::Printf(
					TEXT(":no_entry: Whitelist is full (%d/%d slots used)."),
					FWhitelistManager::GetAllEntries().Num(),
					FWhitelistManager::GetMaxSlots());
			}
			else if (FWhitelistManager::AddPlayer(ParsedName, ParsedPuid, DiscordUsername, ExpiresAt, ParsedGroup))
			{
				FString AddedMsg;
				if (ExpiresAt.GetTicks() > 0)
				{
					AddedMsg = FString::Printf(
						TEXT(":green_circle: **%s** added (expires %s)."),
						*ParsedName,
						*ExpiresAt.ToString(TEXT("%Y-%m-%d %H:%M UTC")));
				}
				else
				{
					AddedMsg = FString::Printf(
						TEXT(":green_circle: **%s** has been added to the whitelist."), *ParsedName);
				}
				if (!ParsedGroup.IsEmpty())
					AddedMsg += FString::Printf(TEXT(" Group: **%s**."), *ParsedGroup);
				Response = AddedMsg;
				PostWhitelistEvent(
					FString::Printf(TEXT("**%s** added to the whitelist"), *ParsedName),
					ParsedName, DiscordUsername, 3066993);

				// DM on add when AuthorDiscordId is known and DM is configured.
				if (!WhitelistConfig.WhitelistApprovedDmMessage.IsEmpty() && !AuthorDiscordId.IsEmpty())
				{
					// Only DM if the command was "add" and we have the target's Discord ID.
					// For direct /whitelist add we don't know the target's Discord ID, so skip.
				}
			}
			else
			{
				Response = FString::Printf(TEXT(":yellow_circle: **%s** is already on the whitelist."), *ParsedName);
			}
		}
	}
	else if (Verb == TEXT("remove"))
	{
		if (Arg.IsEmpty())
		{
			Response = TEXT(":warning: Usage: `/whitelist remove <PlayerName>`");
		}
		else if (FWhitelistManager::RemovePlayer(Arg, TEXT(""), DiscordUsername))
		{
			// Clear any pending expiry warning for this player so that if they
			// are re-added with a new expiry the warning fires correctly.
			WarnedExpiryNames.Remove(Arg);
			SaveWarnedExpiryNames();

			Response = FString::Printf(TEXT(":red_circle: **%s** has been removed from the whitelist."), *Arg);
			PostWhitelistEvent(
				FString::Printf(TEXT("**%s** removed from the whitelist"), *Arg),
				Arg, DiscordUsername, 15158332);
		}
		else
		{
			Response = FString::Printf(TEXT(":yellow_circle: **%s** was not on the whitelist."), *Arg);
		}
	}
	else if (Verb == TEXT("list"))
	{
		// Arg may be empty (list all) or a group name to filter by.
		const bool bFilterByGroup = !Arg.IsEmpty();
		TArray<FWhitelistEntry> AllEntries = FWhitelistManager::GetAllEntries();

		TArray<FString> Names;
		for (const FWhitelistEntry& E : AllEntries)
		{
			if (!bFilterByGroup || E.Group.Equals(Arg, ESearchCase::IgnoreCase))
				Names.Add(E.Name);
		}

		const FString Status = FWhitelistManager::IsEnabled() ? TEXT("ENABLED") : TEXT("disabled");
		if (Names.Num() == 0)
		{
			if (bFilterByGroup)
				Response = FString::Printf(TEXT(":scroll: Whitelist is **%s**. No players in group `%s`."), *Status, *Arg);
			else
				Response = FString::Printf(TEXT(":scroll: Whitelist is **%s**. No players listed."), *Status);
		}
		else
		{
			if (bFilterByGroup)
				Response = FString::Printf(
					TEXT(":scroll: Whitelist is **%s**. Group `%s` (%d players): %s"),
					*Status, *Arg, Names.Num(), *FString::Join(Names, TEXT(", ")));
			else
				Response = FString::Printf(
					TEXT(":scroll: Whitelist is **%s**. Players (%d): %s"),
					*Status, Names.Num(), *FString::Join(Names, TEXT(", ")));
		}
	}
	else if (Verb == TEXT("status"))
	{
		const FString WhitelistState = FWhitelistManager::IsEnabled()
			? TEXT(":white_check_mark: Whitelist: **ENABLED**")
			: TEXT(":no_entry_sign: Whitelist: **disabled**");
		const int32 Count = FWhitelistManager::GetAllEntries().Num();
		const int32 Slots = FWhitelistManager::GetMaxSlots();
		FString SlotInfo;
		if (Slots > 0)
		{
			SlotInfo = FString::Printf(TEXT("\nSlots: %d/%d"), Count, Slots);
		}
		else
		{
			SlotInfo = FString::Printf(TEXT("\nSlots: %d/unlimited"), Count);
		}
		Response = WhitelistState + SlotInfo;
	}
	else if (Verb == TEXT("export"))
	{
		const TArray<FWhitelistEntry> AllEntries = FWhitelistManager::GetAllEntries();
		FString JsonOut = TEXT("[");
		for (int32 i = 0; i < AllEntries.Num(); ++i)
		{
			const FWhitelistEntry& E = AllEntries[i];
			FString ExpiresStr;
			if (E.ExpiresAt.GetTicks() > 0)
				ExpiresStr = E.ExpiresAt.ToIso8601();
			JsonOut += FString::Printf(TEXT("{\"name\":\"%s\",\"puid\":\"%s\",\"group\":\"%s\",\"expires_at\":\"%s\"}"),
				*JsonEscapeStr(E.Name), *JsonEscapeStr(E.EosPUID), *JsonEscapeStr(E.Group), *ExpiresStr);
			if (i < AllEntries.Num() - 1) JsonOut += TEXT(",");
		}
		JsonOut += TEXT("]");

		FString Msg = FString::Printf(
			TEXT(":scroll: **Whitelist Export** (%d entries):\n```json\n%s\n```"),
			AllEntries.Num(), *JsonOut);
		if (Msg.Len() > 1900)
		{
			Msg = Msg.Left(1900) + TEXT("\n*(truncated)*");
		}
		Response = Msg;
	}
	else if (Verb == TEXT("import"))
	{
		if (Arg.IsEmpty())
		{
			Response = TEXT(":warning: Usage: `/whitelist import <json-array>`");
		}
		else
		{
			int32 Added = 0, Skipped = 0;
			TSharedPtr<FJsonValue> JsonVal;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Arg);
			if (!FJsonSerializer::Deserialize(Reader, JsonVal) || !JsonVal.IsValid())
			{
				Response = TEXT(":x: Import failed — could not parse JSON. Ensure the input is valid JSON.");
			}
			else
			{
				const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
				if (!JsonVal->TryGetArray(Arr) || !Arr)
				{
					Response = TEXT(":x: Import failed — JSON root must be an array (`[...]`), not an object or other type.");
				}
				else
				{
					for (const TSharedPtr<FJsonValue>& Item : *Arr)
					{
						if (Item->Type == EJson::String)
						{
							if (FWhitelistManager::AddPlayer(Item->AsString(), TEXT(""), DiscordUsername))
								++Added;
							else
								++Skipped;
						}
						else if (Item->Type == EJson::Object)
						{
							const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
							if (Item->TryGetObject(ObjPtr) && ObjPtr)
							{
								FString IName, IPuid, IGroup;
								(*ObjPtr)->TryGetStringField(TEXT("name"), IName);
								(*ObjPtr)->TryGetStringField(TEXT("puid"), IPuid);
								(*ObjPtr)->TryGetStringField(TEXT("group"), IGroup);
								if (FWhitelistManager::AddPlayer(IName, IPuid, DiscordUsername,
								                                 FDateTime(0), IGroup))
									++Added;
								else
									++Skipped;
							}
						}
					}
					Response = FString::Printf(TEXT(":inbox_tray: Import complete. Added %d, skipped %d."), Added, Skipped);
				}
			}
		}
	}
	else if (Verb == TEXT("log"))
	{
		int32 N = 10;
		if (!Arg.IsEmpty()) N = FMath::Clamp(FCString::Atoi(*Arg), 1, 20);
		const TArray<FWhitelistAuditEntry> Log = FWhitelistManager::GetAuditLog(N);
		if (Log.Num() == 0)
		{
			Response = TEXT(":scroll: No whitelist audit log entries.");
		}
		else
		{
			FString LogText = FString::Printf(TEXT(":scroll: **Whitelist Audit Log** (last %d):\n"), Log.Num());
			for (const FWhitelistAuditEntry& E : Log)
			{
				LogText += FString::Printf(TEXT("`[%s]` **%s** `%s` by %s\n"),
					*E.Timestamp.ToString(TEXT("%Y-%m-%d %H:%M")),
					*E.Action,
					*E.Target,
					E.AdminName.IsEmpty() ? TEXT("system") : *E.AdminName);
			}
			Response = LogText;
		}
	}
	else if (Verb == TEXT("role"))
	{
		FString RoleVerb, TargetUserId;
		if (!Arg.Split(TEXT(" "), &RoleVerb, &TargetUserId, ESearchCase::IgnoreCase))
		{
			RoleVerb     = Arg.TrimStartAndEnd();
			TargetUserId = TEXT("");
		}
		RoleVerb     = RoleVerb.TrimStartAndEnd().ToLower();
		TargetUserId = TargetUserId.TrimStartAndEnd();

		if (WhitelistConfig.WhitelistRoleId.IsEmpty())
		{
			Response = TEXT(":warning: `WhitelistRoleId` is not configured in `DefaultDiscordBridge.ini`. "
			                "Set it to the snowflake ID of the whitelist role.");
		}
		else if (GuildId.IsEmpty())
		{
			Response = TEXT(":warning: Guild ID not yet available. Try again in a moment.");
		}
		else if (TargetUserId.IsEmpty())
		{
			Response = TEXT(":warning: Usage: `/whitelist role add <discord_user_id>` "
			                "or `/whitelist role remove <discord_user_id>`");
		}
		else if (RoleVerb == TEXT("add"))
		{
			ModifyDiscordRole(TargetUserId, WhitelistConfig.WhitelistRoleId, /*bGrant=*/true);
			Response = FString::Printf(
				TEXT(":green_circle: Granting whitelist role to Discord user `%s`..."), *TargetUserId);
		}
		else if (RoleVerb == TEXT("remove"))
		{
			ModifyDiscordRole(TargetUserId, WhitelistConfig.WhitelistRoleId, /*bGrant=*/false);
			Response = FString::Printf(
				TEXT(":red_circle: Revoking whitelist role from Discord user `%s`..."), *TargetUserId);
		}
		else
		{
			Response = TEXT(":question: Usage: `/whitelist role add <discord_user_id>` "
			                "or `/whitelist role remove <discord_user_id>`");
		}
	}
	else if (Verb == TEXT("search"))
	{
		if (Arg.IsEmpty())
		{
			Response = TEXT(":warning: Usage: `/whitelist search <partial-name>`");
		}
		else
		{
			const TArray<FWhitelistEntry> Results = FWhitelistManager::Search(Arg);
			if (Results.Num() == 0)
			{
				Response = FString::Printf(TEXT(":mag: No whitelist entries matching `%s`."), *Arg);
			}
			else
			{
				FString ResultText = FString::Printf(TEXT(":mag: Search results for `%s` (%d):\n"), *Arg, Results.Num());
				for (const FWhitelistEntry& E : Results)
				{
					FString ExtraInfo;
					if (!E.Group.IsEmpty())
						ExtraInfo += FString::Printf(TEXT(" [%s]"), *E.Group);
					if (E.ExpiresAt.GetTicks() > 0)
						ExtraInfo += FString::Printf(TEXT(" (expires %s)"),
							*E.ExpiresAt.ToString(TEXT("%Y-%m-%d %H:%M UTC")));
					ResultText += FString::Printf(TEXT("• **%s**%s\n"), *E.Name, *ExtraInfo);
				}
				Response = ResultText.TrimEnd();
				if (Response.Len() > 1900)
					Response = Response.Left(1900) + TEXT("\n*(truncated)*");
			}
		}
	}
	else if (Verb == TEXT("groups"))
	{
		const TArray<FWhitelistEntry> AllEntries = FWhitelistManager::GetAllEntries();
		TMap<FString, int32> GroupCounts;
		for (const FWhitelistEntry& E : AllEntries)
		{
			const FString GroupKey = E.Group.IsEmpty() ? TEXT("(default)") : E.Group;
			int32& Count = GroupCounts.FindOrAdd(GroupKey);
			++Count;
		}
		if (GroupCounts.Num() == 0)
		{
			Response = TEXT(":busts_in_silhouette: Whitelist is empty — no groups.");
		}
		else
		{
			FString GroupText = FString::Printf(TEXT(":busts_in_silhouette: **Whitelist Groups** (%d entries total):\n"),
				AllEntries.Num());
			for (const auto& Pair : GroupCounts)
			{
				GroupText += FString::Printf(TEXT("• **%s** — %d player%s\n"),
					*Pair.Key, Pair.Value, Pair.Value == 1 ? TEXT("") : TEXT("s"));
			}
			Response = GroupText.TrimEnd();
		}
	}
	else if (Verb == TEXT("apply"))
	{
		if (!WhitelistConfig.bWhitelistApplyEnabled)
		{
			Response = TEXT(":no_entry_sign: Whitelist applications are not enabled on this server.");
		}
		else if (WhitelistConfig.WhitelistApplicationChannelId.IsEmpty())
		{
			Response = TEXT(":warning: Whitelist application channel is not configured.");
		}
		else if (Arg.IsEmpty())
		{
			Response = TEXT(":warning: Usage: `/whitelist apply <YourInGameName>`");
		}
		else if (AuthorDiscordId.IsEmpty())
		{
			Response = TEXT(":warning: Could not determine your Discord user ID. Please try again.");
		}
		else
		{
			// Store the pending application keyed by Discord user ID.
			// Record expiry time (24 hours) so ignored applications don't
			// accumulate forever in memory.
			PendingWhitelistApps.Add(AuthorDiscordId, Arg);
			PendingWhitelistAppExpiry.Add(AuthorDiscordId, FDateTime::UtcNow() + FTimespan::FromHours(24.0));

			// Build an embed with Approve/Deny buttons posted to WhitelistApplicationChannelId.
			const FString AppJson = FString::Printf(
				TEXT("{")
				TEXT("\"embeds\":[{")
				TEXT("\"color\":3447003,")
				TEXT("\"title\":\":clipboard: Whitelist Application\",")
				TEXT("\"description\":\"**Discord User:** <@%s>\\n**In-Game Name:** `%s`\",")
				TEXT("\"footer\":{\"text\":\"Use the buttons below to approve or deny\"}")
				TEXT("}],")
				TEXT("\"components\":[{")
				TEXT("\"type\":1,")
				TEXT("\"components\":[")
				TEXT("{\"type\":2,\"style\":3,\"label\":\"Approve\",\"custom_id\":\"wl_approve:%s\"},")
				TEXT("{\"type\":2,\"style\":4,\"label\":\"Deny\",\"custom_id\":\"wl_deny:%s\"}")
				TEXT("]")
				TEXT("}]}"),
				*AuthorDiscordId,
				*JsonEscapeStr(Arg),
				*AuthorDiscordId,
				*AuthorDiscordId);

			const FString AppUrl = FString::Printf(
				TEXT("%s/channels/%s/messages"),
				*DiscordApiBase, *WhitelistConfig.WhitelistApplicationChannelId);

			TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AppReq = FHttpModule::Get().CreateRequest();
			AppReq->SetURL(AppUrl);
			AppReq->SetVerb(TEXT("POST"));
			AppReq->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bot %s"), *Config.BotToken));
			AppReq->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
			AppReq->SetContentAsString(AppJson);
			AppReq->OnProcessRequestComplete().BindWeakLambda(this,
				[](FHttpRequestPtr, FHttpResponsePtr Resp, bool bOk)
				{
					if (!bOk || !Resp.IsValid() || Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
					{
						UE_LOG(LogDiscordBridge, Warning,
						       TEXT("DiscordBridge: Failed to post whitelist application embed."));
					}
				});
			AppReq->ProcessRequest();

			Response = FString::Printf(
				TEXT(":mailbox_with_mail: Your application for **%s** has been submitted! "
				     "An admin will review it shortly."), *Arg);
		}
	}
	else if (Verb == TEXT("link"))
	{
		if (!WhitelistConfig.bWhitelistVerificationEnabled)
		{
			Response = TEXT(":no_entry_sign: Account verification is not enabled on this server.");
		}
		else if (Arg.IsEmpty())
		{
			Response = TEXT(":warning: Usage: `/whitelist link <YourInGameName>`");
		}
		else if (AuthorDiscordId.IsEmpty())
		{
			Response = TEXT(":warning: Could not determine your Discord user ID. Please try again.");
		}
		else if (!WhitelistConfig.WhitelistVerificationChannelId.IsEmpty() &&
		         ResponseChannelId != WhitelistConfig.WhitelistVerificationChannelId)
		{
			Response = FString::Printf(
				TEXT(":no_entry_sign: Please use this command in <#%s>."),
				*WhitelistConfig.WhitelistVerificationChannelId);
		}
		else
		{
			// Generate a random 6-digit code.
			const int32 Code = FMath::RandRange(100000, 999999);
			const FString CodeStr = FString::FromInt(Code);

			// Invalidate any prior pending code for this Discord user so they
			// cannot accumulate multiple valid codes and share them with others.
			{
				TArray<FString> OldCodes;
				for (const auto& Pair : PendingVerifications)
				{
					if (Pair.Value == AuthorDiscordId)
						OldCodes.Add(Pair.Key);
				}
				for (const FString& Old : OldCodes)
				{
					PendingVerifications.Remove(Old);
					PendingVerificationNames.Remove(Old);
					PendingVerificationExpiry.Remove(Old);
				}
			}

			PendingVerifications.Add(CodeStr, AuthorDiscordId);
			PendingVerificationNames.Add(CodeStr, Arg);
			PendingVerificationExpiry.Add(CodeStr, FDateTime::UtcNow() + FTimespan::FromMinutes(10.0));

			Response = FString::Printf(
				TEXT(":key: Type `/verify %s` in-game within **10 minutes** to link your account **%s** to the whitelist."),
				*CodeStr, *Arg);
		}
	}
	else
	{
		Response = TEXT(":question: Unknown whitelist command. Available: `on`, `off`, "
		                "`add <name> [puid:<id>] [group:<group>] [duration]`, `remove <name>`, "
		                "`list [group]`, `search <partial>`, `groups`, `status`, "
		                "`export`, `import <json>`, `log [N]`, "
		                "`role add <discord_id>`, `role remove <discord_id>`, "
		                "`apply <in-game-name>`, `link <in-game-name>`.");
	}

	const FString& ReplyChannel = ResponseChannelId.IsEmpty() ? Config.ChannelId : ResponseChannelId;
	SendMessageToChannel(ReplyChannel, Response);
}

void UDiscordBridgeSubsystem::ModifyDiscordRole(const FString& UserId, const FString& RoleId, bool bGrant)
{
	if (RoleId.IsEmpty() || GuildId.IsEmpty() || Config.BotToken.IsEmpty())
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridge: ModifyDiscordRole: missing RoleId, GuildId, or BotToken."));
		return;
	}

	// PUT  = grant the role
	// DELETE = revoke the role
	const FString Verb = bGrant ? TEXT("PUT") : TEXT("DELETE");
	const FString Url = FString::Printf(
		TEXT("%s/guilds/%s/members/%s/roles/%s"),
		*DiscordApiBase, *GuildId, *UserId, *RoleId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	// PUT with empty body still needs a Content-Type header to avoid 411.
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetContentAsString(TEXT(""));

	const bool bGrantCopy = bGrant;
	const FString UserIdCopy = UserId;
	Request->OnProcessRequestComplete().BindWeakLambda(
		this,
		[bGrantCopy, UserIdCopy](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid())
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: Role %s request failed for user '%s'."),
				       bGrantCopy ? TEXT("grant") : TEXT("revoke"), *UserIdCopy);
				return;
			}
			// 204 No Content is the success response for both PUT and DELETE role endpoints.
			if (Resp->GetResponseCode() != 204)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: Role %s for user '%s' returned HTTP %d: %s"),
				       bGrantCopy ? TEXT("grant") : TEXT("revoke"), *UserIdCopy,
				       Resp->GetResponseCode(), *Resp->GetContentAsString());
			}
			else
			{
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Role %s succeeded for user '%s'."),
				       bGrantCopy ? TEXT("grant") : TEXT("revoke"), *UserIdCopy);
			}
		});

	Request->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
// Discord role member cache helpers
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::RebuildWhitelistRoleNameSet()
{
	WhitelistRoleMemberNames.Empty();
	for (const TPair<FString, TArray<FString>>& Pair : RoleMemberIdToNames)
	{
		for (const FString& Name : Pair.Value)
		{
			WhitelistRoleMemberNames.Add(Name);
		}
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// SendDiscordDM
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::SendDiscordDM(const FString& DiscordUserId, const FString& Message)
{
	if (DiscordUserId.IsEmpty() || Message.IsEmpty() || Config.BotToken.IsEmpty())
	{
		return;
	}

	// Step 1: Create (or retrieve) the DM channel.
	const FString CreateDMUrl = DiscordApiBase + TEXT("/users/@me/channels");
	const FString BodyJson    = FString::Printf(TEXT("{\"recipient_id\":\"%s\"}"), *DiscordUserId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
	Req->SetURL(CreateDMUrl);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Req->SetContentAsString(BodyJson);

	const FString MessageCopy = Message;
	Req->OnProcessRequestComplete().BindWeakLambda(this,
		[this, MessageCopy](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bOk)
		{
			if (!bOk || !Resp.IsValid() || Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: SendDiscordDM – failed to create DM channel (HTTP %d)."),
				       Resp.IsValid() ? Resp->GetResponseCode() : 0);
				return;
			}
			TSharedPtr<FJsonObject> DMObj;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Resp->GetContentAsString());
			if (!FJsonSerializer::Deserialize(Reader, DMObj) || !DMObj.IsValid())
			{
				return;
			}
			FString DMChannelId;
			DMObj->TryGetStringField(TEXT("id"), DMChannelId);
			if (!DMChannelId.IsEmpty())
			{
				// Step 2: Send the message to the DM channel.
				SendMessageToChannel(DMChannelId, MessageCopy);
			}
		});
	Req->ProcessRequest();
}

void UDiscordBridgeSubsystem::UpdateWhitelistRoleMemberEntry(
	const TSharedPtr<FJsonObject>& MemberObj, bool bRemoved)
{
	if (!MemberObj.IsValid())
	{
		return;
	}

	// Extract Discord user ID – present in both member objects and remove events.
	const TSharedPtr<FJsonObject>* UserPtr = nullptr;
	if (!MemberObj->TryGetObjectField(TEXT("user"), UserPtr) || !UserPtr)
	{
		return;
	}
	FString UserId;
	if (!(*UserPtr)->TryGetStringField(TEXT("id"), UserId) || UserId.IsEmpty())
	{
		return;
	}

	if (bRemoved)
	{
		// Member left the guild – remove any cached entry and rebuild.
		if (RoleMemberIdToNames.Remove(UserId) > 0)
		{
			RebuildWhitelistRoleNameSet();
		}
		return;
	}

	// Determine whether this member currently holds WhitelistRoleId.
	bool bHasRole = false;
	const TArray<TSharedPtr<FJsonValue>>* Roles = nullptr;
	if (MemberObj->TryGetArrayField(TEXT("roles"), Roles) && Roles)
	{
		for (const TSharedPtr<FJsonValue>& RoleVal : *Roles)
		{
			FString RoleId;
			if (RoleVal->TryGetString(RoleId) && RoleId == WhitelistConfig.WhitelistRoleId)
			{
				bHasRole = true;
				break;
			}
		}
	}

	if (!bHasRole)
	{
		// Member no longer holds the role – remove from cache if present.
		if (RoleMemberIdToNames.Remove(UserId) > 0)
		{
			RebuildWhitelistRoleNameSet();
		}
		return;
	}

	// Collect all display names for this member (server nick, global name, username).
	TArray<FString> Names;
	FString Nick;
	if (MemberObj->TryGetStringField(TEXT("nick"), Nick) && !Nick.IsEmpty())
	{
		Names.AddUnique(Nick.ToLower());
	}
	FString GlobalName;
	if ((*UserPtr)->TryGetStringField(TEXT("global_name"), GlobalName) && !GlobalName.IsEmpty())
	{
		Names.AddUnique(GlobalName.ToLower());
	}
	FString Username;
	if ((*UserPtr)->TryGetStringField(TEXT("username"), Username) && !Username.IsEmpty())
	{
		Names.AddUnique(Username.ToLower());
	}

	if (Names.Num() == 0)
	{
		return;
	}

	RoleMemberIdToNames.FindOrAdd(UserId) = Names;
	RebuildWhitelistRoleNameSet();

	UE_LOG(LogDiscordBridge, Verbose,
	       TEXT("DiscordBridge: Whitelist role cache updated for user '%s' (%s)."),
	       *UserId, *FString::Join(Names, TEXT(", ")));
}

void UDiscordBridgeSubsystem::FetchWhitelistRoleMembers()
{
	if (WhitelistConfig.WhitelistRoleId.IsEmpty() || GuildId.IsEmpty() || Config.BotToken.IsEmpty())
	{
		return;
	}

	// Clear the cache before starting a fresh paginated fetch so stale entries
	// from a previous load do not linger if membership has changed.
	RoleMemberIdToNames.Empty();
	WhitelistRoleMemberNames.Empty();

	// Initiate pagination starting from the beginning (no `after` cursor).
	FetchWhitelistRoleMembersPage(TEXT(""));
}

void UDiscordBridgeSubsystem::FetchWhitelistRoleMembersPage(const FString& AfterUserId)
{
	// Discord's maximum per-request limit for GET /guilds/{id}/members is 1000.
	// Pages are fetched sequentially using the `after` cursor (last user ID of
	// the previous page) until a page returns fewer than 1000 members, which
	// indicates the final page has been reached.
	FString Url = FString::Printf(
		TEXT("%s/guilds/%s/members?limit=1000"),
		*DiscordApiBase, *GuildId);

	if (!AfterUserId.IsEmpty())
	{
		Url += FString::Printf(TEXT("&after=%s"), *AfterUserId);
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));

	Request->OnProcessRequestComplete().BindWeakLambda(
		this,
		[this](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid())
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: FetchWhitelistRoleMembersPage request failed."));
				return;
			}
			if (Resp->GetResponseCode() != 200)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: FetchWhitelistRoleMembersPage returned HTTP %d: %s"),
				       Resp->GetResponseCode(), *Resp->GetContentAsString());
				return;
			}

			// Parse the JSON array of member objects.
			TArray<TSharedPtr<FJsonValue>> Members;
			const TSharedRef<TJsonReader<>> Reader =
				TJsonReaderFactory<>::Create(Resp->GetContentAsString());
			if (!FJsonSerializer::Deserialize(Reader, Members))
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: FetchWhitelistRoleMembersPage – failed to parse JSON."));
				return;
			}

			// Process each member from this page.
			FString LastUserId;
			for (const TSharedPtr<FJsonValue>& Val : Members)
			{
				const TSharedPtr<FJsonObject>* MemberPtr = nullptr;
				if (!Val->TryGetObject(MemberPtr) || !MemberPtr)
				{
					continue;
				}
				UpdateWhitelistRoleMemberEntry(*MemberPtr);

				// Track the last user ID for the pagination cursor.
				const TSharedPtr<FJsonObject>* UserPtr = nullptr;
				if ((*MemberPtr)->TryGetObjectField(TEXT("user"), UserPtr) && UserPtr)
				{
					(*UserPtr)->TryGetStringField(TEXT("id"), LastUserId);
				}
			}

			if (Members.Num() == 1000 && !LastUserId.IsEmpty())
			{
				// Full page received – there may be more members; fetch the next page.
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Whitelist role cache page complete (%d members). "
				            "Fetching next page after user %s…"),
				       Members.Num(), *LastUserId);
				FetchWhitelistRoleMembersPage(LastUserId);
			}
			else
			{
				// Final page – log the completed cache size.
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Whitelist role cache built – %d member(s) hold WhitelistRoleId (%d name(s) cached)."),
				       RoleMemberIdToNames.Num(), WhitelistRoleMemberNames.Num());
			}
		});

	Request->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
// In-game chat command helpers
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::SendPlayerEventEmbed(const FString& TargetChannelId,
                                                   const FString& Title,
                                                   int32 Color,
                                                   const FString& PlayerName)
{
	TArray<TSharedPtr<FJsonValue>> Fields;

	// Primary "Player" field.
	{
		TSharedPtr<FJsonObject> Field = MakeShared<FJsonObject>();
		Field->SetStringField(TEXT("name"),   TEXT("Player"));
		Field->SetStringField(TEXT("value"),  PlayerName);
		Field->SetBoolField  (TEXT("inline"), true);
		Fields.Add(MakeShared<FJsonValueObject>(Field));
	}

	// Attempt to enrich the embed with warn count from PlayerWarningRegistry.
	// We look up by display name since we don't have the UID here.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>())
		{
			// Try to find the UID for this player via the session registry.
			if (UPlayerSessionRegistry* SessionReg = GI->GetSubsystem<UPlayerSessionRegistry>())
			{
				const TArray<FPlayerSessionRecord> Matches = SessionReg->FindByName(PlayerName);
				if (Matches.Num() == 1)
				{
					const int32 WarnCount = WarnReg->GetWarningCount(Matches[0].Uid);
					TSharedPtr<FJsonObject> WarnField = MakeShared<FJsonObject>();
					WarnField->SetStringField(TEXT("name"),   TEXT("Warnings"));
					WarnField->SetStringField(TEXT("value"),  FString::FromInt(WarnCount));
					WarnField->SetBoolField  (TEXT("inline"), true);
					Fields.Add(MakeShared<FJsonValueObject>(WarnField));
				}
			}
		}
	}

	TSharedPtr<FJsonObject> Embed = MakeShared<FJsonObject>();
	Embed->SetStringField(TEXT("title"),     Title);
	Embed->SetNumberField(TEXT("color"),     Color);
	Embed->SetArrayField (TEXT("fields"),    Fields);
	Embed->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

	TArray<TSharedPtr<FJsonValue>> Embeds;
	Embeds.Add(MakeShared<FJsonValueObject>(Embed));

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetArrayField(TEXT("embeds"), Embeds);

	SendMessageBodyToChannel(TargetChannelId, Body);
}

void UDiscordBridgeSubsystem::SendGameChatStatusMessage(const FString& Message)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AFGChatManager* ChatManager = AFGChatManager::Get(World);
	if (!ChatManager)
	{
		return;
	}

	FChatMessageStruct ChatMsg;
	ChatMsg.MessageType   = EFGChatMessageType::CMT_CustomMessage;
	ChatMsg.MessageSender = FText::FromString(TEXT("[Server]"));
	ChatMsg.MessageText   = FText::FromString(Message);

	ChatManager->BroadcastChatMessage(ChatMsg);
}

bool UDiscordBridgeSubsystem::IsVerificationEnabled() const
{
	return WhitelistConfig.bWhitelistVerificationEnabled;
}

void UDiscordBridgeSubsystem::SendJoinHintToPlayer(APlayerController* Controller,
                                                    const FString& PlayerName)
{
	if (!Controller || Config.JoinHintMessage.IsEmpty())
	{
		return;
	}

	AFGPlayerController* FGController = Cast<AFGPlayerController>(Controller);
	if (!FGController)
	{
		return;
	}

	USMLRemoteCallObject* RCO =
		FGController->GetRemoteCallObjectOfClass<USMLRemoteCallObject>();
	if (!RCO)
	{
		// RCO not yet available (can happen if called before the controller fully
		// initialises). Silently skip rather than broadcasting to all players.
		return;
	}

	FString HintText = Config.JoinHintMessage;
	HintText = HintText.Replace(TEXT("%PlayerName%"), *PlayerName);

	RCO->SendChatMessage(HintText, FLinearColor::White);
}

void UDiscordBridgeSubsystem::SendInGameJoinBroadcast(const FString& PlayerName)
{
	if (!Config.bInGameJoinBroadcastEnabled || Config.InGameJoinBroadcast.IsEmpty())
	{
		return;
	}

	FString BroadcastText = Config.InGameJoinBroadcast;
	BroadcastText = BroadcastText.Replace(TEXT("%PlayerName%"), *PlayerName);

	SendGameChatStatusMessage(BroadcastText);
}

void UDiscordBridgeSubsystem::HandleInGameVerify(const FString& PlayerName, const FString& Code)
{
	// Locate the invoking player's controller early so we can send private error
	// feedback via the RCO instead of broadcasting to all players, and also to
	// resolve the EOS PUID used by the whitelist on the success path.
	APlayerController* InvokerPC    = nullptr;
	FString            ResolvedEosPUID;
	if (UWorld* VerWorld = GetWorld())
	{
		for (FConstPlayerControllerIterator It = VerWorld->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PC = It->Get();
			if (!PC || !PC->PlayerState) continue;
			if (PC->PlayerState->GetPlayerName() != PlayerName) continue;
			InvokerPC = PC;
			const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
			if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
				ResolvedEosPUID = NetId.ToString().ToLower();
			break;
		}
	}

	// Helper: send a message to the invoking player only.
	// Falls back to a server-wide broadcast when the player's RCO is unavailable.
	auto SendPrivate = [this, InvokerPC](const FString& Msg, FLinearColor Color)
	{
		if (AFGPlayerController* FGC = Cast<AFGPlayerController>(InvokerPC))
		{
			if (USMLRemoteCallObject* RCO = FGC->GetRemoteCallObjectOfClass<USMLRemoteCallObject>())
			{
				RCO->SendChatMessage(Msg, Color);
				return;
			}
		}
		SendGameChatStatusMessage(Msg);
	};

	const FString* DiscordUserIdPtr = PendingVerifications.Find(Code);
	if (DiscordUserIdPtr && !DiscordUserIdPtr->IsEmpty())
	{
		const FDateTime* ExpiryPtr = PendingVerificationExpiry.Find(Code);
		if (!ExpiryPtr || *ExpiryPtr <= FDateTime::UtcNow())
		{
			// Code expired — clean up and notify the invoking player privately.
			PendingVerifications.Remove(Code);
			PendingVerificationNames.Remove(Code);
			PendingVerificationExpiry.Remove(Code);
			SendPrivate(
				TEXT("[DiscordBridge] Verification code has expired. Please request a new one with /whitelist link."),
				FLinearColor::Yellow);
		}
		else
		{
			const FString DiscordUserId  = *DiscordUserIdPtr;
			const FString* NamePtr       = PendingVerificationNames.Find(Code);
			// Always whitelist using the actual in-game PlayerName of the player who typed
			// /verify. The Discord-submitted name is kept only for the audit log.
			const FString  AuditName     = NamePtr && !NamePtr->IsEmpty() ? *NamePtr : PlayerName;

			PendingVerifications.Remove(Code);
			PendingVerificationNames.Remove(Code);
			PendingVerificationExpiry.Remove(Code);

			// Add using the real in-game player name and resolved EosPUID (may be empty).
			if (FWhitelistManager::AddPlayer(PlayerName, ResolvedEosPUID, TEXT("[Verification]")))
			{
				// Announce success to all players — it is appropriate as a broadcast.
				SendGameChatStatusMessage(FString::Printf(
					TEXT("[DiscordBridge] Account linked! **%s** has been added to the whitelist."),
					*PlayerName));
				PostWhitelistEvent(
					FString::Printf(TEXT("**%s** added via in-game verification (Discord: %s)"),
						*PlayerName, *AuditName),
					PlayerName, TEXT("[Verification]"), 3066993);

				// Confirm to the Discord user who initiated the link.
				if (!WhitelistConfig.WhitelistApprovedDmMessage.IsEmpty())
				{
					const FString DmMsg = WhitelistConfig.WhitelistApprovedDmMessage
						.Replace(TEXT("%PlayerName%"), *PlayerName);
					SendDiscordDM(DiscordUserId, DmMsg);
				}
				else
				{
					SendDiscordDM(DiscordUserId, FString::Printf(
						TEXT("✅ Your in-game account **%s** has been verified and added to the whitelist!"),
						*PlayerName));
				}
			}
			else
			{
				// Already whitelisted — notify the invoking player privately.
				SendPrivate(
					FString::Printf(TEXT("[DiscordBridge] **%s** is already on the whitelist."), *PlayerName),
					FLinearColor::Yellow);
			}
		}
	}
	else
	{
		// Unknown code — notify the invoking player privately.
		SendPrivate(
			TEXT("[DiscordBridge] Unknown or expired verification code."),
			FLinearColor::Red);
	}
}

FString UDiscordBridgeSubsystem::GetDiscordInviteUrl() const
{
	return Config.DiscordInviteUrl;
}

void UDiscordBridgeSubsystem::HandleInGameWhitelistCommand(const FString& SubCommand)
{
	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: In-game whitelist command: '%s'"), *SubCommand);

	FString Response;

	FString Verb, Arg;
	if (!SubCommand.Split(TEXT(" "), &Verb, &Arg, ESearchCase::IgnoreCase))
	{
		Verb = SubCommand.TrimStartAndEnd();
		Arg  = TEXT("");
	}
	Verb = Verb.TrimStartAndEnd().ToLower();
	Arg  = Arg.TrimStartAndEnd();

	if (Verb == TEXT("on"))
	{
		FWhitelistManager::SetEnabled(true, TEXT("[server]"));
		Response = TEXT("Whitelist ENABLED. Only whitelisted players can join.");
		PostWhitelistEvent(TEXT("Whitelist **enabled**"), TEXT(""), TEXT("[server]"), 3447003);
	}
	else if (Verb == TEXT("off"))
	{
		FWhitelistManager::SetEnabled(false, TEXT("[server]"));
		Response = TEXT("Whitelist DISABLED. All players can join freely.");
		PostWhitelistEvent(TEXT("Whitelist **disabled**"), TEXT(""), TEXT("[server]"), 10038562);
	}
	else if (Verb == TEXT("add"))
	{
		if (Arg.IsEmpty())
		{
			Response = TEXT("Usage: /ingamewhitelist add <PlayerName>");
		}
		else if (FWhitelistManager::GetMaxSlots() > 0 &&
		         FWhitelistManager::GetAllEntries().Num() >= FWhitelistManager::GetMaxSlots())
		{
			Response = FString::Printf(TEXT("Whitelist is full (%d/%d slots)."),
				FWhitelistManager::GetAllEntries().Num(), FWhitelistManager::GetMaxSlots());
		}
		else if (FWhitelistManager::AddPlayer(Arg, TEXT(""), TEXT("[server]")))
		{
			Response = FString::Printf(TEXT("%s has been added to the whitelist."), *Arg);
			PostWhitelistEvent(
				FString::Printf(TEXT("**%s** added to the whitelist"), *Arg),
				Arg, TEXT("[server]"), 3066993);
		}
		else
		{
			Response = FString::Printf(TEXT("%s is already on the whitelist."), *Arg);
		}
	}
	else if (Verb == TEXT("remove"))
	{
		if (Arg.IsEmpty())
		{
			Response = TEXT("Usage: /ingamewhitelist remove <PlayerName>");
		}
		else if (FWhitelistManager::RemovePlayer(Arg, TEXT(""), TEXT("[server]")))
		{
			Response = FString::Printf(TEXT("%s has been removed from the whitelist."), *Arg);
			PostWhitelistEvent(
				FString::Printf(TEXT("**%s** removed from the whitelist"), *Arg),
				Arg, TEXT("[server]"), 15158332);
		}
		else
		{
			Response = FString::Printf(TEXT("%s was not on the whitelist."), *Arg);
		}
	}
	else if (Verb == TEXT("list"))
	{
		const TArray<FString> All = FWhitelistManager::GetAll();
		const FString Status = FWhitelistManager::IsEnabled() ? TEXT("ENABLED") : TEXT("disabled");
		if (All.Num() == 0)
		{
			Response = FString::Printf(TEXT("Whitelist is %s. No players listed."), *Status);
		}
		else
		{
			Response = FString::Printf(
				TEXT("Whitelist is %s. Players (%d): %s"),
				*Status, All.Num(), *FString::Join(All, TEXT(", ")));
		}
	}
	else if (Verb == TEXT("status"))
	{
		const FString WhitelistState = FWhitelistManager::IsEnabled()
			? TEXT("ENABLED") : TEXT("disabled");
		Response = FString::Printf(TEXT("Whitelist: %s"), *WhitelistState);
	}
	else if (Verb == TEXT("log"))
	{
		const TArray<FWhitelistAuditEntry> Log = FWhitelistManager::GetAuditLog(5);
		if (Log.Num() == 0)
		{
			Response = TEXT("No whitelist audit log entries.");
		}
		else
		{
			FString LogText = TEXT("Whitelist Audit Log (last 5):\n");
			for (const FWhitelistAuditEntry& E : Log)
			{
				LogText += FString::Printf(TEXT("[%s] %s %s by %s\n"),
					*E.Timestamp.ToString(TEXT("%Y-%m-%d %H:%M")),
					*E.Action, *E.Target,
					E.AdminName.IsEmpty() ? TEXT("system") : *E.AdminName);
			}
			Response = LogText;
		}
	}
	else
	{
		Response = TEXT("Unknown whitelist command. Available: on, off, add <name>, remove <name>, list, status, log.");
	}

	SendGameChatStatusMessage(Response);
}

// ─────────────────────────────────────────────────────────────────────────────
// PostWhitelistEvent
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::PostWhitelistEvent(const FString& Action, const FString& Target,
                                                   const FString& AdminName, int32 Color)
{
	if (WhitelistConfig.WhitelistEventsChannelId.IsEmpty() || Config.BotToken.IsEmpty())
	{
		return;
	}

	const FString Timestamp = FDateTime::UtcNow().ToIso8601();

	// Build embed JSON
	const FString EmbedJson = FString::Printf(
		TEXT("{\"embeds\":[{\"color\":%d,\"title\":\":shield: Whitelist Updated\","
		     "\"description\":\"%s\","
		     "\"footer\":{\"text\":\"By %s\"},"
		     "\"timestamp\":\"%s\"}]}"),
		Color,
		*JsonEscapeStr(Action),
		*JsonEscapeStr(AdminName),
		*Timestamp);

	const FString Url = FString::Printf(
		TEXT("%s/channels/%s/messages"),
		*DiscordApiBase, *WhitelistConfig.WhitelistEventsChannelId);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
	Req->SetURL(Url);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Req->SetContentAsString(EmbedJson);
	Req->OnProcessRequestComplete().BindWeakLambda(this,
		[](FHttpRequestPtr, FHttpResponsePtr Resp, bool bOk)
		{
			if (!bOk || !Resp.IsValid() || Resp->GetResponseCode() < 200 || Resp->GetResponseCode() >= 300)
			{
				UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: PostWhitelistEvent failed."));
			}
		});
	Req->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
// IDiscordBridgeProvider – subscribe / unsubscribe helpers
// These wrap the native multicast delegates so external modules (TicketSystem
// and any other future mod built against the IDiscordBridgeProvider interface)
// can subscribe without including DiscordBridgeSubsystem.h directly.
// ─────────────────────────────────────────────────────────────────────────────

FDelegateHandle UDiscordBridgeSubsystem::SubscribeInteraction(
TFunction<void(const TSharedPtr<FJsonObject>&)> Callback)
{
return OnDiscordInteractionReceived.AddLambda(MoveTemp(Callback));
}

void UDiscordBridgeSubsystem::UnsubscribeInteraction(FDelegateHandle Handle)
{
OnDiscordInteractionReceived.Remove(Handle);
}

FDelegateHandle UDiscordBridgeSubsystem::SubscribeRawMessage(
TFunction<void(const TSharedPtr<FJsonObject>&)> Callback)
{
return OnDiscordRawMessageReceived.AddLambda(MoveTemp(Callback));
}

void UDiscordBridgeSubsystem::UnsubscribeRawMessage(FDelegateHandle Handle)
{
OnDiscordRawMessageReceived.Remove(Handle);
}

// ─────────────────────────────────────────────────────────────────────────────
// /stats command handler
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleStatsCommand(const FString& ResponseChannelId)
{
	if (Config.BotToken.IsEmpty()) return;

	UWorld* World = GetWorld();
	if (!World) { SendMessageToChannel(ResponseChannelId, TEXT("Stats unavailable (no world).")); return; }

	AGameStateBase* GS = World->GetGameState<AGameStateBase>();
	const int32  PlayerCount = GS ? GS->PlayerArray.Num() : 0;

	// Build a plain-text stats block (embeds require a slightly different build path).
	FString Stats = FString::Printf(
		TEXT("**📊 Server Statistics — %s**\n"), *Config.ServerName);
	Stats += FString::Printf(TEXT("Players: %d\n"), PlayerCount);

	TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
	EmbedObj->SetStringField(TEXT("title"), FString::Printf(TEXT("📊 Server Stats – %s"), *Config.ServerName));
	EmbedObj->SetNumberField(TEXT("color"), 3447003); // blue

	TArray<TSharedPtr<FJsonValue>> Fields;
	auto AddField = [&](const FString& Name, const FString& Value, bool bInline = true)
	{
		TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
		F->SetStringField(TEXT("name"),   Name);
		F->SetStringField(TEXT("value"),  Value.IsEmpty() ? TEXT("—") : Value);
		F->SetBoolField  (TEXT("inline"), bInline);
		Fields.Add(MakeShared<FJsonValueObject>(F));
	};

	AddField(TEXT("Players Online"), FString::FromInt(PlayerCount));
	AddField(TEXT("Server"),        Config.ServerName.IsEmpty() ? TEXT("(unnamed)") : Config.ServerName);
	AddField(TEXT("Timestamp"),     FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d %H:%M:%S UTC")), false);

	EmbedObj->SetArrayField(TEXT("fields"), Fields);
	EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetArrayField(TEXT("embeds"),
		TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });

	const FString& TargetChannel = ResponseChannelId.IsEmpty() ? Config.ChannelId : ResponseChannelId;
	SendMessageBodyToChannel(TargetChannel, Body);
}

// ─────────────────────────────────────────────────────────────────────────────
// /playerstats command handler
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandlePlayerStatsCommand(const FString& ResponseChannelId,
                                                        const FString& TargetPlayerName)
{
	if (Config.BotToken.IsEmpty()) return;

	const FString& TargetChannel = ResponseChannelId.IsEmpty() ? Config.ChannelId : ResponseChannelId;

	if (TargetPlayerName.IsEmpty())
	{
		SendMessageToChannel(TargetChannel, TEXT("Usage: /playerstats <player name>"));
		return;
	}

	// Look up per-player stats from the in-memory counters collected by OnPlayerAction.
	TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
	EmbedObj->SetStringField(TEXT("title"),
		FString::Printf(TEXT("📈 Player Stats – %s"), *TargetPlayerName));
	EmbedObj->SetNumberField(TEXT("color"), 10181046); // purple

	TArray<TSharedPtr<FJsonValue>> Fields;
	auto AddField = [&](const FString& Name, const FString& Value, bool bInline = true)
	{
		TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
		F->SetStringField(TEXT("name"),   Name);
		F->SetStringField(TEXT("value"),  Value.IsEmpty() ? TEXT("0") : Value);
		F->SetBoolField  (TEXT("inline"), bInline);
		Fields.Add(MakeShared<FJsonValueObject>(F));
	};

	// Retrieve from the in-memory counters populated by event hooks.
	const FPlayerStatCounters* Counters = PlayerStats.Find(TargetPlayerName);
	if (Counters)
	{
		AddField(TEXT("Buildings Built"),     FString::FromInt(Counters->BuildingsBuilt));
		AddField(TEXT("Items Picked Up"),     FString::FromInt(Counters->ItemsPickedUp));
		AddField(TEXT("Buildings Dismantled"),FString::FromInt(Counters->BuildingsDismantled));
	}
	else
	{
		EmbedObj->SetStringField(TEXT("description"),
			FString::Printf(TEXT("No statistics on record for **%s**."), *TargetPlayerName));
	}

	EmbedObj->SetArrayField(TEXT("fields"), Fields);
	EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetArrayField(TEXT("embeds"),
		TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });
	SendMessageBodyToChannel(TargetChannel, Body);
}

// ─────────────────────────────────────────────────────────────────────────────
// Reaction voting helpers
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::AddJoinReactions(const FString& MessageId,
                                                const FString& ChannelId,
                                                const FString& PlayerName)
{
	if (!Config.bEnableJoinReactionVoting) return;
	if (Config.BotToken.IsEmpty() || ChannelId.IsEmpty() || MessageId.IsEmpty()) return;

	auto AddReaction = [this, MessageId, ChannelId](const FString& Emoji)
	{
		const FString Url = FString::Printf(
			TEXT("%s/channels/%s/messages/%s/reactions/%s/@me"),
			*DiscordApiBase, *ChannelId, *MessageId,
			*FGenericPlatformHttp::UrlEncode(Emoji));

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
		Req->SetURL(Url);
		Req->SetVerb(TEXT("PUT"));
		Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bot %s"), *Config.BotToken));
		Req->ProcessRequest();
	};

	AddReaction(TEXT("👍"));
	AddReaction(TEXT("👎"));

	// Track the vote for automatic kick if threshold is configured.
	if (Config.VoteKickThreshold > 0)
	{
		FPendingVote Vote;
		Vote.MessageId   = MessageId;
		Vote.ChannelId   = ChannelId;
		Vote.PlayerName  = PlayerName;
		Vote.ExpiresAt   = FDateTime::UtcNow() + FTimespan::FromMinutes(Config.VoteWindowMinutes);
		PendingVotes.Add(MessageId, Vote);

		// Schedule a check when the vote window expires.
		// Clamp to a minimum of 1 second so that a zero/negative VoteWindowMinutes
		// misconfiguration does not fire the ticker immediately (before any votes arrive).
		const float DelaySeconds = FMath::Max(1.0f, static_cast<float>(Config.VoteWindowMinutes * 60));
		FTSTicker::FDelegateHandle VoteHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateWeakLambda(this, [this, MessageId](float) -> bool
			{
				CheckVoteResult(MessageId);
				VoteKickTimerHandles.Remove(MessageId); // self-prune after firing
				return false; // one-shot
			}),
			DelaySeconds);
		VoteKickTimerHandles.Add(MessageId, VoteHandle);
	}
}

void UDiscordBridgeSubsystem::CheckVoteResult(const FString& MessageId)
{
	if (Config.VoteKickThreshold <= 0) return;
	const FPendingVote* Vote = PendingVotes.Find(MessageId);
	if (!Vote) return;

	const FString VoteCopy   = Vote->PlayerName;
	const FString ChannelCopy = Vote->ChannelId;
	PendingVotes.Remove(MessageId);

	// Fetch reactions from the Discord REST API to count 👎.
	// limit=100 is the maximum Discord allows per request; for typical
	// VoteKickThreshold values this is more than sufficient.
	const FString Url = FString::Printf(
		TEXT("%s/channels/%s/messages/%s/reactions/%s?limit=100"),
		*DiscordApiBase, *ChannelCopy, *MessageId,
		*FGenericPlatformHttp::UrlEncode(TEXT("👎")));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
	Req->SetURL(Url);
	Req->SetVerb(TEXT("GET"));
	Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bot %s"), *Config.BotToken));

	Req->OnProcessRequestComplete().BindWeakLambda(
		this,
		[this, VoteCopy, Threshold = Config.VoteKickThreshold]
		(FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bOk)
		{
			if (!bOk || !Resp.IsValid()) return;

			TArray<TSharedPtr<FJsonValue>> Reactors;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Resp->GetContentAsString());
			if (FJsonSerializer::Deserialize(Reader, Reactors) &&
			    Reactors.Num() >= Threshold)
			{
				// Exclude the bot's own reaction.
				int32 VoteCount = 0;
				for (const TSharedPtr<FJsonValue>& V : Reactors)
				{
					const TSharedPtr<FJsonObject>* UserObj;
					if (!V->TryGetObject(UserObj)) continue;
					FString UserId;
					(*UserObj)->TryGetStringField(TEXT("id"), UserId);
					if (UserId != BotUserId) ++VoteCount;
				}

				if (VoteCount >= Threshold)
				{
					UE_LOG(LogDiscordBridge, Log,
					       TEXT("DiscordBridge: VoteKick threshold (%d 👎) reached for '%s' — kicking."),
					       Threshold, *VoteCopy);

					if (UWorld* World = GetWorld())
					{
						for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
						{
							APlayerController* PC = It->Get();
							if (!PC || !PC->PlayerState) continue;
							if (PC->PlayerState->GetPlayerName().Equals(VoteCopy, ESearchCase::IgnoreCase))
							{
								PC->ClientWasKicked(FText::FromString(TEXT("Removed by community vote.")));
								if (UNetConnection* Conn = Cast<UNetConnection>(PC->Player))
									Conn->Close();
								break;
							}
						}
					}
				}
			}
		});
	Req->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
// AFK kick ticker
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::StartAfkKickTicker()
{
	if (Config.AfkKickMinutes <= 0) return;
	if (AfkKickTickerHandle.IsValid()) return;

	const float Interval = 30.0f; // check every 30 seconds
	AfkKickTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime) -> bool
		{
			return AfkKickTick(DeltaTime);
		}),
		Interval);
	UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: AFK kick enabled — threshold %d minutes."), Config.AfkKickMinutes);
}

bool UDiscordBridgeSubsystem::AfkKickTick(float /*DeltaTime*/)
{
	if (Config.AfkKickMinutes <= 0) return true;

	UWorld* World = GetWorld();
	if (!World) return true;

	const FDateTime Now        = FDateTime::UtcNow();
	const FTimespan Threshold  = FTimespan::FromMinutes(Config.AfkKickMinutes);

	TArray<APlayerController*> ToKick;
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC || !PC->PlayerState || PC->IsLocalController()) continue;

		const FString Name = PC->PlayerState->GetPlayerName();
		if (Name.IsEmpty()) continue; // PlayerState not yet replicated — skip
		FPlayerAfkState& State = AfkStates.FindOrAdd(Name);

		// Use the building-built counter as the activity indicator.
		const FPlayerStatCounters* Stats = PlayerStats.Find(Name);
		const int32 CurrentBuilt = Stats ? Stats->BuildingsBuilt : 0;

		if (State.LastBuildCount != CurrentBuilt)
		{
			State.LastBuildCount   = CurrentBuilt;
			State.LastActivityTime = Now;
		}

		// Also detect activity via pawn movement so players who are exploring,
		// mining, or otherwise not building are not incorrectly AFK-kicked.
		// This is essential because PlayerStats is not currently updated by any
		// game hook, meaning BuildingsBuilt is always 0 without movement detection.
		if (APawn* Pawn = PC->GetPawn())
		{
			const FVector CurrentLoc = Pawn->GetActorLocation();
			if (State.LastKnownLocation == FVector::ZeroVector)
			{
				// First tick for this player — record location without counting as activity.
				State.LastKnownLocation = CurrentLoc;
			}
			else if (!CurrentLoc.Equals(State.LastKnownLocation, 50.f))
			{
				State.LastKnownLocation = CurrentLoc;
				State.LastActivityTime  = Now;
			}
		}

		if (State.LastActivityTime == FDateTime(0))
			State.LastActivityTime = Now;

		const FTimespan Idle = Now - State.LastActivityTime;
		if (Idle >= Threshold)
		{
			UE_LOG(LogDiscordBridge, Log,
			       TEXT("DiscordBridge: AFK kicking '%s' (idle %.0f minutes)."),
			       *Name, Idle.GetTotalMinutes());
			ToKick.Add(PC);
		}
	}

	for (APlayerController* PC : ToKick)
	{
		const FString Name = PC->PlayerState ? PC->PlayerState->GetPlayerName() : TEXT("(unknown)");
		PC->ClientWasKicked(FText::FromString(Config.AfkKickReason));
		if (UNetConnection* Conn = Cast<UNetConnection>(PC->Player))
			Conn->Close();

		AfkStates.Remove(Name);

		// Notify Discord.
		const FString& NotifChannel = Config.PlayerEventsChannelId.IsEmpty()
			? Config.ChannelId : Config.PlayerEventsChannelId;
		SendMessageToChannel(NotifChannel,
			FString::Printf(TEXT(":zzz: **%s** was kicked for inactivity (AFK)."), *Name));
	}

	return true; // keep ticking
}

// ─────────────────────────────────────────────────────────────────────────────
// Game-world subsystem bindings (game phase + schematic unlock announcements)
// ─────────────────────────────────────────────────────────────────────────────

bool UDiscordBridgeSubsystem::TryBindToGameSubsystems()
{
UWorld* World = GetWorld();
if (!World) return false;

bool bAllBound = true;

// Bind to AFGGamePhaseManager::mOnCurrentGamePhaseUpdated.
if (!bBoundGamePhase)
{
AFGGamePhaseManager* PhaseMgr = AFGGamePhaseManager::Get(World);
if (PhaseMgr)
{
PhaseMgr->mOnCurrentGamePhaseUpdated.AddDynamic(
this, &UDiscordBridgeSubsystem::OnGamePhaseUpdated);
PhaseMgr->mOnGameCompleted.AddDynamic(
this, &UDiscordBridgeSubsystem::OnGameCompleted);
bBoundGamePhase = true;
UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Bound to AFGGamePhaseManager delegates."));
}
else
{
bAllBound = false;
}
}

// Bind to AFGSchematicManager::PurchasedSchematicDelegate.
if (!bBoundSchematic)
{
AFGSchematicManager* SchMgr = AFGSchematicManager::Get(World);
if (SchMgr)
{
SchMgr->PurchasedSchematicDelegate.AddDynamic(
this, &UDiscordBridgeSubsystem::OnSchematicPurchased);
bBoundSchematic = true;
UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Bound to AFGSchematicManager::PurchasedSchematicDelegate."));
}
else
{
bAllBound = false;
}
}

// Bind to UMuteRegistry delegates when bNotifyMuteEvents=true.
if (!bBoundMuteEvents && Config.bNotifyMuteEvents)
{
UGameInstance* GI = GetGameInstance();
UModLoadingLibrary* ModLib = GI ? GI->GetSubsystem<UModLoadingLibrary>() : nullptr;
if (ModLib && !ModLib->IsModLoaded(TEXT("BanChatCommands")))
{
// BanChatCommands is not installed — UMuteRegistry will never become available.
// Mark as done so the deferred-bind ticker is not held open indefinitely.
bBoundMuteEvents = true;
UE_LOG(LogDiscordBridge, Log,
TEXT("DiscordBridge: BanChatCommands not installed — mute event notifications disabled."));
}
else
{
UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
if (MuteReg)
{
MutedEventHandle = MuteReg->OnPlayerMuted.AddLambda(
[this](const FMuteEntry& Entry, bool bIsTimed)
{
NotifyMuteEvent(Entry.PlayerName, Entry.Uid, true, Entry.Reason);
});
UnmutedEventHandle = MuteReg->OnPlayerUnmuted.AddLambda(
[this](const FString& Uid)
{
FString PlayerName;
if (UGameInstance* GI = GetGameInstance())
{
if (UPlayerSessionRegistry* Registry = GI->GetSubsystem<UPlayerSessionRegistry>())
{
FPlayerSessionRecord Record;
if (Registry->FindByUid(Uid, Record) && !Record.DisplayName.IsEmpty())
PlayerName = Record.DisplayName;
}
}
NotifyMuteEvent(PlayerName, Uid, false, TEXT(""));
});
bBoundMuteEvents = true;
UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Bound to UMuteRegistry mute-event delegates."));
}
else
{
bAllBound = false; // BanChatCommands installed but UMuteRegistry not yet ready — keep ticking
}
}
}

return bAllBound; // return true → stop ticker
}

// ─────────────────────────────────────────────────────────────────────────────
// Game phase announcement
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::OnGamePhaseUpdated(UFGGamePhase* NewPhase, bool bSuppressNarrative)
{
if (!bGatewayReady || !NewPhase) return;

const FString PhaseName = NewPhase->mDisplayName.ToString();

UE_LOG(LogDiscordBridge, Log,
       TEXT("DiscordBridge: Game phase updated → %s"), *PhaseName);

const FString& TargetChannel = Config.PhaseEventsChannelId.IsEmpty()
? Config.ChannelId
: Config.PhaseEventsChannelId;

if (TargetChannel.IsEmpty()) return;

if (Config.bUseEmbedsForPhaseEvents)
{
TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
EmbedObj->SetStringField(TEXT("title"), TEXT("🏭 New Game Phase Reached!"));
EmbedObj->SetNumberField(TEXT("color"), 16766720); // gold
EmbedObj->SetStringField(TEXT("description"), FString::Printf(TEXT("**%s**"), *PhaseName));
EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });
SendMessageBodyToChannel(TargetChannel, Body);
}
else
{
TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetStringField(TEXT("content"),
FString::Printf(TEXT("🏭 New game phase reached: **%s**"), *PhaseName));
SendMessageBodyToChannel(TargetChannel, Body);
}
}

void UDiscordBridgeSubsystem::OnGameCompleted(bool /*bSuppressNarrative*/)
{
if (!bGatewayReady) return;

UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Game completed — posting victory announcement."));

const FString& TargetChannel = Config.PhaseEventsChannelId.IsEmpty()
? Config.ChannelId
: Config.PhaseEventsChannelId;

if (TargetChannel.IsEmpty()) return;

TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
EmbedObj->SetStringField(TEXT("title"), TEXT("🎉 Factory Complete!"));
EmbedObj->SetNumberField(TEXT("color"), 16766720);
EmbedObj->SetStringField(TEXT("description"),
TEXT("The factory has reached the final phase! Congratulations!"));
EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });
SendMessageBodyToChannel(TargetChannel, Body);
}

// ─────────────────────────────────────────────────────────────────────────────
// Schematic unlock announcement
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::OnSchematicPurchased(TSubclassOf<UFGSchematic> SchematicClass)
{
if (!bGatewayReady || !SchematicClass) return;

const FString SchematicName = UFGSchematic::GetSchematicDisplayName(SchematicClass).ToString();
const ESchematicType Type   = UFGSchematic::GetType(SchematicClass);

// Map schematic type to a human-readable label.
FString TypeLabel;
switch (Type)
{
case ESchematicType::EST_Milestone:         TypeLabel = TEXT("Milestone");            break;
case ESchematicType::EST_Alternate:         TypeLabel = TEXT("Alternate Recipe");     break;
case ESchematicType::EST_MAM:               TypeLabel = TEXT("MAM Research");         break;
case ESchematicType::EST_HardDrive:         TypeLabel = TEXT("Hard Drive");           break;
case ESchematicType::EST_ResourceSink:      TypeLabel = TEXT("AWESOME Shop");         break;
case ESchematicType::EST_Tutorial:          TypeLabel = TEXT("Tutorial");             break;
case ESchematicType::EST_Customization:     TypeLabel = TEXT("Customizer");           break;
default:                                    TypeLabel = TEXT("Research");             break;
}

UE_LOG(LogDiscordBridge, Log,
       TEXT("DiscordBridge: Schematic purchased → %s (%s)"), *SchematicName, *TypeLabel);

const FString& TargetChannel = Config.SchematicEventsChannelId.IsEmpty()
? (Config.PhaseEventsChannelId.IsEmpty() ? Config.ChannelId : Config.PhaseEventsChannelId)
: Config.SchematicEventsChannelId;

if (TargetChannel.IsEmpty()) return;

if (Config.bUseEmbedsForSchematicEvents)
{
TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
EmbedObj->SetStringField(TEXT("title"), TEXT("🔬 Unlock Achieved!"));
EmbedObj->SetNumberField(TEXT("color"), 3066993); // green

TArray<TSharedPtr<FJsonValue>> Fields;

auto AddField = [&](const FString& Name, const FString& Value)
{
TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
F->SetStringField(TEXT("name"),   Name);
F->SetStringField(TEXT("value"),  Value.IsEmpty() ? TEXT("—") : Value);
F->SetBoolField  (TEXT("inline"), true);
Fields.Add(MakeShared<FJsonValueObject>(F));
};

AddField(TEXT("Name"), SchematicName);
AddField(TEXT("Type"), TypeLabel);

EmbedObj->SetArrayField(TEXT("fields"), Fields);
EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });
SendMessageBodyToChannel(TargetChannel, Body);
}
else
{
TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetStringField(TEXT("content"),
FString::Printf(TEXT("🔬 Unlock achieved: **%s** (%s)"), *SchematicName, *TypeLabel));
SendMessageBodyToChannel(TargetChannel, Body);
}
}

// ─────────────────────────────────────────────────────────────────────────────
// Scheduled announcements
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::StartAnnouncementTicker()
{
	if (Config.AnnouncementIntervalMinutes <= 0) return;
	if (AnnouncementTickerHandle.IsValid()) return;

	AnnouncementAccumulatedSeconds = 0.0f;
	AnnouncementTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime) -> bool
		{
			return AnnouncementTick(DeltaTime);
		}),
		1.0f);

	UE_LOG(LogDiscordBridge, Log,
		TEXT("DiscordBridge: Scheduled announcements enabled — every %d minute(s)."),
		Config.AnnouncementIntervalMinutes);
}

void UDiscordBridgeSubsystem::StartScheduledAnnouncementTickers()
{
	for (const FScheduledAnnouncement& SA : Config.ScheduledAnnouncements)
	{
		if (SA.IntervalMinutes <= 0 || SA.Message.IsEmpty()) continue;

		const FString TargetChannel = SA.ChannelId.IsEmpty() ? Config.ChannelId : SA.ChannelId;
		const FString Msg           = SA.Message;
		const float   Interval      = static_cast<float>(SA.IntervalMinutes) * 60.0f;

		TWeakObjectPtr<UDiscordBridgeSubsystem> WeakThis(this);
		FTSTicker::FDelegateHandle Handle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateLambda([WeakThis, TargetChannel, Msg](float) -> bool
			{
				UDiscordBridgeSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->bGatewayReady) return true;
				TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
				Body->SetStringField(TEXT("content"), Msg);
				Self->SendMessageBodyToChannel(TargetChannel, Body);
				return true;
			}),
			Interval);
		ScheduledAnnouncementHandles.Add(Handle);
	}
}

bool UDiscordBridgeSubsystem::AnnouncementTick(float DeltaTime)
{
	if (Config.AnnouncementIntervalMinutes <= 0) return true;
	if (!bGatewayReady) return true;
	if (Config.AnnouncementMessage.IsEmpty()) return true;

	AnnouncementAccumulatedSeconds += DeltaTime;
	const float IntervalSeconds = Config.AnnouncementIntervalMinutes * 60.0f;
	if (AnnouncementAccumulatedSeconds < IntervalSeconds) return true;

	// Subtract the interval rather than resetting to 0 so overshoot time is
	// preserved across ticks (same pattern as BackupAccumulatedSeconds etc. in
	// BanSystemModule.cpp).  Resetting to 0 would silently discard any extra
	// time beyond the interval boundary, causing cumulative drift.
	AnnouncementAccumulatedSeconds -= IntervalSeconds;

	const FString& Target = Config.AnnouncementChannelId.IsEmpty()
		? Config.ChannelId : Config.AnnouncementChannelId;

	if (!Target.IsEmpty())
	{
		TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
		Body->SetStringField(TEXT("content"), Config.AnnouncementMessage);
		SendMessageBodyToChannel(Target, Body);
	}

	return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Scheduled in-game broadcast messages
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::StartInGameMessageTickers()
{
	if (!InGameMessagesConfig.bEnabled)
	{
		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: In-game broadcast messages are disabled (Enabled=False)."));
		return;
	}

	if (InGameMessagesConfig.Messages.Num() == 0)
	{
		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: No in-game broadcast messages configured."));
		return;
	}

	for (int32 i = 0; i < InGameMessagesConfig.Messages.Num(); ++i)
	{
		const FInGameBroadcastMessage& Entry = InGameMessagesConfig.Messages[i];
		if (Entry.IntervalMinutes <= 0 || Entry.Message.IsEmpty())
			continue;

		const FString Msg        = Entry.Message;
		const FString SenderName = Entry.SenderName;
		const float   Interval   = static_cast<float>(Entry.IntervalMinutes) * 60.0f;

		TWeakObjectPtr<UDiscordBridgeSubsystem> WeakThis(this);
		FTSTicker::FDelegateHandle Handle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateLambda(
				[WeakThis, Msg, SenderName](float) -> bool
				{
					UDiscordBridgeSubsystem* Self = WeakThis.Get();
					if (!Self)
						return false;

					UWorld* World = Self->GetWorld();
					if (!World)
						return true;

					AFGChatManager* ChatManager = AFGChatManager::Get(World);
					if (!ChatManager)
						return true;

					FChatMessageStruct ChatMsg;
					ChatMsg.MessageType   = EFGChatMessageType::CMT_CustomMessage;
					ChatMsg.MessageSender = FText::FromString(SenderName);
					ChatMsg.MessageText   = FText::FromString(Msg);

					ChatManager->BroadcastChatMessage(ChatMsg);
					return true; // keep ticking
				}),
			Interval);

		InGameMessageTickerHandles.Add(Handle);

		UE_LOG(LogDiscordBridge, Log,
		       TEXT("DiscordBridge: In-game broadcast [%d] every %d min sender=\"%s\" message=\"%s\""),
		       i, Entry.IntervalMinutes, *SenderName, *Msg);
	}

	UE_LOG(LogDiscordBridge, Log,
	       TEXT("DiscordBridge: Started %d in-game broadcast message ticker(s)."),
	       InGameMessageTickerHandles.Num());
}

// ─────────────────────────────────────────────────────────────────────────────
// /help / bot info command
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleBotInfoCommand(const FString& ResponseChannelId)
{
if (Config.BotToken.IsEmpty() || ResponseChannelId.IsEmpty()) return;

// ── Embed 1: General / chat commands ─────────────────────────────────────────
{
TSharedPtr<FJsonObject> Embed = MakeShared<FJsonObject>();
Embed->SetStringField(TEXT("title"), TEXT("📖 DiscordBridge — Features & Commands"));
Embed->SetNumberField(TEXT("color"), 3447003); // Discord blurple
Embed->SetStringField(TEXT("description"),
TEXT("This bot bridges **Satisfactory** in-game chat with Discord and provides ")
TEXT("server management via **slash commands**.  Use `/` to see available commands.\n\u200b"));

TArray<TSharedPtr<FJsonValue>> Fields;
auto AddField = [&](const FString& Name, const FString& Value, bool bInline = false)
{
TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
F->SetStringField(TEXT("name"),   Name);
F->SetStringField(TEXT("value"),  Value.IsEmpty() ? TEXT("\u200b") : Value);
F->SetBoolField  (TEXT("inline"), bInline);
Fields.Add(MakeShared<FJsonValueObject>(F));
};

// Chat bridge
AddField(TEXT("💬 Chat Bridge"),
TEXT("In-game player messages are automatically relayed to Discord, and ")
TEXT("Discord messages sent here are shown in-game.\n\u200b"));

// Player / server commands
const FString ServerName = Config.ServerName.IsEmpty() ? TEXT("this server") : Config.ServerName;
AddField(TEXT("🖥️ Server & Player Commands"),
TEXT("`/server`  — Server info embed (name, player count, uptime)\n")
TEXT("`/online`  — Online players list as a rich embed\n")
TEXT("`/players`  — Online player count (plain text)\n")
TEXT("`/stats`  — Server statistics (phases, schematics, buildings)\n")
TEXT("`/player stats <name>`  — Per-player build/item stats\n\u200b"));

// Whitelist
AddField(TEXT("🔒 Whitelist Commands"),
TEXT("`/whitelist on`  — Enable the server whitelist\n")
TEXT("`/whitelist off`  — Disable the server whitelist\n")
TEXT("`/whitelist add <name>`  — Add a player to the whitelist\n")
TEXT("`/whitelist remove <name>`  — Remove a player from the whitelist\n")
TEXT("`/whitelist list`  — Show all whitelisted players\n")
TEXT("`/whitelist status`  — Show whether the whitelist is active\n\u200b"));

// Help itself
AddField(TEXT("ℹ️ Help"),
TEXT("`/help`  — Show this feature/command reference again\n\u200b"));

Embed->SetArrayField(TEXT("fields"), Fields);
Embed->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

// Build footer separately
TSharedPtr<FJsonObject> Footer = MakeShared<FJsonObject>();
Footer->SetStringField(TEXT("text"), FString::Printf(TEXT("DiscordBridge • %s"), *ServerName));
Embed->SetObjectField(TEXT("footer"), Footer);

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(Embed) });
SendMessageBodyToChannel(ResponseChannelId, Body);
}

// ── Embed 2: Admin / Moderator commands (only when BanSystem is active) ──────
{
TSharedPtr<FJsonObject> Embed = MakeShared<FJsonObject>();
Embed->SetStringField(TEXT("title"), TEXT("🛡️ Moderation Commands (BanSystem)"));
Embed->SetNumberField(TEXT("color"), 15158332); // red
Embed->SetStringField(TEXT("description"),
TEXT("The following slash commands require the **Admin** or **Moderator** Discord role ")
TEXT("configured in `DefaultBanBridge.ini`.\n\u200b"));

TArray<TSharedPtr<FJsonValue>> Fields;
auto AddField = [&](const FString& Name, const FString& Value, bool bInline = false)
{
TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
F->SetStringField(TEXT("name"),   Name);
F->SetStringField(TEXT("value"),  Value.IsEmpty() ? TEXT("\u200b") : Value);
F->SetBoolField  (TEXT("inline"), bInline);
Fields.Add(MakeShared<FJsonValueObject>(F));
};

// Admin — ban management
AddField(TEXT("⚔️ Admin — Ban Management"),
TEXT("`/ban add <player> [reason]`  — Permanently ban a player\n")
TEXT("`/ban temp <player> <duration> [reason]`  — Temporary ban (e.g. `1d`, `2h`)\n")
TEXT("`/ban remove <uid>`  — Unban by EOS Product User ID\n")
TEXT("`/ban removename <name>`  — Unban by last-seen in-game name\n")
TEXT("`/ban byname <name> [reason]`  — Ban by in-game name\n")
TEXT("`/ban check <player>`  — Check if a player is currently banned\n")
TEXT("`/ban reason <player> <reason>`  — Update the reason for an active ban\n")
TEXT("`/ban list [page]`  — List active bans (paginated)\n")
TEXT("`/ban extend <player> <duration>`  — Extend a temporary ban\n")
TEXT("`/ban duration <player>`  — Show remaining ban duration\n\u200b"),
false);

// Admin — server links, history, warns, notes
AddField(TEXT("📋 Admin — History, Warnings & Notes"),
TEXT("`/player history <query>`  — Full join/ban history for a player\n")
TEXT("`/warn add <player> <reason>`  — Issue a warning to a player\n")
TEXT("`/warn list <player>`  — List all warnings for a player\n")
TEXT("`/warn clearall <player>`  — Clear all warnings for a player\n")
TEXT("`/warn clearone <id>`  — Remove a single warning by its ID\n")
TEXT("`/player note <player> <text>`  — Add a staff note to a player's record\n")
TEXT("`/player notes <player>`  — Show all staff notes for a player\n")
TEXT("`/player reason <uid>`  — Show the ban reason for a player\n\u200b"),
false);

// Admin — server links, config
AddField(TEXT("⚙️ Admin — Server Links & Config"),
TEXT("`/ban link <uid1> <uid2>`  — Link two UIDs so a ban blocks both\n")
TEXT("`/ban unlink <uid1> <uid2>`  — Remove a UID link\n")
TEXT("`/mod mutereason <player> <reason>`  — Update the reason on an active mute\n")
TEXT("`/admin reloadconfig`  — Hot-reload BanSystem / BanChatCommands config\n")
TEXT("`/admin panel`  — Post an interactive panel embed with kick/ban/mute/warn buttons\n")
TEXT("`/admin clearchat [reason]`  — Flush in-game chat and notify staff\n\u200b"),
false);

// Moderator commands
AddField(TEXT("👮 Moderator Commands"),
TEXT("`/mod kick <player> [reason]`  — Kick a player from the server\n")
TEXT("`/mod modban <player> [reason]`  — Permanent ban (moderator-level)\n")
TEXT("`/mod mute <player> [reason]`  — Mute a player in-game\n")
TEXT("`/mod unmute <player>`  — Unmute a player (indefinite mute)\n")
TEXT("`/mod tempmute <player> <duration> [reason]`  — Temporary mute\n")
TEXT("`/mod tempunmute <player>`  — Lift a timed mute early\n")
TEXT("`/mod mutecheck <player>`  — Check if a player is muted\n")
TEXT("`/mod mutelist`  — List all currently muted players\n")
TEXT("`/mod announce <message>`  — Broadcast a message to all in-game players\n")
TEXT("`/mod stafflist`  — List configured admins and moderators\n")
TEXT("`/mod staffchat <message>`  — Send a message to the staff Discord channel\n")
TEXT("`/mod freeze <player>`  — Toggle movement freeze for a player (admin)\n\u200b"),
false);

Embed->SetArrayField(TEXT("fields"), Fields);
Embed->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

TSharedPtr<FJsonObject> Footer = MakeShared<FJsonObject>();
Footer->SetStringField(TEXT("text"), TEXT("Commands require AdminRoleId / ModeratorRoleId in DefaultBanBridge.ini"));
Embed->SetObjectField(TEXT("footer"), Footer);

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(Embed) });
SendMessageBodyToChannel(ResponseChannelId, Body);
}
}

// ─────────────────────────────────────────────────────────────────────────────
// /server command
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleServerCommand(const FString& ResponseChannelId)
{
if (Config.BotToken.IsEmpty()) return;

UWorld* World = GetWorld();
AGameStateBase* GS = World ? World->GetGameState<AGameStateBase>() : nullptr;
const int32 PlayerCount = GS ? GS->PlayerArray.Num() : 0;

TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
EmbedObj->SetStringField(TEXT("title"),
FString::Printf(TEXT("🖥️ Server: %s"),
Config.ServerName.IsEmpty() ? TEXT("(unnamed)") : *Config.ServerName));
EmbedObj->SetNumberField(TEXT("color"), 5793266); // teal

TArray<TSharedPtr<FJsonValue>> Fields;
auto AddField = [&](const FString& Name, const FString& Value, bool bInline = true)
{
TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
F->SetStringField(TEXT("name"),   Name);
F->SetStringField(TEXT("value"),  Value.IsEmpty() ? TEXT("—") : Value);
F->SetBoolField  (TEXT("inline"), bInline);
Fields.Add(MakeShared<FJsonValueObject>(F));
};

AddField(TEXT("Players Online"), FString::FromInt(PlayerCount));
AddField(TEXT("Status"),         TEXT("✅ Online"));
AddField(TEXT("Time (UTC)"),     FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d %H:%M:%S")), false);

EmbedObj->SetArrayField(TEXT("fields"), Fields);
EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });
SendMessageBodyToChannel(ResponseChannelId, Body);
}

// ─────────────────────────────────────────────────────────────────────────────
// /online command
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleOnlineCommand(const FString& ResponseChannelId)
{
if (Config.BotToken.IsEmpty()) return;

UWorld* World = GetWorld();
AGameStateBase* GS = World ? World->GetGameState<AGameStateBase>() : nullptr;

if (!GS || GS->PlayerArray.Num() == 0)
{
SendMessageToChannel(ResponseChannelId, TEXT("👤 No players are currently online."));
return;
}

FString PlayerList;
int32 Idx = 1;
int32 NonNullCount = 0;
for (APlayerState* PS : GS->PlayerArray)
{
if (!PS) continue;
PlayerList += FString::Printf(TEXT("%d. **%s**\n"), Idx++, *PS->GetPlayerName());
++NonNullCount;
}

TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
EmbedObj->SetStringField(TEXT("title"),
FString::Printf(TEXT("👥 Online Players (%d)"), NonNullCount));
EmbedObj->SetNumberField(TEXT("color"), 3066993); // green
EmbedObj->SetStringField(TEXT("description"), PlayerList);
EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });
SendMessageBodyToChannel(ResponseChannelId, Body);
}

// ─────────────────────────────────────────────────────────────────────────────
// Mute event notifications
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::NotifyMuteEvent(const FString& PlayerName, const FString& Uid,
                                               bool bIsMuted, const FString& Reason)
{
if (!Config.bNotifyMuteEvents || !bGatewayReady) return;

const FString& Target = !Config.ModeratorChannelId.IsEmpty() ? Config.ModeratorChannelId
: !Config.BanEventsChannelId.IsEmpty() ? Config.BanEventsChannelId
: Config.ChannelId;

if (Target.IsEmpty()) return;

const FString Emoji  = bIsMuted ? TEXT("🔇") : TEXT("🔊");
const FString Action = bIsMuted ? TEXT("Muted") : TEXT("Unmuted");
const int32 Colour = bIsMuted ? 15158332 : 3066993; // red / green

TSharedPtr<FJsonObject> EmbedObj = MakeShared<FJsonObject>();
EmbedObj->SetStringField(TEXT("title"),
FString::Printf(TEXT("%s Player %s: %s"), *Emoji, *Action, *PlayerName));
EmbedObj->SetNumberField(TEXT("color"), Colour);
if (bIsMuted && !Reason.IsEmpty())
EmbedObj->SetStringField(TEXT("description"),
FString::Printf(TEXT("**Reason:** %s"), *Reason));
EmbedObj->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
Body->SetArrayField(TEXT("embeds"),
TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(EmbedObj) });
SendMessageBodyToChannel(Target, Body);
}

// ─────────────────────────────────────────────────────────────────────────────
// Slash command registration
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::RegisterSlashCommands()
{
// The Discord bulk-overwrite endpoint replaces ALL guild application commands
// atomically.  We register all command groups here.
const FString Url = FString::Printf(
TEXT("%s/applications/%s/guilds/%s/commands"),
*DiscordApiBase, *BotUserId, *GuildId);

// ── Helpers ──────────────────────────────────────────────────────────────────

// Build a command option JSON value.  Type: 3=STRING, 4=INTEGER, 5=BOOLEAN.
// When bAutocomplete is true the option enables Discord's type-ahead suggestions.
auto MakeOpt = [](const FString& Name, const FString& Desc, int32 Type,
                  bool bRequired, bool bAutocomplete = false)
	-> TSharedPtr<FJsonValue>
{
	TSharedPtr<FJsonObject> O = MakeShared<FJsonObject>();
	O->SetStringField(TEXT("name"),        Name);
	O->SetStringField(TEXT("description"), Desc);
	O->SetNumberField(TEXT("type"),        Type);
	if (bRequired)     O->SetBoolField(TEXT("required"),     true);
	if (bAutocomplete) O->SetBoolField(TEXT("autocomplete"), true);
	return MakeShared<FJsonValueObject>(O);
};

// Build a SUB_COMMAND JSON value (type 1).
auto MakeSub = [](const FString& Name, const FString& Desc,
                  TArray<TSharedPtr<FJsonValue>> Opts = {}) -> TSharedPtr<FJsonValue>
{
	TSharedPtr<FJsonObject> S = MakeShared<FJsonObject>();
	S->SetNumberField(TEXT("type"),        1); // SUB_COMMAND
	S->SetStringField(TEXT("name"),        Name);
	S->SetStringField(TEXT("description"), Desc);
	if (!Opts.IsEmpty())
		S->SetArrayField(TEXT("options"), Opts);
	return MakeShared<FJsonValueObject>(S);
};

// Build a top-level CHAT_INPUT (type 1) command.
auto MakeCmd = [](const FString& Name, const FString& Desc,
                  TArray<TSharedPtr<FJsonValue>> Opts = {}) -> TSharedPtr<FJsonValue>
{
	TSharedPtr<FJsonObject> C = MakeShared<FJsonObject>();
	C->SetNumberField(TEXT("type"),        1); // CHAT_INPUT
	C->SetStringField(TEXT("name"),        Name);
	C->SetStringField(TEXT("description"), Desc);
	if (!Opts.IsEmpty())
		C->SetArrayField(TEXT("options"), Opts);
	return MakeShared<FJsonValueObject>(C);
};

// Shorthand lambdas for common option types.
auto Str  = [&](const FString& N, const FString& D) { return MakeOpt(N, D, 3, true);  };
auto StrO = [&](const FString& N, const FString& D) { return MakeOpt(N, D, 3, false); };
auto Int  = [&](const FString& N, const FString& D) { return MakeOpt(N, D, 4, true);  };
auto IntO = [&](const FString& N, const FString& D) { return MakeOpt(N, D, 4, false); };
// Autocomplete-enabled string options (for player name suggestions).
auto StrAC  = [&](const FString& N, const FString& D) { return MakeOpt(N, D, 3, true,  true); };
auto StrOAC = [&](const FString& N, const FString& D) { return MakeOpt(N, D, 3, false, true); };

TArray<TSharedPtr<FJsonValue>> Commands;

// ── Standalone public commands ───────────────────────────────────────────────
Commands.Add(MakeCmd(TEXT("players"), TEXT("Show the list of online players.")));
Commands.Add(MakeCmd(TEXT("stats"),   TEXT("Show server statistics.")));
Commands.Add(MakeCmd(TEXT("server"),  TEXT("Show server info embed.")));
Commands.Add(MakeCmd(TEXT("online"),  TEXT("Show online players as a rich embed.")));
Commands.Add(MakeCmd(TEXT("help"),    TEXT("Show the bot command reference.")));

// ── /ban – ban management (admin) ────────────────────────────────────────────
Commands.Add(MakeCmd(TEXT("ban"), TEXT("Ban management commands."),
{
	MakeSub(TEXT("add"),        TEXT("Permanently ban a player."),
		{ StrAC(TEXT("player"), TEXT("Name, EOS:<puid>, or IP:<addr>")), StrO(TEXT("reason"), TEXT("Ban reason")) }),
	MakeSub(TEXT("temp"),       TEXT("Temporarily ban a player."),
		{ StrAC(TEXT("player"), TEXT("Name, EOS:<puid>, or IP:<addr>")), Str(TEXT("duration"), TEXT("Duration: 30m 2h 1d 1w")), StrO(TEXT("reason"), TEXT("Ban reason")) }),
	MakeSub(TEXT("remove"),     TEXT("Remove a ban by player UID."),
		{ StrAC(TEXT("uid"),  TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("removename"), TEXT("Remove a ban by display name."),
		{ StrAC(TEXT("name"),   TEXT("Player display name")) }),
	MakeSub(TEXT("byname"),     TEXT("Ban a player by display name."),
		{ StrAC(TEXT("name"),   TEXT("Player display name")), StrO(TEXT("reason"), TEXT("Ban reason")) }),
	MakeSub(TEXT("check"),      TEXT("Check a player's ban status."),
		{ StrAC(TEXT("player"), TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("reason"),     TEXT("Edit the reason on an active ban."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")), Str(TEXT("new_reason"), TEXT("New ban reason")) }),
	MakeSub(TEXT("list"),       TEXT("List all active bans (10 per page)."),
		{ IntO(TEXT("page"),  TEXT("Page number (default 1)")) }),
	MakeSub(TEXT("extend"),     TEXT("Extend a temporary ban."),
		{ StrAC(TEXT("player"), TEXT("Name, EOS:<puid>, or IP:<addr>")), Str(TEXT("duration"), TEXT("Extra time: 30m 2h 1d")) }),
	MakeSub(TEXT("duration"),   TEXT("Show remaining time on a temp ban."),
		{ StrAC(TEXT("player"), TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("link"),       TEXT("Link two UIDs so a ban blocks both."),
		{ Str(TEXT("uid1"),   TEXT("First compound UID")), Str(TEXT("uid2"), TEXT("Second compound UID")) }),
	MakeSub(TEXT("unlink"),     TEXT("Remove a link between two UIDs."),
		{ Str(TEXT("uid1"),   TEXT("First compound UID")), Str(TEXT("uid2"), TEXT("Second compound UID")) }),
	MakeSub(TEXT("schedule"),   TEXT("Schedule a delayed ban."),
		{ StrAC(TEXT("player"),       TEXT("Name, EOS:<puid>, or IP:<addr>")),
		  Str(TEXT("delay"),        TEXT("Delay before ban: 30m 2h")),
		  StrO(TEXT("ban_duration"),TEXT("Ban length (omit for permanent)")),
		  StrO(TEXT("reason"),      TEXT("Ban reason")) }),
	MakeSub(TEXT("quick"),      TEXT("Apply a pre-defined ban template."),
		{ Str(TEXT("template"), TEXT("Template slug")), StrAC(TEXT("player"), TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("bulk"),       TEXT("Ban multiple players at once."),
		{ Str(TEXT("players"), TEXT("Space-separated UIDs")), Str(TEXT("reason"), TEXT("Reason for all targets")) }),
}));

// ── /warn – warning management (admin) ───────────────────────────────────────
Commands.Add(MakeCmd(TEXT("warn"), TEXT("Warning management commands."),
{
	MakeSub(TEXT("add"),      TEXT("Issue a formal warning."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")), Str(TEXT("reason"), TEXT("Warning reason")) }),
	MakeSub(TEXT("list"),     TEXT("List all warnings for a player."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("clearall"), TEXT("Remove all warnings for a player."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("clearone"), TEXT("Remove a single warning by ID."),
		{ Int(TEXT("warning_id"), TEXT("Warning integer ID")) }),
}));

// ── /mod – moderator commands (mod or admin) ─────────────────────────────────
Commands.Add(MakeCmd(TEXT("mod"), TEXT("Moderation commands (moderator or admin)."),
{
	MakeSub(TEXT("kick"),       TEXT("Kick a connected player."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")), StrO(TEXT("reason"), TEXT("Kick reason")) }),
	MakeSub(TEXT("modban"),     TEXT("Temporarily ban a player (mod action)."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")), StrO(TEXT("reason"), TEXT("Ban reason")) }),
	MakeSub(TEXT("mute"),       TEXT("Mute a player's in-game chat."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")),
		  IntO(TEXT("minutes"),   TEXT("Duration in minutes (0=indefinite)")),
		  StrO(TEXT("reason"),    TEXT("Mute reason")) }),
	MakeSub(TEXT("unmute"),     TEXT("Lift a mute from a player."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("tempmute"),   TEXT("Apply a timed mute."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")), Str(TEXT("duration"), TEXT("Duration: 30m, 2h, 1d, 1w or plain minutes")), StrO(TEXT("reason"), TEXT("Reason for the mute")) }),
	MakeSub(TEXT("tempunmute"), TEXT("Lift a timed mute."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("mutecheck"),  TEXT("Check mute status and expiry."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("mutelist"),   TEXT("List all currently muted players.")),
	MakeSub(TEXT("mutereason"), TEXT("Update the reason on an active mute."),
		{ StrAC(TEXT("player"),     TEXT("Name, EOS:<puid>, or IP:<addr>")), Str(TEXT("new_reason"), TEXT("New mute reason")) }),
	MakeSub(TEXT("announce"),   TEXT("Broadcast a message to in-game players."),
		{ Str(TEXT("message"),    TEXT("Message to broadcast")) }),
	MakeSub(TEXT("stafflist"),  TEXT("Show online staff members.")),
	MakeSub(TEXT("staffchat"),  TEXT("Send a message to online staff only."),
		{ Str(TEXT("message"),    TEXT("Staff-only message")) }),
	MakeSub(TEXT("freeze"),     TEXT("Toggle movement freeze for a player (admin only)."),
		{ StrAC(TEXT("player"),   TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
}));

// ── /player – player information commands (admin) ────────────────────────────
Commands.Add(MakeCmd(TEXT("player"), TEXT("Player information and note commands."),
{
	MakeSub(TEXT("history"),    TEXT("Show known session records for a player."),
		{ StrAC(TEXT("query"),   TEXT("Player name, EOS PUID, or IP address")) }),
	MakeSub(TEXT("note"),       TEXT("Add a private admin note."),
		{ StrAC(TEXT("player"),  TEXT("Name, EOS:<puid>, or IP:<addr>")), Str(TEXT("text"), TEXT("Note text")) }),
	MakeSub(TEXT("notes"),      TEXT("List all admin notes for a player."),
		{ StrAC(TEXT("player"),  TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("reason"),     TEXT("Show the ban reason for a UID."),
		{ Str(TEXT("uid"),     TEXT("Player compound UID")) }),
	MakeSub(TEXT("playtime"),   TEXT("Show a player's server playtime."),
		{ StrAC(TEXT("player"),  TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
	MakeSub(TEXT("stats"),      TEXT("Show per-player build and item stats."),
		{ StrAC(TEXT("name"),    TEXT("Player display name")) }),
	MakeSub(TEXT("reputation"), TEXT("Show a player's reputation score."),
		{ StrAC(TEXT("player"),  TEXT("Name, EOS:<puid>, or IP:<addr>")) }),
}));

// ── /appeal – ban appeal management (admin) ──────────────────────────────────
Commands.Add(MakeCmd(TEXT("appeal"), TEXT("Ban appeal management commands."),
{
	MakeSub(TEXT("list"),    TEXT("List pending ban appeals.")),
	MakeSub(TEXT("dismiss"), TEXT("Delete a ban appeal."),
		{ Int(TEXT("id"), TEXT("Appeal integer ID")) }),
	MakeSub(TEXT("approve"), TEXT("Approve an appeal and unban the player."),
		{ Int(TEXT("id"), TEXT("Appeal integer ID")) }),
	MakeSub(TEXT("deny"),    TEXT("Deny an appeal without unbanning."),
		{ Int(TEXT("id"), TEXT("Appeal integer ID")) }),
}));

// ── /admin – admin utility commands ──────────────────────────────────────────
Commands.Add(MakeCmd(TEXT("admin"), TEXT("Admin utility commands."),
{
	MakeSub(TEXT("say"),          TEXT("Broadcast an admin message in-game."),
		{ Str(TEXT("message"),  TEXT("Message to broadcast")) }),
	MakeSub(TEXT("poll"),         TEXT("Create a poll in this channel."),
		{ Str(TEXT("question"), TEXT("Poll question")),
		  Str(TEXT("options"),  TEXT("Pipe-separated options: Yes|No|Maybe")) }),
	MakeSub(TEXT("reloadconfig"), TEXT("Reload the bridge configuration from disk.")),
	MakeSub(TEXT("panel"),        TEXT("Post an interactive admin panel with action buttons.")),
	MakeSub(TEXT("clearchat"),    TEXT("Flush in-game chat and notify staff."),
		{ StrO(TEXT("reason"),    TEXT("Reason for clearing chat")) }),
}));

// ── /whitelist – whitelist management (role-restricted) ──────────────────────
Commands.Add(MakeCmd(TEXT("whitelist"), TEXT("Whitelist management commands."),
{
	MakeSub(TEXT("on"),     TEXT("Enable the server whitelist.")),
	MakeSub(TEXT("off"),    TEXT("Disable the server whitelist.")),
	MakeSub(TEXT("add"),    TEXT("Add a player to the whitelist."),
		{ StrAC(TEXT("name"),       TEXT("In-game player name")),
		  StrO(TEXT("group"),     TEXT("Group name (optional)")),
		  StrO(TEXT("duration"),  TEXT("Expiry duration: 7d 1w (optional)")) }),
	MakeSub(TEXT("remove"), TEXT("Remove a player from the whitelist."),
		{ StrAC(TEXT("name"),       TEXT("In-game player name")) }),
	MakeSub(TEXT("list"),   TEXT("Show all whitelisted players."),
		{ StrO(TEXT("group"),     TEXT("Filter by group (optional)")) }),
	MakeSub(TEXT("status"), TEXT("Show whether the whitelist is active.")),
	MakeSub(TEXT("apply"),  TEXT("Submit a whitelist application."),
		{ Str(TEXT("name"),       TEXT("Your in-game player name")) }),
	MakeSub(TEXT("link"),   TEXT("Link your Discord account via a verification code."),
		{ Str(TEXT("code"),       TEXT("Verification code")) }),
	MakeSub(TEXT("search"), TEXT("Search the whitelist by name."),
		{ StrAC(TEXT("query"),      TEXT("Partial name to search for")) }),
}));

// ── /ticket – ticket management (support role) ───────────────────────────────
Commands.Add(MakeCmd(TEXT("ticket"), TEXT("Support ticket management commands."),
{
	MakeSub(TEXT("panel"),    TEXT("Post the ticket selection panel to the configured channel.")),
	MakeSub(TEXT("list"),     TEXT("List all open tickets.")),
	MakeSub(TEXT("assign"),   TEXT("Claim/assign a ticket to a staff member."),
		{ Str(TEXT("user"), TEXT("@mention of the staff member")) }),
	MakeSub(TEXT("claim"),    TEXT("Claim this ticket for yourself.")),
	MakeSub(TEXT("unclaim"),  TEXT("Release your claim on this ticket.")),
	MakeSub(TEXT("transfer"), TEXT("Transfer this ticket to another staff member."),
		{ Str(TEXT("user"), TEXT("@mention of the target staff member")) }),
	MakeSub(TEXT("priority"), TEXT("Set the priority level of this ticket."),
		{ Str(TEXT("level"), TEXT("Priority level (low, normal, high, urgent)")) }),
	MakeSub(TEXT("macro"),    TEXT("Apply a saved macro/template response."),
		{ Str(TEXT("name"), TEXT("Macro name")) }),
	MakeSub(TEXT("macros"),   TEXT("List all available macros.")),
	MakeSub(TEXT("stats"),    TEXT("Show ticket statistics.")),
	MakeSub(TEXT("report"),   TEXT("Submit a ticket report/feedback."),
		{ Str(TEXT("text"), TEXT("Report text")) }),
	MakeSub(TEXT("tag"),      TEXT("Add a tag to this ticket."),
		{ Str(TEXT("tag"), TEXT("Tag name")) }),
	MakeSub(TEXT("untag"),    TEXT("Remove a tag from this ticket."),
		{ Str(TEXT("tag"), TEXT("Tag name")) }),
	MakeSub(TEXT("tags"),     TEXT("List all tags on this ticket.")),
	MakeSub(TEXT("note"),     TEXT("Add a staff-only note to this ticket."),
		{ Str(TEXT("text"), TEXT("Note text")) }),
	MakeSub(TEXT("notes"),    TEXT("List all staff notes on this ticket.")),
	MakeSub(TEXT("escalate"), TEXT("Escalate this ticket to a senior staff member.")),
	MakeSub(TEXT("remind"),   TEXT("Set a reminder for this ticket."),
		{ Str(TEXT("text"), TEXT("Reminder text")) }),
	MakeSub(TEXT("blacklist"),     TEXT("Blacklist a user from creating tickets."),
		{ Str(TEXT("user"), TEXT("User ID to blacklist")) }),
	MakeSub(TEXT("unblacklist"),   TEXT("Remove a user from the ticket blacklist."),
		{ Str(TEXT("user"), TEXT("User ID to unblacklist")) }),
	MakeSub(TEXT("blacklistlist"), TEXT("List all blacklisted users.")),
	MakeSub(TEXT("merge"),    TEXT("Merge another ticket into this one."),
		{ Str(TEXT("ticket_id"), TEXT("Channel ID of the ticket to merge")) }),
}));

// Serialize the commands array and send to Discord.
const int32 NumCommands = Commands.Num();
FString BodyStr;
{
	TSharedRef<TJsonWriter<>> W = TJsonWriterFactory<>::Create(&BodyStr);
	if (!FJsonSerializer::Serialize(Commands, W))
	{
		UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in RegisterSlashCommands."));
		return;
	}
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
	FHttpModule::Get().CreateRequest();
Request->SetURL(Url);
Request->SetVerb(TEXT("PUT"));
Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bot %s"), *Config.BotToken));
Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
Request->SetContentAsString(BodyStr);
Request->OnProcessRequestComplete().BindLambda(
	[NumCommands](FHttpRequestPtr, FHttpResponsePtr Resp, bool bSuccess)
	{
		if (bSuccess && Resp.IsValid() &&
			(Resp->GetResponseCode() == 200 || Resp->GetResponseCode() == 201))
		{
			UE_LOG(LogDiscordBridge, Log,
				TEXT("DiscordBridge: Slash commands registered successfully (%d commands)."),
				NumCommands);
		}
		else
		{
			UE_LOG(LogDiscordBridge, Warning,
				TEXT("DiscordBridge: Slash command registration failed (HTTP %d): %s"),
				Resp.IsValid() ? Resp->GetResponseCode() : 0,
				Resp.IsValid() ? *Resp->GetContentAsString() : TEXT("no response"));
		}
	});
Request->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
// Slash command helpers
// ─────────────────────────────────────────────────────────────────────────────

FString UDiscordBridgeSubsystem::GetSlashOptionString(
const TArray<TSharedPtr<FJsonValue>>* Options,
const FString& Name)
{
if (!Options) return FString();
for (const TSharedPtr<FJsonValue>& Opt : *Options)
{
const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
if (!Opt->TryGetObject(ObjPtr) || !ObjPtr) continue;
FString OptName;
if (!(*ObjPtr)->TryGetStringField(TEXT("name"), OptName) ||
    !OptName.Equals(Name, ESearchCase::IgnoreCase)) continue;
// Try string value first (Discord sends INTEGER values as numbers).
FString StrVal;
if ((*ObjPtr)->TryGetStringField(TEXT("value"), StrVal)) return StrVal;
double NumVal = 0.0;
if ((*ObjPtr)->TryGetNumberField(TEXT("value"), NumVal))
return FString::Printf(TEXT("%lld"), static_cast<int64>(NumVal));
return FString();
}
return FString();
}

// ─────────────────────────────────────────────────────────────────────────────
// Autocomplete interaction handler
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleAutocompleteInteraction(
	const TSharedPtr<FJsonObject>& DataObj)
{
	// Extract interaction credentials.
	FString InteractionId, InteractionToken;
	DataObj->TryGetStringField(TEXT("id"),    InteractionId);
	DataObj->TryGetStringField(TEXT("token"), InteractionToken);
	if (InteractionId.IsEmpty() || InteractionToken.IsEmpty()) return;

	// Drill into data → options to find the focused option.  Discord sends
	// the current option tree; the one being typed has "focused": true.
	// For commands with subcommands the structure is:
	//   data.options[0] (subcommand, type 1)  → .options[] (leaf options)
	const TSharedPtr<FJsonObject>* CmdDataPtr = nullptr;
	if (!DataObj->TryGetObjectField(TEXT("data"), CmdDataPtr) || !CmdDataPtr) return;

	const TArray<TSharedPtr<FJsonValue>>* TopOptions = nullptr;
	(*CmdDataPtr)->TryGetArrayField(TEXT("options"), TopOptions);
	if (!TopOptions) return;

	// Resolve the leaf options array — walk into sub-command if present.
	const TArray<TSharedPtr<FJsonValue>>* LeafOptions = TopOptions;
	{
		const TSharedPtr<FJsonObject>* FirstOpt = nullptr;
		if (!TopOptions->IsEmpty() && (*TopOptions)[0]->TryGetObject(FirstOpt) && FirstOpt)
		{
			double OptType = 0;
			(*FirstOpt)->TryGetNumberField(TEXT("type"), OptType);
			if (static_cast<int32>(OptType) == 1) // SUB_COMMAND
			{
				const TArray<TSharedPtr<FJsonValue>>* SubOpts = nullptr;
				if ((*FirstOpt)->TryGetArrayField(TEXT("options"), SubOpts) && SubOpts)
					LeafOptions = SubOpts;
			}
		}
	}

	// Find the focused option and extract the partial typed value.
	FString FocusedValue;
	for (const TSharedPtr<FJsonValue>& Opt : *LeafOptions)
	{
		const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
		if (!Opt->TryGetObject(ObjPtr) || !ObjPtr) continue;
		bool bFocused = false;
		(*ObjPtr)->TryGetBoolField(TEXT("focused"), bFocused);
		if (bFocused)
		{
			(*ObjPtr)->TryGetStringField(TEXT("value"), FocusedValue);
			break;
		}
	}

	// ── Build the choices array from the PlayerSessionRegistry ─────────────
	// Choices cover three identifier types that the command handlers accept:
	//   • Display name  (value = "PlayerName")
	//   • EOS compound UID (value = "EOS:<32hex>")
	//   • IP compound UID  (value = "IP:<address>")
	// Routing depends on what the admin has started typing:
	//   - Empty           → recent players by display name
	//   - Starts "EOS:"   → EOS UID substring search
	//   - Starts "IP:" or IP fragment (digits + dots)
	//                     → IP substring search via FindByIp()
	//   - Otherwise       → name search, with EOS/IP alternatives for each match

	TArray<TSharedPtr<FJsonValue>> Choices;

	UGameInstance* GI = GetGameInstance();
	UPlayerSessionRegistry* Registry = GI ? GI->GetSubsystem<UPlayerSessionRegistry>() : nullptr;

	if (Registry)
	{
		const FString FocusedLower = FocusedValue.ToLower();

		// Helper: append one choice (name capped at Discord's 100-char limit).
		auto AddChoice = [&Choices](const FString& Label, const FString& Value)
		{
			if (Choices.Num() >= 25) return; // Discord maximum
			TSharedPtr<FJsonObject> Choice = MakeShared<FJsonObject>();
			Choice->SetStringField(TEXT("name"),  Label.Left(100));
			Choice->SetStringField(TEXT("value"), Value);
			Choices.Add(MakeShared<FJsonValueObject>(Choice));
		};

		// Helper: true when the string looks like a partial IPv4 address
		// (only decimal digits and dots, at least one dot).
		auto IsIpFragment = [](const FString& S) -> bool
		{
			if (S.IsEmpty()) return false;
			bool bHasDot = false;
			for (TCHAR C : S)
			{
				if (C == TEXT('.')) { bHasDot = true; continue; }
				if (C < TEXT('0') || C > TEXT('9')) return false;
			}
			return bHasDot;
		};

		if (FocusedValue.IsEmpty())
		{
			// Empty input: show the most recently seen players with name, EOS,
			// and IP choices so all three identifier types are immediately
			// accessible without needing to type anything first.
			TSet<FString> SeenValues;
			for (const FPlayerSessionRecord& Rec : Registry->GetAllRecords())
			{
				// 1. Display name choice.
				if (!SeenValues.Contains(Rec.DisplayName))
				{
					SeenValues.Add(Rec.DisplayName);
					AddChoice(Rec.DisplayName, Rec.DisplayName);
				}
				// 2. EOS UID choice.
				if (!Rec.Uid.IsEmpty() && !SeenValues.Contains(Rec.Uid))
				{
					SeenValues.Add(Rec.Uid);
					const FString Label = FString::Printf(
						TEXT("%s (%s)"), *Rec.DisplayName, *Rec.Uid);
					AddChoice(Label, Rec.Uid);
				}
				// 3. IP address choice.
				if (!Rec.IpAddress.IsEmpty())
				{
					const FString IpUid = TEXT("IP:") + Rec.IpAddress;
					if (!SeenValues.Contains(IpUid))
					{
						SeenValues.Add(IpUid);
						const FString Label = FString::Printf(
							TEXT("%s (IP: %s)"), *Rec.DisplayName, *Rec.IpAddress);
						AddChoice(Label, IpUid);
					}
				}
				if (Choices.Num() >= 25) break;
			}
		}
		else if (FocusedLower.StartsWith(TEXT("eos:")))
		{
			// Typing an EOS compound UID — filter all records whose UID contains
			// the typed prefix (case-insensitive).
			TSet<FString> SeenUids;
			for (const FPlayerSessionRecord& Rec : Registry->GetAllRecords())
			{
				if (Rec.Uid.IsEmpty()) continue;
				if (!Rec.Uid.ToLower().Contains(FocusedLower)) continue;
				if (SeenUids.Contains(Rec.Uid)) continue;
				SeenUids.Add(Rec.Uid);
				const FString Label = FString::Printf(
					TEXT("%s (%s)"), *Rec.DisplayName, *Rec.Uid);
				AddChoice(Label, Rec.Uid);
			}
		}
		else if (FocusedLower.StartsWith(TEXT("ip:")) || IsIpFragment(FocusedValue))
		{
			// Typing an IP address — strip any "IP:" prefix then search.
			const FString IpQuery = FocusedLower.StartsWith(TEXT("ip:"))
				? FocusedValue.Mid(3) : FocusedValue;
			TSet<FString> SeenIps;
			for (const FPlayerSessionRecord& Rec : Registry->FindByIp(IpQuery))
			{
				if (Rec.IpAddress.IsEmpty()) continue;
				if (SeenIps.Contains(Rec.IpAddress)) continue;
				SeenIps.Add(Rec.IpAddress);
				const FString IpUid = TEXT("IP:") + Rec.IpAddress;
				const FString Label = FString::Printf(
					TEXT("%s (%s)"), *Rec.DisplayName, *Rec.IpAddress);
				AddChoice(Label, IpUid);
			}
		}
		else
		{
			// Name search: for each matching record surface three choices so the
			// admin can pick the exact identifier they want to target.
			TSet<FString> SeenValues;
			for (const FPlayerSessionRecord& Rec : Registry->FindByName(FocusedValue))
			{
				// 1. Display name choice.
				if (!SeenValues.Contains(Rec.DisplayName))
				{
					SeenValues.Add(Rec.DisplayName);
					AddChoice(Rec.DisplayName, Rec.DisplayName);
				}
				// 2. EOS UID choice.
				if (!Rec.Uid.IsEmpty() && !SeenValues.Contains(Rec.Uid))
				{
					SeenValues.Add(Rec.Uid);
					const FString Label = FString::Printf(
						TEXT("%s (%s)"), *Rec.DisplayName, *Rec.Uid);
					AddChoice(Label, Rec.Uid);
				}
				// 3. IP address choice.
				if (!Rec.IpAddress.IsEmpty())
				{
					const FString IpUid = TEXT("IP:") + Rec.IpAddress;
					if (!SeenValues.Contains(IpUid))
					{
						SeenValues.Add(IpUid);
						const FString Label = FString::Printf(
							TEXT("%s (IP: %s)"), *Rec.DisplayName, *Rec.IpAddress);
						AddChoice(Label, IpUid);
					}
				}
				if (Choices.Num() >= 25) break;
			}
		}
	}

	// ── Respond with type 8 (APPLICATION_COMMAND_AUTOCOMPLETE_RESULT) ──────
	TSharedPtr<FJsonObject> ResponseData = MakeShared<FJsonObject>();
	ResponseData->SetArrayField(TEXT("choices"), Choices);

	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("type"), 8); // AUTOCOMPLETE_RESULT
	Body->SetObjectField(TEXT("data"), ResponseData);

	FString BodyString;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
		if (!FJsonSerializer::Serialize(Body.ToSharedRef(), Writer))
		{
			UE_LOG(LogDiscordBridge, Warning, TEXT("DiscordBridge: JSON serialization failed in autocomplete response."));
			return;
		}
	}

	const FString Url = FString::Printf(
		TEXT("%s/interactions/%s/%s/callback"),
		*DiscordApiBase, *InteractionId, *InteractionToken);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"),
	                   FString::Printf(TEXT("Bot %s"), *Config.BotToken));
	Request->SetContentAsString(BodyString);
	Request->OnProcessRequestComplete().BindLambda(
		[](FHttpRequestPtr, FHttpResponsePtr Resp, bool bConnected)
		{
			if (!bConnected || !Resp.IsValid() ||
			    (Resp->GetResponseCode() != 200 && Resp->GetResponseCode() != 204))
			{
				UE_LOG(LogDiscordBridge, Verbose,
				       TEXT("DiscordBridge: Autocomplete callback returned HTTP %d"),
				       Resp.IsValid() ? Resp->GetResponseCode() : 0);
			}
		});
	Request->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
// Slash command interaction handler
// ─────────────────────────────────────────────────────────────────────────────

void UDiscordBridgeSubsystem::HandleSlashCommandInteraction(const TSharedPtr<FJsonObject>& DataObj)
{
// Extract common interaction fields.
FString InteractionId, InteractionToken, InteractionChannelId;
DataObj->TryGetStringField(TEXT("id"),         InteractionId);
DataObj->TryGetStringField(TEXT("token"),      InteractionToken);
DataObj->TryGetStringField(TEXT("channel_id"), InteractionChannelId);

// Extract member identity and role list.
FString AuthorId, AuthorName;
TArray<TSharedPtr<FJsonValue>> AuthorRolesArray;
const TSharedPtr<FJsonObject>* MemberObjPtr = nullptr;
if (DataObj->TryGetObjectField(TEXT("member"), MemberObjPtr) && MemberObjPtr)
{
(*MemberObjPtr)->TryGetStringField(TEXT("nick"), AuthorName);
const TSharedPtr<FJsonObject>* UserPtr = nullptr;
if ((*MemberObjPtr)->TryGetObjectField(TEXT("user"), UserPtr) && UserPtr)
{
(*UserPtr)->TryGetStringField(TEXT("id"), AuthorId);
if (AuthorName.IsEmpty())
(*UserPtr)->TryGetStringField(TEXT("global_name"), AuthorName);
if (AuthorName.IsEmpty())
(*UserPtr)->TryGetStringField(TEXT("username"), AuthorName);
}
const TArray<TSharedPtr<FJsonValue>>* RolesArr = nullptr;
if ((*MemberObjPtr)->TryGetArrayField(TEXT("roles"), RolesArr) && RolesArr)
AuthorRolesArray = *RolesArr;
}
if (AuthorName.IsEmpty()) AuthorName = TEXT("Discord User");

// Extract the top-level command name and its options array.
const TSharedPtr<FJsonObject>* CmdDataPtr = nullptr;
if (!DataObj->TryGetObjectField(TEXT("data"), CmdDataPtr) || !CmdDataPtr) return;

FString CmdName;
(*CmdDataPtr)->TryGetStringField(TEXT("name"), CmdName);
CmdName = CmdName.ToLower();

const TArray<TSharedPtr<FJsonValue>>* TopOptions = nullptr;
(*CmdDataPtr)->TryGetArrayField(TEXT("options"), TopOptions);

// ── Standalone public commands ───────────────────────────────────────────────
// These are handled inline and respond directly to the interaction.

if (CmdName == TEXT("players"))
{
FString Reply;
if (UWorld* World = GetWorld())
{
if (AGameStateBase* GS = World->GetGameState<AGameStateBase>())
{
TArray<FString> Names;
for (APlayerState* PS : GS->PlayerArray)
if (PS) Names.Add(PS->GetPlayerName());
Reply = Names.Num() == 0
? TEXT("No players currently online.")
: FString::Printf(TEXT("**Online players (%d):** %s"),
    Names.Num(), *FString::Join(Names, TEXT(", ")));
}
}
if (Reply.IsEmpty()) Reply = TEXT("No players currently online.");
RespondToInteraction(InteractionId, InteractionToken, 4, Reply, false);
return;
}

if (CmdName == TEXT("stats"))
{
UWorld* World = GetWorld();
AGameStateBase* GS = World ? World->GetGameState<AGameStateBase>() : nullptr;
const int32 PlayerCount = GS ? GS->PlayerArray.Num() : 0;
const FString Reply = FString::Printf(
TEXT("**📊 Server Statistics — %s**\nPlayers Online: **%d**\nTime (UTC): %s"),
Config.ServerName.IsEmpty() ? TEXT("(unnamed)") : *Config.ServerName,
PlayerCount,
*FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d %H:%M:%S")));
RespondToInteraction(InteractionId, InteractionToken, 4, Reply, false);
return;
}

if (CmdName == TEXT("server"))
{
UWorld* World = GetWorld();
AGameStateBase* GS = World ? World->GetGameState<AGameStateBase>() : nullptr;
const int32 PlayerCount = GS ? GS->PlayerArray.Num() : 0;
const FString Reply = FString::Printf(
TEXT("**🖥️ Server: %s**\nStatus: ✅ Online\nPlayers: **%d**\nTime (UTC): %s"),
Config.ServerName.IsEmpty() ? TEXT("(unnamed)") : *Config.ServerName,
PlayerCount,
*FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d %H:%M:%S")));
RespondToInteraction(InteractionId, InteractionToken, 4, Reply, false);
return;
}

if (CmdName == TEXT("online"))
{
UWorld* World = GetWorld();
AGameStateBase* GS = World ? World->GetGameState<AGameStateBase>() : nullptr;
FString Reply;
if (!GS || GS->PlayerArray.Num() == 0)
{
Reply = TEXT("�� No players are currently online.");
}
else
{
Reply = FString::Printf(TEXT("**👥 Online Players (%d):**\n"), GS->PlayerArray.Num());
int32 Idx = 1;
for (APlayerState* PS : GS->PlayerArray)
if (PS) Reply += FString::Printf(TEXT("%d. **%s**\n"), Idx++, *PS->GetPlayerName());
}
RespondToInteraction(InteractionId, InteractionToken, 4, Reply, false);
return;
}

if (CmdName == TEXT("help"))
{
const FString Reply =
TEXT("**📖 DiscordBridge Commands**\n")
TEXT("`/players` — Online player list\n")
TEXT("`/stats` — Server statistics\n")
TEXT("`/server` — Server info\n")
TEXT("`/online` — Online players embed\n")
TEXT("`/whitelist on|off|add|remove|list|status|apply|link|search` — Whitelist\n")
TEXT("`/ban add|temp|remove|check|list|extend|…` — Ban by name, EOS UID, or IP (admin)\n")
TEXT("`/warn add|list|clearall|clearone` — Warning management (admin)\n")
TEXT("`/mod kick|mute|unmute|freeze|announce|…` — Moderation (moderator/admin)\n")
TEXT("`/player history|note|notes|playtime|…` — Player info (admin)\n")
TEXT("`/appeal list|approve|deny|dismiss` — Appeal management (admin)\n")
TEXT("`/admin say|poll|reloadconfig|panel|clearchat` — Admin utilities (admin)\n")
TEXT("`/ticket panel|list|assign|claim|…` — Support ticket management");
RespondToInteraction(InteractionId, InteractionToken, 4, Reply, false);
return;
}

// ── /whitelist – handled within DiscordBridgeSubsystem ───────────────────────
if (CmdName == TEXT("whitelist"))
{
if (!TopOptions || TopOptions->IsEmpty())
{
RespondToInteraction(InteractionId, InteractionToken, 4, TEXT("❌ Invalid whitelist command."), true);
return;
}
const TSharedPtr<FJsonObject>* SubObjPtr = nullptr;
if (!(*TopOptions)[0]->TryGetObject(SubObjPtr) || !SubObjPtr)
{
RespondToInteraction(InteractionId, InteractionToken, 4, TEXT("❌ Invalid whitelist command."), true);
return;
}

FString SubName;
(*SubObjPtr)->TryGetStringField(TEXT("name"), SubName);
const TArray<TSharedPtr<FJsonValue>>* SubOpts = nullptr;
(*SubObjPtr)->TryGetArrayField(TEXT("options"), SubOpts);

// Check whitelist role permission BEFORE acknowledging the interaction so that
// the error reaches the user ephemerally (not as a separate channel message).
const bool bIsPublicVerb = (SubName == TEXT("apply") || SubName == TEXT("link"));
bool bHasRole = (!GuildOwnerId.IsEmpty() && AuthorId == GuildOwnerId) || bIsPublicVerb;
if (!bHasRole && !WhitelistConfig.WhitelistCommandRoleId.IsEmpty())
{
for (const TSharedPtr<FJsonValue>& RV : AuthorRolesArray)
{
FString RId;
if (RV->TryGetString(RId) && RId == WhitelistConfig.WhitelistCommandRoleId)
{
bHasRole = true;
break;
}
}
}
if (!bHasRole)
{
RespondToInteraction(InteractionId, InteractionToken, 4,
    TEXT("❌ You do not have permission to use whitelist commands."), true);
return;
}

// Permission granted — acknowledge and process.
RespondToInteraction(InteractionId, InteractionToken, 4,
    TEXT("✅ Processing whitelist command…"), true);

// Build the sub-command string matching HandleWhitelistCommand's expected format.
FString SubCmd = SubName;
if (SubName == TEXT("add"))
{
const FString Name     = GetSlashOptionString(SubOpts, TEXT("name"));
const FString Group    = GetSlashOptionString(SubOpts, TEXT("group"));
const FString Duration = GetSlashOptionString(SubOpts, TEXT("duration"));
if (!Name.IsEmpty())
{
SubCmd += TEXT(" ") + Name;
if (!Group.IsEmpty())    SubCmd += TEXT(" group:") + Group;
if (!Duration.IsEmpty()) SubCmd += TEXT(" ") + Duration;
}
}
else if (SubName == TEXT("remove") || SubName == TEXT("apply"))
{
const FString Name = GetSlashOptionString(SubOpts, TEXT("name"));
if (!Name.IsEmpty()) SubCmd += TEXT(" ") + Name;
}
else if (SubName == TEXT("list"))
{
const FString Group = GetSlashOptionString(SubOpts, TEXT("group"));
if (!Group.IsEmpty()) SubCmd += TEXT(" ") + Group;
}
else if (SubName == TEXT("link"))
{
const FString Code = GetSlashOptionString(SubOpts, TEXT("code"));
if (!Code.IsEmpty()) SubCmd += TEXT(" ") + Code;
}
else if (SubName == TEXT("search"))
{
const FString Query = GetSlashOptionString(SubOpts, TEXT("query"));
if (!Query.IsEmpty()) SubCmd += TEXT(" ") + Query;
}
// "on", "off", "status" carry no extra arguments.

HandleWhitelistCommand(SubCmd, AuthorName, InteractionChannelId, AuthorId);
return;
}

// ── /player stats – handled here since HandlePlayerStatsCommand lives here ───
if (CmdName == TEXT("player") && TopOptions && !TopOptions->IsEmpty())
{
const TSharedPtr<FJsonObject>* SubCheck = nullptr;
FString SubNameCheck;
if ((*TopOptions)[0]->TryGetObject(SubCheck) && SubCheck)
(*SubCheck)->TryGetStringField(TEXT("name"), SubNameCheck);

if (SubNameCheck == TEXT("stats"))
{
RespondToInteraction(InteractionId, InteractionToken, 4,
    TEXT("✅ Fetching player stats…"), true);
const TArray<TSharedPtr<FJsonValue>>* StatsOpts = nullptr;
(*SubCheck)->TryGetArrayField(TEXT("options"), StatsOpts);
HandlePlayerStatsCommand(InteractionChannelId, GetSlashOptionString(StatsOpts, TEXT("name")));
return;
}
}

// ── /ticket – delegated to TicketSubsystem via the interaction delegate ──────
if (CmdName == TEXT("ticket"))
{
if (!OnDiscordInteractionReceived.IsBound())
{
UE_LOG(LogDiscordBridge, Warning,
       TEXT("DiscordBridge: /ticket slash command received but no interaction "
            "subscriber is registered. TicketSubsystem may not be loaded."));
RespondToInteraction(InteractionId, InteractionToken, 4,
    TEXT("❌ Ticket system is not available — the TicketSubsystem module is not loaded."),
    true);
return;
}

RespondToInteraction(InteractionId, InteractionToken, 5, FString(), true);
OnDiscordInteractionReceived.Broadcast(DataObj);
return;
}

// ── Ban / mod / warn / player / appeal / admin ───────────────────────────────
// These are delegated to UBanDiscordSubsystem via the interaction delegate.
// Acknowledge first so Discord does not show "interaction failed"; the real
// response is posted to the channel by the existing command handler.
static const TArray<FString> BanGroups = {
TEXT("ban"), TEXT("warn"), TEXT("mod"),
TEXT("player"), TEXT("appeal"), TEXT("admin"),
};
if (BanGroups.Contains(CmdName))
{
if (!OnDiscordInteractionReceived.IsBound())
{
// BanDiscordSubsystem is not subscribed — respond with a helpful error
// instead of the "Processing command…" ack that would leave the user
// waiting forever.
UE_LOG(LogDiscordBridge, Warning,
       TEXT("DiscordBridge: /%s slash command received but no interaction "
            "subscriber is registered. BanDiscordSubsystem may not be loaded."),
       *CmdName);
RespondToInteraction(InteractionId, InteractionToken, 4,
    TEXT("❌ Ban system is not available — the BanDiscordSubsystem module is not loaded."),
    true);
return;
}

RespondToInteraction(InteractionId, InteractionToken, 5, FString(), true);
OnDiscordInteractionReceived.Broadcast(DataObj);
}
}

// ─────────────────────────────────────────────────────────────────────────────
// WarnedExpiryNames persistence
// ─────────────────────────────────────────────────────────────────────────────

static FString GetWarnedExpiryNamesPath()
{
	return FPaths::ProjectSavedDir() / TEXT("DiscordBridge") / TEXT("WarnedExpiryNames.json");
}

void UDiscordBridgeSubsystem::SaveWarnedExpiryNames() const
{
	const FString Path = GetWarnedExpiryNamesPath();
	const FString Dir  = FPaths::GetPath(Path);
	IPlatformFile& PF  = FPlatformFileManager::Get().GetPlatformFile();
	if (!PF.DirectoryExists(*Dir))
		PF.CreateDirectoryTree(*Dir);

	TArray<TSharedPtr<FJsonValue>> Arr;
	for (const FString& Name : WarnedExpiryNames)
		Arr.Add(MakeShared<FJsonValueString>(Name));

	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetArrayField(TEXT("warned"), Arr);

	FString JsonStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
	if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
	{
		UE_LOG(LogDiscordBridge, Warning,
			TEXT("DiscordBridge: JSON serialization failed in SaveWarnedExpiryNames — file not updated."));
		return;
	}

	// Write to a temporary file first, then atomically rename over the destination
	// so a server crash mid-write cannot corrupt the saved data.
	const FString TmpPath = Path + TEXT(".tmp");
	if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogDiscordBridge, Warning,
			TEXT("DiscordBridge: failed to write temp file %s for WarnedExpiryNames"), *TmpPath);
		return;
	}

	if (!IFileManager::Get().Move(*Path, *TmpPath, /*bReplace=*/true))
	{
		UE_LOG(LogDiscordBridge, Warning,
			TEXT("DiscordBridge: failed to atomically rename '%s' → '%s' for WarnedExpiryNames"),
			*TmpPath, *Path);
		IFileManager::Get().Delete(*TmpPath);
	}
}

void UDiscordBridgeSubsystem::LoadWarnedExpiryNames()
{
	const FString Path = GetWarnedExpiryNamesPath();
	FString JsonStr;
	if (!FFileHelper::LoadFileToString(JsonStr, *Path))
		return; // File absent on first run — that's fine.

	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		UE_LOG(LogDiscordBridge, Warning,
			TEXT("DiscordBridge: failed to parse WarnedExpiryNames from %s"), *Path);
		return;
	}

	const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
	if (Root->TryGetArrayField(TEXT("warned"), Arr) && Arr)
	{
		for (const TSharedPtr<FJsonValue>& V : *Arr)
		{
			FString Name;
			if (V->TryGetString(Name) && !Name.IsEmpty())
				WarnedExpiryNames.Add(Name);
		}
	}
}
