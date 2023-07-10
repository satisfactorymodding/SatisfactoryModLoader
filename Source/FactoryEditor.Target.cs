// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class FactoryEditorTarget : TargetRules
{
	public FactoryEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		CppStandard = CppStandardVersion.Cpp20;
        
		ExtraModuleNames.Add("FactoryGame");
	}
}
