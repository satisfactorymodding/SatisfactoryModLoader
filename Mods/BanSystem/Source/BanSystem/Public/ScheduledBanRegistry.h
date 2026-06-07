// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/CriticalSection.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BanTypes.h"
#include "ScheduledBanRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogScheduledBanRegistry, Log, All);

/**
 * UScheduledBanRegistry
 *
 * Stores bans that are scheduled to take effect at a future UTC timestamp.
 * Persists to scheduled_bans.json (same directory as bans.json).
 * A 30-second tick checks whether any scheduled bans have become due and
 * applies them via UBanDatabase::AddBan + UBanEnforcer::KickConnectedPlayer.
 *
 * Thread-safe: all public methods acquire the internal Mutex.
 */
UCLASS()
class BANSYSTEM_API UScheduledBanRegistry : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // ── USubsystem ───────────────────────────────────────────────────────────
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /**
     * Schedule a new ban to take effect at EffectiveAt.
     * DurationMinutes == 0 means permanent when the ban is applied.
     * Returns the newly created entry (with auto-assigned Id).
     * Saves to disk immediately. Thread-safe.
     */
    FScheduledBanEntry AddScheduled(const FString& Uid,
                                    const FString& PlayerName,
                                    const FString& Reason,
                                    const FString& ScheduledBy,
                                    FDateTime      EffectiveAt,
                                    int32          DurationMinutes,
                                    const FString& Category = TEXT(""));

    /** Returns all pending (not yet applied) scheduled bans. Thread-safe. */
    TArray<FScheduledBanEntry> GetAllPending() const;

    /**
     * Delete a scheduled ban by integer Id (before it fires).
     * Returns true if found and removed. Thread-safe.
     */
    bool DeleteScheduled(int64 Id);

    /**
     * Delete a scheduled ban by integer Id (before it fires) and return the
     * removed entry via OutEntry for audit-log purposes.
     * Returns true if found and removed. Thread-safe.
     */
    bool DeleteScheduled(int64 Id, FScheduledBanEntry& OutEntry);

    /**
     * Tick: check each pending entry, apply any that are now due.
     * Called every 30 s by the module ticker.
     */
    void Tick(float DeltaTime);

private:
    void    LoadFromFile();
    bool    SaveToFile() const;
    FString GetRegistryPath() const;

    /** Apply a single scheduled ban (called from Tick when EffectiveAt has passed).
     *  Returns true when the entry was handled (applied or intentionally skipped),
     *  false when a transient failure occurred and the entry should be re-queued. */
    bool ApplyScheduledBan(const FScheduledBanEntry& Entry);

    TArray<FScheduledBanEntry> Pending;
    int64                      NextId = 1;
    mutable FCriticalSection   Mutex;
    FString                    FilePath;

    float  AccumulatedSeconds = 0.0f;
    static constexpr float TickIntervalSeconds = 30.0f;
};
