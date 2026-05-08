// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Containers/Ticker.h"

class BANSYSTEM_API FBanSystemModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    /** On every server start, writes current settings to Saved/BanSystem/BanSystem.ini.
     *  That folder is never touched by mod updates so settings survive any wipe
     *  of the mod directory. */
    static void BackupConfigIfNeeded();

    /** Restores Mods/BanSystem/Config/DefaultBanSystem.ini with the full annotated
     *  template if the file is missing or has been stripped of comment lines by
     *  Alpakit's staging step. */
    static void RestoreDefaultConfigIfNeeded();

    /** Ticker callback that fires at BackupIntervalHours to trigger a scheduled backup. */
    bool OnBackupTick(float DeltaTime);

    /** Ticker callback that fires at PruneIntervalHours to prune expired bans. */
    bool OnPruneTick(float DeltaTime);

    /** Ticker callback that fires daily to prune old player session records
     *  when SessionRetentionDays > 0. */
    bool OnSessionPruneTick(float DeltaTime);

    /** Ticker callback that fires every 30 s to apply due scheduled bans. */
    bool OnScheduledBanTick(float DeltaTime);

    /**
     * Ticker callback that polls the BanSystem config files every
     * ConfigPollIntervalSeconds seconds and reloads them when changed.
     *
     * This provides Alpakit-safe hot reload: operators can edit
     * Saved/BanSystem/BanSystem.ini (which is never touched by Alpakit
     * staging) and have the new settings take effect within one poll
     * interval without restarting the server.
     */
    bool OnConfigPollTick(float DeltaTime);

    FTSTicker::FDelegateHandle BackupTickHandle;
    FTSTicker::FDelegateHandle PruneTickHandle;
    FTSTicker::FDelegateHandle SessionPruneTickHandle;
    FTSTicker::FDelegateHandle ScheduledBanTickHandle;
    FTSTicker::FDelegateHandle ConfigPollTickHandle;

    /** Accumulated time since the last scheduled backup (seconds). */
    double BackupAccumulatedSeconds = 0.0;
    /** Accumulated time since the last scheduled prune (seconds). */
    double PruneAccumulatedSeconds = 0.0;
    /** Accumulated time since the last session-records prune (seconds). */
    double SessionPruneAccumulatedSeconds = 0.0;

    /** How often (seconds) to poll for config-file changes (matches BanChatCommands). */
    static constexpr float ConfigPollIntervalSeconds = 60.0f;

    /**
     * File modification timestamps captured on the last successful config reload.
     * Two files are monitored:
     *   [0] Saved/BanSystem/BanSystem.ini     — persistent operator override
     *   [1] Mods/BanSystem/Config/DefaultBanSystem.ini — mod-distributed defaults
     * A change in either file triggers a ReloadConfig() + BackupConfigIfNeeded().
     */
    FDateTime ConfigFileModTimes[2];
};
