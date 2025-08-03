using UnrealBuildTool;

public class ReliableMessagingSteamP2P : ModuleRules
{
    public ReliableMessagingSteamP2P(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "ReliableMessaging", "SteamShared"
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
                "SteamSockets"
            }
        );
        
        AddEngineThirdPartyPrivateStaticDependencies(Target, "Steamworks");
    }
}