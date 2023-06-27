using UnrealBuildTool;
using System.IO;
using System;

public class SMLEditor : ModuleRules
{
    public SMLEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
               
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