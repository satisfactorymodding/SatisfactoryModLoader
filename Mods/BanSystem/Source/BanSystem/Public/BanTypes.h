// Copyright Yamahasxviper. All Rights Reserved.
// Direct port of Tools/BanSystem/src/models.ts

#pragma once

#include "CoreMinimal.h"
#include "BanTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBanTypes, Log, All);

// ─────────────────────────────────────────────────────────────────────────────
//  Appeal status
// ─────────────────────────────────────────────────────────────────────────────

UENUM(BlueprintType)
enum class EAppealStatus : uint8
{
    Pending   UMETA(DisplayName = "Pending"),
    Approved  UMETA(DisplayName = "Approved"),
    Denied    UMETA(DisplayName = "Denied"),
    Dismissed UMETA(DisplayName = "Dismissed"),
};

// ─────────────────────────────────────────────────────────────────────────────
//  Ban template (quick-ban preset)
// ─────────────────────────────────────────────────────────────────────────────

/**
 * A ban template (preset) defined in DefaultBanSystem.ini as:
 *   +BanTemplates=slug|DurationMinutes|Human-readable reason
 * Duration 0 = permanent.
 */
USTRUCT(BlueprintType)
struct BANSYSTEM_API FBanTemplate
{
    GENERATED_BODY()

    /** Short identifier used with /qban (e.g. "griefing"). */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    FString Slug;

    /** Ban duration in minutes (0 = permanent). */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    int32 DurationMinutes = 0;

    /** Pre-filled reason string. */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    FString Reason;

    /** Optional ban category tag applied when the template is used. */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    FString Category;

    /**
     * Parse a pipe-delimited config string ("slug|DurationMinutes|Reason[|Category]")
     * into an FBanTemplate.  Returns true on success, false if the string has
     * fewer than 3 pipe-separated fields.
     */
    static bool FromConfigString(const FString& ConfigStr, FBanTemplate& OutTemplate);

    /** Convenience: parse a whole TArray<FString> into an array of templates. */
    static TArray<FBanTemplate> ParseTemplates(const TArray<FString>& ConfigStrings);
};

// ─────────────────────────────────────────────────────────────────────────────
//  Scheduled ban entry
// ─────────────────────────────────────────────────────────────────────────────

/**
 * A ban scheduled to take effect at a future UTC timestamp.
 * Stored in scheduled_bans.json (same directory as bans.json).
 */
USTRUCT(BlueprintType)
struct BANSYSTEM_API FScheduledBanEntry
{
    GENERATED_BODY()

    /** Auto-incremented integer primary key (0 when not yet persisted). */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    int64 Id = 0;

    /** Compound UID to ban: "EOS:xxx". */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Uid;

    /** Display name at time of scheduling (informational). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString PlayerName;

    /** Ban reason. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Reason;

    /** Admin who scheduled the ban. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString ScheduledBy;

    /** UTC timestamp when the ban should take effect. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime EffectiveAt;

    /** UTC timestamp when the ban was created. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime CreatedAt;

    /** Duration in minutes (0 = permanent). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    int32 DurationMinutes = 0;

    /** Optional ban category tag. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Category;

    /** Number of times this entry has failed to apply and been re-queued. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    int32 RetryCount = 0;

    FScheduledBanEntry()
        : Id(0)
        , EffectiveAt(int64(0))
        , CreatedAt(int64(0))
        , DurationMinutes(0)
        , RetryCount(0)
    {}
};

/**
 * A single ban record — mirrors the SQLite schema in database.ts and
 * the BanRecord interface in models.ts exactly.
 */
USTRUCT(BlueprintType)
struct BANSYSTEM_API FBanEntry
{
    GENERATED_BODY()

    /** Auto-incremented integer primary key (0 when not yet persisted). */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    int64 Id = 0;

    /** Compound key: "EOS:00020aed...". */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Uid;

    /** Raw EOS Product User ID. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString PlayerUID;

    /** "EOS" | "UNKNOWN" | "IP" */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Platform;

    /** Human-readable display name at time of ban (informational, may be stale). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString PlayerName;

    /** Why this player was banned. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Reason;

    /** Admin username or "system". */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString BannedBy;

    /** UTC timestamp when the ban was created. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime BanDate;

    /**
     * UTC timestamp when the ban expires.
     * FDateTime(0) (epoch) means the ban is permanent.
     */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime ExpireDate;

    /** true = permanent ban; false = temporary (ExpireDate is valid). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    bool bIsPermanent = true;

    /**
     * Optional list of additional compound UIDs that are linked to this ban
     * (cross-platform identity, e.g. two EOS UIDs for the same person across accounts).
     *
     * When UBanDatabase::IsCurrentlyBannedByAnyId() is called, it searches both
     * the primary Uid and every entry in this list.  Use /linkbans to associate
     * two UIDs and /unlinkbans to remove the association.
     */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    TArray<FString> LinkedUids;

    /**
     * Optional category/severity tag (e.g. "griefing", "cheating", "harassment").
     * Used for filtering in /banlist, the REST API, and Discord commands.
     * Set automatically when a ban template is used.
     */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Category;

    /**
     * Optional list of evidence URLs or descriptions (screenshots, video links, logs).
     * Stored as-is; no validation is performed on the content.
     */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    TArray<FString> Evidence;

