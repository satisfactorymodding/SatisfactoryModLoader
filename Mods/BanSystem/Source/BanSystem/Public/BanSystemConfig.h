// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BanSystemConfig.generated.h"

/**
 * A single warning-escalation tier.
 * When a player accumulates WarnCount or more warnings (or PointThreshold or more
 * warning points when PointThreshold > 0), they are automatically banned for
 * DurationMinutes minutes (0 = permanent).
 */
USTRUCT(BlueprintType)
struct BANSYSTEM_API FWarnEscalationTier
{
    GENERATED_BODY()

    /** Warning count threshold that triggers this tier (evaluated when PointThreshold == 0). */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 WarnCount = 0;

    /**
     * Accumulated warning-point threshold that triggers this tier.
     * When non-zero, points are used instead of plain warn count.
     * Set this to use the Warning Points System; leave 0 for plain count mode.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 PointThreshold = 0;

    /** Ban duration in minutes (0 = permanent). */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 DurationMinutes = 0;
};

/**
 * UBanSystemConfig
 *
 * Per-server configuration for BanSystem.
 *
 * RECOMMENDED: manage settings in the persistent override file:
 *   Saved/BanSystem/BanSystem.ini
 * That file is never touched by mod updates or Alpakit dev deploys.
 * BanSystem writes the current settings there on every server start so your
 * configuration survives any wipe of the mod directory.
 *
 * Settings are also read from the mod's own Config/DefaultBanSystem.ini, but
 * that file may be overwritten when the mod is updated.  Use it only to check
 * the current defaults, not as the long-term home for your configuration.
 *
 * Both files use the same section header:
 *   [/Script/BanSystem.BanSystemConfig]
 *
 * Example Saved/BanSystem/BanSystem.ini override:
 *
 *   [/Script/BanSystem.BanSystemConfig]
 *   DatabasePath=/home/user/bans.json
 *   RestApiPort=3001
 *   MaxBackups=10
 */
