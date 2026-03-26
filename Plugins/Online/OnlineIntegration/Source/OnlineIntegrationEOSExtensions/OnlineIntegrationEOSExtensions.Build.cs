using UnrealBuildTool;

public class OnlineIntegrationEOSExtensions : ModuleRules
{
    public OnlineIntegrationEOSExtensions(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp20;
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "Engine", "OnlineServicesEOS", "OnlineServicesEOS",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "OnlineIntegration",
                "OnlineServicesEOS",
                "OnlineServicesEOSGS",
                "CoreOnline",
                "EOSShared",
                "EOSSDK"
            }
        );
    }
}