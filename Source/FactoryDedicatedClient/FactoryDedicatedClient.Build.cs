using UnrealBuildTool;

public class FactoryDedicatedClient : ModuleRules
{
    public FactoryDedicatedClient(ReadOnlyTargetRules Target) : base(Target)
    {
	    CppStandard = CppStandardVersion.Cpp20;
	    DefaultBuildSettings = BuildSettingsVersion.Latest;

		if (/*Target.Platform != UnrealTargetPlatform.PS5 &&
			Target.Platform != UnrealTargetPlatform.XSX*/ true)
		{
			// We depend on using CURL directly to override certificate management and hostname resolution
			PrivateIncludePaths.Add($"{EngineDirectory}/Source/Runtime/Online/HTTP/Private");
			AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");

			PrivateDefinitions.Add("WITH_CURL=1");
			PrivateDefinitions.Add("WITH_CURL_XCURL=0");
		}
		else
		{
			PrivateDefinitions.Add("WITH_CURL=0");
			PrivateDefinitions.Add("WITH_CURL_XCURL=0");
		}
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "FactoryGame",
                "SSL",
                "OpenSSL",
                "HTTP",
                "UMG",
                "OnlineSubsystemUtils",
                "Json",
                "DeveloperSettings",
                "OnlineIntegration"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Sockets",
                "JsonUtilities"
            }
        );
    }
}
