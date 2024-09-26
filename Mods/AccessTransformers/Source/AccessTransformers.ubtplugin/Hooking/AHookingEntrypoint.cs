using System;
using System.IO;
using System.Reflection;
using EpicGames.UHT.Utils;
using HarmonyLib;

namespace AccessTransformers.Hooking;

[UnrealHeaderTool(InitMethod = "Init")]
// ReSharper disable once UnusedType.Global

// Requires A to be first in the order when loading types
public class AHookingEntrypoint
{
    // ReSharper disable once UnusedMember.Local
    private static void Init()
    {
        // UE only loads the main assembly and not any dependency dlls, and .net doesn't either
        AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
        Patch();
    }
    
    private static bool _hasAppliedPatches;

    private static void Patch()
    {
        // UHT can run multiple times in the same UBT process (for different targets for example)
        // and Harmony does not check whether a patch for the same ID has already been applied
        // resulting in the same patch being applied multiple times, causing duplicate code to be generated
        if (_hasAppliedPatches)
            return;

        Harmony harmony = new("AccessTransformers");
        harmony.PatchAll();
        _hasAppliedPatches = true;
    }

    private static Assembly? CurrentDomain_AssemblyResolve(object? sender, ResolveEventArgs args)
    {
        var runningAssembly = new FileInfo(Assembly.GetExecutingAssembly().Location);
        var localFile = new FileInfo(Path.Join(runningAssembly.Directory!.FullName, args.Name.Split(",")[0] + ".dll"));
        return UhtTables.LoadAssembly(localFile.FullName);
    }
}
