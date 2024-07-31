// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Alpakit : ModuleRules
{
	public Alpakit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;

		PublicDependencyModuleNames.AddRange(new[] {
			"Core",
			"DesktopPlatform",
		});
		
		PublicDependencyModuleNames.AddRange(new[] {
			"SML",
		});
		
		PrivateDependencyModuleNames.AddRange(new[] {
			"ApplicationCore",
			"Json",
			"Projects",
			"InputCore",
			"UnrealEd",
			"LevelEditor",
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"ExternalImagePicker",
			"EditorStyle",
			"PluginBrowser",
			"LauncherServices",
			"TargetDeviceServices",
		});
	}
}