UCLASS(Config = BanSystem, meta = (DisplayName = "Ban System"))
class BANSYSTEM_API UBanSystemConfig : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Absolute path to the JSON ban file.
     * Leave empty to use the default: <ProjectSaved>/BanSystem/bans.json
     * On Linux this is typically:
     *   /home/<user>/.config/Epic/FactoryGame/Saved/BanSystem/bans.json
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString DatabasePath;

    /**
     * Port for the local HTTP management REST API (default: 3000).
     * The API binds to all interfaces (0.0.0.0).
     * Restrict external access with your server firewall if needed.
     * Set to 0 to disable the REST API entirely.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 RestApiPort = 3000;

    /**
     * Maximum number of automatic database backups to keep (default: 5).
     * A backup is created on demand via POST /bans/backup.
     * Older backups beyond this limit are deleted automatically.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 MaxBackups = 5;

    /**
     * Optional API key for authenticating REST API requests.
     * When non-empty, all endpoints except GET /health require the header:
     *   X-Api-Key: <value>
     * Leave empty to disable API key authentication (default; only safe on a firewalled server).
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString RestApiKey;

    /**
     * Optional Discord webhook URL for ban/unban/warn/kick notifications.
     * When set, BanDiscordNotifier posts an embed to this URL whenever a ban is
     * created or removed, a warning is issued, or a player is kicked.
     * Leave empty to disable Discord notifications (default).
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString DiscordWebhookUrl;

    /**
     * Number of warnings before an automatic permanent ban is issued (default: 0 = disabled).
     * When a player reaches this many warnings via /warn, they are automatically permanently
     * banned with reason "Auto-banned: reached warning threshold".
     * Set to 0 to disable auto-banning on warnings.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 AutoBanWarnCount = 0;

    /**
     * Duration in minutes for the auto-ban issued when AutoBanWarnCount is reached (default: 0 = permanent).
     * Set to 0 for a permanent auto-ban.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 AutoBanWarnMinutes = 0;

    /**
     * Warning escalation tiers for automatic bans based on warning count.
     *
     * Each tier specifies a warning count threshold and the ban duration in minutes
     * (0 = permanent ban). When a player's total warning count reaches a tier's
     * threshold, they are automatically banned for the corresponding duration.
     *
     * Tiers are evaluated in ascending order; the highest matching tier wins.
     * AutoBanWarnCount / AutoBanWarnMinutes act as a simple single-tier fallback
     * when this array is empty.
     *
     * Example (DefaultBanSystem.ini):
     *   +WarnEscalationTiers=(WarnCount=2,DurationMinutes=30)
     *   +WarnEscalationTiers=(WarnCount=3,DurationMinutes=1440)
     *   +WarnEscalationTiers=(WarnCount=5,DurationMinutes=0)
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    TArray<FWarnEscalationTier> WarnEscalationTiers;

    /**
     * Number of days to retain player session records (default: 0 = keep forever).
     * Records older than this value are pruned by POST /players/prune.
     * Set to 0 to disable automatic pruning by age (records are only removed by the
     * explicit prune endpoint).
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 SessionRetentionDays = 0;

    /**
     * Interval in hours between automatic database backups (default: 0 = disabled).
     * When non-zero, BanSystem schedules a recurring timer that calls
     * UBanDatabase::Backup() every BackupIntervalHours.
     * Set to 0 to rely solely on the manual POST /bans/backup endpoint and the
     * one-time startup backup written by BanSystemModule.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    float BackupIntervalHours = 0.0f;

    /**
     * When true, BanSystem posts a Discord webhook notification whenever a
     * temporary ban expires and the player is allowed to reconnect.
     * Only has an effect when DiscordWebhookUrl is set.
     * Default: false.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    bool bNotifyBanExpired = false;

    /**
     * Interval in hours between automatic expired-ban prune runs (default: 0 = disabled).
     * When non-zero, BanSystem schedules a recurring timer that calls
     * PruneExpiredBans() every PruneIntervalHours so bans.json never grows
     * unbounded on busy servers.
     * Set to 0 to rely solely on the manual POST /bans/prune endpoint.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    float PruneIntervalHours = 0.0f;

    /**
     * When true, BanSystem pushes live JSON events (ban, unban, warn, join) to
     * a WebSocket endpoint configured in WebSocketPushUrl.
     * Requires SMLWebSocket mod to be installed.
     * Default: false.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    bool bPushEventsToWebSocket = false;

    /**
     * WebSocket endpoint to push live events to when bPushEventsToWebSocket=true.
     * Example: ws://localhost:9000/events
     * Leave empty to disable.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString WebSocketPushUrl;

    /**
     * Number of days after which warnings are considered "decayed" and excluded from
     * automatic escalation checks (default: 0 = warnings never decay).
     * When non-zero, warnings older than WarnDecayDays days are ignored by
     * GetWarningCount() (they are NOT deleted — they remain in the history for audit).
     * Set to 0 to use all warnings regardless of age (original behaviour).
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 WarnDecayDays = 0;

    // ─────────────────────────────────────────────────────────────────────────
    //  Ban templates (quick-ban presets)
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * Ban preset definitions for the /qban quick-ban command.
     * Each entry is a pipe-delimited string: "slug|DurationMinutes|Reason[|Category]"
     *   slug            — short identifier used in the command (e.g. "griefing")
     *   DurationMinutes — 0 = permanent
     *   Reason          — pre-filled ban reason
     *   Category        — optional category tag
     *
     * Example (DefaultBanSystem.ini):
     *   +BanTemplates=griefing|10080|Griefing — destroying other players' builds|griefing
     *   +BanTemplates=cheating|0|Cheating — use of third-party tools|cheating
     *   +BanTemplates=harassment|1440|Harassment of other players|harassment
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    TArray<FString> BanTemplates;

    // ─────────────────────────────────────────────────────────────────────────
    //  Configurable kick message templates
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * Custom message shown to players who are permanently banned (default: built-in).
     * Supports template variables: {reason}, {appeal_url}.
     * Leave empty to use the default message.
     *
     * Example:
     *   BanKickMessageTemplate=You are permanently banned. Reason: {reason}. Appeal at {appeal_url}
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString BanKickMessageTemplate;

    /**
     * Custom message shown to players who are temporarily banned (default: built-in).
     * Supports template variables: {reason}, {expiry}, {appeal_url}.
     * Leave empty to use the default message.
     *
     * Example:
     *   TempBanKickMessageTemplate=You are banned until {expiry} UTC. Reason: {reason}
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString TempBanKickMessageTemplate;

    /**
     * URL included in the {appeal_url} template variable for ban kick messages.
     * Typically the address of the /appeals/portal endpoint.
     * Example: http://myserver.com:3000/appeals/portal
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString AppealUrl;

    // ─────────────────────────────────────────────────────────────────────────
    //  Multi-server ban sync
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * WebSocket endpoint URLs of peer servers to synchronise bans with.
     * When a ban or unban is applied on this server it is broadcast as a JSON
     * event to all configured peers; incoming ban events from peers are applied
     * automatically by UBanSyncClient.
     *
     * Example (DefaultBanSystem.ini):
     *   +PeerWebSocketUrls=ws://server2.example.com:9000/events
     *   +PeerWebSocketUrls=ws://192.168.1.50:9000/events
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    TArray<FString> PeerWebSocketUrls;

    /**
     * When true, SSL certificate chain validation is enforced for all wss://
     * WebSocket connections (peer sync and push events).
     *
     * Enabling this prevents MITM attacks where an attacker could inject
     * fabricated ban/unban messages into the peer-sync channel.
     *
     * IMPORTANT: Only enable this if every target server presents a valid,
     * CA-signed TLS certificate and UE5's OpenSSL build is linked against a
     * CA certificate bundle (system or bundled).  On a bare game-server install
     * without a CA bundle, setting this to true will cause ALL wss:// connections
     * to fail with an SSL verification error.
     *
     * Default: false (disabled) — TLS encryption is still used; only
     * certificate-chain validation is skipped (SSL_VERIFY_NONE).
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    bool bVerifyWSCertificate = false;

    // ─────────────────────────────────────────────────────────────────────────
    //  Geo-IP region blocking
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * When true, GeoIP lookups are performed at player login using GeoIpApiUrl.
     * Players from blocked (or not in the allowed) countries are kicked.
     * Default: false.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    bool bGeoIpEnabled = false;

    /**
     * HTTP URL of the GeoIP API endpoint.
     * The URL must accept GET requests with the IP address as the last path component
     * and return a JSON object containing a "countryCode" string field (ISO 3166-1 alpha-2).
     *
     * Example (ip-api.com free tier):
     *   GeoIpApiUrl=http://ip-api.com/json/{ip}?fields=countryCode
     *
     * The placeholder {ip} is replaced at runtime with the connecting player's IP address.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString GeoIpApiUrl;

    /**
     * Allowlist of ISO 3166-1 alpha-2 country codes (e.g. "US", "CA", "GB").
     * When non-empty, only players from listed countries are allowed to join.
     * Mutually exclusive with BlockedCountryCodes (allowed list takes precedence).
     *
     * Example: +AllowedCountryCodes=US
     *          +AllowedCountryCodes=CA
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    TArray<FString> AllowedCountryCodes;

    /**
     * Blocklist of ISO 3166-1 alpha-2 country codes.
     * Players from listed countries are kicked at login.
     * Ignored when AllowedCountryCodes is non-empty.
     *
     * Example: +BlockedCountryCodes=XX
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    TArray<FString> BlockedCountryCodes;

    /**
     * Message shown to players kicked by the Geo-IP filter.
     * Supports {country} template variable.
     * Default: "You are not permitted to join this server from your region."
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    FString GeoIpKickMessage;

    // ─────────────────────────────────────────────────────────────────────────
    //  Admin action rate limiting
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * Maximum number of ban/tempban actions an admin can issue within
     * AdminBanRateLimitMinutes before subsequent bans are rejected.
     * Default: 0 = disabled.
     *
     * NOTE: This setting is unused by BanChatCommands. The in-game /ban rate limiter
     * reads UBanChatCommandsConfig::AdminBanRateLimitCount instead.
     * This value is only consulted by BanRestApi and BanDiscordSubsystem panel actions.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 AdminBanRateLimitCount = 0;

    /**
     * Rolling window in minutes for the admin ban rate limiter.
     * Default: 5.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 AdminBanRateLimitMinutes = 5;

    // ─────────────────────────────────────────────────────────────────────────
    //  Chat-pattern auto-warn / auto-mute
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * Number of chat-filter hits within ChatFilterAutoWarnWindowMinutes that
     * automatically triggers a warning for the player.
     * Default: 0 = disabled.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 ChatFilterAutoWarnThreshold = 0;

    /**
     * Rolling window in minutes for the chat-filter auto-warn counter.
     * Default: 10.
     */
    UPROPERTY(Config, BlueprintReadOnly, Category = "BanSystem")
    int32 ChatFilterAutoWarnWindowMinutes = 10;

    /** Returns the singleton config instance. */
    static const UBanSystemConfig* Get();
};
