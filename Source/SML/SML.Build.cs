// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;

public class SML : ModuleRules
{
    public SML(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {"FactoryGame"});
        
        //SML transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Json"
        });
        
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
            "InstancedSplines"
        });

        if (Target.bBuildEditor) {
            PublicDependencyModuleNames.Add("UnrealEd");
        }

        var platformName = Enum.GetName(typeof(UnrealTargetPlatform), Target.Platform);
        var projectFilePath = Target.ProjectFile.ToString();
        var projectRootPath = projectFilePath.Substring(0, projectFilePath.LastIndexOf(Path.DirectorySeparatorChar));
        var fullLibPath = Path.Combine(projectRootPath, "Library", platformName);
        Console.WriteLine("Full Library Path: " + fullLibPath);
        PublicAdditionalLibraries.Add(Path.Combine(fullLibPath, "funchook.lib"));
    }
}
