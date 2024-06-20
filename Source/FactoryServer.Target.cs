// Fill out your copyright notice in the Description page of Project Settings.

using System;
using UnrealBuildTool;

public class FactoryServerTarget : TargetRules
{
	public FactoryServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		BuildEnvironment = TargetBuildEnvironment.Shared;
		LinkType = TargetLinkType.Modular;
		CppStandard = CppStandardVersion.Cpp20;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		ExtraModuleNames.AddRange(new[] {"FactoryGame"});
		
		// bOverrideAppNameForSharedBuild = true;

		bUseChecksInShipping = true;
		bUseLoggingInShipping = true;
		
		WindowsPlatform.bEnableRayTracing = false;
		LinuxPlatform.bEnableRayTracing = false;
	}
}
