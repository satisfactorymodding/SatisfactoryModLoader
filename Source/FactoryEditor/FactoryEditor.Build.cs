// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FactoryEditor : ModuleRules
{
	public FactoryEditor( ReadOnlyTargetRules Target ) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp20;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		PublicDependencyModuleNames.AddRange( new string[] { 
			"Core", 
			"CoreUObject", 
			"CoreOnline",
			"Engine",
			"InputCore",
			"SlateCore",
			"EditorSubsystem",
			"FactoryGame"
		});
	}
}
