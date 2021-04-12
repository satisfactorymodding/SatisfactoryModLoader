// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryGameEditorTarget : TargetRules
{
	public FactoryGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		
		CppStandard = CppStandardVersion.Cpp17;
		ExtraModuleNames.AddRange(new[] { "FactoryGame"});
		DefaultBuildSettings = BuildSettingsVersion.V2;
	}
}
