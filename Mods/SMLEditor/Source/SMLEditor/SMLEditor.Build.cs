using UnrealBuildTool;
using System.IO;
using System;

public class SMLEditor : ModuleRules
{
    public SMLEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        CppStandard = CppStandardVersion.Cpp20;
	    DefaultBuildSettings = BuildSettingsVersion.Latest;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = false;
               
        PublicDependencyModuleNames.AddRange(new[] {
            "SML",
            "FactoryGame",
            "UnrealEd",
            "BlueprintGraph",
            "GraphEditor",
            "EditorWidgets",
            "DesktopPlatform",
            "Kismet",
            "ToolWidgets",
            "InputCore",
            "Slate",
            "SlateCore", 
            "AssetDefinition",
            "ToolMenus",
            "EditorFramework",
        });
        
        PrivateDependencyModuleNames.AddRange(new[] {
	        "PropertyEditor",
	        "SubobjectDataInterface",
        });

        //SML transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Json"
        });
        
        //FactoryGame transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject",
            "Engine",
            "BlueprintGraph",
            "KismetCompiler",
            "SlateCore", "Slate",
            "Projects"
        });
    }
}