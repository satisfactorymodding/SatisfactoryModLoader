using System;
using EpicGames.UHT.Utils;
using HarmonyLib;

namespace AccessTransformers.Hooking;

[HarmonyPatch("UhtCodeGenerator", "CodeGenerator")]
// ReSharper disable once UnusedType.Global
public static class HookCodeGenExporter
{
    // ReSharper disable once UnusedMember.Local
    private static bool Prefix(IUhtExportFactory factory)
    {
        Types.AccessTransformers.Load(factory.Session);
        return true;
    }
    
    // ReSharper disable once UnusedMember.Local
    private static void Postfix(IUhtExportFactory factory)
    {
        var unusedFriends = Types.AccessTransformers.FriendAccessTransformers.GetUnusedTransformers();
        foreach (var (transformer, pluginName) in unusedFriends)
        {
            factory.Session.AddMessage(UhtMessage.MakeMessage(UhtMessageType.Error, null, transformer.File,
                transformer.Line, $"Unused friend access transformer {transformer} requested by {pluginName}"));
        }
        var unusedAccessors = Types.AccessTransformers.AccessorAccessTransformers.GetUnusedTransformers();
        foreach (var (transformer, pluginName) in unusedAccessors)
        {
            factory.Session.AddMessage(UhtMessage.MakeMessage(UhtMessageType.Error, null, transformer.File,
                transformer.Line, $"Unused accessor access transformer {transformer} requested by {pluginName}"));
        }
    }
}