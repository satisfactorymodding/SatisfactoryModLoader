// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** A single whitelist entry with optional EOS PUID, expiry, and group. */
struct DISCORDBRIDGE_API FWhitelistEntry
{
    FString   Name;
    FString   EosPUID;
    FDateTime ExpiresAt; // FDateTime(0) = permanent
    /** Optional group/tier tag (e.g. "VIP", "Staff"). Empty = default group. */
    FString   Group;
};

/** A single audit log entry. */
struct DISCORDBRIDGE_API FWhitelistAuditEntry
{
    FDateTime Timestamp;
    FString   AdminName;
    FString   Action;  // "add", "remove", "enable", "disable"
    FString   Target;
};

/**
 * Manages the server whitelist for the DiscordBridge mod.
 * Config stored at <ProjectSavedDir>/DiscordBridge/ServerWhitelist.json.
 */
class DISCORDBRIDGE_API FWhitelistManager
{
public:
    static void Load(bool bDefaultEnabled = false);
    static void Save();
    static bool IsEnabled();
    static void SetEnabled(bool bNewEnabled, const FString& AdminName = TEXT(""));

    /** Returns true if the given player name/PUID is on the whitelist (name comparison case-insensitive). */
    static bool IsWhitelisted(const FString& PlayerName, const FString& EosPUID = TEXT(""));

    /** Returns true if the given EOS PUID is on the whitelist. */
    static bool IsWhitelistedByPUID(const FString& EosPUID);

    /**
     * Adds a player and saves. Returns false if already listed or capacity full.
     * ExpiresAt == FDateTime(0) means permanent.
     * Group is optional; empty string = no group.
     */
    static bool AddPlayer(const FString& PlayerName,
                          const FString& EosPUID    = TEXT(""),
                          const FString& AdminName  = TEXT(""),
                          FDateTime      ExpiresAt  = FDateTime(0),
                          const FString& Group      = TEXT(""));

    /**
     * Removes a player and saves. Returns false if not found.
     * If EosPUID is non-empty, remove by PUID; otherwise remove by name (case-insensitive).
     */
    static bool RemovePlayer(const FString& PlayerName, const FString& EosPUID = TEXT(""), const FString& AdminName = TEXT(""));

    /** Returns a copy of player names (backward-compat). */
    static TArray<FString> GetAll();

    /** Returns all entries. */
    static TArray<FWhitelistEntry> GetAllEntries();

    /** Returns entries whose Name contains PartialName (case-insensitive). */
    static TArray<FWhitelistEntry> Search(const FString& PartialName);

    // ── Audit log ────────────────────────────────────────────────────────────

    /** Caller must already hold Mutex. */
    static void LogAudit(const FString& Admin, const FString& Action, const FString& Target);
    static TArray<FWhitelistAuditEntry> GetAuditLog(int32 MaxEntries = 20);

    // ── Capacity ─────────────────────────────────────────────────────────────

    /** Returns number of active (non-expired) whitelist entries. */
    static int32 GetActiveEntryCount();
    static int32 GetMaxSlots();
    static void  SetMaxSlots(int32 InMaxSlots);

    // ── Timed entries ────────────────────────────────────────────────────────

    /** Parse a duration string (e.g. "7d", "2h", "30m", "1w"). Returns FTimespan::Zero() on failure. */
    static FTimespan ParseDuration(const FString& DurStr);

    /** Remove expired entries. Fills OutExpiredNames with removed player names. Calls Save() if any removed. */
    static void RemoveExpiredEntries(TArray<FString>& OutExpiredNames);

private:
    static FString GetFilePath();
    static void    Save_Locked(); // caller must already hold Mutex

    static bool                         bEnabled;
    static TArray<FWhitelistEntry>      Entries;
    static TArray<FWhitelistAuditEntry> AuditLog;
    static int32                        MaxSlots;
    static FCriticalSection             Mutex;
};
