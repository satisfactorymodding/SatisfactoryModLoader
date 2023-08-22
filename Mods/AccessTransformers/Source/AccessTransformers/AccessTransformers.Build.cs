// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AccessTransformers : ModuleRules
{
	public AccessTransformers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;

		PublicDependencyModuleNames.AddRange(new[] {
			"Core",
			"CoreUObject",
			"Engine",
			"Projects",
			"EditorSubsystem",
			"DirectoryWatcher",
			"Slate",
		});
	}
}
