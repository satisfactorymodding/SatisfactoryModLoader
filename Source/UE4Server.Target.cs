// Fill out your copyright notice in the Description page of Project Settings.

using System;
using UnrealBuildTool;

public class UE4ServerTarget : TargetRules
{
	public UE4ServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		LinkType = TargetLinkType.Modular;
		
		CppStandard = CppStandardVersion.Cpp17;
		ExtraModuleNames.AddRange(new[] {"FactoryGame"});
		DefaultBuildSettings = BuildSettingsVersion.V2;
		DisableOptimizeCodeForModules = new[]
		{
			"SML"
		};
		
		// bOverrideAppNameForSharedBuild = true;

		// Set these in UE4's Engine/Source/UE4Server.Target.cs to match
		bUseChecksInShipping = true;
		bUseLoggingInShipping = true;
	}
}
