using UnrealBuildTool;

public class OnlineIntegrationPostSplashScreen : ModuleRules
{
    public OnlineIntegrationPostSplashScreen(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
	        [
		        "Core"
	        ]
        );
        // Note:
        // OnlineServicesEOSGS is intentionally NOT listed as a dependency here.
        // The module is loaded dynamically at runtime to preserve the ability
        // to conditionally enable or disable EOS based on configuration without
        // hard-linking this module to a specific OnlineServices implementation.
        
        PrivateDependencyModuleNames.AddRange(
	        [
		        "CoreUObject",
                "Engine",
                "OnlineServicesInterface", 
		        "EOSShared"
	        ]
        );
        
    }
}