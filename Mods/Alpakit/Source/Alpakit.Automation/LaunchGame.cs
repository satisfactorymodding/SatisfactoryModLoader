using System.Diagnostics;
using System.IO;
using AutomationTool;
using Microsoft.Extensions.Logging;

namespace Alpakit.Automation;

public class LaunchGame
{
    public enum LaunchType
    {
        Steam,
        SteamDS,
        EpicEA,
        EpicExp,
        EpicDS,
        EpicDSExp,
        Custom
    }
    
    private static string GetGameLaunchUrl(LaunchType LaunchType)
    {
        switch (LaunchType)
        {
            case LaunchType.Steam:
                return "steam://rungameid/526870";
            case LaunchType.SteamDS:
                return "steam://rungameid/1690800";
            case LaunchType.EpicEA:
                return "com.epicgames.launcher://apps/CrabEA?action=launch&silent=true";
            case LaunchType.EpicExp:
                return "com.epicgames.launcher://apps/CrabTest?action=launch&silent=true";
            case LaunchType.EpicDS:
                return "com.epicgames.launcher://apps/CrabDedicatedServer?action=launch&silent=true";
            case LaunchType.EpicDSExp:
                // No more nice names
                return "com.epicgames.launcher://apps/c509233193024c5f8124467d3aa36199?action=launch&silent=true";
            default:
                throw new AutomationException("Invalid Launch Type {0}", LaunchType);
        }
    }

    public static void Launch(LaunchType Type, string? CustomLaunchPath, string? CustomLaunchArgs, ILogger logger)
    {
        if (Type == LaunchType.Custom)
        {
            if (CustomLaunchPath == null)
                throw new AutomationException("Custom Launch Type requested, but no program to launch was specified");

            ProcessStartInfo processInfo = new()
            {
                FileName = CustomLaunchPath,
                Arguments = CustomLaunchArgs,
                UseShellExecute = true
            };

            logger.LogInformation($"Custom Launch starting process: `{processInfo.FileName}` with arguments `{processInfo.Arguments}`");
            Process.Start(processInfo);
            return;
        }

        Process.Start(new ProcessStartInfo(GetGameLaunchUrl(Type)) { UseShellExecute = true });
    }
}
