using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection.Emit;
using System.Text;
using EpicGames.Core;
using EpicGames.UHT.Types;
using HarmonyLib;
using Microsoft.Extensions.Logging;

namespace AccessTransformers.Hooking;

[HarmonyPatch("UhtHeaderCodeGeneratorHFile", "AppendClass")]
// ReSharper disable once UnusedType.Global
public static class HookClassGeneration
{
    // ReSharper disable once UnusedMember.Local
    private static IEnumerable<CodeInstruction> Transpiler(IEnumerable<CodeInstruction> instructions)
    {
        var codes = new List<CodeInstruction>(instructions);

        var addedCodes = new[] {
            new CodeInstruction(OpCodes.Ldarg_1),
            new CodeInstruction(OpCodes.Ldarg_2),
            CodeInstruction.Call((StringBuilder builder, UhtClass @class) => InsertCodeForClass(builder, @class))
        };
        
        var inclassMacroIndex = codes.FindIndex((instruction) => instruction.LoadsConstant("INCLASS"));
        var inclassMacroIndexEnd = codes.FindIndex(inclassMacroIndex, (instruction) => instruction.opcode == OpCodes.Leave_S);
        codes.InsertRange(inclassMacroIndexEnd, addedCodes);
        
        var inclassNoPureDeclsMacroIndex = codes.FindIndex((instruction) => instruction.LoadsConstant("INCLASS_NO_PURE_DECLS"));
        var inclassNoPureDeclsMacroIndexEnd = codes.FindIndex(inclassNoPureDeclsMacroIndex, (instruction) => instruction.opcode == OpCodes.Leave_S);
        codes.InsertRange(inclassNoPureDeclsMacroIndexEnd, addedCodes);

        return codes;
    }

    private static string _newLineSeparator = " \\\r\n";
    
    private static void InsertCodeForClass(StringBuilder builder, UhtClass @class)
    {
        var friends = Types.AccessTransformers.FriendAccessTransformers.GetFor(@class.EngineName, @class.EngineNamePrefix + @class.EngineName);
        var accessors = Types.AccessTransformers.AccessorAccessTransformers.GetFor(@class.EngineName, @class.EngineNamePrefix + @class.EngineName);

        if (friends.Count > 0)
        {
            foreach (var friend in friends)
            {
                var implementations = friend.GetImplementation(@class);
                if (implementations == null)
                    continue;
                foreach (var implementation in implementations)
                {
                    builder.Append('\t').Append(implementation).Append(_newLineSeparator);
                }
            }
        }

        if (accessors.Count > 0)
        {
            builder.Append("public:").Append(_newLineSeparator);
            foreach (var accessor in accessors)
            {
                var implementations = accessor.GetImplementation(@class);
                if (implementations == null)
                    continue;
                foreach (var implementation in implementations)
                {
                    builder.Append('\t').Append(implementation).Append(_newLineSeparator);
                }
            }
        }
        
        friends.ForEach(Types.AccessTransformers.FriendAccessTransformers.MarkUsed);
        accessors.ForEach(Types.AccessTransformers.AccessorAccessTransformers.MarkUsed);
    }
}