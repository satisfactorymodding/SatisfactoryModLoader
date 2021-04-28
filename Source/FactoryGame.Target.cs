// Fill out your copyright notice in the Description page of Project Settings.

using System;
using UnrealBuildTool;

public class FactoryGameTarget : TargetRules
{
	public FactoryGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		LinkType = TargetLinkType.Modular;
		
		CppStandard = CppStandardVersion.Cpp17;
		ExtraModuleNames.AddRange(new[] {"FactoryGame"});
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		bOverrideAppNameForSharedBuild = true;

		bUseChecksInShipping = true;
		bUseLoggingInShipping = true;
	}
}