    FBanEntry()
        : Id(0)
        , BanDate(FDateTime::UtcNow())
        , ExpireDate(FDateTime(0))
        , bIsPermanent(true)
    {}

    /** Returns true if this is a temporary ban that has already passed its expiry. */
    bool IsExpired() const
    {
        if (bIsPermanent) return false;
        return FDateTime::UtcNow() > ExpireDate;
    }

    /**
     * Returns true if the given compound UID matches this ban's primary Uid or
     * any entry in LinkedUids (case-insensitive).
     */
    bool MatchesUid(const FString& InUid) const
    {
        if (Uid.Equals(InUid, ESearchCase::IgnoreCase)) return true;
        for (const FString& L : LinkedUids)
            if (L.Equals(InUid, ESearchCase::IgnoreCase)) return true;
        return false;
    }

    /** Human-readable message shown to the player when they are kicked.
     *
     * Supports template variables: {reason}, {expiry}, {appeal_url}.
     * Template strings come from UBanSystemConfig::BanKickMessageTemplate
     * and TempBanKickMessageTemplate when non-empty.
     */
    FString GetKickMessage() const;
};

/**
 * A single warning record issued to a player by an admin.
 */
USTRUCT(BlueprintType)
struct BANSYSTEM_API FWarningEntry
{
    GENERATED_BODY()

    /** Auto-incremented integer primary key (0 when not yet persisted). */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    int64 Id = 0;

    /** Compound UID of the warned player: "EOS:xxx". */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Uid;

    /** Display name at time of warning (informational, may be stale). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString PlayerName;

    /** Reason for the warning. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Reason;

    /** Admin username or "console" who issued the warning. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString WarnedBy;

    /** UTC timestamp when the warning was issued. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime WarnDate;

    /** UTC timestamp when the warning expires. Only used when bHasExpiry is true. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime ExpireDate;

    /** When true, this warning has an expiry time and will be ignored after ExpireDate. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    bool bHasExpiry = false;

    /**
     * Point value of this warning (default 1 = minor).
     * Escalation tiers can be triggered by accumulated point total rather than count.
     * Common values: 1=minor, 2=moderate, 3=severe.
     */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    int32 Points = 1;

    FWarningEntry()
        : Id(0)
        , WarnDate(FDateTime::UtcNow())
        , ExpireDate(FDateTime(0))
        , bHasExpiry(false)
        , Points(1)
    {}

    /** Returns true when this is a timed warning that has passed its expiry date. */
    bool IsExpired() const
    {
        if (!bHasExpiry) return false;
        return FDateTime::UtcNow() > ExpireDate;
    }
};

/**
 * A ban appeal submitted by a player via the REST API.
 */
USTRUCT(BlueprintType)
struct BANSYSTEM_API FBanAppealEntry
{
    GENERATED_BODY()

    /** Auto-incremented integer primary key (0 when not yet persisted). */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    int64 Id = 0;

    /** Compound UID of the appealing player: "EOS:xxx". */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Uid;

    /** Player-supplied reason for the appeal. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Reason;

    /** Optional contact information (Discord handle, email, etc.). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString ContactInfo;

    /** UTC timestamp when the appeal was submitted. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime SubmittedAt;

    /** Current status of the appeal (default: Pending). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    EAppealStatus Status = EAppealStatus::Pending;

    /** Admin who reviewed the appeal (empty if still pending). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString ReviewedBy;

    /** Optional admin note recorded when approving or denying. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString ReviewNote;

    /** UTC timestamp when the appeal was reviewed (FDateTime(0) if pending). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime ReviewedAt;

    FBanAppealEntry()
        : Id(0)
        , SubmittedAt(FDateTime::UtcNow())
        , Status(EAppealStatus::Pending)
        , ReviewedAt(FDateTime(0))
    {}
};

/**
 * A single audit log entry recording an admin action.
 */
USTRUCT(BlueprintType)
struct BANSYSTEM_API FAuditEntry
{
    GENERATED_BODY()

    /** Auto-incremented integer primary key (0 when not yet persisted). */
    UPROPERTY(BlueprintReadOnly, Category = "Ban System")
    int64 Id = 0;

    /**
     * Action type: "ban", "tempban", "unban", "kick", "warn", "clearwarns",
     * "whitelist_add", "whitelist_remove".
     */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Action;

    /** Compound UID of the affected player: "EOS:xxx". */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString TargetUid;

    /** Display name of the affected player at time of action (may be empty). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString TargetName;

    /** Compound UID of the admin who performed the action, or "console". */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString AdminUid;

    /** Display name of the admin (may be empty for console actions). */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString AdminName;

    /** Optional extra details, e.g. reason or duration string. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString Details;

    /**
     * BanSystem mod version at the time of the action.
     * Populated automatically by UBanAuditLog::LogAction() from SML's
     * UModLoadingLibrary.  Empty on records loaded from files written by
     * older versions of BanSystem (backward-compatible JSON field).
     */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FString ModVersion;

    /** UTC timestamp when the action was performed. */
    UPROPERTY(BlueprintReadWrite, Category = "Ban System")
    FDateTime Timestamp;

    FAuditEntry()
        : Id(0)
        , Timestamp(FDateTime::UtcNow())
    {}
};
