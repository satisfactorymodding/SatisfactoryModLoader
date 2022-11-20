﻿#pragma once
#include "CoreMinimal.h"

struct SML_API FSMLConfiguration {
public:
    /** Constructor setting configuration defaults */
    FSMLConfiguration();

    /**
    * Development mode is the mode in which SML will load
    * mods which are considered unsafe in normal environment
    * Most notable, it will be able to load raw .dll or .pak mods, which
    * is handy for development process because you avoid packing stuff every time you want to test it
    * Note that such mods CANNOT have dependencies or dependents, and are always loaded in the last order
    * Environment with enabled development mode is invalid for submitting bug reports
    */
    bool bDevelopmentMode;

    /**
    * Opens a console window wich outputs all standard output streams
    * for allowing you to better debug the runtime
    */
    bool bConsoleWindow;

    /**
    * List of fully qualified chat command names that won't be usable by players in the game
    * Full command name is mod_reference:command_name
    * Note that this setting will only affect players, other command senders will still be able to use it
    */
    TArray<FString> DisabledChatCommands;

    /**
    * Whenever to enable console commands which are considered cheat and disabled by default
    * See UFGCheatManager for command list
    */
    bool bEnableCheatConsoleCommands;

    /**
    * List of all user accepted crash reporting endpoints.
    * If any mod defines a Crash Reporting Endpoint URL that is contained within this list,
    * the modding crash reporter will send a crash report to the URL if possible without further notice to the user.
    */
    TArray<FString> AcceptedCrashReportingEndpoints;

    /**
    * List of user rejected crash reporting endpoints.
    * Opposite to AcceptedCrashReportingEndpoints.
    * Necessary to not repeat asking a user for the same endpoint multiple times between sessions.
    */
    TArray<FString> RejectedCrashReportingEndpoints;

    /**
    * If enabled, disables the custom satisfactory modding crash reporter and no crash reports will ever be sent
    * to any of the mods nor the modding infrastructure maintainers.
    */
    bool bDisableModdingCrashReporter;
    
public:
    /** Deserializes configuration from JSON object */
    static void ReadFromJson(const TSharedPtr<class FJsonObject>& Json, FSMLConfiguration& OutConfiguration, bool* OutIsMissingSections = NULL);

    /** Serializes configuration into JSON object */
    static void WriteToJson(const TSharedPtr<class FJsonObject>& OutJson, const FSMLConfiguration& Configuration);
};