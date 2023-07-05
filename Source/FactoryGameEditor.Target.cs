// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class FactoryGameEditorTarget : TargetRules
{
	public FactoryGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		
		CppStandard = CppStandardVersion.Cpp20;
		ExtraModuleNames.AddRange(new[] { "FactoryGame"});
		DefaultBuildSettings = BuildSettingsVersion.V2;
	}
}
