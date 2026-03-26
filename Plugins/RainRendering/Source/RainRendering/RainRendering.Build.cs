// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RainRendering : ModuleRules
{
	public RainRendering(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateIncludePaths.AddRange(
			new string[]
			{
				System.IO.Path.Combine(GetModuleDirectory("Renderer"),"Private"),
				System.IO.Path.Combine(GetModuleDirectory("Renderer"),"Internal")	
			});
		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"RHI",
				"Renderer",
				"RenderCore",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"RHI",
				"Renderer",
				"Projects",
				"RenderCore",
				"DeveloperSettings"
			}
		);
		if (Target.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);

	}
}
