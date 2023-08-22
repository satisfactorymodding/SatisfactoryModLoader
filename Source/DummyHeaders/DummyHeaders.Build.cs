// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DummyHeaders : ModuleRules
{
    public DummyHeaders(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core", "CoreUObject", "Engine"
        });
    }
}
