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
			"DeveloperSettings",
			"PhysicsCore",
			"InputCore",
			"OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemUtils", "OnlineServicesInterface",
			"OnlineIntegration",
			"SignificanceManager",
			"GeometryCollectionEngine",
			"ChaosVehiclesCore", "ChaosVehicles", "ChaosSolverEngine",
			"AnimGraphRuntime",
			"AkAudio", 
			"AssetRegistry",
			"NavigationSystem",
			"ReplicationGraph",
			"AIModule",
			"GameplayTasks",
			"SlateCore", "Slate", "UMG",
			"RenderCore",
			"CinematicCamera",
			"Foliage",
            "Niagara",
            "EnhancedInput",
            "GameplayCameras",
            "TemplateSequence",
            "NetCore",
            "GameplayTags",
			"ModelViewViewModel",
		});
        
		if (Target.Platform == UnrealTargetPlatform.Win64) {
			// Plugins that only support Win64
			PublicDependencyModuleNames.AddRange(new[] {
				"OnlineSubsystemEOS",
			});
		}
		
		PublicDependencyModuleNames.AddRange(new[] {
			"AbstractInstance",
			"InstancedSplinesComponent",
			"SignificanceISPC"
		});
		
		PublicDependencyModuleNames.AddRange(new[] {
			"DummyHeaders",
		});
        
		PublicDefinitions.Add("IS_PUBLIC_BUILD=1");
		PublicDefinitions.Add("WITH_TELEMETRY=0");
	}
}
