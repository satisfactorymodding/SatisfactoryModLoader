// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using EpicGames.Core;
using UnrealBuildTool;
using Microsoft.Extensions.Logging;

// Target preset class shared by both game and server configurations. Editor still has it's own configuration not derived from this class.
public class FactorySharedTarget : TargetRules
{
	/** Allows overriding whenever the checks in the shipping builds should be used from the commandline */
	[CommandLine("-UseChecksInShipping")]
	public bool UseChecksInShippingOverride = false;

	/** Allows overriding the build type from the command line */
	[CommandLine("-Monolithic", Value = "Monolithic")] 
	[CommandLine("-Modular", Value = "Modular")]
	public TargetLinkType LinkTypeOverride = TargetLinkType.Default;

	public FactorySharedTarget(TargetInfo Target) : base(Target)
	{
		// Marked this as game because the project file generator was trying to initialize this class and failing because it was abstract. What a not very smart tool.
		Type = UnrealBuildTool.TargetType.Game;
		
		// Default to shared build environment and modular build on desktop platforms
		var defaultLinkTypeForPlatform = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) ? TargetLinkType.Modular : TargetLinkType.Monolithic;

		BuildEnvironment = TargetBuildEnvironment.Shared;
		LinkType = LinkTypeOverride != TargetLinkType.Default ? LinkTypeOverride : defaultLinkTypeForPlatform;

		// Shared build settings
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		bOverrideAppNameForSharedBuild = true;
		bOverrideBuildEnvironment = true;
		bUseLoggingInShipping = true;
		bAllowGeneratedIniWhenCooked = true;
		// Enable diagnostics when disabled plugins are being pulled back into the build as dependencies for other plugins
		DisablePluginsConflictWarningLevel = WarningLevel.Warning;

		// [ZolotukhinN:10/07/2023] Enabled Network Push Model support in normal game builds, it's disabled in non-editor by default
		bWithPushModel = true;
		// [ZolotukhinN:04/05/2023] Allow cheat manager initialization in Shipping builds to allow cheating even in shipping builds when compiling with WITH_CHEATS=1
		GlobalDefinitions.Add("UE_WITH_CHEAT_MANAGER=1");
		// Allow checks in shipping depending on the command line configuration
		bUseChecksInShipping = UseChecksInShippingOverride;
		
		// Common module names for the game targets
		ExtraModuleNames.AddRange(new[] {
			"FactoryGame"
		});
		if (UseChecksInShippingOverride || LinkTypeOverride != TargetLinkType.Default)
		{
			Logger.LogInformation($"{Target.Name}: Building with command line overrides: ChecksInShipping: {bUseChecksInShipping} (default: false); LinkType: {LinkType} (default: {defaultLinkTypeForPlatform})");
		}
	}
}