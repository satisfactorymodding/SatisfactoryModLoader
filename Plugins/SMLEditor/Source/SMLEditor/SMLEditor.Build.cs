using UnrealBuildTool;
using System.IO;
using System;

public class SMLEditor : ModuleRules
{
    public SMLEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {
            "SML",
            "FactoryGame",
            "UnrealEd",
        });
        bLegacyPublicIncludePaths = false;
        
        //SML transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Projects"
        });
        
        //FactoryGame transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject",
            "Engine",
            "BlueprintGraph",
            "KismetCompiler",
            "SlateCore", "Slate",
        });
        
        PrivateDependencyModuleNames.AddRange(new[] {
            "DesktopPlatform",
            "Kismet"
        });
    }
}