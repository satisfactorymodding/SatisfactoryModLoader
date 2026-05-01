using System.Collections.Generic;
using System.Reflection.Emit;
using System.Text;
using EpicGames.UHT.Types;
using HarmonyLib;

namespace AccessTransformers.Hooking;

[HarmonyPatch("UhtHeaderCodeGeneratorHFile", "AppendScriptStruct")]
// ReSharper disable once UnusedType.Global
public static class HookStructGeneration
{
    // ReSharper disable once UnusedMember.Local
    private static IEnumerable<CodeInstruction> Transpiler(IEnumerable<CodeInstruction> instructions)
    {
        var codes = new List<CodeInstruction>(instructions);

        var addedCodes = new[] {
            new CodeInstruction(OpCodes.Ldarg_1),
            new CodeInstruction(OpCodes.Ldarg_2),
            CodeInstruction.Call((StringBuilder builder, UhtScriptStruct scriptStruct) => InsertCodeForStruct(builder, scriptStruct))
        };
        
        var inclassMacroIndex = codes.FindIndex((instruction) => instruction.LoadsConstant("\tfriend struct Z_Construct_UScriptStruct_"));
        codes.InsertRange(inclassMacroIndex - 1, addedCodes);

        return codes;
    }

    private static string _newLineSeparator = " \\\r\n";
    
    private static void InsertCodeForStruct(StringBuilder builder, UhtScriptStruct scriptStruct)
    {
        var friends = Types.AccessTransformers.FriendAccessTransformers.GetFor(scriptStruct.EngineName, scriptStruct.EngineNamePrefix + scriptStruct.EngineName);
        var accessors = Types.AccessTransformers.AccessorAccessTransformers.GetFor(scriptStruct.EngineName, scriptStruct.EngineNamePrefix + scriptStruct.EngineName);

        if (friends.Count > 0)
        {
            foreach (var friend in friends)
            {
                var implementations = friend.GetImplementation(scriptStruct);
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
                var implementations = accessor.GetImplementation(scriptStruct);
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
