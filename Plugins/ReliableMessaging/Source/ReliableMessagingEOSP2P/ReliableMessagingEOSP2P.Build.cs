using UnrealBuildTool;

public class ReliableMessagingEOSP2P : ModuleRules
{
    public ReliableMessagingEOSP2P(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "CoreUObject", "ReliableMessaging",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "EOSSDK",
                "EOSShared",
                "Sockets",
                "SocketSubsystemEOS",
                "ReliableMessaging"
            }
        );
    }
}