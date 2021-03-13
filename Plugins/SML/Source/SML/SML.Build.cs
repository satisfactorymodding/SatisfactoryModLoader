// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;
using System.Runtime.InteropServices;
using System.Text;

public class SML : ModuleRules
{
    public SML(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        //SML transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Json",
            "MovieScene",
            "Projects"
        });
        PrivateDependencyModuleNames.AddRange(new[] {"RenderCore"});
        
        PublicDependencyModuleNames.AddRange(new string[] {"FactoryGame"});
        
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
        
        var projectFilePath = Target.ProjectFile.ToString();
        var projectRootPath = projectFilePath.Substring(0, projectFilePath.LastIndexOf(Path.DirectorySeparatorChar));
        var absoluteHeaderFilePath = Path.Combine(projectRootPath, "Source/FactoryGame/Public/FactoryGame.h");
        var moduleRelativeHeaderFilePath = new StringBuilder(260);
        PathRelativePathTo(moduleRelativeHeaderFilePath, ModuleDirectory, FILE_ATTRIBUTE_DIRECTORY,
            absoluteHeaderFilePath, FILE_ATTRIBUTE_NORMAL);
        
        PrivatePCHHeaderFile = moduleRelativeHeaderFilePath.ToString();
        
        var thirdPartyFolder = Path.Combine(ModuleDirectory, "../../ThirdParty");
        PublicIncludePaths.Add(Path.Combine(thirdPartyFolder, "include"));
        
        var platformName = Target.Platform.ToString();
        var libraryFolder = Path.Combine(thirdPartyFolder, platformName);
        
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "funchook.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "detex.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libfbxsdk-md.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libxml2-md.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "zlib-md.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "AssemblyAnalyzer.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "Zydis.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "Zycore.lib"));
    }
    
    //Copied from https://stackoverflow.com/questions/275689/how-to-get-relative-path-from-absolute-path
    //Cannot really use Path.getRelativePath because it's since .NET Framework 5.0 only
    //Dude why the hell do I even need to write wrappers around native code just to get relative path properly
    private const int FILE_ATTRIBUTE_DIRECTORY = 0x10;
    private const int FILE_ATTRIBUTE_NORMAL = 0x80;

    [DllImport("shlwapi.dll", SetLastError = true)]
    private static extern int PathRelativePathTo(StringBuilder pszPath, string pszFrom, int dwAttrFrom, string pszTo, int dwAttrTo);
}
