// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class FactoryGame : ModuleRules
{
	public FactoryGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;
		ShadowVariableWarningLevel = WarningLevel.Warning;

		//FactoryGame transitive dependencies
		PublicDependencyModuleNames.AddRange(new[] {
			"Core", "CoreUObject",
			"Engine",
			"InputCore",
			"OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemEOS", "OnlineSubsystemUtils",
			"SignificanceManager",
			"APEX", "ApexDestruction",
			"AnimGraphRuntime",
			"AkAudio", 
			"PhysXVehicles",
			"AssetRegistry",
			"NavigationSystem",
			"ReplicationGraph",
			"AIModule",
			"GameplayTasks",
			"SlateCore", "Slate", "UMG",
			"InstancedSplines",
			"RenderCore"
		});
        
		PublicDefinitions.Add( "IS_PUBLIC_BUILD=1" ); 
	}
}
