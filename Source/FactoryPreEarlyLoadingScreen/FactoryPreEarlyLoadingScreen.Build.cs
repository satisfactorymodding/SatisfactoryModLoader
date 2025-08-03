using UnrealBuildTool;

public class FactoryPreEarlyLoadingScreen : ModuleRules
{
    public FactoryPreEarlyLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
    {
	    CppStandard = CppStandardVersion.Cpp20;
	    DefaultBuildSettings = BuildSettingsVersion.Latest;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "PreLoadScreen",
                "ApplicationCore"
            }
        );
    }
}